# stm32GPSNavigator01 
# ATENCIÓN/WARNING: CODIGO NO FUNCIONAL TODAVIA/NON-FUNCTIONAL CODE YET

## Implementación de un navegador GPS sencillo utilizando como hardware:
- STM32F407ZGT6 Dev Board (https://es.aliexpress.com/item/High-Quality-STM32F407ZGT6-Development-Board-ARM-M4-STM32F4-Board-Compatibility-Multiple-Extension/32761236140.html?spm=a2g0s.9042311.0.0.9NfgLa)
![stm32f407zgt6](images/stm32f407zgt6.jpg?raw=true "STM32F407ZGT6"))

- Programador/Depurador ST-LINK/V2 [ST-LINK/V2](http://www.st.com/en/development-tools/st-link-v2.html)
![STLINKV2](images/stlinkv2.jpg?raw=true "ST-LINK/V2")

- Pantalla FT811CB con chip FTDI EVE2(http://www.hotmcu.com/5-graphical-lcd-capacitive-touch-screen-800x480-spi-ft811-p-301.html?cPath=6_16)
![FT811CB](images/ft811cb.jpg?raw=true "FT811 Eve2")

- GPS Serial \(Modified HOLUX M1000 Bluetooth GPS\) 
![Modified HOLUX M1000 Bluetooth GPS](images/holuxM1000.jpg?raw=true "Holux M1000")

## Utiliza las siguientes librerias y secciones de código de terceros:
* Core STM32GENERIC (https://github.com/danieleff/STM32GENERIC)
* GD23STM32_F103x,  FT81x Team (https://github.com/lightcalamar/GD23STM32_F103x)
* NMEA Library: [http://nmea.sourceforge.net/](http://nmea.sourceforge.net/) -> (https://github.com/RndMnkIII/stm32_nmealib)
* Código de conversión de coordenadas geograficas a UTM y viceversa LatLong-UTM.c++ by Eugene Reimer, ereimer@shaw.ca, 2002-December

## Diagrama de Conexion:
![CONEXION](images/CONEXIONADO.png?raw=true "CONEXION")

Basado en el trabajo del equipo FT81X \(@ TFTLCDCyg, @lightcalamar and @RndMnkIII\). 2016-2017.