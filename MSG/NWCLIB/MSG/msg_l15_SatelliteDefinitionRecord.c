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
 *  FILE        :       msg_l15_SatelliteDefinitionRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 SatelliteDefinitionRecord I/O
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
 * FUNCTION:     freadSatelliteDefinitionRecord
 * DESCRIPTION:  Read a SatelliteDefinition structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  SatelliteDefinition structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadSatelliteDefinitionRecord(SatelliteDefinition_Record *r, FILE *fp)
{
  freadGPSCID(&r->SatelliteId,fp);
  freadFloat(&r->NominalLongitude,1,fp);
  fread(&r->SatelliteStatus,1,1,fp);
}


/************************************************************
 * FUNCTION:     fwriteSatelliteDefinitionRecord
 * DESCRIPTION:  Write a SatelliteDefinition structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  SatelliteDefinition structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteSatelliteDefinitionRecord(SatelliteDefinition_Record *r, FILE *fp)
{
  fwriteGPSCID(&r->SatelliteId,fp);
  fwriteFloat(&r->NominalLongitude,1,fp);
  fwrite(&r->SatelliteStatus,1,1,fp);
}

