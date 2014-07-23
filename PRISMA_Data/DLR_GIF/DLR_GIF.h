//------------------------------------------------------------------------------
//
// DLR_GIF.h
// 
// Purpose: 
//
//   GPS Interface functions
//
// Last modified:
//
//   2006/04/16  MGF  Created
//   2006/04/24  SDA  Removed #include mex.h
//   2006/06/20  EG   Modified comments, added CS_len, TE_len
//                    renamed _length and _lgth to _len
//   2006/06/23  EG   Removed EPH_max_age,time_window,time_diff,Th_LackOBS;
//                    Added as TCs
//   2006/06/26  EG   Added Update_eph, gif_generate_TE, changed IF gif_process_eph
//   2006/06/27  EG   Added update_idx, TE_string, extended buffer for TE elements
//   2006/06/27  EG   Added Status class
//   2006/06/28  EG   Added update_count
//   2006/06/29  EG   Changed update_count to update_status, moved time constants to commands
//   2006/07/01  EG   Added Ntracked, Ncommon
//   2006/07/10  EG   Added synchronization time 
//   2006/07/17  EG   Removed MSS_len
//   2007/03/08  SDA  Removed unnecessary #include statements
//   2007/03/09  SDA  Replaced string class with String class
//                    Added necessary Strings for message decoding
//   2007/03/23  SDA  Changed MaxCountCom from 6 to 30 and comments
//   2007/07/10  SDA  Renamed file DLR_WinMon to DLR_String (OM review)
//   2007/07/10  SDA  Renamed Stringa class to String (OM review)
//   2008/07/10  SDA  Changed default value of MaxCountNav from 30s to 15s (SDF review)
//                    Modified comments accordingly
//   2013/04/24  SDA  Added function gif_merge_obs
//
// (c) 2009 DLR/GSOC
//
//------------------------------------------------------------------------------

#include "DLR_GPS_Time.h"
#include "DLR_String.h"
using namespace rtn;

class Status {
public:
  const static int  Nbits    = 7;    // Number of status bits     
  const static char NewBytes = 0x01; // Bytes arrived in last 30 s
  const static char NewMsg   = 0x02; // Mitel Msg arrived in last 30 s
  const static char NewF62   = 0x04; // F62 with valid checksum arrived in last 15 s
  const static char NewF40   = 0x08; // F40 with valid checksum arrived in last 15 s
  const static char Tracking = 0x10; // At least one sat tracked
  const static char ComplEph = 0x20; // F14 messages complete
  const static char ValidNav = 0x40; // Valid navigation from F40
};

const int     EPH_len     = 992;           // # of elems. in the EPH vector
const int     OBS_len     = 81;            // # of elems. in the OBS vector 
const int     OBS_B_len   = 3*OBS_len;     // # of elems. in the OBS buffer

const int     F14_len     =   304;  // Size of GPS ephemeris message
const int     F40_len     =   104;  // Size of navigation solution message
const int     F62_len     =   601;  // Size of raw data message
const int     CS_len      =     6;  // Size of cold start message
const int     TE_len      =     8;  // Size of transmit ephemeris message
const int     EPH_Rx      = 32*12;  // Max # of eph elements in 12 channels of the Rx
const int     TE_limit    =    20;  // Upper limit of counts allowed in N_send_TE

const int     MaxCountCom =    30;  // When max. counter is reached, a communication error bit is set
const int     MaxCountNav =    15;  // When max. counter is reached, a navigation error bit is set

// Necessary Strings for message decoding
const String    STX       = String((char)0x02);    // Start character for GPS messages
const String    ETX       = String((char)0x03);    // End character for GPS messages
const String    STXF      = String((char)0x02, 'F');
const String    STXF14    = String((char)0x02, 'F', '1', '4');
const String    STXF40    = String((char)0x02, 'F', '4', '0');
const String    STXF62    = String((char)0x02, 'F', '6', '2');

namespace rtn{

  //------------------------------------------------------------------------------
  //
  // Ntracked
  //
  //  Purpose
  //
  //    Determines the number of tracked satellites
  //
  //  Input
  //    
  //    OBS[81]            Observations output to GOD
  //
  //------------------------------------------------------------------------------

  unsigned char Ntracked( double* OBS );

  //------------------------------------------------------------------------------
  //
  // Ncommon
  //
  //  Purpose
  //
  //    Determines the number of commonly tracked satellites
  //
  //  Input
  //    
  //    OBS_M[81]            Observations of MAIN output to GOD
  //    OBS_T[81]            Observations of TARGET output to GOD
  //
  //------------------------------------------------------------------------------

  unsigned char Ncommon( double* OBS_M,double* OBS_T );

