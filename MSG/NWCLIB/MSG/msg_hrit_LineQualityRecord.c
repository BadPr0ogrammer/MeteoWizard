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
 *  FILE        :       msg_hrit_LineQualityRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       LineQualityRecord I/O
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
#include <string.h>
#include "msg_hrit.h"


/************************************************************
 * FUNCTION:     freadLineQualityRecord
 * DESCRIPTION:  Read a LineQualityRecord structure
 * DATA IN:      fp: file
 * DATA OUT:     l:  LineQualityRecord
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
freadLineQualityRecord(Line_Quality_Record *l, FILE *fp)
{
  freadUInt(&l->Line_Number_in_Grid,1,fp);
  freadTimeCDSShort(&l->Line_Mean_Acquisition,fp);
  fread(&l->Line_Validity,1,1,fp);
  fread(&l->Line_Radiometric_Quality,1,1,fp);
  fread(&l->Line_Geometric_Quality,1,1,fp);
}


/************************************************************
 * FUNCTION:     fwriteLineQualityRecord
 * DESCRIPTION:  Write a LineQualityRecord structure
 * DATA IN:      fp: file
 *               l:  LineQualityRecord
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
fwriteLineQualityRecord(Line_Quality_Record *l, FILE *fp)
{
  fwriteUInt(&l->Line_Number_in_Grid,1,fp);
  fwriteTimeCDSShort(&l->Line_Mean_Acquisition,fp);
  fwrite(&l->Line_Validity,1,1,fp);
  fwrite(&l->Line_Radiometric_Quality,1,1,fp);
  fwrite(&l->Line_Geometric_Quality,1,1,fp);
}


/************************************************************
 * FUNCTION:     fprintfLineQualityRecord
 * DESCRIPTION:  Displays a LineQualityRecord contents
 * DATA IN:      stream: output stream
 *               l:      LineQualityRecord
 *               label:  Text for the parent structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
fprintfLineQualityRecord(FILE *stream, Line_Quality_Record *l, char *label)
{
  char ch80[80];

  fprintf(stream,"%s.Line_Number_in_Grid      %d\n",
          label,l->Line_Number_in_Grid);
  sprintf(ch80,"%s.Line_Mean_Acquisition",label);
  fprintfTimeCDSShort(stream,&l->Line_Mean_Acquisition,ch80);
  fprintf(stream,"%s.Line_Validity            %d\n",
          label,l->Line_Validity);
  fprintf(stream,"%s.Line_Radiometric_Quality %d\n",
          label,l->Line_Radiometric_Quality);
  fprintf(stream,"%s.Line_Geometric_Quality   %d\n",
          label,l->Line_Geometric_Quality);
}

