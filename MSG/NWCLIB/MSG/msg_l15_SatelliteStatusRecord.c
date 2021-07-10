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
 *  FILE        :       msg_l15_SatelliteStatusRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 SatelliteStatusRecord I/O
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
 * FUNCTION:     freadSatelliteStatusRecord
 * DESCRIPTION:  Read a SatelliteStatus structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  SatelliteStatus structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadSatelliteStatusRecord(SatelliteStatus_Record *r, FILE *fp)
{
  freadSatelliteDefinitionRecord(&r->SatelliteDefinition,fp);
  freadSatelliteOperationsRecord(&r->SatelliteOperations,fp);
  freadOrbitRecord(&r->Orbit,fp);
  freadAttitudeRecord(&r->Attitude,fp);
  freadDouble(&r->SpinRateatRCStart,1,fp);
  freadUTCCorrelationRecord(&r->UTCCorrelation,fp);
}


/************************************************************
 * FUNCTION:     fwriteSatelliteStatusRecord
 * DESCRIPTION:  Write a SatelliteStatus structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  SatelliteStatus structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteSatelliteStatusRecord(SatelliteStatus_Record *r, FILE *fp)
{
  fwriteSatelliteDefinitionRecord(&r->SatelliteDefinition,fp);
  fwriteSatelliteOperationsRecord(&r->SatelliteOperations,fp);
  fwriteOrbitRecord(&r->Orbit,fp);
  fwriteAttitudeRecord(&r->Attitude,fp);
  fwriteDouble(&r->SpinRateatRCStart,1,fp);
  fwriteUTCCorrelationRecord(&r->UTCCorrelation,fp);
}

