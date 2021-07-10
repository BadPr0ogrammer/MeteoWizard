/******************************************************************************
 *  COPYRIGHT   :       Copyright 2000, EUMETSAT, All Rights Reserved
 *  PRODUCED BY :       This SW (document) was developed by GMV S.A. ,under
 *                      contract of INM, within he context of the EUMETSAT
 *                      Satellite Application facility on Nowcasting
 *                      and Short Range Forecasting, under the Cooperation
 *                      Agreement dated on 05 December 1996, between EUMETSAT
 *                      and INM.
 *  PROJECT     :       SAFNWC
 *  UNIT NAME   :       MSG
 *  FILE        :       msg_navigation.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Navigation routines
 *
 ****************************************************************************
 * HISTORY
 *
 *  DATE      VERSION  AUTHOR  REASONS
 *
 *  11/02/03  v0.1     GMV     SAFNWC/MSG v0.1
 *  26/03/04  v1.0     GMV     SAFNWC/MSG v1.0
 *
 ****************************************************************************/
#define _USE_MATH_DEFINES
#include "msg.h"
#include <math.h>

#define RPOL 6356.5838 /* km */
#define REQ  6378.1690 /* km */
#define H    42164.0   /* km */

#define NINT(a) ((a)>=0?(int)((a)+0.5):(int)((a)-0.5))


/************************************************************
 * FUNCTION:     msg_nav_direct
 * DESCRIPTION:  (lat,lon) -> (line,col) in SEVIRI projection
 * DATA IN:      lat: latitude (IN DEGREES)
 *               lon: longitude (IN DEGREES)
 *               sub_lon: sub-satellite longitude (in DEGREES)
 *               coff,cfac,loff,lfac: SEVIRI navigation coeff
 *                  Note: (coefficients assume x,y in degrees)
 *
 * DATA OUT:     line: SEVIRI line
 *               col:  SEVIRI column
 *
 * RETURN VALUE: Status
 *                0: Ok
 *                1: The provided point is not seen by SEVIRI
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 03.2002    1.0     GMV     First Version
 *
 *************************************************************/
int
msg_nav_direct(double lat, double lon, double sub_lon,
               int *line, int *column, 
	       double loff, double lfac,
	       double coff, double cfac) 
{
  double lat_rad,lon_rad,sub_lon_rad;
  double x,y,x_deg,y_deg;
  int status;

  /* Geographical coordinates in radians */
  lat_rad     = lat*M_PI/180.0;
  lon_rad     = lon*M_PI/180.0;
  sub_lon_rad = sub_lon*M_PI/180.0;

  /* GEO Projection */
  status=geo_nav_direct(lat_rad,lon_rad,sub_lon_rad,&x,&y);
  if(status) {  /* The point is not seen by SEVIRI */
    *line=0;
    *column=0;
    return(1);
  }

  /* Convert from (x,y) to (l,c) */
  /* --------------------------- */
  x_deg=x*180.0/M_PI;
  y_deg=y*180.0/M_PI;

  *line   = NINT(((y_deg*lfac)/pow(2,16))+loff);
  *column = NINT(((x_deg*cfac)/pow(2,16))+coff);
 
  return(0);
}


/************************************************************
 * FUNCTION:     geo_nav_direct
 * DESCRIPTION:  (lat,lon) -> (x,y) in GEO projection
 * DATA IN:      lat: latitude (IN RADIANS)
 *               lon: longitude (IN RADIANS)
 *               sub_lon: sub-satellite longitude (in RADIANS)
 *
 * DATA OUT:     x: scan angles (in RADIANS)
 *               y: scan angles (in RADIANS)
 *
 * RETURN VALUE: Status
 *                0: Ok
 *                1: The provided point is not seen in 
 *                   the projection
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 03.2002    1.0     GMV     First Version
 *
 *************************************************************/
int
geo_nav_direct(double lat, double lon, double sub_lon,
               double *x, double *y)
{


  double rpol2,req2,aux1,aux2,c_lat,cos_c_lat,rl,r1,r2,r3,rn;
  double ad2,bd,cd,delta2,halfsom;

  /* Auxiliary constants */
  /* ------------------- */
  rpol2=RPOL*RPOL;
  req2=REQ*REQ;
  aux1=rpol2/req2;
  aux2=(req2-rpol2)/req2;
  cd=H*H-req2;

  /* Auxiliary variables */
  /* ------------------- */
  c_lat=atan(aux1*tan(lat));
  cos_c_lat=cos(c_lat);

  rl=RPOL/sqrt(1-aux2*cos_c_lat*cos_c_lat);

  r1=H-rl*cos_c_lat*cos(lon-sub_lon);
  r2= -rl*cos_c_lat*sin(lon-sub_lon);
  r3=  rl*sin(c_lat);

  rn=sqrt(r1*r1+r2*r2+r3*r3);

  /* Check point */
  /* ----------- */
  ad2=r1*r1+r2*r2+r3*r3*req2/rpol2;
  bd=H*r1;

  delta2=bd*bd-ad2*cd;
  halfsom=bd*rn/ad2;

  if(delta2 < 0 || rn > halfsom) { /* Point is not seen */
    *x=0;
    *y=0;
    return(1);
  }

  /* Compute Scan Angles */
  /* ------------------- */
  *x=atan(-r2/r1);
  *y=asin(-r3/rn);
  return(0);
}
/*---------------------------------------------------------*/


