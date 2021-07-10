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
 *  FILE        :       msg_l15_ImageAcquisitionRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 ImageAcquisitionRecord I/O
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
 * FUNCTION:     freadImageAcquisitionRecord
 * DESCRIPTION:  Read a ImageAcquisition structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  ImageAcquisition structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadImageAcquisitionRecord(ImageAcquisition_Record *r, FILE *fp)
{
  freadPlannedAcquisitionTimeRecord(&r->PlannedAcquisitionTime, fp);
  freadRadiometerStatusRecord(&r->RadiometerStatus,fp);
  freadRadiometerSettingsRecord(&r->RadiometerSettings,fp);
  freadRadiometerOperationsRecord(&r->RadiometerOperations,fp);
}


/************************************************************
 * FUNCTION:     fwriteImageAcquisitionRecord
 * DESCRIPTION:  Write a ImageAcquisition structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  ImageAcquisition structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteImageAcquisitionRecord(ImageAcquisition_Record *r, FILE *fp)
{
  fwritePlannedAcquisitionTimeRecord(&r->PlannedAcquisitionTime, fp);
  fwriteRadiometerStatusRecord(&r->RadiometerStatus,fp);
  fwriteRadiometerSettingsRecord(&r->RadiometerSettings,fp);
  fwriteRadiometerOperationsRecord(&r->RadiometerOperations,fp);
}

