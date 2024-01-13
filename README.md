# Turntable firmware

A turntable built using a stepper motor and a NodeMCU(esp8266). Originally created to showcase some of my 3d prints

A simple demo can be found at https://www.tiktok.com/@stl.cats/video/7323672252963179782

## Setup

Ensure to setup the ESP8266 in Arduino IDE (a quick google search is probably the most up-to-date way), and to install WiFiManager library (https://github.com/tzapu/WiFiManager). From there, you can use this as any other Arduino project.

When code is pushed to the NodeMCU and it starts for the first time (or it cannot connect to the WiFi), it'll create a WiFi network called "turntable", connect to it and follow the captive WiFi instructions (or visit neverssl.com if it doesn't automatically appear) to setup the wifi network of your place. 

Once that's completed, you can visit the ip of the NodeMCU to control the turntable

## Circuit

### Materials

- NodeMCU(esp8266)
- ULN2003 driver module
- Stepper motor (used 28BYJ-48 5V)
- Female connectors (at least 6)
- USB Cable
- USB power source (1A or more)

### Connections

```
NodeMCU D5 --> IN1
NodeMCU D6 --> IN2
NodeMCU D7 --> IN3
NodeMCU D8 --> IN4

NodeMCU VIn --> + (ULN2003 driver)
NodeMCU GND --> - (ULN2003 driver)

ULN2003 driver --> stepper mottor

```