  //------------------------------------------------------------------------------
  //
  // update_status
  //
  //  Purpose
  //    Updates the status flag and counter.
  //    The status flag indicates whether a certain criteria has been been met
  //    in the past which is determined from a counter.
  //
  //  Input
  //    pass          Indicator whether a certain check has been passed
  //    count         Array with counter values
  //    status        Status byte for MAIN or TARGET GPS
  //    status_Buf    Buffer of status byte
  //    idx           Index number [0,Nbits]
  //    MaxCount      Maximum count number
  //    update        Byte incrementing the status    
  // 
  //  Output
  //    count         Updated on output
  //    status        Updated on output
  //    status_Buf    Buffer of status byte
  //
  //------------------------------------------------------------------------------

  void update_status (
    bool           pass,
    int*           count,
    unsigned char& status,
    unsigned char& status_Buf,
    int            idx, 
    int            MaxCount, 
    const char     update);

  //------------------------------------------------------------------------------
  //
  // update_idx
  //
  //  Purpose
  //    Updates an index using a cylic index scheme in the interval [0,11]
  //
  //  Input
  //    idx           Index on input
  // 
  //  Output
  //    idx           Updated index on output
  //
  //------------------------------------------------------------------------------

  void update_idx( int& idx );

  //------------------------------------------------------------------------------
  //
  // TE_string
  //
  //  Purpose
  //    Generates a TE string
  //
  //  Input
  //    PRN             PRN of GPS satellite
  // 
  //  Output
  //    TE              Character string
  //
  //------------------------------------------------------------------------------

  void TE_string( int PRN, char* TE );

  //------------------------------------------------------------------------------
  //
  // gif_generate_TE
  //
  //  Purpose
  //    Generates a TE message if observations have no associated GPS ephemerides
  //
  //  Input/Output
  //    EPH_list       I    Vector of bools indicates whether ephemeris are available
  //    MAIN_OBS[81]   I    Observations from MAIN at current time
  //    TARGET_OBS[81] I    Observations of TARGET at current time (input)
  //    AutoTE         I    Flag indicates whether TE generation is enabled
  //    RepRateTE      I    Repetition rate for TE messages [every # of calls]
  //    LoopCounter    I/O  Counter runs from 0 to RepRateTE
  //    idx_TE_M       I/O  Stores the PRN for which TE has last been issued
  //    idx_TE_T       I/O  Stores the PRN for which TE has last been issued
  //    N_send_TE      I/O  Vector of number of send TE for 32 PRNs
  //    Req_TE_MAIN    O    Vector of 8 chars with message content (empty or TE msg)
  //    Req_TE_TARGET  O    Vector of 8 chars with message content (empty or TE msg)
  //    count_M        I/O  Vector of counters indicate how many past bit test were unsuccessful 
  //    status_M       I/O  Communication and Tracking Status Byte
  //    count_T        I/O  Vector of counters indicate how many past bit test were unsuccessful 
  //    status_M       I/O  Communication and Tracking Status Byte
  //    status_Buf_M   I/O  Byte Buffer
  //    status_Buf_T   I/O  Byte Buffer
  //
  //------------------------------------------------------------------------------

  void gif_generate_TE( 
    bool*          EPH_list,
    double*        MAIN_OBS,
    double*        TARGET_OBS,
    bool           AutoTE,
    int            RepRateTE,
    int&           LoopCounter,
    int&           idx_TE_M,
    int&           idx_TE_T,
    int*           N_send_TE,
    char*          Req_TE_MAIN,
    char*          Req_TE_TARGET,
    int*           count_M,
    unsigned char& status_M,
    int*           count_T,
    unsigned char& status_T,
    unsigned char& status_Buf_M,
    unsigned char& status_Buf_T );

  //------------------------------------------------------------------------------
  //
  // gif_process_eph
  //
  //  Purpose
  //    Updates the ephemerides vector that contains all the ephemerides data
  //    of all satellites with the incoming new Ephemerides data output by the
  //    the GPS receiver
  //
  //  Input
  //    EPH[992]      Previous set of ephemerides, to update with the new 
  //                  ephemerides information (32sat*31val/sat)
  //    EPH_Ms1[384]  Set of ephemerides issued by the MAIN Rx1 (12ch*32val/ch)
  //    EPH_Ts1[384]  Set of ephemerides issued by the TARGET Rx1 (12ch*32val/ch)
  //    EPH_Ms2[384]  Set of ephemerides issued by the MAIN Rx2 (12ch*32val/ch)
  //    EPH_Ts2[384]  Set of ephemerides issued by the TARGET Rx2 (12ch*32val/ch)
  //    t             Current GPS time
  //    GIF_TC_EPHage Maximum age of the Eph
  // 
  //  Output
  //    EPH[992]      The function modifies the content of the input vector 
  //                  on output with new ephemerides information from EPH_s
  //    EPH_list      List of valid ephemerides    
  //
  //------------------------------------------------------------------------------

