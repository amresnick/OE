//------------------------------------------------------------------------------
//
// DLR_String.cpp
// 
// Purpose: 
//
//   String handling
//
// Last modified:
//
//   2006/03/18  SDA  Created for PRISMA
//   2006/03/19  SDA  Added define and introduced namespace
//   2007/03/09  SDA  Added String class
//                    Removed old CheckSum
//   2007/05/25  SDA  Revised constructors, added null termination
//   2007/06/06  SDA  Added constructor String(int Size)
//   2007/07/10  SDA  Renamed file DLR_WinMon to DLR_String (OM review)
//   2007/07/10  SDA  Renamed Stringa class to String (OM review)
//   2007/09/26  SDA  Added Valid_CheckSum method (OM review)
//   2008/07/07  SDA  Added safety check on off input to find method
//   2008/11/10  SDA  Reviewed comments
//   2011/10/20  SDA  Introduced protection against overvlow in Checksum computation
//   
// (c) 2009 DLR/GSOC
//
//------------------------------------------------------------------------------

#include "DLR_String.h"
#include <stdio.h>

namespace rtn {

  //------------------------------------------------------------------------------
  //
  // String (class implementation)
  //
  // Purpose:
  //
  //   String data type and associated operations
  //
  //------------------------------------------------------------------------------


  // Constructors, destructor

  String::String (int Size)                        // Creates empty string
    : n(Size)
  {
    s = new char [Size+1];
    s[Size]=(char)0;
  };

  String::String (char a)                          // 1char-String
    : n(1)
  {
    s = new char [2];
    s[0]=a; 
    s[1]=(char)0;
  };

  String::String (char a, char b)                  // 2char-String
    : n(2)
  {
    s = new char [3];
    s[0]=a; s[1]=b;
    s[2]=(char)0;
  };

  String::String (char a, char b, char c, char d)  // 4char-String
    : n(4)
  {
    s = new char [5];
    s[0]=a; s[1]=b; s[2]=c; s[3]=d;
    s[4]=(char)0;
  };

  String::String (char* a, int len)                // len-char-String
    : n(len)
  {
    s = new char [len+1];
    for (int i=0; i<len; i++) s[i]=a[i];
    s[len]=(char)0;
  };

  String::~String()
  { 
    delete [] s;
  };

  // Assignment
  String& String::operator=(const String& S)
  {
    // Copy
    if (this == &S) return (*this);
    // Discard previous string, allocate new string
    delete [] s;
    s = new char [S.n+1];
    n = S.n;
    // Copy elements
    for (int i=0; i<n; i++) s[i]=S.s[i];
    return (*this);
  };

  // Comparison
  bool String::operator==(const String& S)
  {
    if (n!=S.n) return false;
    for (int i=0;i<n;i++){
      if (s[i]!=S.s[i]) return false;
    };
    return true;
  };

  // Component access

  String String::slice (int first, int len) const
  {
    
    if (first<0)     first=0;
    if (len<1)       len  =1;
    if (first>n-1)   return String('?');
    if (first+len>n) len=n-first;
    
    return String(&s[first],len);
  
  };

  int String::find (const String& a, int off) const
  {
    int  find=-1;
    if (off<0)   return find;
    if (off>n-1) return find;
    for (int i=off;i<n;i++) {
      if (s[i]==a.s[0]) {
        if (a.n==1) return i;
        for (int j=1;j<a.n;j++) {
          if (i+j>=n) {
            find=-1;
            break;
          };
          if (s[i+j]!=a.s[j]) {
            find=-1;
            break;
          };
          find = i;
        };
        if (find!=-1) break;
      };
    };
    return find;
  };

  // C-like string (null-terminated)

  char* String::cstr() const
  {
    return s;
  };

  // CheckSum

  String String::CheckSum() const
  {
    unsigned short chk=0;
    char           hex[2+1];
    for (int i=0;i<n;i++) {
      chk = chk^s[i];
      if ( chk>255 ) {
        chk = 255;
        break;
      }
    }
    sprintf(hex,"%2.2X",chk);
    return String(hex,2);
  };

  // CheckSum validity

  bool String::Valid_CheckSum() const
  {
    // First compute checksum inline
    unsigned short chk=0;
    char           hex[2+1];
    for (int i=1;i<=n-4;i++) {
      chk = chk^s[i];
      if ( chk>255 ) {
        chk = 255;
        break;
      }
    }
    sprintf(hex,"%2.2X",chk);
    // Second compare checksums
    if (hex[0]!=s[n-3]) return false;
    if (hex[1]!=s[n-2]) return false;
    return true;
  };

}; // End namespace
