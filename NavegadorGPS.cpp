#include "NavegadorGPS.h"

const int PantallaFT::pantalla_dim_x=800;
const int PantallaFT::pantalla_dim_y=480;

DispositivoGPS::DispositivoGPS(SerialUART& uart, uint32_t bps): suart(uart), baudrate(bps)
{

}

MapaGPS::MapaGPS()
{
}

MapaGPS::MapaGPS(char *nombrebase, double minx, double miny, 
                         double maxx, double maxy, int mapapxancho, int mapapxalto, 
                         int nceldasx, int nceldasy){
  mapa_nombre_base = nombrebase;
  mapa_geo_min_x = minx;
  mapa_geo_min_y = miny;
  mapa_geo_max_x = maxx;
  mapa_geo_max_y = maxy;
  mapa_px_ancho = mapapxancho;
  mapa_px_alto = mapapxalto;
  mapa_num_celdas_ancho = nceldasx;
  mapa_num_celdas_alto = nceldasy;
}

void NavegadorGPS::localizarCelda(int& fila, int& col){
  
}

