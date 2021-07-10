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
 *  FILE        :       msg_l15_4pix10bit.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 4pix10bit Unpack/Pack
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


#include <stdlib.h>
#include <stdio.h>
#include "msg_l15.h"


/************************************************************
 * FUNCTION:     Unpack4pix10bit
 * DESCRIPTION:  Unpack 4 10bits pixels packed in 5 bytes
 * DATA IN:      *data: array with packed data (5 bytes)
 * DATA OUT:     *a: unsigned short array with unpacked data (4 pixels)
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
Unpack4pix10bit(unsigned char *data, unsigned short *a)
{
  a[0]=(data[0]*256+data[1])/64;
  a[1]=((data[1]*256+data[2])&16368)/16;
  a[2]=((data[2]*256+data[3])&4092)/4;
  a[3]=((data[3]*256+data[4])&1023);
}


/************************************************************
 * FUNCTION:     Pack4pix10bit
 * DESCRIPTION:  Pack 4 10bits pixels in 5 bytes
 * DATA IN:      *a: unsigned short array with unpacked data (4 pixels)
 * DATA OUT:     *data: array with packed data (5 bytes)
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
Pack4pix10bit(unsigned short *a, unsigned char *data)
{
  data[0]=(a[0]*64)/256;
  data[1]=(a[0]*64)%256+(a[1]*16)/256;
  data[2]=(a[1]*16)%256+(a[2]*4)/256;
  data[3]=(a[2]*4)%256+a[3]/256;
  data[4]=a[3]%256;
}

