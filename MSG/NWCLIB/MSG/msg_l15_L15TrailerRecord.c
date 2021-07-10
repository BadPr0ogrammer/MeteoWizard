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
 *  FILE        :       msg_l15_L15TrailerRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 L15TrailerRecord I/O
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
 * FUNCTION:     freadL15TrailerRecord
 * DESCRIPTION:  Read a L15Trailer structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  L15Trailer structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadL15TrailerRecord(L15Trailer_Record *r, FILE *fp)
{
  fread(&r->L15TRAILERVersion,1,1,fp);
  freadImageProductionStatsRecord(&r->ImageProductionStats,fp);
  freadNavigationExtrationResultsRecord(&r->NavigationExtrationResults,fp);
  freadRadiometricQualityRecord(&r->RadiometricQuality,fp);
  freadGeometricQualityRecord(&r->GeometricQuality,fp);
  freadTimelinessAndCompletenessRecord(&r->TimelinessAndCompleteness,fp);
}


/************************************************************
 * FUNCTION:     fwriteL15TrailerRecord
 * DESCRIPTION:  Write a L15Trailer structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  L15Trailer structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteL15TrailerRecord(L15Trailer_Record *r, FILE *fp)
{
  fwrite(&r->L15TRAILERVersion,1,1,fp);
  fwriteImageProductionStatsRecord(&r->ImageProductionStats,fp);
  fwriteNavigationExtrationResultsRecord(&r->NavigationExtrationResults,fp);
  fwriteRadiometricQualityRecord(&r->RadiometricQuality,fp);
  fwriteGeometricQualityRecord(&r->GeometricQuality,fp);
  fwriteTimelinessAndCompletenessRecord(&r->TimelinessAndCompleteness,fp);
}

