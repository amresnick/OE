//------------------------------------------------------------------------------
//
// DLR_GIF
// 
// Purpose: 
//
//   GPS Interface functions
//
// Last modified:
//
//   2006/04/16  MGF  Created
//   2006/05/10  MGF  valid_meas cond. (gif_winmondecoder) into ok_1F and ok_CN0
//   2006/06/20  EG   Modified comments, revised logic to issue GPS obs records
//   2006/06/21  EG   Simplified while loop, checking if no recent measurements are there
//   2006/06/26  EG   Added Update_eph, gif_generate_TE, changed IF gif_process_eph
//   2006/06/27  EG   Added update_idx, TE_string, extended buffer for TE
//   2006/06/28  EG   Added update_count
//   2006/06/29  EG   Changed update_count to update_status, introduced status_buf 
//   2006/07/01  EG   Added Ntracked, Ncommon
//   2006/07/10  EG   Added synchronization time, 
//                    Assured that navigation and raw data have same time tag
//   2006/07/17  EG   Changed winmondecoder by adding the message length as input 
//   2006/08/06  SDA  Removed #include "mex.h"
//   2006/08/08  SDA  Fixed bug in gif_process_eph (loop indexing)
//   2006/09/15  EG   Corrected number of digits for CIS in EPH
//   2007/03/07  SDA  Removed #define DEBUG 1
//                    Removed unnecessary buffer lenght check in gif_winmondecoder
//                    Added check on lenght of message before accessing it, this
//                    solves GIF crash occured at SSC with ref. numb. SPR-109
//   2007/03/08  SDA  Replaced non-printable characters with definition of STX,ETX
//                    Added necessary #include statements
//   2007/03/09  SDA  Replaced string class with String class
//   2007/04/17  SDA  Changed computation of ValidNav to include checks on first
//                    3D-fix,PDOP,nSAT and F40/F62 time difference
//   2007/05/23  SDF  Fixed bug in gif_process_obs: introduction of variable MainDeliveredPrev.
//                    Fixed bug in gif_process_obs: modified check-loop to verify if at least one set of
//                    observations is within the time window. Modified attached comment.
//                    In gif_generate_TE moved inizialization TE_done = false from first block 
//                    of the function to block "Treat MAIN".
//   2007/05/24  SDF  Modified comment opening block "Treat MAIN".
//   2007/06/06  SDA  Reformatting.
//   2007/06/06  SDA  Removed #include "mex.h". Added <stdio.h> and <stdlib.h>
//   2007/06/07  SDA  Replaced abs with fabs to avoid warning with gcc
//   2007/06/07  SDA  Removed obsolete comments
//   2007/06/07  SDA  Initialized end_F40 and end_F63 to -1 to avoid gcc warning
//   2007/06/12  SDA  Corrected search loop of synchronous measurements in memory buffer
//   2007/07/03  SDA  More robust implementation of sprintf command in TE_string function
//   2007/07/10  SDA  Renamed fracsec to musec (OM review)
//                    Renamed file DLR_WinMon to DLR_String (OM review)
//                    Renamed Stringa class to String (OM review)
//   2007/09/14  SDA  Modifications to cope with arrival of correspondent
//                    F40 and F62 messages at different calls of GIF:
//                     1) gif_winmondecoder: removed comparison btw. F40 and F62 times
//                     2) gif_process_obs: modified logic of buffering
//   2007/09/17  SDA  Modifications to cope with arrival of correspondent
//                    F40 and F62 messages at different calls of GIF:
//                     1) gif_process_obs: updated logic for the 2 issue cases
//                        availability of valid data is now based on presence of
//                        raw data and not only time like before
//   2007/09/18  SDA  Modifications to cope with arrival of correspondent
//                    F40 and F62 messages at different calls of GIF:
//                     1) gif_process_obs: updated logic for the one s/c only delivery case
//   2007/09/26  SDA  Replaced checksum validity check with string class method (OM review)
//                    Removed unused CHK variable in gif_winmondecoder
//   2008/07/07  SDA  Removed unnecessary comments
//   2008/07/07  SDF  Replaced erroneous *+ operator with + only in two lines of code
//   2008/07/08  SDA  Replaced hardcoded 0.001 s value with TC time_diff input
//                    Added comments
//   2008/07/14  SDA  Changed if statement for time_window comparison from < to <=
//   2008/11/13  SDA  Corrected call to CUC GPStime constructor, (unsigned int) instead of (int)
//
//
// (c) 2009 DLR/GSOC
//
//------------------------------------------------------------------------------

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "DLR_GIF.h"
#include "DLR_String.h"

namespace rtn {

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

  unsigned char Ntracked( double* OBS )
  {
    // Variables

    int count;

    count = 0;
    for (int ch = 0; ch<12; ch++) {       // Search for PRNs which are not zero
      if ( OBS[3+ch] != 0 ) count++;
    };  

    return count;
  };    

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

