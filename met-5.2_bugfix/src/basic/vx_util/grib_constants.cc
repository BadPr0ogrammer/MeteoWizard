// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2016
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

using namespace std;

///////////////////////////////////////////////////////////////////////////////

#include <cctype>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cmath>

#include "grib_constants.h"

///////////////////////////////////////////////////////////////////////////////

bool is_precip_grib_code(int gc) {
   bool match = false;

   //
   // Check whether this grib code is a precipitation type:
   //    - precipitation rate
   //    - thunderstorm probability
   //    - total precipitation
   //    - large scale precipitation
   //    - convective precipitation
   //
   if(gc == prate_grib_code || gc == tstm_grib_code  ||
      gc == apcp_grib_code  || gc == ncpcp_grib_code ||
      gc == acpcp_grib_code) match = true;

   return(match);
}

///////////////////////////////////////////////////////////////////////////////
