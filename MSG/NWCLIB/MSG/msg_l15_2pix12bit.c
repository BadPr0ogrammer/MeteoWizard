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
 *  FILE        :       msg_l15_2pix12bit.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 2pix12bit Unpack/Pack
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
 * FUNCTION:     Unpack2pix12bit
 * DESCRIPTION:  Unpack 2 12bits pixels packed in 3 bytes
 * DATA IN:      *data: array with packed data (3 bytes)
 * DATA OUT:     *a: unsigned short array with unpacked data (2 pixels)
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 06.2003    1.0     OOAL    Creation
 *
 *************************************************************/
void
Unpack2pix12bit(unsigned char *data, unsigned short *a)
{
  a[0]=(data[0]*256+data[1])/16;
  a[1]=(data[1]*256+data[2])&4095;
}


/************************************************************
 * FUNCTION:     Pack2pix12bit
 * DESCRIPTION:  Pack 2 12bits pixels in 3 bytes
 * DATA IN:      *a: unsigned short array with unpacked data (2 pixels)
 * DATA OUT:     *data: array with packed data (3 bytes)
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 06.2003    1.0     OOAL    Creation
 *
 *************************************************************/
void
Pack2pix12bit(unsigned short *a, unsigned char *data)
{
  data[0]=(a[0]*16)/256;
  data[1]=(a[0]*16)%256+(a[1])/256;
  data[2]=a[1]%256;
}

