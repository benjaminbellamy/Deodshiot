# Deodshiot
_A Light Triggered Air Freshener_

This project was heavily inspired by [James Callaghan](https://github.com/jcallaghan)’s project: [Can you IoT an Airwick air freshener?](https://jcallaghan.com/2020/03/can-you-iot-an-airwick-air-freshener/)

The default behaviour of this device before you tweak it is to spray once every 15mn. This is wasteful and inconvenient.

I wanted to have the Air Freshener triggered every time I leave the restroom, when I switch the light off.
Depending on the sliding switch position, it will spray more or less often:
* ❚ : Off
* ● : Will spray once every **30mn** at most, if light was on at during least **5mn**.
* ● ● : Will spray once every **5mn** at most, if light was on at during least **3mn**.
* ● ● ● : Will spray once every **30s** at most, if light was on at during least **5s**.

I also wanted everything to fit in and to use the default AA batteries.

There are two versions:
* Deodshiot, using a 3V3 [Arduino Pro Mini](https://store.arduino.cc/arduino-pro-mini)
* DeodshiotIOT, using a [NodeMCU](http://www.nodemcu.com/) / ESP-8266 / [LOLIN (WEMOS) D1 mini](https://docs.wemos.cc/en/latest/d1/d1_mini.html) connecting to a [ThingsBoard](https://thingsboard.io/) server, so that you may monitor how long you are spending there and make statistics out of it…

_Todo: Test with a MQ-136 gas sensor if the Air Freshener can be triggered when it smells bad._

## Parts List
You will need:
* 2 pieces of bakelite testing plate (0.1in/2.54mm, 6x8 and 6x15)
* 2 resistors ~1KΩ
* 1 photoresistor
* 1 PNP transistor (PN2222 or equivalent)
* 1 diode (1N4007 or equivalent)
* 1 relay (JRC-23F or equivalent)
* 1 microcontroller (Arduino Pro Mini or equivalent / LOLIN WEMOS D1 mini or equivalent for the IOT version)

## The build
There is nothing complicated as long as you are cautious.

Have a close look at the schematics and pictures below to see how things work.

* Remove the top cover.
* Remove the 4 screws (you need a long - 4cm long minimum - Philips ⨁ screwdriver).
* Remove the block out of Air Freshener.
* Push gently the part with the motor away from the rest (so that the axes are out), then up.
* Remove the circuit board.
* Un-solder the sliding switch and the two battery connectors. (NB: You need to bend the sliding swicth pins so that they can fit into the 0.1in/2.54mm testing plate.)
* Cut the 2 bakelite testing plates, solder all the components.
* Drill one hole so that the wires can go through.
* Solder the wires to the bakelite testing plates, microcontroller an motor. Double check that the motor turns the right way.
* Put everything back in place.
* Drill one hole in the top cover so that the photoresitor can see the ambiant light.

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
