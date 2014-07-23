//------------------------------------------------------------------------------
//
// DLR_String.h
// 
// Purpose: 
//
//   String handling
//   
// Last modified:
//
//   2006/03/18  SDA  Created for PRISMA
//   2006/03/19  SDA  Added define and introduced namespace
//   2007/03/08  SDA  Removed <vector>
//   2007/03/09  SDA  Added String class
//                    Removed old CheckSum
//   2007/05/25  SDA  Removed obsolete constructor
//   2007/06/06  SDA  Added constructor String(int Size)
//   2007/07/10  SDA  Renamed file DLR_WinMon to DLR_String (OM review)
//   2007/07/10  SDA  Renamed Stringa class to String (OM review)
//   2007/09/26  SDA  Added Valid_CheckSum method (OM review)
//   2008/11/10  SDA  Reviewed comments
//
// (c) 2009 DLR/GSOC
//
//------------------------------------------------------------------------------

#ifndef INC_DLR_WINMON_H
#define INC_DLR_WINMON_H

namespace rtn {

  //------------------------------------------------------------------------------
  //
  // String (class definition)
  //
  // Purpose:
  //
  //   String data type and associated operations
  //
  //------------------------------------------------------------------------------

  class String
  {

  public:

    // Constructors
    String (int Size);                        // Empty string of specified size
    String (char a);                          // 1char-String
    String (char a, char b);                  // 2char-String
    String (char a, char b, char c, char d);  // 4char-String
    String (char*a, int len);                 // len-char-String

    // Destructor
    ~String();

    // Size
    int size() const { return n; };

    // Assignment
    String& operator=(const String& S);

    // Comparison
    bool operator==(const String& S);

    // Component access
    char  operator () (int i) const { return s[i]; };
    char& operator () (int i)       { return s[i]; };

    String     slice (int first, int len) const;
    int        find (const String& a, int off) const;

    // C-like string (null-terminated)
    char* cstr() const;

    // CheckSum
    String  CheckSum() const;

    // CheckSum validity
    bool Valid_CheckSum() const;

  private:

    // Elements
    int    n;     // Dimension
    char  *s;     // String s(n)

  };

}; // End namespace

#endif  // include-Blocker

