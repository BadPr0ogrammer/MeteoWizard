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
 *  FILE        :       msg_hrit_HRITHeader129.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       HRITHeader129 I/O
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
 * FUNCTION:     freadHRITHeader129
 * DESCRIPTION:  Read HRIT Header129
 * DATA IN:      fp: file
 * DATA OUT:     h:  header129 structure
 * COMMENT:      Allocate memory for h.Line_Quality_Entries
 *               for NL lines (header1.NL) before call this
 *               functions. Deallocate reserved memory when
 *               no further needed.
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadHRITHeader129(hrit_header129 *h, FILE *fp, int nl)
{
  int i;

  fread(&h->Header_Type,1,1,fp);
  freadUShort(&h->Header_Record_Length,1,fp);
  for(i=0; i<nl; i++)
    freadLineQualityRecord(&h->Line_Quality_Entries[i],fp);
}


/************************************************************
 * FUNCTION:     fwriteHRITHeader129
 * DESCRIPTION:  Write HRIT Header129
 * DATA IN:      fp: file
 *               h:  header129 structure
 * COMMENT:      Allocate memory for h.Line_Quality_Entries
 *               for NL lines (header1.NL) before call this
 *               functions. Deallocate reserved memory when
 *               no further needed.
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteHRITHeader129(hrit_header129 *h, FILE *fp, int nl)
{
  int i;

  fwrite(&h->Header_Type,1,1,fp);
  fwriteUShort(&h->Header_Record_Length,1,fp);
  for(i=0; i<nl; i++)
    fwriteLineQualityRecord(&h->Line_Quality_Entries[i],fp);
}


/************************************************************
 * FUNCTION:     fprintfHRITHeader129
 * DESCRIPTION:  Displays HRIT Header129 contents
 * DATA IN:      stream: output stream
 *               h:  header129 structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
fprintfHRITHeader129(FILE *stream, hrit_header129 *h, int nl)
{
  int i;
  char ch40[40];

  fprintf(stream,"---------HEADER TYPE #129------------\n");
  fprintf(stream,"Header_Type               %d\n",h->Header_Type);
  fprintf(stream,"Header_Record_Length      %d\n",h->Header_Record_Length);
  for(i=0; i<nl; i++) {
    sprintf(ch40,"LineQuality[%d]",i);
    fprintfLineQualityRecord(stream,&h->Line_Quality_Entries[i],ch40);
  }
  fprintf(stream,"\n");
}

