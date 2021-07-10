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
 *  FILE        :       msg_l15_GeometricProcessingRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 GeometricProcessingRecord I/O
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
 * FUNCTION:     freadGeometricProcessingRecord
 * DESCRIPTION:  Read a GeometricProcessing structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  GeometricProcessing structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadGeometricProcessingRecord(GeometricProcessing_Record *r, FILE *fp)
{
  int i;

  freadOptAxisDistancesRecord(&r->OptAxisDistances,fp);
  freadEarthModelRecord(&r->EarthModel,fp);
  for(i=0; i<12; i++) freadFloat((float *)&r->AtmosphericModel[i],360,fp);
  fread(&r->ResamplingFunctions,1,12,fp);
}


/************************************************************
 * FUNCTION:     fwriteGeometricProcessingRecord
 * DESCRIPTION:  Write a GeometricProcessing structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  GeometricProcessing structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteGeometricProcessingRecord(GeometricProcessing_Record *r, FILE *fp)
{
  int i;

  fwriteOptAxisDistancesRecord(&r->OptAxisDistances,fp);
  fwriteEarthModelRecord(&r->EarthModel,fp);
  for(i=0; i<12; i++) fwriteFloat((float *)&r->AtmosphericModel[i],360,fp);
  fwrite(&r->ResamplingFunctions,1,12,fp);
}

