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
 *  FILE        :       msg_l15_ProjectionDescriptionRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 ProjectionDescriptionRecord I/O
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
 * FUNCTION:     freadProjectionDescriptionRecord
 * DESCRIPTION:  Read a ProjectionDescription structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  ProjectionDescription  structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadProjectionDescriptionRecord(ProjectionDescription_Record *r, FILE *fp)
{
  fread(&r->TypeOfProjection,1,1,fp);
  freadFloat(&r->LongitudeOfSSP,1,fp);
}


/************************************************************
 * FUNCTION:     fwriteProjectionDescriptionRecord
 * DESCRIPTION:  Write a ProjectionDescription structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  ProjectionDescription  structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteProjectionDescriptionRecord(ProjectionDescription_Record *r, FILE *fp)
{
  fwrite(&r->TypeOfProjection,1,1,fp);
  fwriteFloat(&r->LongitudeOfSSP,1,fp);
}

