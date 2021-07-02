/*************************************************************************
* COPYRIGHT AND LICENCE INFORMATION
* 
* Freeware Licence Disclaimer
* 
* The user acknowledges and shall at all times respect EUMETSAT's
* intellectual property rights in the software. EUMETSAT shall at all
* times retain such intellectual property rights in the software and in
* all copies thereof regardless of form.
* 
* The user may freely use, copy, modify and/or distribute the software.
* The user agrees when using the software in any recognisable form to
* name EUMETSAT as the source by including "?(year)
* EUMETSAT". Furthermore, In any distributed version of the software,
* including modifications or derivatives, the present licence text shall
* be included.  The user of the software may provide feedback, report
* problems and suggest enhancements to the software to EUMETSAT. In
* addition, the user shall grant to EUMETSAT unrestricted use of this
* information.
* 
* Neither EUMETSAT nor its Member States are liable for the usefulness
* or proper functioning of software, nor do they accept any liability
* for any consequences, whether direct or indirect, of any use of
* software or for any results related to the use of software or for any
* right or claims by third parties related to all or any part of
* software or its use. Where the source code is made available to users
* this is done without any warranty, and EUMETSAT will not provide any
* support for its use and customisation."
*
* Introduction:
* =============
* The Program "MSG_navigation_v1.02.c" is an example code provided to give
* the users guidance for a possible implementation of the equations
* given in the LRIT/HRIT Global Specification [1] to navigate MSG
* (METEOSAT 8 onwards) data, i.e. to link the pixel coordinates column
* and line to the corresponding geographical coordinates latitude and
* longitude.
*
* Users should take note, however, that it does NOT provide software
* for reading MSG data either in LRIT/HRIT, in native or any other
* format and that EUMETSAT cannot guarantee the accuracy of this
* software. The software is for use with MSG data only and will not
* work in the given implementation for Meteosat first generation data.
* 
* Two functions/subroutines are provided:
*   pixcoord2geocoord: for conversion of column/line into lat./long.
*   geocoord2pixcoord: for conversion of lat./long. into column/line
* 
* The main routine gives an example how to utilize these two functions by
* reading a value for column and line at the start of the program on the
* command line and convert these values into the corresponding
* geographical coordinates and back again. The results are then printed
* out on the screen.
*
* To Compile the program use for example:
*
* COMMAND PROMPT: gcc MSG_navigation_v1.02.c -o MSG_navigation_v1.02 -lm
* 
* Run the program by typing 
* 
* COMMAND PROMPT: ./MSG_navigation <COLUMS> <ROWS> <HRV>
* 
* where <HRV> is the switch which should be 0 for VisIR images and 1
* for HRVis images.
*
* ----------------------------------------------------------------------
*
* NOTE: Please be aware, that the program assumes the MSG image is
* ordered in the operational scanning direction which means from south
* to north and from east to west. With that the VIS/IR channels contains
* of 3712 x 3712 pixels, start to count on the most southern line and the
* most eastern column with pixel number 1,1 and the HRV Upper and Lower 
* Areas are placed in the HRV-reference grid which contains 11136 x 11136 
* HRV pixels. Please see [3] for information about the alignment of HRV 
* Areas to the HRV-reference grid and the HRV-reference grid to the other
* Non-HRV channels.
*
*
* NOTE on CFAC/LFAC and COFF/LOFF:
* The parameters CFAC/LFAC and COFF/LOFF are the scaling coefficients
* provided by the navigation record of the LRIT/HRIT header and used
* by the scaling function given in Ref [1], page 28.
*
* COFF/LOFF are the offsets for column and line which are defining the 
* middle of the Image  (centre pixel) and are basically 1856/1856 for 
* the VIS/IR channels and 5566/5566 for the HRV channel reference grid. 
* Please see also [3] for more information about this.
*
* CFAC/LFAC are responsible for the image "spread" in the NS and EW
* directions. They are calculated as follows:
* CFAC = LFAC = 2^16 / delta
* with
* delta = 83.84333 micro Radian (size of one VIS/IR MSG pixel)
* delta_HRV = 83.84333/3 micro Radian (size of one HRV MSG pixel)
* 
* CFAC     = LFAC     =  781648343.404  rad^-1 for VIS/IR
* CFAC_HRV = LFAC_HRV = 2344945030.212  rad^-1 for HRV
*
* which should be rounded to the nearest integer as stated in Ref [1].
* 
* CFAC     = LFAC     =  781648343  rad^-1 for VIS/IR
* CFAC_HRV = LFAC_HRV = 2344945030  rad^-1 for HRV
*
* the sign of CFAC/LFAC gives the orientation of the image.
* Negative sign give data scanned from south to north as in the
* operational scanning. Positive sign vice versa.
*
* The terms "line" and "row" are used interchangeable.
*
* PLEASE NOTE that the values of CFAC/LFAC which are given in the
* Header of the LRIT/HRIT Level 1.5 Data (see [2]) are actually in 
* Degrees^1 and should be converted in Radians for use with these 
* routines (see example and values above).
*
* The other parameters are given in Ref [1].
*
* Further information may be found in either Ref [1], Ref [2] or
*  Ref [3] or on the Eumetsat website http://www.eumetsat.int/ .
*
*  REFERENCE:                                            
*  [1] LRIT/HRIT Global Specification                     
*      (CGMS 03, Issue 2.6, 12.08.1999)                  
*      for the parameters used in the program.
*  [2] MSG Ground Segment LRIT/HRIT Mission Specific 
*      Implementation, EUMETSAT Document, 
*      (EUM/MSG/SPE/057, Issue 6, 21. June 2006).
*  [3] MSG Level 1.5 Image Data Format Description
*      (EUM/MSG/ICD/105, Issue v6, 23. February 2010).
*
* Please email the User Service (via
* http://www.eumetsat.int/Home/Main/AboutEUMETSAT/Contact_Us/index.htm
* if you have any questions regarding this software.
*
*
***********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#include "MSG_navigation_v1.02.h"

/**************************************************************
 * function pixcoord2geocoord                                 *
 *                                                            *
 * PURPOSE:                                                   *
 *   return the latitude and longitude of an MSG image        *
 *   for a given pair of pixel column and row.                *
 *   (based on the formulas given in Ref. [1])                *
 *                                                            *
 *                                                            *
 * DEPENDENCIES:                                              *
 *   none                                                     *
 *                                                            *
 *                                                            *
 * REFERENCE:                                                 *
 * [1] LRIT/HRIT Global Specification                         *
 *     (CGMS 03, Issue 2.6, 12.08.1999)                       *
 *     for the parameters used in the program.                *
 * [2] MSG Ground Segment LRIT/HRIT Mission Specific          *
 *     Implementation, EUMETSAT Document,                     *
 *     (EUM/MSG/SPE/057, Issue 6, 21. June 2006).             *
 *                                                            *
 *                                                            *
 * MODIFICATION HISTORY:                                      *
 *  Version 1.02                                              *
 *  08.08.2008 removed a bug in longi = atan(s2/s1) statement *
 *  30.11.2011 added HRV to the calculation                   *
 *             Implemented with introducing CFAC/LFAC in      *
 *             function call                                  *
 *   Copyright(c) EUMETSAT 2005, 2009, 2011                   *
 *                                                            *
 *                                                            *
 * INPUT:                                                     *
 *   row    (int) row-value of the pixel                      *
 *   column (int) line-value of the pixel                     *
 *   coff   (int) coefficient of the scalling function        *
 *                (see page 28, Ref [1])                      *
 *   loff   (int) coefficient of the scalling function        *
 *                (see page 28, Ref [1])                      *
 *   cfac  (real) image "spread" in the EW direction          *
 *   lfac  (real) image "spread" in the NS direction          *
 *                                                            *
 * OUTPUT:                                                    *
 *   latitude  (double) geographic Latitude of the given      *
 *                      pixel [Degrees]                       *
 *   longitude (double) geographic Longitude of the given     *
 *                      pixel [Degrees]                       *
 *                                                            *
 *                                                            *
 *************************************************************/

