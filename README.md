# DuinoCoin_I2C
DuinoCoin mining using the I2C Protocol, with Arduino and ESP8266 / ESP32 boards.

Link Official: https://github.com/revoxhere/duino-coin


## Pinouts

Connect the pins of the ESP8266 or ESP32 on the Arduino (Uno/Nano) like the table/images below.

|| ESP8266 | ESP32 | Arduino |
|:-:| :----: | :----: | :-----: |
||3.3V | 3.3V | 5V |
||GND | GND | GND |
|`SCL`|D1 (GPIO5) | GPIO22 | A5 |
|`SDA`|D2 (GPIO4) | GPIO21 | A4 |


### ESP8266 with one Arduino Nano.

<img src="https://raw.githubusercontent.com/ricaun/DuinoCoinI2C/main/Resources/Fritzing/DuinoCoinI2C/DuinoCoinI2C_1xNano.png" alt="DuinoCoinI2C" width="50%">


### ESP8266 with three Arduino Nano

<img src="https://raw.githubusercontent.com/ricaun/DuinoCoinI2C/main/Resources/Fritzing/DuinoCoinI2C/DuinoCoinI2C_3xNano.png" alt="DuinoCoinI2C" width="50%">


### ESP8266 with three Arduino UNO

<img src="https://raw.githubusercontent.com/ricaun/DuinoCoinI2C/main/Resources/Fritzing/DuinoCoinI2C/DuinoCoinI2C.png" alt="DuinoCoinI2C" width="50%">

# Library Dependency

* [DuinoCoin](https://github.com/ricaun/arduino-DuinoCoin) (Handle the `Ducos1a` hash work)
* [ArduinoUniqueID](https://github.com/ricaun/ArduinoUniqueID) (Handle the chip ID)
* [StreamJoin](https://github.com/ricaun/StreamJoin) (StreamString for AVR)
