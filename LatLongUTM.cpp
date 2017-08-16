//Codigo adaptado por RndMnkIII. 10/08/2017:
//Código original:
// LatLong-UTM.c++
// Conversions:  LatLong to UTM;  and UTM to LatLong;
// by Eugene Reimer, ereimer@shaw.ca, 2002-December;
// with LLtoUTM & UTMtoLL routines based on those by Chuck Gantz chuck.gantz@globalstar.com;
// with ellipsoid & datum constants from Peter H Dana website (http://www.colorado.edu/geography/gcraft/notes/datum/edlist.html);
// Copyright © 1995,2002,2010 Eugene Reimer, Peter Dana, Chuck Gantz.  Released under the GPL;  see http://www.gnu.org/licenses/gpl.html
// (Peter Dana's non-commercial clause precludes using the LGPL)
#include "LatLongUTM.h"

Ellipsoid::Ellipsoid(){}
Ellipsoid::Ellipsoid(int id, char* name, double radius, double fr){
    Name=name;  EquatorialRadius=radius;  eccSquared=2/fr-1/(fr*fr);
}
  
Datum::Datum(){}
Datum::Datum(int id, char* name, int eid, double dx, double dy, double dz){
  Name=name;  eId=eid;  dX=dx;  dY=dy;  dZ=dz;
}

void DatumConvert(int dIn, double LatIn, double LongIn, double HtIn, int dTo,  double& LatTo, double& LongTo, double& HtTo){
   // converts LatLongHt in datum dIn, to LatLongHt in datum dTo;  2002dec: by Eugene Reimer, from PeterDana equations.
   // Lat and Long params are in degrees;  North latitudes and East longitudes are positive;  Height is in meters;
   // ==This approach to Datum-conversion is a waste of time;  to get acceptable accuracy a large table is needed -- see NADCON, NTv2...
   double a,ee,N,X,Y,Z,EE,p,b,t;
   
   //--transform to XYZ, using the "In" ellipsoid
   //LongIn += 180;
   a = ellip[datum[dIn].eId].EquatorialRadius;
   ee= ellip[datum[dIn].eId].eccSquared;
   N = a / sqrt(1 - ee*sin(LatIn*deg2rad)*sin(LatIn*deg2rad));
   X = (N + HtIn) * cos(LatIn*deg2rad) * cos(LongIn*deg2rad);
   Y = (N + HtIn) * cos(LatIn*deg2rad) * sin(LongIn*deg2rad);
   Z = (N*(1-ee) + HtIn) * sin(LatIn*deg2rad);

   //--apply delta-terms dX dY dZ
   //cout<<"\tX:" <<X <<" Y:" <<Y <<" Z:" <<Z;    //==DEBUG
   X+= datum[dIn].dX - datum[dTo].dX;
   Y+= datum[dIn].dY - datum[dTo].dY;
   Z+= datum[dIn].dZ - datum[dTo].dZ;
   //cout<<"\tX:" <<X <<" Y:" <<Y <<" Z:" <<Z;    //==DEBUG
   
   //--transform back to LatLongHeight, using the "To" ellipsoid
   a = ellip[datum[dTo].eId].EquatorialRadius;
   ee= ellip[datum[dTo].eId].eccSquared;
   EE= ee/(1-ee);
   p = sqrt(X*X + Y*Y);
   b = a*sqrt(1-ee);
   t = atan(Z*a/(p*b));
   LatTo = atan((Z+EE*b*sin(t)*sin(t)*sin(t)) / (p-ee*a*cos(t)*cos(t)*cos(t)));
   LongTo= atan(Y/X);
   HtTo  = p/cos(LatTo) - a/sqrt(1-ee*sin(LatTo)*sin(LatTo));
   LatTo  *= rad2deg;
   LongTo *= rad2deg;  LongTo -= 180;
}


