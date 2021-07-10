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
 *  FILE        :       msg.h
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Types I/O
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

#ifndef __MSG_H__
#define __MSG_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "msg_basictypes.h"
#include "msg_hrit.h"
#include "msg_l15.h"

#define MSG_INVALID -9999.0

int msg_nav_direct(double lat, double lon, double sub_lon,
	           int *line, int *column, 
		   double loff, double lfac,
		   double coff, double cfac);
int msg_nav_inverse(int line, int column, double sub_lon,
                    double *lat, double *lon, 
                    double loff, double lfac,
                    double coff, double cfac);

int geo_nav_direct(double lat, double lon, double sub_lon,
                   double *x, double *y);
int geo_nav_inverse(double x, double y, double sub_lon,
                    double *lat, double *lon);


double msg_cnt2rad(int count, double scale, double offset);
double msg_rad2bt(double rad, double alpha, double beta, double vc);
double msg_rad2ref(double rad, double factor);

#endif
