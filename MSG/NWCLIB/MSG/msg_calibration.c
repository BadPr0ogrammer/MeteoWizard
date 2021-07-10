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
 *  FILE        :       msg_calibration.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Calibration 
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

#include "msg.h"
#include <math.h>

#define C1 1E-16*1.19104  /* Wm2 ; C1=2*h*c*c */
#define C2 1E-2*1.43877   /* Km  ; C2=(hc)/K */


/****************************************************************
 * FUNCTION:       msg_cnt2rad
 * DESCRIPTION:    Calculates Radiance corresponding to a 
 *                 SEVIRI count
 *                 Radiance is computed as follow:
 *                 R = C*scale + offset (nW m-2 sr-1 (cm-1)-1)
 *
 * DATA IN:        count: SEVIRI count (10 bits)
 *                 scale: Calibration scale
 *                 offset: Calibration ofsset
 *
 * RETURN VALUE:   Radiances (in mW m-2 sr-1 (cm-1)-1), or
 *                 MSG_INVALID if count == 0, or
 *                                computed Radiance < 0
 *
 ****************************************************************
 * HISTORY
 *
 *    DATE   VERSION   AUTHOR   REASONS
 *  03.2002    1.0      GMV     Creation
 *
 ****************************************************************/
double
msg_cnt2rad(int count, double scale, double offset)
{
  double r;

  /* Check C=0 */
  if(count == 0) return(MSG_INVALID);
 
  /* Compute R */
  r = count*scale + offset;

  /* Return Value */
  if(r < 0) return(MSG_INVALID);
  else      return(r);
}


/*****************************************************************
 * FUNCTION:       msg_rad2bt
 *
 * DESCRIPTION:    Calculates brightness temperature using the
 *                 Radiance
 *
 * DATA IN:        rad: in mW m-2 sr-1 (cm-1)-1
 *                 alpha: Alpha parameter
 *                 beta:  Beta parameter
 *                 vc:    Central wave number (in cm-1)
 *
 * VALUE RETURNED: Brightness Temperature, in K, or
 *                 MSG_INVALID if R=MSG_INVALID
 *
 *****************************************************************
 * HISTORY
 *
 *    DATE   VERSION   AUTHOR   REASONS
 *  03.2002    1.0      GMV     Creation
 * 
 *****************************************************************/
double
msg_rad2bt(double rad, double alpha, double beta, double vc)
{
  float Tb;
 
  /* Chech R value */
  if(rad == MSG_INVALID) return(MSG_INVALID);
   
  /* Values are converted to International System */
  vc *= 100.0;   /* From cm-1                 to m-1                */
  rad *= 1.0E-5; /* From mW m-2 sr-1 (cm-1)-1 to W m-2 sr-1 (m-1)-1 */

  /* Compute Tb */
  Tb=((C2*vc)/(alpha*log(C1*vc*vc*vc/rad+1)))-(beta/alpha);
  return(Tb);
}

/*****************************************************************
 * FUNCTION:       msg_rad2ref
 *
 * DESCRIPTION:    Calculates Reflectance from Radiance
 *
 * DATA IN:        rad: in mW m-2 sr-1 (cm-1)-1
 *                 factor: Solar exo-atmospheric irradiance
 *                         convoluted with the SSR 
 *                         (in mW m-2 sr-1 (cm-1)-1)
 *
 * VALUE RETURNED: Reflectance, in % [0,1], or
 *                 MSG_INVALID if R=MSG_INVALID, or
 *                                computed Reflectance < 0, or
 *                                computes Reflectance > 1
 *
 *****************************************************************
 * HISTORY
 *
 *    DATE   VERSION   AUTHOR   REASONS
 *  03.2002    1.0      GMV     Creation
 * 
 *****************************************************************/
double
msg_rad2ref(double rad, double factor)
{
  double ref;
 
  /* Chech R value */
  if(rad == MSG_INVALID) return(MSG_INVALID);
   
  /* Compute ref */
  ref=rad/factor;
  if(ref < 0 || ref > 1) return(MSG_INVALID);
  else                   return(ref);
}