int pixcoord2geocoord(double c, double l, double *latitude, double *longitude, int hrv)
{  
  /*  calculate viewing angle of the satellite by use of the equation  */
  /*  on page 28, Ref [1]. */
  double COFF, CFAC;
  if (hrv) {
    COFF = COFF_HRV;
    CFAC = CFAC_HRV;
  } else {
    COFF = COFF_VIR;
    CFAC = CFAC_VIR;
  }
  double x = (1 << 16) * ( (double)c - COFF) / CFAC;
  double y = (1 << 16) * ( (double)l - COFF) / CFAC;

  /*  now calculate the inverse projection */

  /* first check for visibility, whether the pixel is located on the Earth   */
  /* surface or in space. 						     */
  /* To do this calculate the argument to sqrt of "sd", which is named "sa". */
  /* If it is negative then the sqrt will return NaN and the pixel will be   */
  /* located in space, otherwise all is fine and the pixel is located on the */
  /* Earth surface.                                                          */
  /* Auxiliary values */
  double cosx = cos(x);
  double cosy = cos(y);
  double sinx = sin(x);
  double siny = sin(y);

  double aux = SAT_HEIGHT * cosx * cosy;
  double aux2 = cosy * cosy + 1.006803 * siny * siny;
  double sa = aux * aux - aux2 * 1737121856;

  /* produce error values
    if (sa < 0) {
        *latitude = -999.999;
        *longitude = -999.999;
        return (-1);
    }*/

  if (sa <= 0) {
    return -1;
    // sa = 0;
  }
  /* now calculate the rest of the formulas using equations on */
  /* page 25, Ref. [1]  */
  double sd = sqrt(sa);
  double sn = (aux - sd) / aux2;
  double s1 = SAT_HEIGHT - sn * cosx * cosy;
  double s2 = sn * sinx * cosy;
  double s3 = - sn * siny;
  double sxy = sqrt(s1 * s1 + s2 * s2);

  /* using the previous calculations the inverse projection can be  */
  /* calculated now, which means calculating the lat./long. from    */
  /* the pixel row and column by equations on page 25, Ref [1].     */
  double longi = RAD2DEG * atan(s2 / s1) + SUBLON;
  double lati = (atan(1.006803 * s3 / sxy)) * RAD2DEG;

  /* valid range for longitudes [-180,180] */
  if (longi > 180)
    longi -= 360;
  if (longi < -180)
    longi += 360;

  /* convert from radians into degrees */
  *latitude = lati;
  *longitude = longi;

  return 0;
}

