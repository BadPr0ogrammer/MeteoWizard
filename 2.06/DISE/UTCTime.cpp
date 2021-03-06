/*------------------------------------------------------------------------------------------
* Columbus Control Center
*
* Data Services Subsystem DaSS
*
* This software is developed by VCS AG under contract for DLR, contract no 6-057-2272.
* 
* The copyright in this document is vested VCS Nachrichtentechnik GmbH. This document may only be
* reproduced in whole or in part, or stored in a retrieval system, or transmitted in any form, or by any
* means electronic, mechanical, photocopying or otherwise, either with the prior permission of VCS AG
* or in accordance with the terms of DLR Contract no 6-057-2272.
*
*
--------------------------------------------------------------------------------------------
****  DaSS MODULE HEADER   ***

TYPE:			// to be added

PURPOSE:		// to be added

FUNCTION:		// to be added

INTERFACES:	// to be added

RESOURCES:		// to be added

PROCESSING:	// to be added

DATA:			// to be added

LOGIC:		// to be added

****  END MODULE HEADER   ***
------------------------------------------------------------------------------------------*/

#include "UTCTime.h"
#include "ErrorHandling.h"

// barh long -> long long

#ifdef WIN32
#include <time.h>

tm *localtime_r(const time_t *timep, tm *result)
{
  tm *tmp = localtime( timep );
  memcpy( result, tmp, sizeof( struct tm ) );
  return tmp;
}

#endif

#ifdef WIN32

#define _W32_FT_OFFSET (116444736000000000ULL)


int gettimeofday(struct timeval *tp, void * tzp)
 {
  union {
    unsigned long long ns100; /*time since 1 Jan 1601 in 100ns units */
    FILETIME ft;
  }  _now;

  if(tp)
    {
      GetSystemTimeAsFileTime (&_now.ft);
      tp->tv_usec=(long)((_now.ns100 / 10ULL) % 1000000ULL );
      tp->tv_sec= (long)((_now.ns100 - _W32_FT_OFFSET) / 10000000ULL);
    }
  /* Always return 0 as per Open Group Base Specifications Issue 6.
     Do not set errno on error.  */
  return 0;
}
#endif


Util::CUTCTime::CUTCTime()
{
}

Util::CUTCTime::CUTCTime(const CUTCTime& t)
{
    m_Time = t.m_Time;
}

Util::CUTCTime::CUTCTime(const timeval& t)
{
    m_Time = t.tv_sec * Util::CTimeSpan::Second()
                           + t.tv_usec * Util::CTimeSpan::Microsecond();
}

Util::CUTCTime::CUTCTime(int sec,
             int     min,
             int     hour,
             int     mday,
             int     mon,
             int     year)

  {
    try
    {
      year -= 1900;
      mon -= 1;
      tm  t={sec,min,hour,mday,mon,year};
      m_Time = mktime(&t) * Util::CTimeSpan::Second();
    }
    catch(...)
    {
     LOGCATCHANDTHROW
    }
  }


Util::CUTCTime::CUTCTime(
    int     sec,
    int     min,
    int     hour,
    int     mday,
    int     mon,
    int     year,
    int     wday,
    int     yday,
    int     isdst)
{
    try
    {
	year -= 1900;
	mon -= 1;
	tm  t={sec,min,hour,mday,mon,year,wday,yday,isdst};
	m_Time = mktime(&t) * Util::CTimeSpan::Second();
   }
    catch(...)
    {
	LOGCATCHANDTHROW
    }
} 

Util::CUTCTime::CUTCTime(const Util::CTimeSpan& t)
	:m_Time( t )
{
}


Util::CUTCTime Util::CUTCTime::Now()
{
      timeval tmp;
      gettimeofday( &tmp, NULL );
      return CUTCTime(tmp);
}

unsigned long Util::CUTCTime :: GetDayOfWeek() const
{
    try
    {
        long long sec =  m_Time/Util::CTimeSpan::Second();
        tm* t_Time = localtime( (time_t *) &sec );
        unsigned long l_Time =  t_Time->tm_wday;
        return l_Time;
    }
    catch(...)
    {
         LOGCATCHANDTHROW
    }
}

unsigned long Util::CUTCTime :: GetDayOfMonth() const
{
    try
    {
        long long sec =  m_Time/Util::CTimeSpan::Second();
        tm* t_Time = localtime( (time_t *)&sec );
        unsigned long l_Time =  t_Time->tm_mday;
        return l_Time;

    }
    catch(...)
    {
         LOGCATCHANDTHROW
    }
}

