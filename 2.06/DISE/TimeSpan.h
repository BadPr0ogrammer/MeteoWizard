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


#ifndef _TIME_SPAN_H
#define _TIME_SPAN_H

// #include <sys/time.h>
#include <time.h>

#include <string>

namespace dass {
    class CCSDSUTime;
};

namespace Util
{
    class CUTCTime;

/**
 * timespan class
 *
**/
class CTimeSpan
{
 public:

/**
 *constructor
 *
 * @param SpanSec seconds part of the timespan
 * @param SpanMSec micro seconds part of the timespan
 * @returns
 * 'to provide: return type + comment
**/
    CTimeSpan():m_Nanoseconds(0){};
/**
  * copy constructor
  */
    CTimeSpan(const CTimeSpan& t);

  /**
 *'destructor
**/
    ~CTimeSpan(){};
/**
 * multiplier to convert milliseconds to microseconds
 *
**/
   /** Zero time */
    static CTimeSpan Zero() { return CTimeSpan(); }

    static CTimeSpan Nanosecond() { CTimeSpan result; result.m_Nanoseconds = 1; return result; }

    /** One Microsecond */
    static CTimeSpan Microsecond() { return Nanosecond() * 1000; }

    /** One Millisecond */
    static CTimeSpan Millisecond() { return Microsecond() * 1000; }

    /** One Second */
    static CTimeSpan Second() { return Millisecond() * 1000; }

    /** One Minute */
    static CTimeSpan Minute() { return Second() * 60; }

    /** One Hour */
    static CTimeSpan Hour() { return Second() * 3600; }

    /** One Day */
    static CTimeSpan Day() { return Second() * 24 * 3600; }

/**
 * return the seconds
 * @returns
 * timespan seconds
**/
    /** unsigned long  GetSecondPart() const {return m_Time.tv_sec;};**/
/**
 * return the microseconds
 * @returns
 * timespan micro-seconds
**/
    /**unsigned long  GetMicroSecPart() const {return  m_Time.tv_usec;}**/

    bool operator ==( const CTimeSpan& other ) const
    {
       return m_Nanoseconds == other.m_Nanoseconds ;
    }

    bool operator!=( const CTimeSpan& other ) const
    {
       return m_Nanoseconds != other.m_Nanoseconds;
    }

    bool operator<( const CTimeSpan& other ) const
    {
        return (m_Nanoseconds < other.m_Nanoseconds);
    }

    bool operator>( const CTimeSpan& other ) const
    {
        return (m_Nanoseconds > other.m_Nanoseconds);
    }

    bool operator<=( const CTimeSpan& other ) const
    {
        return (m_Nanoseconds <= other.m_Nanoseconds);
    }
    bool operator>=( const CTimeSpan& other ) const
    {
        return (m_Nanoseconds >= other.m_Nanoseconds);
    }

/**
  * get a new timespan by adding a timespan
  */
    CTimeSpan operator + (const CTimeSpan& ts ) const;

/**
  * get a new UTCTime by adding a UTCTime object
  */
    CUTCTime operator + (const CUTCTime& t ) const;

/**
  * get a new timespan by substract a timespan
  */
    CTimeSpan operator - (const CTimeSpan& ts ) const;

/**
  * get a new timespan by multiplication of an integer
  */
    CTimeSpan operator * ( int mul ) const;

/**
  * get a new timespan by multiplication of a float
  */
    CTimeSpan operator * ( float mul ) const;

/**
  * divided by an integer get a new timespan
  */
    CTimeSpan operator / ( int div ) const;

/**
  * divided by a timespan get a new timespan
  */
    unsigned long long operator / ( const CTimeSpan& ts  ) const;

    CTimeSpan operator % ( const CTimeSpan& ts  ) const;
    
    
    /** 
    access function
    */
    unsigned long long getNanoseconds() const
    {
	    return m_Nanoseconds;
    }

private:
    friend class CUTCTime;
    friend class dass::CCSDSUTime;

/**
  * store the timespan
  */
   unsigned long long m_Nanoseconds;

};

/**
  * an integer multiply a timespan get a new timespan
  */
   inline CTimeSpan operator*( unsigned int i, const CTimeSpan& v ) { return v * int(i); }

} 

#endif
