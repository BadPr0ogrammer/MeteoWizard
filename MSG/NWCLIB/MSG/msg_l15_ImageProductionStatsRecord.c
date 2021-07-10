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
 *  FILE        :       msg_l15_ImageProductionStatsRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 ImageProductionStatsRecord I/O
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
 * FUNCTION:     freadImageProductionStatsRecord
 * DESCRIPTION:  Read a ImageProductionStats structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  ImageProductionStats structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 * 05.11.01   1.1     OOAL    campo GP_SC_ID
 *
 *************************************************************/
void
freadImageProductionStatsRecord(ImageProductionStats_Record *r, FILE *fp)
{
  freadGPSCID(&r->SatelliteId,fp);
  fread(&r->ch,1,338,fp);
}


/************************************************************
 * FUNCTION:     fwriteImageProductionStatsRecord
 * DESCRIPTION:  Write a ImageProductionStats structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  ImageProductionStats structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 * 05.11.01   1.1     OOAL    Campo GP_SC_ID
 *
 *************************************************************/
void
fwriteImageProductionStatsRecord(ImageProductionStats_Record *r, FILE *fp)
{
  fwriteGPSCID(&r->SatelliteId,fp);
  fwrite(&r->ch,1,338,fp);
}

