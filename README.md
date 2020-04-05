# Deodshiot
_A Light Triggered Air Freshener_

This project was heavily inspired by [James Callaghan](https://github.com/jcallaghan)’s project: [Can you IoT an Airwick air freshener?](https://jcallaghan.com/2020/03/can-you-iot-an-airwick-air-freshener/)

I wanted to have the Air Freshener triggered every time I leave the restroom, when I switch the light off.

I also wanted everything to fit in and to use the default AA batteries.

This is what this project does.

There are two versions:
* Deodshiot, using a 3V3 [Arduino Pro Mini](https://store.arduino.cc/arduino-pro-mini)
* DeodshiotIOT, using a [NodeMCU](http://www.nodemcu.com/) / ESP-8266 / [LOLIN (WEMOS) D1 mini](https://docs.wemos.cc/en/latest/d1/d1_mini.html) connecting to a [ThingsBoard](https://thingsboard.io/) server, so that you may monitor how long you are spending there…

Todo: Test with a MQ-136 gas sensor if the Air Freshener can be triggered when it smells bad.

## Parts List
You will need:
* 2 pieces of bakelite testing plates (6x8 and 6x15)
* 2 resistors ~1KΩ
* 1 photoresistor
* 1 PNP transistor (PN2222 or equivalent)
* 1 diode (1N4007 or equivalent)
* 1 relay (JRC-23F or equivalent)
* 1 microcontroller (Arduino Pro Mini or equivalent / LOLIN WEMOS D1 mini or equivalent for the IOT version)

## Schematics
Schematic is very classic.
* 1 digital output controls the motor. We use a transistor and a relay to avoid frying the microcontroller.
* 1 analog input reads value from the photoresistor.
* 2 digital inputs read value from the sliding switch (position ● / ● ● / ● ● ●). We use the embedded pullup resistors (INPUT_PULLUP).

### Arduino version
<img src="https://raw.githubusercontent.com/benjaminbellamy/Deodshiot/master/Images/Deodshiot_schem.svg?sanitize=true" width="100%">

### IOT version
<img src="https://raw.githubusercontent.com/benjaminbellamy/Deodshiot/master/Images/DeodshiotIOT_schem.svg?sanitize=true" width="100%">



## Bakelite testing plates

### First one
![Bakelite #2](https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot-1.png)
![Bakelite #2](https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot-2.png)
<img src="https://raw.githubusercontent.com/benjaminbellamy/Deodshiot/master/Images/Bakelite-1.svg?sanitize=true" width="100%">

### Second one
<img src="https://raw.githubusercontent.com/benjaminbellamy/Deodshiot/master/Images/Bakelite-2.svg?sanitize=true" width="100%">

## Project pictures
<img src="https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot_01.jpg" width="23%"> <img src="https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot_02.jpg" width="23%"> <img src="https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot_03.jpg" width="23%"> <img src="https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot_04.jpg" width="23%"> <img src="https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot_05.jpg" width="23%"> <img src="https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot_06.jpg" width="23%"> <img src="https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot_07.jpg" width="23%"> <img src="https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot_08a.jpg" width="23%"> <img src="https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot_08b.jpg" width="23%"> <img src="https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot_09.jpg" width="23%"> <img src="https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot_10.jpg" width="23%"> <img src="https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/Deodshiot_11.jpg" width="23%">

## Measurement readings
You may use Arduino Serial Plotter to check if everything is working as intended.
<img src="https://github.com/benjaminbellamy/Deodshiot/raw/master/Images/SerialPlotter.png" width="100%">
