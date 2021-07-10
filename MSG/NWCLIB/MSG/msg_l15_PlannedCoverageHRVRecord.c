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
 *  FILE        :       msg_l15_PlannedCoverageHRVRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 PlannedCoverageHRVRecord I/O
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
 * FUNCTION:     freadPlannedCoverageHRVRecord
 * DESCRIPTION:  Read a PlannedCoverageHRV structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  PlannedCoverageHRV structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadPlannedCoverageHRVRecord(PlannedCoverageHRV_Record *r, FILE *fp)
{
  freadUInt(&r->LowerSouthLinePlanned,1,fp);
  freadUInt(&r->LowerNorthLinePlanned,1,fp);
  freadUInt(&r->LowerEastColumnPlanned,1,fp);
  freadUInt(&r->LowerWestColumnPlanned,1,fp);
  freadUInt(&r->UpperSouthLinePlanned,1,fp);
  freadUInt(&r->UpperNorthLinePlanned,1,fp);
  freadUInt(&r->UpperEastColumnPlanned,1,fp);
  freadUInt(&r->UpperWestColumnPlanned,1,fp);
}


/************************************************************
 * FUNCTION:     fwritePlannedCoverageHRVRecord
 * DESCRIPTION:  Write a PlannedCoverageHRV structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  PlannedCoverageHRV structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwritePlannedCoverageHRVRecord(PlannedCoverageHRV_Record *r, FILE *fp)
{
  fwriteUInt(&r->LowerSouthLinePlanned,1,fp);
  fwriteUInt(&r->LowerNorthLinePlanned,1,fp);
  fwriteUInt(&r->LowerEastColumnPlanned,1,fp);
  fwriteUInt(&r->LowerWestColumnPlanned,1,fp);
  fwriteUInt(&r->UpperSouthLinePlanned,1,fp);
  fwriteUInt(&r->UpperNorthLinePlanned,1,fp);
  fwriteUInt(&r->UpperEastColumnPlanned,1,fp);
  fwriteUInt(&r->UpperWestColumnPlanned,1,fp);
}

