//UtilidadesGPS.cpp
//By RndMnkIII. 10/08/2017
#include "UtilidadesGPS.h"

const double UtilidadesGPS::PI2 = 6.28318530717958647692;
 
double UtilidadesGPS::rad2grados(double radianes){
    return radianes * 360.0 / PI2;
}