  void gif_process_eph( 
    double* EPH,
    double* EPH_Ms1,
    double* EPH_Ts1,
    double* EPH_Ms2,
    double* EPH_Ts2,
    GPStime t,
    double  GIF_TC_EPHage,
    bool*   EPH_list);

  //------------------------------------------------------------------------------
  //
  // gif_winmondecoder
  //
  //  Purpose
  //    Analyses the incoming buffer of GPS messages and generates
  //    the observation vector and the ephemerides vector 
  //
  //  Input
  //    MSS         Input string of characters full of incoming message
  //    MSS_len     Length of message
  //    PDOP        Maximum PDOP allowed to output valid nav. solution (TC)
  //    nSAT        Minimum number of satellites to output a valid nav. solution (TC)
  //    CN0         Minimum CN0 of observables to output (TC)
  //
  //  Output
  //    t_sync      Synchronization time derived from F40
  //    OBS[81]     Vector of doubles containing the observables
  //    EPH[384]    Vector of double containing the ephemerides for the 
  //                satellites of the GPS receiver channels
  //    count       Vector of counters indicate how many past bit test were unsuccessful 
  //    status      Communication and Tracking Status Byte
  //    status_Buf  Byte Buffer
  //
  //------------------------------------------------------------------------------

  void gif_winmondecoder( 
    char*          MSS,
    int            MSS_len,
    double         PDOP,
    int            nSAT,
    double         CN0, 
    GPStime&       t_sync,
    double*        OBS,
    double*        EPH,
    int*           count,
    unsigned char& status,
    unsigned char& status_Buf );

  //------------------------------------------------------------------------------
  //
  // gif_process_obs
  //
  //  Purpose
  //
  //    Delivers the observation of MAIN and TARGET to be used by the GOD module.  
  //    This function works with a buffer that contains the 3 last valid
  //    observations. There is one buffer for MAIN and one buffer for TARGET.
  //
  //    The process is as follows:
  //      1  Update with the incoming observations from gop_winmondecoder
  //         only if this is a valid observation
  //      2  Logic to deliver the observations of the last 30 seconds
  //          a As a general basis it will deliver the last set that contains
  //            data from MAIN and TARGET.
  //          b If a. is not available, deliver the latest available set of data
  //            with only observations from MAIN or from TARGET
  //
  //  Input/Output
  //    MAIN_OBS[81]       Observations from MAIN at current time (input)
  //                       Observation to deliver to GOD (output)
  //    TARGET_OBS[81]     Observations of TARGET at current time (input)
  //                       Observation to deliver to GOD (output)
  //    t                  Current time
  //    time_window        Variable [s] filters observations older than time_window
  //    time_diff          Maximum time difference [s] to consider MAIN and TARGET obs. as simultaneous
  //    MAIN_OBS_B[3*81]   Buffer of last 3 valid observations for MAIN (input)
  //                       Updated buffer for MAIN (output)
  //    TARGET_OBS_B[3*81] Buffer of last 3 valid observations for TARGET (input)
  //                       Updated buffer for TARGET (output)
  //    MainDelivered      Boolean true if the last measurements contained
  //                       information of the MAIN GPS receiver (input, updated on output) 
  //    TargetDelivered    Boolean true if the last measurements contained
  //                       information of the TARGET GPS receiver (input, updated on output) 
  //
  //------------------------------------------------------------------------------

  void gif_process_obs( 
    double* MAIN_OBS,
    double* TARGET_OBS,
    GPStime t,
    double  time_window,
    double  time_diff,
    double* MAIN_OBS_B,
    double* TARGET_OBS_B,
    bool&   MainDelivered,
    bool&   TargetDelivered); 

  //------------------------------------------------------------------------------
  //
  // Update_eph
  //
  //  Purpose
  //    Updates the ephemerides vector with incoming ephemerides data from the
  //    the GPS receiver
  //
  //  Input
  //    EPH[992]      Current set of ephemerides (32sat*31val/sat)
  //    EPH_s[384]    Set of ephemerides issued by the Rx (12ch*32val/ch)
  // 
  //  Output
  //    EPH[992]      Modified on output with new ephemerides from EPH_s
  //
  //------------------------------------------------------------------------------

  void Update_eph( 
    double* EPH,
    double* EPH_s );

  //------------------------------------------------------------------------------
  //
  // gif_merge_obs
  //
  //  Purpose
  //    Merges the observations from two active receivers (same s/c)
  //
  //  Input
  //    OBS1[81]     Observations from Rx 1
  //    OBS2[81]     Observations from Rx 2
  // 
  //  Output
  //    OBS[81]      Merged observations
  //
  //------------------------------------------------------------------------------

  void gif_merge_obs( 
    double* OBS1,
    double* OBS2,
    double* OBS );

}; // End of additional definitions for the namespace


