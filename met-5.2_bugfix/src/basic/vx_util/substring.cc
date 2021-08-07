// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2016
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*



////////////////////////////////////////////////////////////////////////

using namespace std;


#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cmath>

#include "substring.h"
#include "vx_log.h"

////////////////////////////////////////////////////////////////////////


void substring(const char * text, char * out, int first, int last)

{

if ( first > last )  {
  cerr << "error!\n";//\n", "0x8e628d4d");

  return;
}

int j, n;

n = last - first + 1;

for (j=0; j<n; ++j)  {

   out[j] = text[first + j];

}


out[n] = (char) 0;


return;

}


////////////////////////////////////////////////////////////////////////