  unsigned char Ncommon( double* OBS_M,double* OBS_T )
  {
    // Variables

    int count;

    count = 0;
    for (int ch = 0; ch<12; ch++) {
      if ( OBS_M[3+ch] != 0 ) {     // Only look at TARGET, if MAIN PRN != 0
        for (int i = 0; i<12; i++) {
          if ( OBS_M[3+ch] == OBS_T[3+i] ) count++;
        };  
      };  
    };  

    return count;
  };    

  //------------------------------------------------------------------------------
  //
  // update_status
  //
  //  Purpose
  //    Updates the status flag and counter.
  //    The status flag indicates whether a certain criteria has been met
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
    const char     update)
  {
    // Note on status_Buf:
    // Bits in status_Buf are set if called for the first time; it is never reset. 
    // Without status_Buf we would have a flag set in the first GIF calls although
    // there was never a passed test.

    // Test passed in this step, so we reset the counter and set the flag 
    if (pass) {
      count[idx]=0; 
      status     |= update;  // Stores current status
      status_Buf |= update;  // Stores if bit has been set once
    };

    // Test not passed but counter still below its maximum
    if (!pass && (count[idx]<MaxCount) ) {
      count[idx]++;                                       // Increment counter
      if ( (status_Buf & update) != 0)  status |= update; // Set flag
    };

    // If the test was not passed and (count=MaxCount), no need to do anything

    return;

  }; // End of function update_status

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
  void update_idx( int& idx )
  {
    if (idx < 11) {idx++;}
    else {idx=0;};

    return;

  }; // End of function update_idx

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
  void TE_string( int PRN, char* TE )
  {
    // Variables

    String CHK(2);

    sprintf(TE,"TE%02d",PRN);
    CHK = (String(TE,4)).CheckSum();
    //No! Avoid usage of non-printable characters
    //sprintf(TE,"TE%02d%s",PRN,CHK.c_str());
    //No! Possible overflows with user defined string
    //sprintf(TE,"%sTE%02d%s%s",STX.cstr(),PRN,CHK.cstr(),ETX.cstr());
    //Yes! Robust solution
    sprintf(TE,"%cTE%02d%c%c%c",STX(0),PRN,CHK(0),CHK(1),ETX(0));
    return;
  }; // End of function update_idx

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
    bool*   EPH_list)
  {

    // Variables

    GPStime t_eph;

    // Update the ephemerides vector from TARGET first

    Update_eph( EPH, EPH_Ts2 );
    Update_eph( EPH, EPH_Ts1 );


    // Update the ephemerides vector from MAIN
    // We update the ephemerides vector from MAIN as second, since these
    // are not susceptible to possible transmission errors of the ISL.
    // A marginal overhead from a partial duplication is accepted.

    Update_eph( EPH, EPH_Ms2 );
    Update_eph( EPH, EPH_Ms1 );



    // Set ephemerides with outdated T_oe to zero

    for ( int i=0; i<32; i++ ){
      t_eph = GPStime((int)EPH[i*31+13],(double)EPH[i*31+14]);
      if ( (t-t_eph) > GIF_TC_EPHage ) for (int j=0; j<31; j++) EPH[i*31+j]=0.0;
    }; 


    // Setup list of valid ephemerides

    for (int i=0; i<32; i++ ){
      EPH_list[i] = false;                         // We don't have ephs (default)  
      if (EPH[i*31+13] != 0) EPH_list[i] = true;   // We have ephs if T_oe not zero
    }; 


    return;

  }; // End of function gif_process_eph

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
  //    status_T       I/O  Communication and Tracking Status Byte
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
    unsigned char& status_Buf_T )
  {

    // Variables

    int     PRN;
    bool    request_M;
    bool    request_T;
    bool    TE_done;
    bool    ComplEph;
    int     Need_Eph_M[12];
    int     Need_Eph_T[12];

    request_M = false;
    request_T = false;

    for ( int iChn=0; iChn<12; iChn++ ) Need_Eph_M[iChn] = 0;
    for ( int iChn=0; iChn<12; iChn++ ) Need_Eph_T[iChn] = 0;

    //
    // Determine and store PRNs which lack ephemeris
    //

    for (int iChn=0; iChn<12; iChn++){
      PRN = (int)MAIN_OBS[3+iChn]; 
      if ( (PRN!=0) && !EPH_list[PRN-1] ) {Need_Eph_M[iChn] = PRN; request_M=true;}  

      PRN = (int)TARGET_OBS[3+iChn]; 
      if ( (PRN!=0) && !EPH_list[PRN-1] ) {Need_Eph_T[iChn] = PRN; request_T=true;} 
    };


    // Update status flags and counters

    ComplEph = (!request_M);
    update_status (ComplEph,count_M,status_M,status_Buf_M,5,MaxCountNav,Status::ComplEph);

    ComplEph = (!request_T);
    update_status (ComplEph,count_T,status_T,status_Buf_T,5,MaxCountNav,Status::ComplEph);

    //
    // Control of sending TE messages
    //


    // Increment counter
    if (LoopCounter < RepRateTE) LoopCounter++; 

    // Check whether we can reset the counter of sent TEs if ephemerides
    // are either no more needed (since the PRN is no longer visible) or
    // if we have meanwhile received the F14 message from the receiver.

    for (int i=0; i<32; i++) {                                  // Loop over PRNs
      bool found_PRN = false;                                   // Search in Need_Eph
      PRN = i+1;                                                //
      for (int iChn=0; iChn<12; iChn++) {                       // lists whether we
        if ( (Need_Eph_M[iChn]==PRN) || (Need_Eph_T[iChn]==PRN) ) { // find a lacking PRN.
          found_PRN = true;                                     // If we do not find it,
          break;                                                // we can reset the 
        };                                                      // entry to zero.
      };  
      if (!found_PRN) N_send_TE[i] = 0;
    };  

    // Generate empty message

    sprintf(Req_TE_MAIN,"        ");
    sprintf(Req_TE_TARGET,"        ");

    if (LoopCounter >= RepRateTE) {               // > should never happen
      LoopCounter = 0;                            // Reset loop counter
      if (AutoTE && (request_M || request_T) ) {  // Allowance and need for msg

        // Note that we generate only one TE message per MAIN and per TARGET.
        // To that end, we sequentialy loop through the vectors Need_Eph using
        // the index idx_TE (index with last TE PRN request) based on the
        // previous execution.
        // There are two possibilities with the cyclic index idx_TE [0,11]:
        // a. Either we need to transmit TE for PRN with idx >= idx_TE
        // b. or there is a PRN in the index regime idx < idx_TE

        // Treat MAIN
        TE_done   = false;
        for (int idx=idx_TE_M; idx<12; idx++) {
          PRN = Need_Eph_M[idx];
          if (PRN != 0) {
            TE_string(PRN,Req_TE_MAIN);
            TE_done = true;                       // TE generated
            idx_TE_M = idx;                       // Store index
            N_send_TE[PRN-1]++;                   // Increment TE counter
            break;                                // Generate TE once
          };
        };
        if (!TE_done) {
          for (int idx=0; idx<idx_TE_M; idx++) {
            PRN = Need_Eph_M[idx];
            if (PRN != 0) {
              TE_string(PRN,Req_TE_MAIN);
              idx_TE_M = idx;                     // Store index
              N_send_TE[PRN-1]++;                 // Increment TE counter
              break;                              // Generate TE once
            };
          };
        };

        // Treat TARGET

        TE_done  = false;  
        for (int idx=idx_TE_T; idx<12; idx++) {
          PRN = Need_Eph_T[idx];
          if (PRN != 0) {
            TE_string(PRN,Req_TE_TARGET);
            TE_done  = true;                      // TE generated
            idx_TE_T = idx;                       // Store index
            N_send_TE[PRN-1]++;                   // Increment TE counter
            break;                                // Generate TE once
          };
        };
        if (!TE_done) {
          for (int idx=0; idx<idx_TE_T; idx++) {
            PRN = Need_Eph_T[idx];
            if (PRN != 0) {
              TE_string(PRN,Req_TE_TARGET);
              idx_TE_T = idx;                     // Store index
              N_send_TE[PRN-1]++;                 // Increment TE counter
              break;                              // Generate TE once
            };    
          };
        };

        // Now, increment index for the next round
        update_idx(idx_TE_M);
        update_idx(idx_TE_T);

      };
    };  

    // We limit the counters in N_send_TE to prevent overflow

    for (int i=0; i<32; i++){                               // Loop over PRNs
      if (N_send_TE[i] > TE_limit) N_send_TE[i] = TE_limit; // No need to softcode
    };                                                      // upper limit


    return;

  }; // End of function gif_generate_TE

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
    unsigned char& status_Buf )
  {

    // Variables

    bool     NewBytes;       // Indicator for new Bytes
    bool     NewMsg;         // Indicator for new Mitel msg
    bool     NewF40;         // Indicator for new F40 msg
    bool     NewF62;         // Indicator for new F62 msg
    bool     Tracking;       // Indicator for single PRN tracking 
    bool     ValidNav;       // Indicator for valid nav solution
    bool     FirstNav;       // Indicator for first 3D-fix
    String   Mss_in(MSS_len);// Copy of input buffer
    String   F14(F14_len);   // F14 Mitel message
    String   F40(F40_len);   // F40 Mitel message
    String   F62(F62_len);   // F62 Mitel message
    int      start_F14,end_F14=0;    // Variables that indicate
    int      start_F40,end_F40=-1;   // the start/end of the message
    int      start_F62,end_F62=-1;   // within the input buffer
    int      it = 0;         // Iteration index

    // Initialization

    NewF40   = false;
    NewF62   = false;
    Tracking = false;
    ValidNav = false;
    FirstNav = false;
    for (int i=0; i<OBS_len; i++ ) OBS[i] = 0.0;   // Output observations vector
    for (int i=0; i<EPH_Rx; i++ )  EPH[i] = 0.0;   // Output ephemerides vector


    // Copy input buffer to a local String

    Mss_in = String(MSS,MSS_len);

    // Check whether we received Bytes and update status flag and counter

    NewBytes = (!Mss_in(0)=='\0');  // Look for end-of-string
    update_status (NewBytes,count,status,status_Buf,0,MaxCountCom,Status::NewBytes);

    // Check whether we received Mitel messages and update status flag and counter
    NewMsg = ( Mss_in.find(STXF,0) != -1 ); // Check <STX>F
    update_status (NewMsg,count,status,status_Buf,1,MaxCountCom,Status::NewMsg);

    // Process F14 GPS Ephemerides Message

    while( true ){
      start_F14 = Mss_in.find(STXF14,end_F14);
      if ( start_F14 == -1 ) break;                         // No F14 in string
      end_F14 = Mss_in.find(ETX,start_F14+1);
      if ( end_F14 == -1 &&
          (end_F14 - start_F14) != (F14_len-1)) break;      // No complete F14 in string

      // If we reach this point, there is a F14 message to process
      F14 = Mss_in.slice(start_F14,F14_len);
      // Processing of the message is done if the Checksum is correct.
      // Otherwise it remains 0, which is the standard value as defined
      // in the initialisation.
      // Validate the CheckSum
      if ( F14.Valid_CheckSum() ){
        EPH[it*32+ 0] = atof(F14.slice( 41, 4).cstr()) ; // TOC week
        EPH[it*32+ 1] = atof(F14.slice( 45, 6).cstr()) ; // TOC secs
        EPH[it*32+ 2] = atof(F14.slice( 51,13).cstr()) ; // AF0
        EPH[it*32+ 3] = atof(F14.slice( 64,16).cstr()) ; // AF1
        EPH[it*32+ 4] = atof(F14.slice( 80,20).cstr()) ; // AF2
        EPH[it*32+ 5] = atof(F14.slice(100, 3).cstr()) ; // IODE
        EPH[it*32+ 6] = atof(F14.slice(103, 8).cstr()) ; // CRS
        EPH[it*32+ 7] = atof(F14.slice(111,16).cstr()) ; // Delta_n
        EPH[it*32+ 8] = atof(F14.slice(127,13).cstr()) ; // M0
        EPH[it*32+ 9] = atof(F14.slice(140,12).cstr()) ; // CUC
        EPH[it*32+10] = atof(F14.slice(152,12).cstr()) ; // e
        EPH[it*32+11] = atof(F14.slice(164,12).cstr()) ; // CUS
        EPH[it*32+12] = atof(F14.slice(176,11).cstr()) ; // sqrt(a)
        EPH[it*32+13] = atof(F14.slice(187, 4).cstr()) ; // TOE week
        EPH[it*32+14] = atof(F14.slice(191, 6).cstr()) ; // TOE s
        EPH[it*32+15] = atof(F14.slice(198,12).cstr()) ; // CIC
        EPH[it*32+16] = atof(F14.slice(210,13).cstr()) ; // Omega
        EPH[it*32+17] = atof(F14.slice(223,12).cstr()) ; // CIS
        EPH[it*32+18] = atof(F14.slice(235,13).cstr()) ; // i0
        EPH[it*32+19] = atof(F14.slice(248, 8).cstr()) ; // CRC
        EPH[it*32+20] = atof(F14.slice(256,13).cstr()) ; // omega
        EPH[it*32+21] = atof(F14.slice(269,16).cstr()) ; // Omega_dot
        EPH[it*32+22] = atof(F14.slice(285,16).cstr()) ; // i_dot
        EPH[it*32+23] = atof(F14.slice( 17, 4).cstr()) ; // week num
        EPH[it*32+24] = atof(F14.slice( 13, 3).cstr()) ; // SV health
        EPH[it*32+25] = atof(F14.slice( 22, 2).cstr()) ; // URA
        EPH[it*32+26] = atof(F14.slice( 28,13).cstr()) ; // TGD
        EPH[it*32+27] = atof(F14.slice( 24, 4).cstr()) ; // IODC
        EPH[it*32+28] = atof(F14.slice(  7, 6).cstr()) ; // Time of Tx
        EPH[it*32+29] = atof(F14.slice(197, 1).cstr()) ; // Fit interval
        EPH[it*32+30] = atof(F14.slice(  6, 1).cstr()) ; // Eph status
        EPH[it*32+31] = atof(F14.slice(  4, 2).cstr()) ; // PRN      
      }; 

      // Security statement to avoid infinite loop, one can get up to 
      // 12 sets of ephemerides each second
      it ++;
      if ( it >= 12 ) break;

    }; // End of processing F14 messages


    //  Process F40 Cartesian Navigation Data Message

    // Search for F40 (one occurrence each 10 seconds)
    start_F40 = Mss_in.find(STXF40,0);
    if ( start_F40 != -1 ) end_F40 = Mss_in.find(ETX,start_F40+1);
    if ( end_F40 != -1 && (end_F40 - start_F40) == (F40_len-1)){
      // F40 is present in the incoming buffer &&
      // Lenght of F40 message is correct
      // Retrieve F40 message
      F40 = Mss_in.slice( start_F40, F40_len );

      // Validate the CheckSum
      if ( F40.Valid_CheckSum() ){
        // Extract time
        int     GPSweek    = atoi(F40.slice( 4, 4).cstr());
        double  GPSseconds = atof(F40.slice( 8,12).cstr());
        GPStime t          = GPStime(GPSweek,GPSseconds);

        // Store data from F40 into the observation vector
        OBS[ 0] = (double)t.CUCintsec();               // Number of seconds
        OBS[ 1] = (double)t.CUCmusec();                // Fractional part of seconds
        OBS[ 2] = atof(F40.slice(20, 2).cstr());       // GPS-UTC

        // Check if the navigation solution is valid
        ValidNav = atoi(F40.slice(94, 1).cstr()) == 2;

        // Check if the navigation solution is the first 3D-fix
        // that is shown to be not accurate. The check is based
        // on the integer nature of the GPSseconds in the msg
        FirstNav = atoi(F40.slice( 15, 5).cstr()) != 0;

        // Additional checks on validity of navigation solution
        // The navigation solution will be accepted under the
        // conditions specified by the incoming PDOP and nSAT
        ValidNav = ValidNav && !FirstNav
                   && atof(F40.slice(97, 4).cstr()) <= PDOP
                   && atoi(F40.slice(95, 2).cstr()) >= nSAT;

        if( ValidNav ){

          OBS[15] = atof(F40.slice(22,12).cstr());  // x position
          OBS[16] = atof(F40.slice(34,12).cstr());  // y position
          OBS[17] = atof(F40.slice(46,12).cstr());  // z position
          OBS[18] = atof(F40.slice(58,12).cstr());  // x velocity
          OBS[19] = atof(F40.slice(70,12).cstr());  // y velocity
          OBS[20] = atof(F40.slice(82,12).cstr());  // z velocity

        }; // End of validity check of the navigation solution
        NewF40 = true;
        // Assignment of TSync (we are very conservative here and accept only
        // messages which have passed all tests successfully)
        if( ValidNav ) t_sync = t;
      }; // End of valid Checksum
    }; // End of F40 section

    // Process of F62 message (Raw measurement and Channel Status)

    // Search for F62 (one occurrence each 10 seconds)
    start_F62 = Mss_in.find(STXF62,0);
    if ( start_F62 != -1 ) end_F62 = Mss_in.find(ETX,start_F62+1);
    if ( end_F62 != -1 && (end_F62 - start_F62) == (F62_len-1)){
      // F62 is present in the incoming buffer &&
      // Lenght of F62 message is correct
      // Retrieve F62 message
      F62 = Mss_in.slice( start_F62, F62_len );

      // Validate the CheckSum
      if ( F62.Valid_CheckSum() ){

        // Extract time
        int     GPSweek    = atoi(F62.slice( 4, 4).cstr());
        double  GPSseconds = atof(F62.slice( 8,12).cstr());
        GPStime t          = GPStime(GPSweek,GPSseconds);

        // Store data from F62 into the Observation vector
        OBS[ 0] = (double)t.CUCintsec();           // Number of seconds
        OBS[ 1] = (double)t.CUCmusec();            // Fractional part of seconds
        OBS[ 2] = atof(F62.slice(20, 2).cstr());   // GPS-UTC

        // Go through all channels
        for(int ch = 0; ch<12; ch++){
          bool ok_1F  = false;
          bool ok_CN0 = false;

          // Check the validity of the current message
          // 1.- If status byte is 1F the message is valid
          if ( F62(34+ch*47+44) == '1' && F62(34+ch*47+45) == 'F' ) ok_1F = true;
          // 2.- Above C/N0 threshold
          if( atof(F62.slice(34+ch*47+38, 5).cstr()) >= CN0 ) ok_CN0 = true;

          if (ok_1F) Tracking = true;                                 // At least 1 PRN is tracked
          if (ok_1F && ok_CN0) {
            // Extract and store the PRN number and the observables
            OBS[3+ch]    = atof(F62.slice(34+ch*47+ 0, 2).cstr()); // PRN
            OBS[ch*4+21] = atof(F62.slice(34+ch*47+ 2,13).cstr()); // CA pseudorange [m]
            OBS[ch*4+22] = atof(F62.slice(34+ch*47+15,14).cstr()); // Integrated Carrier Phase [cycles]
            OBS[ch*4+23] = atof(F62.slice(34+ch*47+29, 9).cstr()); // Range rate [m/s]
            OBS[ch*4+24] = atof(F62.slice(34+ch*47+38, 5).cstr()); // Carrier to Noise Ratio [dBHz]
          }; // End validity check in each channel
        }; // End channel loop
        NewF62 = true;   
      }; // End of valid Checksum
    }; // End of F62 section

    // Update status flag and counter based on F40 analysis
    update_status (NewF40,count,status,status_Buf,3,MaxCountNav,Status::NewF40);
    update_status (ValidNav,count,status,status_Buf,6,MaxCountNav,Status::ValidNav);

    // Update status flag and counter based on F62 analysis
    update_status (NewF62,count,status,status_Buf,2,MaxCountNav,Status::NewF62);
    update_status (Tracking,count,status,status_Buf,4,MaxCountNav,Status::Tracking);

    return;

  }; // End of function gif_winmondecoder

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
  //      1  Update with the incoming observations from gif_winmondecoder
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
    bool&   TargetDelivered) 
  {
    // Variables

    bool MAIN_available   = false;
    bool TARGET_available = false;

    GPStime t_M; // Time of previous valid observation for MAIN
    GPStime t_T; // Time of previous valid observation for TARGET

    int out_M; // Index for record item to be delivered (MAIN)
    int out_T; // Index for record item to be delivered (TARGET)

    // Update buffer with valid observations

    if ( MAIN_OBS[0] != 0 ){  // Valid MAIN measurements have non-zero GPS time
      // Check if current measurements (F40 or F62) correpond to received
      // measurements (F40 or F62) at previous call
      if ( fabs(GPStime((unsigned int)MAIN_OBS[0],(unsigned int)MAIN_OBS[1]) - 
                GPStime((unsigned int)MAIN_OBS_B[2*OBS_len],(unsigned int)MAIN_OBS_B[1+2*OBS_len])) < time_diff)
      {

        // Measurements correspond to previous message, write data in the third record
        if ( (MAIN_OBS[15]*MAIN_OBS[15]+MAIN_OBS[16]*MAIN_OBS[16]+MAIN_OBS[17]*MAIN_OBS[17]) == 0.0 ) {
          // F62 message has arrived
          for ( int i=3;  i<15; i++ ) MAIN_OBS_B[i+2*OBS_len] = MAIN_OBS[i];
          for ( int i=21; i<81; i++ ) MAIN_OBS_B[i+2*OBS_len] = MAIN_OBS[i];
        }else{
          // F40 message has arrived
          for ( int i=15; i<21; i++ ) MAIN_OBS_B[i+2*OBS_len] = MAIN_OBS[i];
        };
        MAIN_OBS_B[  2*OBS_len] = MAIN_OBS[0];
        MAIN_OBS_B[1+2*OBS_len] = MAIN_OBS[1];
        MAIN_OBS_B[2+2*OBS_len] = MAIN_OBS[2];

      }else{

        // New measurements have arrived, records have to be shifted in the buffer
        for ( int i=0; i<2*OBS_len; i++ )
          MAIN_OBS_B[i] = MAIN_OBS_B[i+OBS_len]; // Move records 2,3 to 1,2 within buffer
        for ( int i=0; i<OBS_len; i++ )
          MAIN_OBS_B[i+2*OBS_len] = MAIN_OBS[i]; // Update new record to position 3

      }; 
    };

    if ( TARGET_OBS[0] != 0 ){ // Valid TARGET measurements have non-zero GPS time
      // Check if current measurements (F40 or F62) correpond to received
      // measurements (F40 or F62) at previous call
      if ( fabs(GPStime((unsigned int)TARGET_OBS[0],(unsigned int)TARGET_OBS[1]) - 
                GPStime((unsigned int)TARGET_OBS_B[2*OBS_len],(unsigned int)TARGET_OBS_B[1+2*OBS_len])) < time_diff)
      {

        // Measurements correspond to previous message, write data in the third record
        if ( (TARGET_OBS[15]*TARGET_OBS[15]+TARGET_OBS[16]*TARGET_OBS[16]+TARGET_OBS[17]*TARGET_OBS[17]) == 0.0 ) {
          // F62 message has arrived
          for ( int i=3;  i<15; i++ ) TARGET_OBS_B[i+2*OBS_len] = TARGET_OBS[i];
          for ( int i=21; i<81; i++ ) TARGET_OBS_B[i+2*OBS_len] = TARGET_OBS[i];
        }else{
          // F40 message has arrived
          for ( int i=15; i<21; i++ ) TARGET_OBS_B[i+2*OBS_len] = TARGET_OBS[i];
        };
        TARGET_OBS_B[  2*OBS_len] = TARGET_OBS[0];
        TARGET_OBS_B[1+2*OBS_len] = TARGET_OBS[1];
        TARGET_OBS_B[2+2*OBS_len] = TARGET_OBS[2];

      }else{

        // New measurements have arrived, records have to be shifted in the buffer
        for ( int i=0; i<2*OBS_len; i++ )
          TARGET_OBS_B[i] = TARGET_OBS_B[i+OBS_len]; // Move records 2,3 to 1,2 within buffer
        for ( int i=0; i<OBS_len; i++ )
          TARGET_OBS_B[i+2*OBS_len] = TARGET_OBS[i]; // Update new record to position 3

      };
    };

    // Delivery logic

    // Initialize first

    for (int i=0; i<OBS_len; i++ ) MAIN_OBS[i]   = 0.0;
    for (int i=0; i<OBS_len; i++ ) TARGET_OBS[i] = 0.0;

    bool MainDeliveredPrev = MainDelivered;
    MainDelivered   = false;
    TargetDelivered = false;

    // Let us first check whether all observations are older than their time tag plus the time window (30s). 
    // If the check is not passed it does not make sense to issue any observation and the function terminates.

    for ( int i=2; i>=0; i-- ){
      t_M = GPStime( (unsigned int)MAIN_OBS_B[i*OBS_len+0],(unsigned int)MAIN_OBS_B[i*OBS_len+1] );
      t_T = GPStime( (unsigned int)TARGET_OBS_B[i*OBS_len+0],(unsigned int)TARGET_OBS_B[i*OBS_len+1] );

      if ( (t - t_M) <= time_window || (t - t_T) <= time_window ) break; // At least one observation within the time window
                                                                         // has been found and the check-loop can be interrupted here 
      if ( i == 0 && (t - t_M) > time_window && (t - t_T) > time_window ) return;   
    }; 


    // Issue Case 1
    // Search for the latest set of observations that are within the time window
    // that contain both MAIN and TARGET observations. We know already that at 
    // least one valid observation is within the last 30 seconds (time window)

    for ( int i=2; i>=0; i-- ){ // loop over MAIN buffer
      for ( int k=2; k>=0; k-- ){ // loop over TARGET buffer

        t_M = GPStime( (unsigned int)MAIN_OBS_B[i*OBS_len+0],(unsigned int)MAIN_OBS_B[i*OBS_len+1] );
        t_T = GPStime( (unsigned int)TARGET_OBS_B[k*OBS_len+0],(unsigned int)TARGET_OBS_B[k*OBS_len+1] );

        // Additional check to verify that raw data from F62 are available from both s/c
        bool raw_data_M = false;
        bool raw_data_T = false;
        bool raw_data   = false;
        for ( int ch=0; ch<12; ch++ ) {
          raw_data_M = ( MAIN_OBS_B[i*OBS_len+3+ch] != 0.0 ) ;
          if ( raw_data_M ) break;
        };
        for ( int ch=0; ch<12; ch++ ) {
          raw_data_T = ( TARGET_OBS_B[k*OBS_len+3+ch] != 0.0 ) ;
          if ( raw_data_T ) break;
        };
        raw_data = raw_data_M && raw_data_T;

        if( t-t_M<=time_window && t-t_T<=time_window && fabs(t_M-t_T)<time_diff && raw_data ){
          // Note that this condition is only passed if we have navigation solutions in F40
          for(int j=0;j<OBS_len;j++) MAIN_OBS[j]  =MAIN_OBS_B[i*OBS_len+j];   
          for(int j=0;j<OBS_len;j++) TARGET_OBS[j]=TARGET_OBS_B[k*OBS_len+j];
          MainDelivered   = true;
          TargetDelivered = true;
          return;
        };
      };
    }; // End Case 1


    // Case 2
    // Case where only either a MAIN or TARGET observation record will be issued.
    // At this point, there are no common observations in a time interval time_diff. 
    // So we either provide a MAIN or a TARGET observation record.

    // Check the availability of MAIN or TARGET during the last time_window
    for (int i=0; i<3; i++ ){
      t_M = GPStime( (unsigned int)MAIN_OBS_B[i*OBS_len+0],(unsigned int)MAIN_OBS_B[i*OBS_len+1] );
      t_T = GPStime( (unsigned int)TARGET_OBS_B[i*OBS_len+0],(unsigned int)TARGET_OBS_B[i*OBS_len+1] );

      // Additional check to verify that raw data from F62 are available from s/c
      bool raw_data_M = false;
      bool raw_data_T = false;
      for ( int ch=0; ch<12; ch++ ) {
        raw_data_M = ( MAIN_OBS_B[i*OBS_len+3+ch] != 0.0 ) ;
        if ( raw_data_M ) break;
      };
      for ( int ch=0; ch<12; ch++ ) {
        raw_data_T = ( TARGET_OBS_B[i*OBS_len+3+ch] != 0.0 ) ;
        if ( raw_data_T ) break;
      };

      if ( (t - t_M) <= time_window && raw_data_M ) {
        MAIN_available   = true;
        // Additional counter to indicate record position in buffer for delivery
        out_M = i;
      };
      if ( (t - t_T) <= time_window && raw_data_T ) {
        TARGET_available = true;
        // Additional counter to indicate record position in buffer for delivery
        out_T = i;
      };
    };

    if ( MAIN_available && !TARGET_available ){  // Only MAIN available, therefore send the newest
      for (int j=0; j<OBS_len; j++) MAIN_OBS[j]   = MAIN_OBS_B[out_M*OBS_len+j];   
      MainDelivered   = true;

    };
    if ( !MAIN_available && TARGET_available ){  // Only TARGET available, therefore send the newest
      for (int j=0; j<OBS_len; j++) TARGET_OBS[j] = TARGET_OBS_B[out_T*OBS_len+j];
      TargetDelivered = true;
    }; 
    if ( MAIN_available && TARGET_available ){  // Both are present but not simultaneous.
      // We therefore send a TARGET set, if the latest record was MAIN and vice versa
      if( MainDeliveredPrev ){
        for (int j=0;j<OBS_len;j ++) TARGET_OBS[j] = TARGET_OBS_B[out_T*OBS_len+j];
        TargetDelivered = true;
      }else{
        for (int j = 0;j<OBS_len;j ++) MAIN_OBS[j] = MAIN_OBS_B[out_M*OBS_len+j];   
        MainDelivered   = true;
      };
    }; // End Case 2

    return;

  }; // End of gif_process_obs

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

  void Update_eph( double* EPH,
    double* EPH_s )

  {
    // Variables

    int     PRN;

    for ( int i=0; i<12; i++ ){
      // Get the PRN number of the channel
      PRN = (int)EPH_s[i*32+31];
      if ( PRN == 0 ) continue;

      // Since this PRN has ephemeris information, override previous information
      // Note: PRN stored explicitly in EPH_S, but implicitly through its location
      // in EPH
      for (int j=0; j<31; j++ ) EPH[(PRN-1)*31+j] = EPH_s[i*32+j]; 
    }; 

    return ;

  }; // End of Update_eph

  //------------------------------------------------------------------------------
  //
  // gif_merge_obs
  //
  //  Purpose
  //    Merges the observations from two active receivers (same s/c).
  //    Rx 1 is default. Rx 2 obs are added if from different PRNs.
  //    Rx 1 obs are flagged with 0.0, Rx 2 obs are flagged with 1.0.
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
    double* OBS )

  {
    // Variables
    bool ValidNav1;
    bool ValidNav2;
    bool NEW_PRN;

    // Initialization (take obs from Rx 1)
    for (int i=0; i<OBS_len; i++ ) OBS[i] = 0.0;

    // Check presence of navigation solutions
    ValidNav1 = false;
    for ( int i=15; i<21; i++ ){
      if ( OBS1[i]!=0.0 ) ValidNav1 = true;
    };
    ValidNav2 = false;
    for ( int i=15; i<21; i++ ){
      if ( OBS2[i]!=0.0 ) ValidNav2 = true;
    };

    // Available cases
    if ( !ValidNav1 && !ValidNav2  ){
      // Choose Rx1, measurements not synch in and across receivers
      for (int i=0; i<OBS_len; i++ ) OBS[i] = OBS1[i];
    }
    if ( ValidNav1 && !ValidNav2  ){
      // Choose Rx1, measurements synch in receiver
      for (int i=0; i<OBS_len; i++ ) OBS[i] = OBS1[i];
    };
    if ( !ValidNav1 && ValidNav2  ){
      // Choose Rx2, measurements synch in receiver
      for (int i=0; i<OBS_len; i++ ) OBS[i] = OBS2[i];
      for (int i=OBS_len-12; i<OBS_len; i++ ) OBS[i] = 1.0; //flag for Rx 2
    };
    if ( ValidNav1 && ValidNav2  ){
      // Start with Rx1, measurements synch in and across receivers
      for (int i=0; i<OBS_len; i++ ) OBS[i] = OBS1[i];
      // Go through all channels to add Rx2 data, if PRN not available
      for(int ch = 0; ch<12; ch++){
        if (OBS[3+ch]==0){ //Only proceed if empty PRN
          NEW_PRN = false;
          for(int ch2 = 0; ch2<12; ch2++){
            for(int ch1 = 0; ch1<12; ch1++){
              if (OBS2[3+ch2]!=0 && OBS[3+ch1]!=OBS2[3+ch2]){
                NEW_PRN = true;
              }else{
                NEW_PRN = false;
                break;
              };
            };
            if(NEW_PRN){
              OBS[3+ch]    = OBS2[3+ch2];    // PRN
              OBS[ch*4+21] = OBS2[ch2*4+21]; // CA pseudorange [m]
              OBS[ch*4+22] = OBS2[ch2*4+22]; // Integrated Carrier Phase [cycles]
              OBS[ch*4+23] = OBS2[ch2*4+23]; // Range rate [m/s]
              OBS[ch*4+24] = OBS2[ch2*4+24]; // Carrier to Noise Ratio [dBHz]
              OBS[OBS_len-12+ch] = 1.0;      // flag for Rx 2
              break;
            };
          };
        };
      };
    };

    return;

  }; // End of gif_merge_obs

}; // End of namespace in DLR_GIF