void LLtoUTM(int eId, double Lat, double Long,  double& Northing, double& Easting, int& Zone){
   // converts LatLong to UTM coords;  3/22/95: by ChuckGantz chuck.gantz@globalstar.com, from USGS Bulletin 1532.
   // Lat and Long are in degrees;  North latitudes and East Longitudes are positive.
   double a = ellip[eId].EquatorialRadius;
   double ee= ellip[eId].eccSquared;
   Long -= int((Long+180)/360)*360;     //ensure longitude within -180.00..179.9
   double N, T, C, A, M;
   double LatRad = Lat*deg2rad;
   double LongRad = Long*deg2rad;

   Zone = int((Long + 186)/6);
   if( Lat >= 56.0 && Lat < 64.0 && Long >= 3.0 && Long < 12.0 )  Zone = 32;
   if( Lat >= 72.0 && Lat < 84.0 ){     //Special zones for Svalbard
      if(      Long >= 0.0  && Long <  9.0 )  Zone = 31;
      else if( Long >= 9.0  && Long < 21.0 )  Zone = 33;
      else if( Long >= 21.0 && Long < 33.0 )  Zone = 35;
      else if( Long >= 33.0 && Long < 42.0 )  Zone = 37;
   }
   double LongOrigin = Zone*6 - 183;      //origin in middle of zone
   double LongOriginRad = LongOrigin * deg2rad;

   double EE = ee/(1-ee);

   N = a/sqrt(1-ee*sin(LatRad)*sin(LatRad));
   T = tan(LatRad)*tan(LatRad);
   C = EE*cos(LatRad)*cos(LatRad);
   A = cos(LatRad)*(LongRad-LongOriginRad);

   M= a*((1 - ee/4    - 3*ee*ee/64 - 5*ee*ee*ee/256  ) *LatRad 
      - (3*ee/8 + 3*ee*ee/32 + 45*ee*ee*ee/1024) *sin(2*LatRad)
      + (15*ee*ee/256 + 45*ee*ee*ee/1024    ) *sin(4*LatRad)
      - (35*ee*ee*ee/3072       ) *sin(6*LatRad));
   
   Easting = k0*N*(A+(1-T+C)*A*A*A/6+(5-18*T+T*T+72*C-58*EE)*A*A*A*A*A/120) + 500000.0;

   Northing = k0*(M+N*tan(LatRad)*(A*A/2+(5-T+9*C+4*C*C)*A*A*A*A/24
          + (61-58*T+T*T+600*C-330*EE)*A*A*A*A*A*A/720));
}


void UTMtoLL(int eId, double Northing, double Easting, int Zone,  double& Lat, double& Long){
   // converts UTM coords to LatLong;  3/22/95: by ChuckGantz chuck.gantz@globalstar.com, from USGS Bulletin 1532.
   // Lat and Long are in degrees;  North latitudes and East Longitudes are positive.
   double a = ellip[eId].EquatorialRadius;
   double ee = ellip[eId].eccSquared;
   double EE = ee/(1-ee);
   double e1 = (1-sqrt(1-ee))/(1+sqrt(1-ee));
   double N1, T1, C1, R1, D, M, mu, phi1Rad;
   double x = Easting - 500000.0;     //remove 500,000 meter offset for longitude
   double y = Northing;
   double LongOrigin = Zone*6 - 183;      //origin in middle of zone

   M = y / k0;
   mu = M/(a*(1-ee/4-3*ee*ee/64-5*ee*ee*ee/256));

   phi1Rad = mu + (3*e1/2-27*e1*e1*e1/32) *sin(2*mu) 
    + (21*e1*e1/16-55*e1*e1*e1*e1/32) *sin(4*mu)
    + (151*e1*e1*e1/96) *sin(6*mu);
   N1 = a/sqrt(1-ee*sin(phi1Rad)*sin(phi1Rad));
   T1 = tan(phi1Rad)*tan(phi1Rad);
   C1 = EE*cos(phi1Rad)*cos(phi1Rad);
   R1 = a*(1-ee)/pow(1-ee*sin(phi1Rad)*sin(phi1Rad), 1.5);
   D = x/(N1*k0);

   Lat = phi1Rad - (N1*tan(phi1Rad)/R1)*(D*D/2-(5+3*T1+10*C1-4*C1*C1-9*EE)*D*D*D*D/24
       +(61+90*T1+298*C1+45*T1*T1-252*EE-3*C1*C1)*D*D*D*D*D*D/720);
   Lat *= rad2deg;
   Long = (D-(1+2*T1+C1)*D*D*D/6+(5-2*C1+28*T1-3*C1*C1+8*EE+24*T1*T1)*D*D*D*D*D/120) / cos(phi1Rad);
   Long = LongOrigin + Long*rad2deg;
}





