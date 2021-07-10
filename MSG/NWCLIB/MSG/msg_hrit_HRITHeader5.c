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
 *  FILE        :       msg_hrit_HRITHeader5.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       HRITHeader5 I/O
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
 * FUNCTION:     freadHRITHeader5
 * DESCRIPTION:  Read HRIT Header5
 * DATA IN:      fp: file
 * DATA OUT:     h:  header5 structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadHRITHeader5(hrit_header5 *h, FILE *fp)
{
  fread(&h->Header_Type,1,1,fp);
  freadUShort(&h->Header_Record_Length,1,fp);
  fread(&h->CDS_P_Field,1,1,fp);
  freadTimeCDSShort(&h->CDS_T_Field,fp);
}


/************************************************************
 * FUNCTION:     fwriteHRITHeader5
 * DESCRIPTION:  Write HRIT Header5
 * DATA IN:      fp: file
 *               h:  header5 structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteHRITHeader5(hrit_header5 *h, FILE *fp)
{
  fwrite(&h->Header_Type,1,1,fp);
  fwriteUShort(&h->Header_Record_Length,1,fp);
  fwrite(&h->CDS_P_Field,1,1,fp);
  fwriteTimeCDSShort(&h->CDS_T_Field,fp);
}


/************************************************************
 * FUNCTION:     fprintfHRITHeader5
 * DESCRIPTION:  Displays HRIT Header5 contents
 * DATA IN:      stream: output stream
 *               h:  header5 structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
fprintfHRITHeader5(FILE *stream, hrit_header5 *h)
{
  fprintf(stream,"---------HEADER TYPE #5------------\n");
  fprintf(stream,"Header_Type           %d\n",h->Header_Type);
  fprintf(stream,"Header_Record_Length  %d\n",h->Header_Record_Length);
  fprintf(stream,"CDS_P_Field           %d\n",h->CDS_P_Field);
  fprintfTimeCDSShort(stream,&h->CDS_T_Field,"CDS_T_Field");
  fprintf(stream,"\n");
}

