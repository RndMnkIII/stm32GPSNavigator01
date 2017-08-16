# stm32GPSNavigator01

Implementación de un navegador simple utilizando como hardware:
- STM32F407ZGT6 Dev Board (https://es.aliexpress.com/item/High-Quality-STM32F407ZGT6-Development-Board-ARM-M4-STM32F4-Board-Compatibility-Multiple-Extension/32761236140.html?spm=a2g0s.9042311.0.0.9NfgLa)
(images/stm32f407zgt6.jpg?raw=true "STM32F407ZGT6"))
- Pantalla FT811CB con chip FTDI EVE2(http://www.hotmcu.com/5-graphical-lcd-capacitive-touch-screen-800x480-spi-ft811-p-301.html?cPath=6_16)
(images/ft811cb.jpg?raw=true "FT811 Eve2")
- GPS Serial [Modified HOLUX M1000 Bluetooth GPS](images/holuxM1000.jpg?raw=true "Holux M1000")

Utiliza las siguientes librerias y secciones de código de terceros:
* Core STM32GENERIC (https://github.com/danieleff/STM32GENERIC)
* NMEA Library: [http://nmea.sourceforge.net/](http://nmea.sourceforge.net/)
* Código de conversión de coordenadas geograficas a UTM y viceversa LatLong-UTM.c++ by Eugene Reimer, ereimer@shaw.ca, 2002-December
