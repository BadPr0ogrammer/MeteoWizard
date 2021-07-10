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
 *  FILE        :       msg_hrit_HRITHeader4.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       HRITHeader4 I/O
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
 * FUNCTION:     freadHRITHeader4
 * DESCRIPTION:  Read HRIT Header4
 * DATA IN:      fp: file
 * DATA OUT:     h:  header4 structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadHRITHeader4(hrit_header4 *h, FILE *fp)
{
  fread(&h->Header_Type,1,1,fp);
  freadUShort(&h->Header_Record_Length,1,fp);
  fread(&h->Annotation_Text,61,1,fp);
}


/************************************************************
 * FUNCTION:     fwriteHRITHeader4
 * DESCRIPTION:  Write HRIT Header4
 * DATA IN:      fp: file
 *               h:  header4 structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteHRITHeader4(hrit_header4 *h, FILE *fp)
{
  fwrite(&h->Header_Type,1,1,fp);
  fwriteUShort(&h->Header_Record_Length,1,fp);
  fwrite(&h->Annotation_Text,61,1,fp);
}


/************************************************************
 * FUNCTION:     fprintfHRITHeader4
 * DESCRIPTION:  Displays HRIT Header4 contents
 * DATA IN:      stream: output stream
 *               h:  header4 structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
fprintfHRITHeader4(FILE *stream, hrit_header4 *h)
{
  char ch62[62];
  strncpy(ch62,h->Annotation_Text,61);
  ch62[61]=0;

  fprintf(stream,"---------HEADER TYPE #4------------\n");
  fprintf(stream,"Header_Type          %d\n",h->Header_Type);
  fprintf(stream,"Header_Record_Length %d\n",h->Header_Record_Length);
  fprintf(stream,"Annotation_Text      %s\n",ch62);
  fprintf(stream,"\n");
}

