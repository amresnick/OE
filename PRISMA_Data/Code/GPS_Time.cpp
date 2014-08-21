//------------------------------------------------------------------------------
//
// GPS_Time.cpp
//
// Purpose:
//
//   GPS time handling
//
// References:
//
//   van Flandern T.C., Pulkinnen K.F.; Low-Precision Formulae for
//     Planetary Positions; Astrophys. Journ. Suppl. vol. 41, pp. 391 (1979)
//   ICD-GPS-200; Navstar GPS Space Segment / Navigation User Interfaces;
//     Revison C; 25 Sept. 1997; Arinc Research Corp., El Segundo (1997).
//
// Note:
//
//   All calendar functions are presently valid only 
//   from 1901 March 1.0 to 2100 Feb. 28.0
//
// Last modified:
//
//   2000/08/19  OMO  Created
//   2000/12/03  OMO  Fixed += operator
//   2001/09/04  OMO  Added MJD function
//   2002/12/31  OMO  New min/max values
//   2003/01/06  OMO  Added relational operators
//   2003/01/24  RKR  Added dayOfYear function.
//   2003/01/28  RKR  Simplified algorithm for dayOfYear computation
//   2003/01/28  OMO  Added (non-)equality tset operator
//   2009/08/13  OMO  Added year(), month(), day() methods
//   
// (c) DLR/GSOC
//
//------------------------------------------------------------------------------

#include <cmath>
#include <iostream>

#include "GPS_Time.h"


using namespace std;



//------------------------------------------------------------------------------
//
// GPStime class (implementation)
//
// Purpose:
//
//   Representation of time in terms of GPS week and seconds of week.
//
//   The GPS week count starts at 1980 Jan 6.0 (week=0); days within a week are
//   counted from 0 (=Sunday) to 6 (=Saturday); seconds within a week are
//   counted from 0.0 to 604800.0.
//
//------------------------------------------------------------------------------

// Limits

const GPStime GPStime::min = GPStime(1901, 3, 1);
const GPStime GPStime::max = GPStime(2100, 2,28);

// Constructor (ensuring a normalized internal representation)

GPStime::GPStime(int week, double secs) {
  double dw = floor(secs/604800.0);
  GPSweek = week + (int) dw;
  GPSsecs = secs - 604800.0*dw;     // [0s,604800s[
}

// GPS time from calendar date (valid from 1901 March 1.0 to 2100 Feb. 28.0)

GPStime::GPStime(int year, int month, int day, int hour, int min, double sec) {

  long  d = 367L*year-7*(year+((month+9)/12))/4+((275*month)/9)+day-723231L;

  GPSweek = (int)floor(d/7.0);
  GPSsecs = 86400.0*(d-7*GPSweek) + 3600.0*hour+60.0*min+sec;

}

// Calendar date
// (valid from 1901 March 1.0 to 2100 Feb. 28.0)

void GPStime::Date ( int& year, int& month, int& day ) const {

  // Convert Julian day number to calendar date

  long c = long(7*GPSweek+floor(GPSsecs/86400.0)+2444245.0) + 1537;
  long d = long ( (c-122.1)/365.25 );
  long e = 365*d + d/4;
  long f = long ( (c-e)/30.6001 );

  day   = c - e - int(30.6001*f);
  month = f - 1 - 12*(f/14);
  year  = d - 4715 - ((7+month)/10);

}

int GPStime::year() const {
  int y,m,d;
  Date(y,m,d);
  return y;
};

int GPStime::month() const {
  int y,m,d;
  Date(y,m,d);
  return m;
};

int GPStime::day() const {
  int y,m,d;
  Date(y,m,d);
  return d;
};

// Time of day

int    GPStime::hour()   const {
  return  ((int)(GPSsecs/3600.0))%24;
}

int    GPStime::minute() const {
  return  ((int)(GPSsecs/60.0))%60;
}

double GPStime::second() const {
  return  GPSsecs - 60.0*floor(GPSsecs/60.0);
}

int    GPStime::MJD0()   const {
  return  44244 + 7*GPSweek + (int)(GPSsecs/86400.0);
}

double GPStime::fracOfDay() const {
  double d=GPSsecs/86400.0;
  return d-floor(d);
}

double GPStime::MJD() const {
  return 44244 + 7*GPSweek + GPSsecs/86400.0;
}

int    GPStime::dayOfWeek() const {
  return (int)(GPSsecs/86400.0);
}

// Day of Year
// (valid from 1901 March 1.0 to 2100 Feb. 28.0)

int    GPStime::dayOfYear() const {

  int doy;
/*
  int year,month,day;
  // Generic algorithm (slightly bulky)
  Date(year,month,day);
  doy = MJD0() - GPStime(year,1,0).MJD0();
*/
  double y;
  int    d;
  // Simplified code for years 1900-2100
  d   = MJD0()-16480;                // Days since 1904 Jan 1.0
  y   = floor(d/365.25);             // Years since 1904
  doy = d-(int)floor(365.25*y);      // Day of year
  if ((int)y%4==0) doy+=1;
  
  return doy;

}


// Comparison

bool operator <  (const GPStime& left, const GPStime& right) {
  return ( (left.GPSweek<right.GPSweek)  ||
           (left.GPSweek==right.GPSweek) && (left.GPSsecs<right.GPSsecs) );
};
bool operator >  (const GPStime& left, const GPStime& right) {
  return ( (left.GPSweek>right.GPSweek)  ||
           (left.GPSweek==right.GPSweek) && (left.GPSsecs>right.GPSsecs) );
};
bool operator <= (const GPStime& left, const GPStime& right) {
  return ( (left.GPSweek<right.GPSweek)  ||
           (left.GPSweek==right.GPSweek) && (left.GPSsecs<=right.GPSsecs) );
};
bool operator >= (const GPStime& left, const GPStime& right) {
  return ( (left.GPSweek>right.GPSweek)  ||
           (left.GPSweek==right.GPSweek) && (left.GPSsecs>=right.GPSsecs) );
};
bool operator == (const GPStime& left, const GPStime& right) {
  return ( (left.GPSweek==right.GPSweek) && (left.GPSsecs==right.GPSsecs) );
};
bool operator != (const GPStime& left, const GPStime& right) {
  return ( (left.GPSweek!=right.GPSweek) || (left.GPSsecs!=right.GPSsecs) );
};

// Time increment and addition

void GPStime::operator += (double dt) {
  double dw = floor((GPSsecs+dt)/604800.0);
  GPSweek += (int) dw;
  GPSsecs += dt - 604800.0*dw;
}

GPStime operator + (const GPStime& left, double right) {
  GPStime t(left);
  t += right;
  return t;
}

// Time difference [s]

double  operator - (const GPStime& left, const GPStime& right) {
  return (left.GPSweek-right.GPSweek)*604800.0 + (left.GPSsecs-right.GPSsecs);
}
