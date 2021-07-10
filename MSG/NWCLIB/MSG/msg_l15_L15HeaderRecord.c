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
 *  FILE        :       msg_l15_L15HeaderRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 L15HeaderRecord I/O
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
 * FUNCTION:     freadL15HeaderRecord
 * DESCRIPTION:  Read a L15Header structure
 * DATA IN:      fp: file
 * DATA OUT:     h:  L15header structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadL15HeaderRecord(L15Header_Record *r, FILE *fp)
{
  fread(&r->L15HEADERVersion,1,1,fp);
  freadSatelliteStatusRecord(&r->SatelliteStatus,fp);
  freadImageAcquisitionRecord(&r->ImageAcquisition,fp);
  freadCelestialEventsRecord(&r->CelestialEvents,fp);
  freadImageDescriptionRecord(&r->ImageDescription,fp);
  freadRadiometricProcessingRecord(&r->RadiometricProcessing,fp);
  freadGeometricProcessingRecord(&r->GeometricProcessing,fp);
  freadIMPFConfigurationRecord(&r->IMPFConfiguration,fp);
}


/************************************************************
 * FUNCTION:     fwriteL15HeaderRecord
 * DESCRIPTION:  Write a L15Header structure
 * DATA IN:      fp: file
 * DATA OUT:     h:  L15header structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteL15HeaderRecord(L15Header_Record *r, FILE *fp)
{
  fwrite(&r->L15HEADERVersion,1,1,fp);
  fwriteSatelliteStatusRecord(&r->SatelliteStatus,fp);
  fwriteImageAcquisitionRecord(&r->ImageAcquisition,fp);
  fwriteCelestialEventsRecord(&r->CelestialEvents,fp);
  fwriteImageDescriptionRecord(&r->ImageDescription,fp);
  fwriteRadiometricProcessingRecord(&r->RadiometricProcessing,fp);
  fwriteGeometricProcessingRecord(&r->GeometricProcessing,fp);
  fwriteIMPFConfigurationRecord(&r->IMPFConfiguration,fp);
}

