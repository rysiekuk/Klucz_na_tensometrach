# Morse Paddle Trainer (Arduino)

Simple Arduino project for Morse key using pressure sensors (load cells).
The device measures the force applied to two paddles (DIT and DASH) and converts it to signals or audio output.

## Hardware

### Microcontroller

* Arduino Nano
  https://www.aliexpress.com/item/1665783181.html

### ADC Converters

* CS1237 24-bit ADC module ×2
  https://www.aliexpress.com/item/1005007150110287.html

### Sensors

* Load cell 300 g ×2
  https://www.aliexpress.com/item/1005011628599440.html

### Audio Output

* 3.5 mm Audio Jack
  https://www.aliexpress.com/item/1005005562420070.html

### Power Supply

* 18650 Lithium Battery Shield V8
  https://www.aliexpress.com/item/1005006252337213.html

## Features

* Measures force applied to Morse paddles
* Separate sensors for **DIT** and **DASH**
* 24-bit ADC for high precision measurement
* Adjustable thresholds
* Key output through 3.5 mm jack
* Battery powered (18650)

## Hardware Configuration

* Arduino Nano reads values from two CS1237 ADC modules
* Each ADC is connected to one load cell
* The system detects paddle pressure and generates Morse signals

## Possible Improvements

* EEPROM configuration storage
* Adjustable sensitivity
* USB configuration interface


## Author
M0RPA
