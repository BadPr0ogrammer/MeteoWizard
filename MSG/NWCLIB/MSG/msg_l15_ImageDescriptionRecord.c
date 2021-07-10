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
 *  FILE        :       msg_l15_ImageDescriptionRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 ImageDescriptionRecord I/O
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
 * FUNCTION:     freadImageDescriptionRecord
 * DESCRIPTION:  Read a ImageDescription structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  ImageDescription structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadImageDescriptionRecord(ImageDescription_Record *r, FILE *fp)
{
  freadProjectionDescriptionRecord(&r->ProjectionDescription,fp);
  freadReferenceGridRecord(&r->ReferenceGridVIS_IR,fp);
  freadReferenceGridRecord(&r->ReferenceGridHRV,fp);
  freadPlannedCoverageVIS_IRRecord(&r->PlannedCoverageVIS_IR,fp);
  freadPlannedCoverageHRVRecord(&r->PlannedCoverageHRV,fp);
  freadLevel1_5ImageProductionRecord(&r->Level1_5ImageProduction,fp);
}


/************************************************************
 * FUNCTION:     fwriteImageDescriptionRecord
 * DESCRIPTION:  Write a ImageDescription structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  ImageDescription structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteImageDescriptionRecord(ImageDescription_Record *r, FILE *fp)
{
  fwriteProjectionDescriptionRecord(&r->ProjectionDescription,fp);
  fwriteReferenceGridRecord(&r->ReferenceGridVIS_IR,fp);
  fwriteReferenceGridRecord(&r->ReferenceGridHRV,fp);
  fwritePlannedCoverageVIS_IRRecord(&r->PlannedCoverageVIS_IR,fp);
  fwritePlannedCoverageHRVRecord(&r->PlannedCoverageHRV,fp);
  fwriteLevel1_5ImageProductionRecord(&r->Level1_5ImageProduction,fp);
}