/************************************************************
 * FUNCTION:     msg_nav_inverse
 * DESCRIPTION:  (line,col) -> (lat,lon) in SEVIRI projection
 * DATA IN:      line: SEVIRI line
 *               col:  SEVIRI column
 *               sub_lon: sub-satellite longitude (in DEGREES)
 *               coff,cfac,loff,lfac: SEVIRI navigation coeff
 *                  Note: (coefficients assume x,y in degrees)
 *
 * DATA OUT:     lat: latitude (IN DEGREES)
 *               lon: longitude (IN DEGREES)
 *
 * RETURN VALUE: Status
 *                0: Ok
 *                1: The pixel is out of the Earth Disk
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 03.2002    1.0     GMV     First Version
 *
 *************************************************************/
int
msg_nav_inverse(int line, int column, double sub_lon,
		double *lat, double *lon, 
		double loff, double lfac,
	        double coff, double cfac)
{

  double x,y,x_rad,y_rad,sub_lon_rad;
  int status;
   
  /* From SEVIRI line,col to scan angles */
  /* ----------------------------------- */
  x=((double)column - coff)*pow(2,16)/cfac;
  y=((double)line - loff)*pow(2,16)/lfac;

  /* in rads */
  x_rad=x*M_PI/180.0;
  y_rad=y*M_PI/180.0;
  sub_lon_rad=sub_lon*M_PI/180.0;

  /* GEO projection */ 
  status=geo_nav_inverse(x_rad,y_rad,sub_lon_rad,lat,lon);
  if(status) return(1);  /* Pixel out of the Earth Disk */

  /* Angles are returned in DEGREES */
  *lat *= 180.0/M_PI;
  *lon *= 180.0/M_PI;

  return(0);
}

/************************************************************
 * FUNCTION:     geo_nav_inverse
 * DESCRIPTION:  (x,y) -> (lat,lon) in GEO projection
 * DATA IN:      x: scan angles (in RADIANS)
 *               y: scan angles (in RADIANS)
 *               sub_lon: sub-satellite longitude (in RADIANS)
 *
 * DATA OUT:     lat: latitude (IN RADIANS)
 *               lon: longitude (IN RADIANS)
 *
 * RETURN VALUE: Status
 *                0: Ok
 *                1: The provided point is not seen in 
 *                   the projection
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 03.2002    1.0     GMV     First Version
 *
 *************************************************************/
int
geo_nav_inverse(double x, double y, double sub_lon,
               double *lat, double *lon)
{

  double rpol2,req2,aux1,aux2,aux3,aux4;
  double cos_x,cos_y,sin_x,sin_y;
  double s1,s2,s3,sxy,sn,sd;

  /* Auxiliary Constants */
  rpol2=RPOL*RPOL;
  req2=REQ*REQ;
  aux1=1737121856.0;

  /* Auxiliary Variables */
  cos_x=cos(x);
  cos_y=cos(y);
  sin_x=sin(x);
  sin_y=sin(y);

  aux2=H*cos_x*cos_y;
  aux3=cos_y*cos_y + req2/rpol2*sin_y*sin_y;

  /* Check point */
  /* ----------- */
  aux4 = aux2*aux2 - aux3*aux1;
  if(aux4 < 0) { /* Point is out of Earth Disk */
    *lat=0;
    *lon=0;
    return(1);
  }

  /* Auxiliary Variables */
  /* ------------------- */
  sd = sqrt(aux4);
  sn = (aux2-sd)/aux3;

  s1 = H - sn*cos_x*cos_y;
  s2 = sn*sin_x*cos_y;
  s3 = -sn*sin_y;

  sxy=sqrt(s1*s1+s2*s2);

  /* Compute Geographical coordinates */
  /* -------------------------------- */
  *lon=(atan(s2/s1))+sub_lon;
  *lat=(atan(req2/rpol2*s3/sxy));

  return(0);
}

