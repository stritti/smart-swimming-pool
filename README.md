# Smart Swimming-Pool

Pool automation for smarter control of the swimming pool :)

> *Status:* Project is sucessfully live since May 2018.

# Hardware

This is my private project to control and monitor my pool using following:

* _ESP32_ to control pumps of water and solar heating
* _ESP8266_ fo show current temeratures on LCD monitor
* _Raspberry Pi_ hosting MQTT and OpenHAB for Smart Home automation

# Components

Th project is plitted in components:

* [Pool-Controller](Pool-Controller)
* [Pool-Monitor](Pool-Monitor)
* [OpenHAB](OpenHAB) Configuration

# Development

## Platform.io IDE

TBD

## Drivers
Install the NodeMCU drivers for your respective operating system if they are not autodetected: https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx

# Open Issues
- [x] Remote control of pumps
- [x] Rule (openHAB) to control status of pumps
- [x] Remote control to switch between modes: Automatic, Manual, Off
- [ ] Move control system from openHAB to ESP
- [ ] replace 433MHz switches by relais
- [ ] Secure MQTT Communication
- [ ] Use weather forcast within rules
- [ ] Measurement of water quality (pH and Cl)

# License

[LICENSE](LICENSE)

---

My Smart Home Blog: https://medium.com/diy-my-smart-home 


# Other Smart Swimmingpool Projects

See in [Wiki](https://github.com/stritti/smart-swimming-pool/wiki/Resources).
