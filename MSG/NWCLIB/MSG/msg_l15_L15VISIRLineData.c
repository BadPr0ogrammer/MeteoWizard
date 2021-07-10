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
 *  FILE        :       msg_l15_L15VISIRLineData.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 L15VISIRLineData I/O
 *
 ****************************************************************************
 * HISTORY
 *
 *  DATE      VERSION  AUTHOR  REASONS
 *
 *  11/02/03  v0.1     GMV     SAFNWC/MSG v0.1
 *				SPR-SAF-NWC-IOP-0089 : SMR-SAF-NWC-IOP-0082
 *  26/03/04  v1.0     GMV     SAFNWC/MSG v1.0
 *
 ****************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include "msg_l15.h"


/************************************************************
 * FUNCTION:     UnpackL15VISIRLineData
 * DESCRIPTION:  Unpack 10bits/pixel data to a unsigned short array
 * DATA IN:      LineData[4640]: unsigned char array with packed data
 * DATA OUT:     a[3712]: unsiged short array with unpacked data
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
UnpackL15VISIRLineData(unsigned char LineData[4640], unsigned short a[3712])
{
  int i;
  for(i=0; i<3712/4; i++) Unpack4pix10bit(LineData+i*5,a+i*4);
}

/************************************************************
 * FUNCTION:     UnpackL15VISIRLineData_12
 * DESCRIPTION:  Unpack 12bits/pixel data to a unsigned short array
 * DATA IN:      LineData[5568]: unsigned char array with packed data
 * DATA OUT:     a[3712]: unsiged short array with unpacked data
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 06.2003    1.0     ADSD    Creation
 *
 *************************************************************/
void
UnpackL15VISIRLineData_12(unsigned char LineData[5568], unsigned short a[3712])
{
  int i;
  for(i=0; i<3712/2; i++) Unpack2pix12bit(LineData+i*3,a+i*2);
}


/************************************************************
 * FUNCTION:     PackL15VISIRLineData
 * DESCRIPTION:  Pack a unsigned short array to a 10bits/pixel data
 * DATA IN:      a[3712]: unsiged short array with unpacked data
 * DATA OUT:     LineData[4640]: unsigned char array with packed data
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
PackL15VISIRLineData(unsigned short a[3712], unsigned char LineData[4640])
{
  int i;
  for(i=0; i<3712/4; i++) Pack4pix10bit(a+i*4,LineData+i*5);
}

/************************************************************
 * FUNCTION:     PackL15VISIRLineData_12
 * DESCRIPTION:  Pack a unsigned short array to a 12bits/pixel data
 * DATA IN:      a[3712]: unsiged short array with unpacked data
 * DATA OUT:     LineData[5568]: unsigned char array with packed data
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 06.2003    1.0     ADSD    Creation
 *
 *************************************************************/
void
PackL15VISIRLineData_12(unsigned short a[3712], unsigned char LineData[5568])
{
  int i;
  for(i=0; i<3712/2; i++) Pack2pix12bit(a+i*2,LineData+i*3);
}


