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
 *  FILE        :       msg_l15_RadiometricProcessingRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 RadiometricProcessingRecord I/O
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
 * FUNCTION:     freadRadiometricProcessingRecord
 * DESCRIPTION:  Read a RadiometricProcessing structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  RadiometricProcessing structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadRadiometricProcessingRecord(RadiometricProcessing_Record *r, FILE *fp)
{
  int i,j;
  float *a;

  freadRPSummaryRecord(&r->RPSummary,fp);
  for(i=0; i<12; i++)
    freadLevel1_5ImageCalibrationRecord(&r->Level1_5ImageCalibration[i],fp);
  freadBlackBodyDataUsedRecord(&r->BlackBodyDataUsed,fp);
  freadMPEFCalFeedBack(&r->IMPF_CAL_Data,fp);
  for(i=0; i<42; i++) freadFloat((float *)&r->RadTransform[i],64,fp);
  freadRadProcMTFAdaptationRecord(&r->RadProcMTFAdaptation,fp);
  for(i=0; i<12; i++)
    for(j=0; j<8; j++) freadFloat((float *)&r->StraylightCorrection[i][j],8,fp);
}


/************************************************************
 * FUNCTION:     fwriteRadiometricProcessingRecord
 * DESCRIPTION:  Write a RadiometricProcessing structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  RadiometricProcessing structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteRadiometricProcessingRecord(RadiometricProcessing_Record *r, FILE *fp)
{
  int i,j;

  fwriteRPSummaryRecord(&r->RPSummary,fp);
  for(i=0; i<12; i++)
    fwriteLevel1_5ImageCalibrationRecord(&r->Level1_5ImageCalibration[i],fp);
  fwriteBlackBodyDataUsedRecord(&r->BlackBodyDataUsed,fp);
  fwriteMPEFCalFeedBack(&r->IMPF_CAL_Data,fp);
  for(i=0; i<42; i++) fwriteFloat((float *)&r->RadTransform[i],64,fp);
  fwriteRadProcMTFAdaptationRecord(&r->RadProcMTFAdaptation,fp);
  for(i=0; i<12; i++)
    for(j=0; j<8; j++)
      fwriteFloat((float *)&r->StraylightCorrection[i][j],8,fp);
}

