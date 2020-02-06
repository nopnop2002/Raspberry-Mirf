# Raspberry-Mirf
A port of the Mirf library to Raspberry Pi. The library provides basic control of the Nordic NRF24l01 RF Transceiver.

I updated [this](https://github.com/dingcheng/MirfPi).   
\* Change the file name of the device.   
\* Replaced SPI transfer function.   
\* Add example.   

# Environment
I tested on this environment:
```
$ uname -a
Linux raspberrypi 4.19.66+ #1253 Thu Aug 15 11:37:30 BST 2019 armv6l GNU/Linux
```

# Wirering

|nRF24L01||Raspberry|
|:-:|:-:|:-:|
|MISO|--|Pin#21(SPI MISO)|
|SCK|--|Pin#23(SPI SCLK)|
|MOSI|--|Pin#19(SPI MOSI)|
|CE|--|Pin#22(GPIO25)(*)|
|CSN|--|Pin#24(SPI CE0)(*)|
|GND|--|GND|
|VCC|--|3.3V|

\*You can change any pin.   
```
Mirf.cePin=25; // GPIO25
Mirf.csnPin=8; // GPIO8
```

# Library Install
```
git clone https://github.com/nopnop2002/Raspberry-Mirf
cd Raspberry-Mirf
make
sudo make install
```

# Example Build
```
make example
```

# Example 
```
sudo ./transmitter

or 

sudo ./receiver
```

# Communicat with Arduino
I used this library on Arduino.   

- from Raspberry to Arduino:   
Raspberry side:transmitter   
Arduino side:[Receiver](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/tree/master/example/Peer-to-peer%20Communication/TimeTest/Receive)

- from Arduino to Raspberry:   
Raspberry side:receiver   
Arduino side:[Emitter](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/tree/master/example/Peer-to-peer%20Communication/TimeTest/Emitter)

# Important point
When changing the settings of the nRF24L01, it is necessary to power cycle the nRF24L01 before executing.   
Because nRF24L01 remembers the previous setting.   