unsigned long Util::CUTCTime :: GetDayOfYear() const
{
    try
    {
        unsigned long l_Time;
        tm *t_Time;
        long long sec =  m_Time/Util::CTimeSpan::Second();
        t_Time = localtime( (time_t *) &sec );
        l_Time =  t_Time->tm_yday;
        return l_Time;

    }
    catch(...)
    {
         LOGCATCHANDTHROW
    }
}

unsigned long Util::CUTCTime :: GetMonth() const
{

    try
    {
        unsigned long l_Time;
        tm *t_Time;
        long long sec =  m_Time/Util::CTimeSpan::Second();
        t_Time = localtime((time_t *)&sec);
        l_Time =  t_Time->tm_mon+1;
        return l_Time;

    }
    catch(...)
    {
         LOGCATCHANDTHROW
    }

}

unsigned long Util::CUTCTime :: GetYear() const
{

    try
    {
        unsigned long l_Time;
        tm *t_Time;
        long long sec =  m_Time/Util::CTimeSpan::Second();
        t_Time = localtime((time_t *)&sec);
        l_Time =  t_Time->tm_year + 1900;
        return l_Time;
    }
    catch(...)
    {
         LOGCATCHANDTHROW
    }

}


unsigned long Util::CUTCTime ::GetHour() const
{

    try
    {
	unsigned long long hoursPlusRemainder = m_Time / Util::CTimeSpan::Hour();
	// remove     
	unsigned long hour = hoursPlusRemainder % 24 ;   
	return hour;    
    }
    catch(...)
    {
         LOGCATCHANDTHROW
    }

}

unsigned long Util::CUTCTime::GetMinuteOfHour() const
{

    try
    {
	unsigned long long minutePlusRemainder = m_Time / Util::CTimeSpan::Minute();
	// remove     
	unsigned long m = minutePlusRemainder % 60 ;   
	return m;    
    }
    catch(...)
    {
         LOGCATCHANDTHROW
    }

}

unsigned long Util::CUTCTime::GetSecondOfMinute() const
{

    try
    {
	unsigned long long sPlusRemainder = m_Time / Util::CTimeSpan::Second();
	// remove     
	unsigned long m = sPlusRemainder % 60 ;   
	return m;    
    }
    catch(...)
    {
         LOGCATCHANDTHROW
    }

}


unsigned long Util::CUTCTime::GetMilliSecondOfSecond() const
{

    try
    {
	unsigned long long sPlusRemainder = m_Time / Util::CTimeSpan::Millisecond();
	// remove     
	unsigned long m = sPlusRemainder % 1000 ;   
	return m;    
    }
    catch(...)
    {
         LOGCATCHANDTHROW
    }

}

#include <time.h>

std::string Util::CUTCTime::Format(const std::string& Spec)
{
    try
    {
    std::string time(64,'0');
	char tmp[64];
	memset( tmp, '0', 64 );
    struct tm tm;
    long long sec =  m_Time/Util::CTimeSpan::Second();
    // barh ::localtimer_(&sec, &tm);
	localtime_r((time_t *) &sec, &tm);

    size_t ret=strftime( tmp ,64, Spec.c_str(),&tm);
    if(ret == 0) return std::string("Format time failed");

	time = tmp;
    return time.substr(0,ret);
    }
    catch(...)
    {
        LOGCATCHANDTHROW
    }
}

Util::CTimeSpan Util::CUTCTime::operator - ( const CUTCTime& other )const
{
      return (m_Time - other.m_Time);
}

bool Util::CUTCTime::operator == (const CUTCTime& t ) const
{
   return m_Time == t.m_Time;
}

bool Util::CUTCTime::operator < (const CUTCTime& t ) const
{
    return (m_Time < t.m_Time);
}

bool Util::CUTCTime::operator <= (const CUTCTime& t ) const
{
    return (m_Time <= t.m_Time);
}

Util::CUTCTime Util::CUTCTime::operator + (const Util::CTimeSpan& t ) const
{
        CUTCTime result;
        result.m_Time = m_Time + t;
        return result;
}

Util::CUTCTime Util::CUTCTime::operator - (const Util::CTimeSpan& t ) const
{
    try{
      CUTCTime result;
      result.m_Time = m_Time - t;
      return result;
    }
    catch(...)
    {
        LOGCATCHANDTHROW
    }
}

unsigned long long  Util::CUTCTime::operator/( const CTimeSpan& d ) const
{
    return m_Time/d;
}

/*Util::CUTCTime  Util::CUTCTime::operator/( unsigned int d ) const
{
    CUTCTime result;
    result.m_Time = m_Time / d;
    return result;
} */

