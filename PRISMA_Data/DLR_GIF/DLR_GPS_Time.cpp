//------------------------------------------------------------------------------
//
// DLR_GPS_Time.cpp
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
//   2003/01/28  OMO  Added (non-)equality test operator
//   2006/03/01  SDA  Modified for PRISMA flight software
//   2006/03/10  MGF  Added Methods CUCintsec() and CUCmusec()
//   2006/03/13  EG   Renamed define and introduced namespace
//   2006/03/19  SDA  Applied changes of 2006/03/10 and 2006/03/13 to same file
//   2006/06/07  SDA  Removed unnecessary methods (Date,fracOf,dayOf)
//   2006/07/10  SDA  Renamed fracsec to musec (OM review)
//   2006/07/10  SDA  Removed unused items: >=, !=, -= (OM review)
//   2007/07/10  SDA  Moved CUC_TIME_RES constant to DLR_GPS_Time.cpp
//                    Removed #include "DLR_SAT_Const.h"
//   2007/09/26  SDA  CUC_TIME_RES constant moved into namespace
//   2008/24/01  SDA  Modified implementation of CUCmusec to decrease numerical errors
//   2008/03/04  JSA  More robust implementation of CUCmusec, CUCintsec, comparison
//                    and difference operators in presence of numerical errors
//   2008/03/05  SDA  Added comments and re-formatted style
//   2008/11/13  SDA  Corrected constructor for CUC representation.
//                    Unsigned int used instead of int!
//
//
// (c) 2009 DLR/GSOC
//
//------------------------------------------------------------------------------

#include <cmath>

#include "DLR_GPS_Time.h"

namespace rtn {

  const double  CUC_TIME_RES  = 1E-6;       // GPS time resolution in CUC format

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

  // CUC representation of the GPS time 

  GPStime::GPStime(unsigned int intsec, unsigned int musec) {

    double dw = floor((double)(intsec/604800));
    GPSweek   = (int)(dw);
    double ds = (double)(intsec - (GPSweek*604800));
    GPSsecs   = ds + ((double)musec)*CUC_TIME_RES;     // [0s,604800s[

  }

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

  double GPStime::MJD() const {
    return 44244 + 7*GPSweek + GPSsecs/86400.0;
  }

  unsigned int    GPStime::CUCintsec()  const{
    // CUC: Int secs since 6th Jan. 1980
    // return  (unsigned int)(GPSweek*604800.0+floor(GPSsecs)) ;
    // More robust implementation in presence of numerical errors
      unsigned int sec = (unsigned int)(GPSweek*604800.0+floor(GPSsecs));
      if ((unsigned int)(floor( ((GPSsecs-floor(GPSsecs))/CUC_TIME_RES)+0.5 )) == 1e6)
        sec++;
      return sec;      
  };

  unsigned int    GPStime::CUCmusec() const{
    // CUC: Micro seconds.
    // The following implementation has been modified because of the associated
    // numerical errors. The maximum numerical errors is estimated as 6e-5 musec.
    // Thus a more robust implementation adopts round(x)=floor(x+0.5).
    // return  (unsigned int)((GPSsecs-floor(GPSsecs))/CUC_TIME_RES)  ;
    // More robust implementation in presence of numerical errors
    unsigned int msec = (unsigned int)(floor( ((GPSsecs-floor(GPSsecs))/CUC_TIME_RES)+0.5 ))  ;
    if (msec == 1e6)
      msec=0;
    return msec;
  };

  // Comparison

  bool operator <  (const GPStime& left, const GPStime& right) {
    // More robust implementation in presence of numerical errors
    double diff = left.GPSsecs-right.GPSsecs;
    diff        = floor(diff/CUC_TIME_RES+0.5)*CUC_TIME_RES;
    return ( (left.GPSweek<right.GPSweek)  ||
             (left.GPSweek==right.GPSweek) && (diff<0.0) );
  };
  bool operator >  (const GPStime& left, const GPStime& right) {
    // More robust implementation in presence of numerical errors
    double diff = left.GPSsecs-right.GPSsecs;
    diff        = floor(diff/CUC_TIME_RES+0.5)*CUC_TIME_RES;
    return ( (left.GPSweek>right.GPSweek)  ||
             (left.GPSweek==right.GPSweek) && (diff>0.0) );
  };
  bool operator <= (const GPStime& left, const GPStime& right) {
    // More robust implementation in presence of numerical errors
    double diff = left.GPSsecs-right.GPSsecs;
    diff        = floor(diff/CUC_TIME_RES+0.5)*CUC_TIME_RES;
    return ( (left.GPSweek<right.GPSweek)  ||
             (left.GPSweek==right.GPSweek) && (diff<=0.0) );
  };
  bool operator == (const GPStime& left, const GPStime& right) {
    // More robust implementation in presence of numerical errors
    double diff = left.GPSsecs-right.GPSsecs;
    diff        = floor(diff/CUC_TIME_RES+0.5)*CUC_TIME_RES;
    return ( (left.GPSweek==right.GPSweek) && (diff==0.0) );
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
    // More robust implementation in presence of numerical errors
    double diff =(left.GPSweek-right.GPSweek)*604800.0 + (left.GPSsecs-right.GPSsecs);
    return floor(diff/CUC_TIME_RES+0.5)*CUC_TIME_RES;
  }
}; // End of namespace rtn