/**************************************************************
 * function geocoord2pixcoord                                 *
 *                                                            *
 * PURPOSE:                                                   *
 *   return the pixel column and line of an MSG image         *
 *   for a given pair of latitude/longitude.                  *
 *   (based on the formulas given in Ref. [1])                *
 *                                                            *
 *                                                            *
 * DEPENDENCIES:                                              *
 *   none                                                     *
 *                                                            *
 *                                                            *
 * REFERENCE:                                                 *
 * [1] LRIT/HRIT Global Specification                         *
 *     (CGMS 03, Issue 2.6, 12.08.1999)                       *
 *     for the parameters used in the program                 *
 * [2] MSG Ground Segment LRIT/HRIT Mission Specific          *
 *     Implementation, EUMETSAT Document,                     *
 *     (EUM/MSG/SPE/057, Issue 6, 21. June 2006).             *
 *                                                            *
 *                                                            *
 * MODIFICATION HISTORY:                                      *
 *   Version 1.02                                             *
 *  30.11.2011 added HRV to the calculation                   *
 *             Implemented with introducing CFAC/LFAC in      *
 *             function call                                  *
 *   Copyright(c) EUMETSAT 2005, 2009, 2011                   *
 *                                                            *
 *                                                            *
 * INPUT:                                                     *
 *   latitude  (double) geographic Latitude of a point        *
 *                      [Degrees]                             *
 *   longitude (double) geographic Longitude of a point       *
 *                      [Degrees]                             *
 *   coff (int)   coefficient of the scalling function        *
 *                (see page 28, Ref [1])                      *
 *   loff (int)   coefficient of the scalling function        *
 *                (see page 28, Ref [1])                      *
 *   cfac  (real) image "spread" in the EW direction          *
 *   lfac  (real) image "spread" in the NS direction          *
 *                                                            *
 *                                                            *
 * OUTPUT:                                                    *
 *   row    (int) row-value of the wanted pixel               *
 *   column (int) column-value of the wanted pixel            *
 *                                                            *
 *************************************************************/

