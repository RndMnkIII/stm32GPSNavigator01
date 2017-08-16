//NavegadorGPS.h
//By RndMnkIII. 14/08/2017
#ifndef RNDMNKIII_NAVEGADOR_GPS_H
#define RNDMNKIII_NAVEGADOR_GPS_H

#include <SerialUART.h>

//asegurarse de que las coordenadas gps están dentro del mapa
//double gps_posicion_geo_x; //en grados decimales ggg.gggggg
//double gps_posicion_geo_y; //en grados decimales gg.gggggg

//bool comprobarPosGPS()
//{
//  if(gps_posicion_geo_x >= mapa_geo_origen_x &&
//    gps_posicion_geo_x <= mapa_geo_limite_x &&
//    gps_posicion_geo_y >= mapa_geo_origen_y &&
//    gps_posicion_geo_y <= mapa_geo_limite_y)
//  {
//     return true; 
//  }
//  else
//  {
//    return false;
//  }
//}


class MapaGPS{
  private:
    char* mapa_nombre_base; //plantilla de nombre, por ejemplo: "CIFU_Z17_x-y.jpg", x,y -> 0-99       
    int mapa_px_ancho;
    int mapa_px_alto;
    int mapa_num_celdas_ancho;
    int mapa_num_celdas_alto;
    double mapa_geo_ancho;
    double mapa_geo_alto;
    double mapa_geo_origen_x;
    double mapa_geo_origen_y;
    double mapa_geo_limite_x;
    double mapa_geo_limite_y;
  public:
    MapaGPS();
    MapaGPS(char *nombrebase, double origenx, double origeny, 
                         double limitex, double limitey, int mapapxancho, int mapapxalto, 
                         int nceldasx, int nceldasy);
};

class CeldaGPS{
  
};

class PantallaFT{
  
};

class DispositivoGPS{
  private:
    SerialUART& suart;
    uint32_t baudrate;
    double gps_posicion_geo_x; //en grados decimales ggg.gggggg
    double gps_posicion_geo_y; //en grados decimales gg.gggggg
    int gps_posicion_px_x;
    int gps_posicion_px_y;
    double gps_orientacion_rad;
    double gps_orientacion_grad;
    double gps_posicion_altura;
    double gps_velocidad;
  public:
    DispositivoGPS(SerialUART& uart, uint32_t bps);
    
    double getLon();
    double getLat();
};

class NavegadorGPS{
  private:
    MapaGPS mapa;
    //SerialUART& suart)
    
    
};
//mapa


//celda
//char *celda_nombre_archivo;
//int celda_px_ancho;
//int celda_px_alto;
//double celda_geo_ancho;
//double celda_geo_alto;
//void inicializa_celda(argumentos);



//pantallaFT
//const int pantallaFT_px_ancho=800;
//const int pantallaFT_px_alto=480;
//const int pantallaFT_mem_num_celdas_ancho=4
//const int pantallaFT_mem_num_celdas_alto=3
//void inicializa_pantallaFT(argumentos);

#endif
