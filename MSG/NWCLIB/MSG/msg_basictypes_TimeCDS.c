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
 *  FILE        :       msg_basictypes_TimeCDS.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Basic Types TimeCDS I/O
 *                      Assumes file written in SUN byte ordering
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
#include "msg_basictypes.h"


/************************************************************
 * FUNCTION:     freadTimeCDS
 * DESCRIPTION:  Read a TimeCDS structure
 * DATA IN:      fp: file
 * DATA OUT:     t:  TimeCDS structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
freadTimeCDS(TimeCDS *t, FILE *fp)
{
  freadUShort(&t->days,2,fp);
  freadUInt(&t->millisecs,4,fp);
  freadUShort(&t->microsecs,2,fp);
}


/************************************************************
 * FUNCTION:     fwriteTimeCDS
 * DESCRIPTION:  Write a TimeCDS structure
 * DATA IN:      fp: file
 *               t:  TimeCDS structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
fwriteTimeCDS(TimeCDS *t, FILE *fp)
{
  fwriteUShort(&t->days,2,fp);
  fwriteUInt(&t->millisecs,4,fp);
  fwriteUShort(&t->microsecs,2,fp);
}


/************************************************************
 * FUNCTION:     fprintfTimeCDS
 * DESCRIPTION:  Displays a TimeCDS contents
 * DATA IN:      stream: output stream
 *               t:      TimeCDS
 *               label:  Text for the parent structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
fprintfTimeCDS(FILE *stream, TimeCDS *t, char *label)
{
  fprintf(stream,"%s.days        %d\n",label,t->days);
  fprintf(stream,"%s.millisecs   %d\n",label,t->millisecs);
  fprintf(stream,"%s.microsecs   %d\n",label,t->microsecs);
}

