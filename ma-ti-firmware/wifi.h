#include <FS.h>                   // This needs to be first, or it all crashes and burns...
#include <SPI.h>                  // Explicit #include of built-in SPI needed for platformio
#include <WiFiConnect.h>          // Allow configuring WiFi via captive portal
#include <time.h>                 // To get current time

#if defined (ARDUINO_ARCH_ESP32) || defined(ESP32)
#  include <HTTPClient.h>
#else
#	 error "Architecture unknown and not supported"
#endif

// HTTP Server
#define JSON_BUFFER 256
char http_data_template[] = "[{"
                            "\"sensor\": \"%s\","
                            "\"source\": \"%s\","
                            "\"description\": \"%s\","
                            "\"pm1dot0\": %s,"
                            "\"pm2dot5\": %s,"
                            "\"pm10\": %s,"
                            "\"longitude\": %d,"
                            "\"latitude\": %d,"
                            "\"recorded\": \"%s\""
                            "}]";

// General
uint32_t g_device_id;                    // Unique ID from ESP chip ID

int timezone = 0;
int dst = 0;
time_t now;
struct tm * timeinfo;

char recorded_template[] = "%d-%02d-%02dT%02d:%02d:%02d.000Z";
bool force_captive_portal = false;

// Start HTTP client
WiFiClient client;
HTTPClient http;

// WifiManager
WiFiConnect wc;
WiFiConnectParam api_key_param("api_key", "API Key", "", 33);
WiFiConnectParam latitude_param("latitude", "Latitude", "", 13);
WiFiConnectParam longitude_param("longitude", "Longitude", "", 13);
WiFiConnectParam sensor_param("sensor", "Sensor model", "PMS7003", 8);
WiFiConnectParam description_param("description", "Description", "", 21);
WiFiConnectParam api_url_param("api_url", "URL for the backend", "http://rald-dev.greenbeep.com/api/v1/measurements", 71);

// vars to store parameters
char api_key[33] = "";
char latitude[12] = "";
char longitude[12] = "";
char description[21] = "";
char api_url[71] = "";
char sensor[8] = "PMS7003";

// flag for saving data
bool shouldSaveConfig = false;

void configModeCallback(WiFiConnect *mWiFiConnect) {
  Serial.println("Entering Access Point");
}

/*
    Callback notifying us of the need to save config
*/
void saveConfigCallback () {
  shouldSaveConfig = true;
}

/*
  Connect to Wifi. Returns false if it can't connect.
*/
bool initWifi()
{
  // Get ESP's unique ID
# if defined (ARDUINO_ARCH_ESP32) || defined(ESP32)
  uint32_t chipId = 0;
  for(int i=0; i<17; i=i+8) {
	  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	}
  g_device_id = chipId;
# elif defined(ARDUINO_ARCH_ESP8266)
  g_device_id = ESP.getChipId();
  Serial.print("Device ID: ");
  Serial.println(g_device_id, HEX);
# else
# 	error "Architecture unknown and not supported"
# endif
  Serial.print("Device ID: ");
  Serial.println(g_device_id, HEX);

  // Let WiFi Manager handle connections
  wc.setDebug(true);

  /* Set our callbacks */
  wc.setAPCallback(configModeCallback);

  // Set how many connection attempts before we fail and go to captive portal mode
  wc.setRetryAttempts(5);

  // How long to wait in captive portal mode before we try to reconnect
  wc.setAPModeTimeoutMins(5);

  // Set Access Point name for captive portal mode
  char ap_name[13];
  sprintf(ap_name, "linka-%x", g_device_id);
  wc.setAPName(ap_name);

  //set config save notify callback
  wc.setSaveConfigCallback(saveConfigCallback);

  Serial.println("Configuring wc parameters...");
  // Configure custom parameters
  wc.addParameter(&api_key_param);
  wc.addParameter(&latitude_param);
  wc.addParameter(&longitude_param);
  wc.addParameter(&sensor_param);
  wc.addParameter(&description_param);
  wc.addParameter(&api_url_param);

  //wc.resetSettings(); //helper to remove the stored wifi connection, comment out after first upload and re upload

  /*
     AP_NONE = Continue executing code
     AP_LOOP = Trap in a continuous loop - Device is useless
     AP_RESET = Restart the chip
     AP_WAIT  = Trap in a continuous loop with captive portal until we have a working WiFi connection
  */
  if (!wc.autoConnect() || force_captive_portal) { // try to connect to wifi
    Serial.println("Starting configuration portal...");
    /* We could also use button etc. to trigger the portal on demand within main loop */
    wc.startConfigurationPortal(AP_WAIT); //if not connected show the configuration portal
  }

  strcpy(api_key, api_key_param.getValue());
  strcpy(latitude, latitude_param.getValue());
  strcpy(longitude, longitude_param.getValue());
  strcpy(sensor, sensor_param.getValue());
  strcpy(description, description_param.getValue());
  strcpy(api_url, api_url_param.getValue());

  if (strcmp(api_key, "") == 0) {
    Serial.println("Stored parameters are empty, reset the parameters");
    wc.startConfigurationPortal(AP_WAIT);
  }

  //TODO: see if this next part for ntp config can go somewhere else
  // Configure ntp client
  configTime(timezone * 3600, dst * 3600, "pool.ntp.org", "time.nist.gov");

  time(&now);
  timeinfo = localtime(&now);
  while (timeinfo->tm_year == 70) {
    delay(500);
    time(&now);
    timeinfo = localtime(&now);
  }

  return true;
}

/*
  Report the latest values to HTTP Server
*/
void reportToHttp(String g_pm1p0_sp_value, String g_pm2p5_sp_value, String g_pm10p0_sp_value)
{
  Serial.println("Reporting to http ");
  Serial.print(g_pm1p0_sp_value + "  ");
  Serial.print(g_pm2p5_sp_value + "  ");
  Serial.println(g_pm10p0_sp_value);
  char measurements[256];
  char recorded[27];
  char source[10];

  Serial.println("generating recorded template: ");
  sprintf(recorded,
          recorded_template,
          timeinfo->tm_year + 1900,
          timeinfo->tm_mon + 1,
          timeinfo->tm_mday,
          timeinfo->tm_hour,
          timeinfo->tm_min,
          timeinfo->tm_sec);
  Serial.println(recorded);
  Serial.print("Printing source: ");
  sprintf(source, "%x", g_device_id);
  Serial.println(source);
  Serial.printf("generating measurements: %s : %s : %s",
          g_pm1p0_sp_value,
          g_pm2p5_sp_value,
          g_pm10p0_sp_value);
  sprintf(measurements,
          http_data_template,
          sensor,
          source,
          description,
          g_pm1p0_sp_value,
          g_pm2p5_sp_value,
          g_pm10p0_sp_value,
          longitude,
          latitude,
          recorded);

  Serial.println(measurements);

  Serial.print("connecting to ");
  Serial.println(api_url);
  if (http.begin(api_url)) {

    // Add headers
    http.addHeader("x-api-key", api_key);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(measurements);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been sent and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
  else {
    Serial.printf("[HTTP] Unable to connect");
  }
}
