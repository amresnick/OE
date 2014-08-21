//------------------------------------------------------------------------------
//
// GPS_Time.h
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
//   2003/01/28  OMO  Added (non-)equality test operator
//   2009/08/13  OMO  Added year(), month(), day() methods
//   
// (c) DLR/GSOC
//
//------------------------------------------------------------------------------


#ifndef INC_GPS_TIME_H
#define INC_GPS_TIME_H


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

    // Component access
    int    week() const { return GPSweek;};
    double secs() const { return GPSsecs;};

    // Date and time
    void   Date ( int& year,          // Calendar date
                  int& month, 
                  int& day ) const; 
    int    year()      const;         // Calendar year
    int    month()     const;         // Calendar month
    int    day()       const;         // Calendar day
    int    hour()      const;         // Hour of day
    int    minute()    const;         // Minute of hour
    double second()    const;         // Seconds of minute
    int    MJD0()      const;         // Modified Julian Date at start of day
    double fracOfDay() const;         // Fractional day
    double MJD()       const;         // Modified Julian Date
    int    dayOfWeek() const;         // Day of week (0 = Sunday)
    int    dayOfYear() const;         // Day of year (1 = January 1st).
    
    // Comparison
    friend bool operator <  (const GPStime& left, const GPStime& right);
    friend bool operator >  (const GPStime& left, const GPStime& right);
    friend bool operator <= (const GPStime& left, const GPStime& right);
    friend bool operator >= (const GPStime& left, const GPStime& right);
    friend bool operator == (const GPStime& left, const GPStime& right);
    friend bool operator != (const GPStime& left, const GPStime& right);

    // Time increment/decrement [s] 
    void operator += (double dt);
    void operator -= (double dt) { (*this) += (-dt); };

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


#endif  // include blocker

