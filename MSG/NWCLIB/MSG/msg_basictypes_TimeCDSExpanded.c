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
 *  FILE        :       msg_basictypes_TimeCDSExpanded.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Basic Types TimeCDSExpanded I/O
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
 * FUNCTION:     freadTimeCDSExpanded
 * DESCRIPTION:  Read a TimeCDSExpanded structure
 * DATA IN:      fp: file
 * DATA OUT:     t:  TimeCDSExpanded structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
freadTimeCDSExpanded(TimeCDSExpanded *t, FILE *fp)
{
  freadUShort(&t->days,1,fp);
  freadUInt(&t->millisecs,1,fp);
  freadUShort(&t->microsecs,1,fp);
  freadUShort(&t->nanosecs,1,fp);
}


/************************************************************
 * FUNCTION:     fwriteTimeCDSExpanded
 * DESCRIPTION:  Write a TimeCDSExpanded structure
 * DATA IN:      fp: file
 *               t:  TimeCDSExpanded structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
fwriteTimeCDSExpanded(TimeCDSExpanded *t, FILE *fp)
{
  fwriteUShort(&t->days,1,fp);
  fwriteUInt(&t->millisecs,1,fp);
  fwriteUShort(&t->microsecs,1,fp);
  fwriteUShort(&t->nanosecs,1,fp);
}


/************************************************************
 * FUNCTION:     fprintfTimeCDSExpanded
 * DESCRIPTION:  Displays a TimeCDSExpanded contents
 * DATA IN:      stream: output stream
 *               t:      TimeCDSExpanded
 *               label:  Text for the parent structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
fprintfTimeCDSExpanded(FILE *stream, TimeCDSExpanded *t, char *label)
{
  fprintf(stream,"%s.days        %d\n",label,t->days);
  fprintf(stream,"%s.millisecs   %d\n",label,t->millisecs);
  fprintf(stream,"%s.microsecs   %d\n",label,t->microsecs);
  fprintf(stream,"%s.nanosecs    %d\n",label,t->nanosecs);
}

