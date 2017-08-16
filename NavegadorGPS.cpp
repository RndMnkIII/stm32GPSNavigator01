#include "NavegadorGPS.h"
DispositivoGPS::DispositivoGPS(SerialUART& uart, uint32_t bps): suart(uart), baudrate(bps)
{

}

MapaGPS::MapaGPS()
{
}

MapaGPS::MapaGPS(char *nombrebase, double origenx, double origeny, 
                         double limitex, double limitey, int mapapxancho, int mapapxalto, 
                         int nceldasx, int nceldasy){
  mapa_nombre_base = nombrebase;
  mapa_geo_origen_x = origenx;
  mapa_geo_origen_y = origeny;
  mapa_geo_limite_x = limitex;
  mapa_geo_limite_y = limitey;
  mapa_px_ancho = mapapxancho;
  mapa_px_alto = mapapxalto;
  mapa_num_celdas_ancho = nceldasx;
  mapa_num_celdas_alto = nceldasy;
}

