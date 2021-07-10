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
 *  FILE        :       msg_l15_OptAxisDistancesRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 OptAxisDistancesRecord I/O
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
 * FUNCTION:     freadOptAxisDistancesRecord
 * DESCRIPTION:  Read a OptAxisDistances structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  OptAxisDistances structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadOptAxisDistancesRecord(OptAxisDistances_Record *r, FILE *fp)
{
  freadFloat((float *)&r->E_WFocalPlane,42,fp);
  freadFloat((float *)&r->N_SFocalPlane,42,fp);
}


/************************************************************
 * FUNCTION:     fwriteOptAxisDistancesRecord
 * DESCRIPTION:  Write a OptAxisDistances structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  OptAxisDistances structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteOptAxisDistancesRecord(OptAxisDistances_Record *r, FILE *fp)
{
  fwriteFloat((float *)&r->E_WFocalPlane,42,fp);
  fwriteFloat((float *)&r->N_SFocalPlane,42,fp);
}

