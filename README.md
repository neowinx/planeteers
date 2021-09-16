# Planeteers

This repository contains the firmware for sensors that sends Particulate Matter information to receiving nodes using LoRa for [AireLibre](https://airelib.re/)

It consists of two main parts:

- [Suchi](https://github.com/neowinx/planeteers/tree/main/suchi-firmware): The firmware for the sensors that sends the data
- [Ma-ti](https://github.com/neowinx/planeteers/tree/main/ma-ti-firmware): The firmware for the node that receives the data from __suchi__ and forwards it to [Linka](https://github.com/garyservin/linka-firmware)

## Motivation

I just recently find out about all the [ LoRa ](https://en.wikipedia.org/wiki/LoRa#LoRaWAN) stuff, and since it's relatively new to me (even though it has been around quite some years already)
I have been trying to devise a project to use it

Around this time, I stumble with the [AireLibre](https://airelib.re/) initiave, and since the project is revolving around 
ubiquitous sensors, the opportunitty of implementing a self sustainable sensor (solar charged, low power) using hobbiest 
level hardware was the answer I was looking for!

### Why two separate projects?

I know that probably there's no need to separate both roles (the sender and the receiver) in two projects, since we could've just manage those differences using precompiled macros

The reason for not doing that, is that we want a minimal codebase in order to have a small memory footprint for the nodes, and having to manage precompiled macros and the resulting
code from them will probably result in someone (mainly myself) making a regrettable mistake

Also, it looks cleaner to have those two things separated for people not very keen into coding but that wants to contribute to the project in a foreseeable future, so in the meantime
we will mantain these two projects until we see otherwise even if that means that some lines of code will be duplicated

### Why not LoRaWAN?

The first prototype for this project was indeed a LoRaWAN node in order to use the [ TTN infraestructure ](https://www.thethingsnetwork.org/)

But gateways are rather
scarse in [ Paraguay ](https://www.thethingsnetwork.org/community) (0 gateways actually in my city) so I began to construct one of those single channel gateways 
(or single channel relays.. or whatever they are called now...)
for testing purposes, only to find out that those are [ condemned by the TTN community ](https://www.thethingsnetwork.org/forum/t/the-future-of-single-channel-gateways/6590)
and that the [ V2 of the TTN will be shutdown this 1 of december 2021 ](https://www.thethingsnetwork.org/forum/t/the-things-network-v2-is-permanently-shutting-down-scheduled/50710)

Because of this, at the current date, TTN V2 is not registering new gateways anymore, only leaving me with the V3 option that only accepts official (proper) gateways from one of the
selected manufacturers or to [ buildin a proper one ](https://www.thethingsnetwork.org/docs/gateways/start/build/) myself.

All that just gives me the same headache you're probably having now, so I will only use LoRa for the moment since the application in this case scenario is rather
simple

Maybe in the future I will reevaluate to use LoRaWAN

Thank you for reading until this point, If I haven't lost you, let's proceed to the more interesting part of the project

## Installation

Reference for the firmware installation are in their corresponding projects:

- [Suchi](https://github.com/neowinx/planeteers/tree/main/suchi-firmware)
- [Ma-ti](https://github.com/neowinx/planeteers/tree/main/ma-ti-firmware)

## Good Luck!

[ neowinx ](https://github.com/neowinx)
