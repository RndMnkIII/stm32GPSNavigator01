//Probando GPS NMEA conectado a la USART2 en la STM32F407ZGT6
//en los pines PA2 (TX), PA3 (RX).
//con la libreria nmealib

#include <nmea.h>
#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <SPI.h>
#include <GD23STM32.h>
#include "UtilidadesGPS.h"
#include "LatLongUTM.h"


String lineaEntrada; 
char recibido;
char lectura[255];
char cadena[255]; 
char cadena2[255]; 
int pos=0;
int it;
nmeaINFO info;
nmeaPARSER parser;
nmeaPOS dpos;
nmeaTIME fechahora;


void leercadena()
{
    while (SerialUART2.available() > 0) {
      recibido=SerialUART2.read();
      lineaEntrada += recibido;
      if(recibido == '\n')
      {
        strncpy(lectura, lineaEntrada.c_str(), sizeof(lectura));
        lectura[sizeof(lectura) - 1] = 0; //array de caracteres terminado en '\0'
        nmea_parse(&parser, lectura, (int)strlen(lectura), &info);
        nmea_info2pos(&info, &dpos);
        double N,E; //coordenadas UTM Norte (- negativo sur), Este (- negativo oeste)
        int Z; //Zona UTM
        LLtoUTM(eWGS84, UtilidadesGPS::rad2grados(dpos.lat), UtilidadesGPS::rad2grados(dpos.lon), N, E, Z); 
        
        sprintf(cadena, "[%03d] Lat:%f, Lon:%f, Alt:%4f, Vel:%4f, Sig:%d, Fix:%d",
            it++, UtilidadesGPS::rad2grados(dpos.lat), //ó info.lat que va en grados NDEG
                                                       //convertir a grados decimales con nmea_ndeg2degree(double val)   
                  UtilidadesGPS::rad2grados(dpos.lon), //ó tambien info.lon que va en grados NDEG
                                                       //convertir a grados decimales con nmea_ndeg2degree(double val) 
                  info.elv,
                  info.speed,
                  info.sig, info.fix);
        sprintf(cadena2, "UTM X:%f, Y:%f Zona:%d",E, N, Z);
        //Serial.println(lineaEntrada);
        //Serial.println(cadena);
        lineaEntrada = "";
        return;
      }
         //nmea_parser_destroy(&parser);
   }
}
 
void setup() {
    //Serial.begin(115200);
    SerialUART2.begin(38400);
    GD.begin();
    //Serial.begin(115200);
    delay(6000);
  
    nmea_zero_INFO(&info);
    nmea_parser_init(&parser);
}

void loop() {
  GD.ClearColorRGB(0);
  GD.Clear();
  leercadena();
  GD.ColorRGB(0x00,0xff,0x88);  GD.cmd_text(400, 200, 28, OPT_CENTER, lectura);
  GD.ColorRGB(0x00,0xff,0x88);  GD.cmd_text(400, 240, 29, OPT_CENTER, cadena);
  GD.ColorRGB(0x00,0xff,0x88);  GD.cmd_text(400, 290, 29, OPT_CENTER, cadena2);
  
  GD.swap();
}



