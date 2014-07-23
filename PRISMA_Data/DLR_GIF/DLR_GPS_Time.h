//------------------------------------------------------------------------------
//
// DLR_GPS_Time.h
// 
// Purpose: 
//
//   GPS time handling
//
// References:
//
//   ICD-GPS-200; Navstar GPS Space Segment / Navigation User Interfaces;
//     Revison C; 25 Sept. 1997; Arinc Research Corp., El Segundo (1997).
//
// Last modified:
//
//   2000/08/19  OMO  Created
//   2001/03/05  OMO  Removed invalid namespace statement
//   2001/08/19  OMO  Added MJD function 
//   2002/12/22  OMO  Default hour, min, sec in GPStime constructor
//   2002/12/31  OMO  New min/max values
//   2003/01/06  OMO  Added relational operators
//   2003/01/24  RKR  Added dayOfYear function.
//   2003/01/28  OMO  Added (non-)equality tset operator
//   2003/03/01  SDA  Modified for PRISMA flight software
//   2006/03/10  MGF  Added Methods CUCintsec() and CUCmusec()
//   2006/03/13  EG   Renamed define and introduced namespace
//   2006/03/19  SDA  Applied changes of 2006/03/10 and 2006/03/13 to same file
//   2006/06/07  SDA  Removed unnecessary methods (Date,fracOf,dayOf)
//   2006/07/10  SDA  Renamed fracsec to musec (OM review)
//   2006/07/10  SDA  Removed unused items: >=, !=, -= (OM review)
//   2008/11/10  SDF  Deleted commented lines for unused operators
//   2008/11/13  SDA  Corrected constructor for CUC representation.
//                    Unsigned int used instead of int!
//   
// (c) 2009 DLR/GSOC
//
//------------------------------------------------------------------------------


#ifndef INC_DLR_GPS_TIME_H
#define INC_DLR_GPS_TIME_H

namespace rtn {

  //------------------------------------------------------------------------------
  //
  // GPStime class
  // 
  // Purpose:
  // 
  //   Representation of time in terms of GPS week and seconds of week
  //
  //   The GPS week count starts at 1980 Jan 6.0 (week=0); days within a week are
  //   counted from 0 (=Sunday) to 6 (=Saturday); seconds within a week are
  //   counted from 0.0 to 604800.0. 
  //
  //------------------------------------------------------------------------------

  class GPStime {

  public:

    // Limits
    static const GPStime min;  // 1901/03/01 
    static const GPStime max;  // 2100/02/28

    // Constructors (ensuring a normalized internal representation)
    GPStime() : GPSweek(0), GPSsecs(0) {}; 
    GPStime(int week, double secs);

    // GPS time from calendar date 
    // (valid from 1901 March 1.0 to 2100 Feb. 28.0)
    GPStime(int year, int month, int day, 
            int hour=0, int min=0, double sec=0.0);

    // GPS time CUC representation
    GPStime(unsigned int intsec, unsigned int musec);

    // Component access
    int    week() const { return GPSweek;};
    double secs() const { return GPSsecs;};

    // Date and time
    int             hour()      const;         // Hour of day
    int             minute()    const;         // Minute of hour
    double          second()    const;         // Seconds of minute
    int             MJD0()      const;         // Modified Julian Date at start of day
    double          MJD()       const;         // Modified Julian Date
    unsigned int    CUCintsec() const;         // CUC: Int secs since 6th Jan. 1980
    unsigned int    CUCmusec()  const;         // CUC: Micro seconds

    // Comparison
    friend bool operator <  (const GPStime& left, const GPStime& right);
    friend bool operator >  (const GPStime& left, const GPStime& right);
    friend bool operator <= (const GPStime& left, const GPStime& right);
    friend bool operator == (const GPStime& left, const GPStime& right);

    // Time increment/decrement [s] 
    void operator += (double dt);

    // Addition/subtraction of times
    friend GPStime operator + (const GPStime& left, double right);    
    friend GPStime operator - (const GPStime& left, double right){
      return left+(-right);
    };    

    // Time difference [s]
    friend double  operator - (const GPStime& left, const GPStime& right);    

  private:

    // Elements
    int     GPSweek;   // GPS week count, week 0 starts at 1980/01/06.0 GPS time
    double  GPSsecs;   // GPS seconds of week ([0s,604800s[)

  };

}; // End namespace 

#endif  // include blocker



