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
#include <cstdio>
#include <cmath>

#include "vx_cal.h"
#include "vx_log.h"


////////////////////////////////////////////////////////////////////////


unixtime string_to_unixtime(const char * s)

{

unixtime t;
int j;

j = sscanf(s, "%lld", &t);

if ( j != 1 )  {

   cerr 
        << "string_to_unixtime(const char *) -> unable to parse input string \""
        << s << "\"\n\n";

   exit ( 1 );

}

return ( t );

}


////////////////////////////////////////////////////////////////////////


ConcatString unixtime_to_string(const unixtime t)

{

char junk[256];

snprintf(junk, sizeof(junk), "%lld", t);

return ( ConcatString(junk) );

}


////////////////////////////////////////////////////////////////////////



