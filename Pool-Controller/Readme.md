# Pool Controller

## BOM / Hardware

* ESP32 Controller
* Temperature Sensor Pool (DS18B20)
* Temperature Sensor Solar (DS18B20)
* 433MHz HC-12 Sender
* 433MHz-Plug Switches for Solar- and Pool-Pump

## Configuration

PIN Usage:
* PIN_DS_SOLAR = 16; // Temp Solar
* PIN_DS_POOL  = 17; // Temp Pool
* PIN_RSSWITCH = 18; // für 433MHz Sender

## Breadboard

<img src="./doc/Pool-Control_Steckplatine.png" />


Source (Fritzing): [./doc/Pool-Control.fzz](./doc/Pool-Control.fzz)