int geocoord2pixcoord(double lati, double longi, double *column, double *row, int hrv)
{
  /* check if the values are sane, otherwise return error values */
  lati =  MAX( -90, MIN( 90,  lati));
  longi = MAX(-180, MIN(180, longi));

  /* convert them to radiants */
  double lat = lati * DEG2RAD;
  double lon = longi * DEG2RAD;
  double subloni = SUBLON * DEG2RAD;

  /* calculate the geocentric latitude from the          */
  /* geograhpic one using equations on page 24, Ref. [1] */
  double c_lat = atan(0.993243 * tan(lat));

  /* using c_lat calculate the length form the Earth */
  /* centre to the surface of the Earth ellipsoid    */
  /* equations on page 23, Ref. [1]                  */
  /* calculate the forward projection using equations on */
  /* page 24, Ref. [1]                                        */
  double cosc_lat = cos(c_lat);
  double r_pol2 = R_POL * R_POL;
  double r_eq2 = R_EQ * R_EQ;
  double rl = R_POL/(sqrt(1 - ((r_eq2 - r_pol2) / r_eq2) * cosc_lat * cosc_lat));
  double r1 = SAT_HEIGHT - rl * cosc_lat * cos(lon - subloni);
  double r2 = -rl * cosc_lat * sin(lon - subloni);
  double r3 = rl * sin(c_lat);
  double rn = sqrt(r1 * r1 + r2 * r2 + r3 * r3);

  /* check for visibility, whether the point on the Earth given by the */
  /* latitude/longitude pair is visible from the satellte or not. This */
  /* is given by the dot product between the vectors of:               */
  /* 1) the point to the spacecraft,			               */
  /* 2) the point to the centre of the Earth.			       */
  /* If the dot product is positive the point is visible otherwise it  */
  /* is invisible.	                          */

  /* compute variables useful to check if pixel is visible from the satellite */
  double ad2 = r1 * r1 + r2 * r2 + r3 * r3 * r_eq2 / r_pol2;
  double bd = SAT_HEIGHT * r1;
  double cd = SAT_HEIGHT * SAT_HEIGHT - r_eq2;
  double delta2 = bd * bd - ad2 * cd;
  double halfsom = bd * rn / ad2;

  if (delta2 >= 0 && rn <= halfsom) {
    /* Intermediate coordinates */
    /* the forward projection is x and y */
    double x = atan(-r2/r1);
    double y = asin(-r3/rn);

    double COFF,CFAC;
    if (hrv) {
      COFF = COFF_HRV;
      CFAC = CFAC_HRV;
    } else {
      COFF = COFF_VIR;
      CFAC = CFAC_VIR;
    }

    *column = COFF + x / (1 << 16) * CFAC;
    *row =    COFF + y / (1 << 16) * CFAC;
  } else {
    return -1;
  }
  return (0);
}
