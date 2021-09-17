#include <stdio.h>
#include <string.h>

const char* queonda(char* str) {
	int init_size = strlen(str);
	char delim[] = " ";

	char *ptr = strtok(str, delim);

	while(ptr != NULL)
	{
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}

	/* This loop will show that there are zeroes in the str after tokenizing */
	for (int i = 0; i < init_size; i++)
	{
		printf("%d ", str[i]); /* Convert the character to integer, in this case
							   the character's ASCII equivalent */
	}
	printf("\n");
  
}

int main()
{
  printf("HOLAA");
  const char* mm = queonda("strtok needs to be called several times to split a string");
	return 0;
}
