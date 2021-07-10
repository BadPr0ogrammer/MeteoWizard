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
 *  FILE        :       msg_l15_LineSideInfoRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 LineSideInfoRecord I/O
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
 * FUNCTION:     freadLineSideInfoRecord
 * DESCRIPTION:  Read a LineSideInfo structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  LineSideInfo structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadLineSideInfoRecord(LineSideInfo_Record *r, FILE *fp)
{
  freadGPSCID(&r->SatelliteId,fp);
  freadTimeCDSExpanded(&r->TrueRepeatCycleStart,fp);
  freadSInt(&r->LineNumberInVIS_IRGrid,1,fp);
  fread(&r->ChannelId,1,1,fp);
  freadTimeCDSShort(&r->L10LineMeanAcquisitionTime,fp);
  fread(&r->LineValidity,1,1,fp);
  fread(&r->LineRadiometricQuality,1,1,fp);
  fread(&r->LineGeometricQuality,1,1,fp);
}


/************************************************************
 * FUNCTION:     fwriteLineSideInfoRecord
 * DESCRIPTION:  Write a LineSideInfo structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  LineSideInfo structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteLineSideInfoRecord(LineSideInfo_Record *r, FILE *fp)
{
  fwriteGPSCID(&r->SatelliteId,fp);
  fwriteTimeCDSExpanded(&r->TrueRepeatCycleStart,fp);
  fwriteSInt(&r->LineNumberInVIS_IRGrid,1,fp);
  fwrite(&r->ChannelId,1,1,fp);
  fwriteTimeCDSShort(&r->L10LineMeanAcquisitionTime,fp);
  fwrite(&r->LineValidity,1,1,fp);
  fwrite(&r->LineRadiometricQuality,1,1,fp);
  fwrite(&r->LineGeometricQuality,1,1,fp);
}

