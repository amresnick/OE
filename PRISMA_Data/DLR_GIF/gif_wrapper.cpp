/*
*
*   --- THIS FILE GENERATED BY S-FUNCTION BUILDER: 3.0 ---
*
*   This file is a wrapper S-function produced by the S-Function
*   Builder which only recognizes certain fields.  Changes made
*   outside these fields will be lost the next time the block is
*   used to load, edit, and resave this file. This file will be overwritten
*   by the S-function Builder block. If you want to edit this file by hand, 
*   you must change it only in the area defined as:  
*
*        %%%-SFUNWIZ_wrapper_XXXXX_Changes_BEGIN 
*            Your Changes go here
*        %%%-SFUNWIZ_wrapper_XXXXXX_Changes_END
*
*   For better compatibility with the Real-Time Workshop, the
*   "wrapper" S-function technique is used.  This is discussed
*   in the Real-Time Workshop User's Manual in the Chapter titled,
*   "Wrapper S-functions".
*
*   Created: Wed Aug  2 18:06:52 2006
*/


/*
* Include Files
*
*/
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include "DLR_GIF.h"
using namespace rtn ;

//#include <stdio.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1459
#define y_width 1
/*
* Create external references here.  
*
*/
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */
extern "C"
{
  /*
  * Output functions
  *
  */
  void gif_Outputs_wrapper(
    const real_T *MEM_in,
    const real_T *TC_DLR_GIF,
    const uint32_T *GPS_TIME,
    const uint32_T *GPS_msg_adr_MAIN,
    const uint32_T *GPS_msg_len_MAIN,
    const uint32_T *GPS_msg_adr_TARGET,
    const uint32_T *GPS_msg_len_TARGET,
    real_T *MEM_out,
    uint32_T *TSync,
    uint32_T *DLR_GPS_Obs_Time,
    uint8_T *DLR_GPS_UTC,
    real_T *DLR_GPS_MAIN_OBS,
    real_T *DLR_GPS_TARGET_OBS,
    real_T *DLR_GPS_EPH,
    uint8_T *DLR_TM_GIF,
    uint8_T *ReqTE_MAIN,
    uint8_T *ReqTE_TARGET,
    uint8_T *GPS_Status_MAIN,
    uint8_T *GPS_Status_TARGET)
  {
    /* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
    //
    //  GIF (GPS Interface)
    //
    //  Purpose
    //
    //    GIF processes the outputs of the GPS receivers on MAIN (M) and TARGET (T)
    //    and generates ephemerides (EPH) and observation (OBS) data required by GOD.
    //    It extracts the OBS and EPH from the WinMon message (gif_winmondecoder)
    //    and updates EPH (gif_process_eph). The observations output by GIF are 
    //    extracted from a buffer which stores the obervations over the last 30 s
    //    and assures that observations are provided preferrably with the same time tag
    //    for MAIN and TARGET (gif_process_obs).
    //
    //  Input
    //    - MEM_in               Last GIF state containing the previous ephemerides 
    //                           as well as the buffer with the latest 3 valid 
    //                           observations for MAIN and TARGET
    //    - TC_DLR_GIF           Telecommands for GIF
    //          [0] Flag enabling automatic request for F14 messages
    //          [1] Validity interval of GPS ephemerides [h]
    //          [2] Repetition rate of TE commands [# GIF steps]
    //          [3] Filters obs older than time_window [s]
    //          [4] Max. time diff. to consider MAIN and TARGET obs simult. [s]
    //          [5] Maximum PDOP to consider valid a nav. solution
    //          [6] Minimum number of Sats to consider valid a nav. sol.
    //          [7] Minimum CN0 to consider valid a GPS observable
    //    - GPS_TIME             Current time
    //    - GPS_msg_adr_MAIN     Memory address for MAIN GPS Rx message
    //          [0] GPS Rx 1
    //          [1] GPS Rx 2
    //    - GPS_msg_len_MAIN     Length of MAIN GPS Rx message
    //          [0] GPS Rx 1
    //          [1] GPS Rx 2
    //    - GPS_msg_adr_TARGET   Memory address for TARGET GPS Rx message
    //          [0] GPS Rx 1
    //          [1] GPS Rx 2
    //    - GPS_msg_len_TARGET   Length of TARGET GPS Rx message
    //          [0] GPS Rx 1
    //          [1] GPS Rx 2
    //
    //  Output
    //    - MEM_out              Memory for the next GIF execution
    //    - TSync                GPS time from F40 for time synchronization
    //    - DLR_GPS_Obs_Time     GPS time extracted from receivers
    //    - DLR_GPS_UTC          GPS - UTC time difference [s]
    //    - DLR_GPS_MAIN_OBS     GPS MAIN observations for GOD
    //    - DLR_GPS_TARGET_OBS   GPS TARGET observations for GOD
    //    - DLR_GPS_EPH          Updated GPS ephemerides
    //    - DLR_TM_GIF           Telemetry for GIF
    //          [0] GPS_Status_MAIN Byte holding communication and tracking status
    //          [1] GPS_Status_TARGET Byte holding communication and tracking status
    //          [2] N_trackedSat_MAIN 
    //          [3] N_trackedSat_TARGET
    //          [4] N_CommonSat Number of commonly tracked satellites
    //    - ReqTE_MAIN           Transmit Ephemeris (TE) message for MAIN
    //    - ReqTE_TARGET         Transmit Ephemeris (TE) message for TARGET
    //    - GPS_Status_MAIN      Status flag on MAIN GPS for GNC FDIR
    //    - GPS_Status_TARGET    Status flag on TARGET GPS for GNC FDIR
    //
    //
    //  Change record:
    //
    //    2006/04/28  MGF  Created
    //    2006/05/08  MGF  Merged TC input  into 1 single port: TC_DLR_GIF
    //                     Merged TM output into 1 single port: DLR_TM_GIF
    //                     Added DLR_GPS_Obs_Time, DLR_GPS_UTC
    //                     Changed type of DLR_GPS_Branch to double
    //    2006/05/09  MGF  Removed enableMode_DLR_GIF and added TC for
    //                     Standby Mode
    //    2006/06/20  EG   Updated comments, shifted command length to DLR_GIF.h,
    //                     renamed length variables to _len
    //    2006/06/21  EG   Removed standby mode
    //    2006/06/26  EG   Added Update_eph, gif_generate_TE, changed IF gif_process_eph
    //    2006/06/28  EG   Started to implement telemetry
    //    2006/06/29  EG   Implemented and tested status Bytes, updated TC
    //    2006/07/01  EG   Removed GPS antenna and hardware configuration (not preocessed I/O)
    //                     Changed sequenced of I/O ports
    //    2006/07/04  EG   Added comment
    //    2006/07/10  EG   Added synchronization time, re-arrangement of output
    //    2006/07/17  EG   Replaced message input by their adress and length
    //    2006/07/18  EG   Fixed check of end of string for F14 messages
    //    2007/03/08  SDA  Removed using std::string
    //    2007/04/15  SDA  Fixed bug in extraction of receiver time
    //    2007/06/12  SDA  Used MainD and TargetD flags to generate time output
    //    2007/07/10  SDA  Renamed fracsec to musec (OM review)
    //    2008/11/12  SDA  Comments review
    //    2008/11/13  SDA  Corrected call to CUC GPStime constructor, (unsigned int) instead of (int)
    //                     Removed unnecessary data type casting for TSync output
    //    2013/04/24  SDA  Initial DEOS changes. Added data stream of second receiver for each s/c
    //                     Temporary assumption: F40 and F62 arrive at the same call of GIF
    //                     Proper implementation: modify gif_process_obs to handle two channels
    //
    //
    // (c) 2009  DLR/German Space Operations Center
    //
    //-------------------------------------------------------------------------

    // Variables     

    int           LoopCounter;            // Counting number of GIF calls [0...RepRateTE]
    int           idx_TE_M,idx_TE_T;      // Index stores position in vector to transmit TE
    int           N_send_TE[32];          // Vector holds number of send TE per PRN
    int           count_M[Status::Nbits]; // Counter for GPS status flag MAIN
    int           count_T[Status::Nbits]; // Counter for GPS status flag TARGET
    unsigned char status_M;               // GPS status MAIN
    unsigned char status_T;               // GPS status TARGET
    unsigned char Buf_status_M;           // Buffer GPS status MAIN stores past successful test
    unsigned char Buf_status_T;           // Buffer GPS status MAIN stores past successful test
    char          TE_MAIN[TE_len];        // String holding the command to request TE
    char          TE_TARGET[TE_len];      // String holding the command to request TE
    double        OBS_T1[OBS_len];        // Holds the observation vector for TARGET (Rx 1)
    double        OBS_M1[OBS_len];        // Holds the observation vector for MAIN (Rx 1)
    double        OBS_T2[OBS_len];        // Holds the observation vector for TARGET (Rx 2)
    double        OBS_M2[OBS_len];        // Holds the observation vector for MAIN (Rx 2)
    double        OBS_T[OBS_len];         // Holds the observation vector for TARGET (Rx 1+2)
    double        OBS_M[OBS_len];         // Holds the observation vector for MAIN (Rx 1+2)
    double        OBS_B_M[OBS_B_len];     // Observation Buffer for MAIN
    double        OBS_B_T[OBS_B_len];     // Observation Buffer for TARGET
    double        EPH_Ms1[EPH_Rx];         // Vector with Eph output by the MAIN Rx 1
    double        EPH_Ts1[EPH_Rx];         // Vector with Eph output by the TARGET Rx 1
    double        EPH_Ms2[EPH_Rx];         // Vector with Eph output by the MAIN Rx 2
    double        EPH_Ts2[EPH_Rx];         // Vector with Eph output by the TARGET Rx 2
    GPStime       t;                      // Current time
    GPStime       t_sync_M,t_sync_T;      // Synchronization time from F40
    bool          MainD;                  // Boolean that indicates if the last
                                          // delivery of OBS contained MAIN OBS
    bool          TargetD;                // Boolean that indicates if the last
                                          // delivery of OBS contained TARGET OBS  
    bool          EPH_list[32];           // List of valid and present ephemerides


    // Initialization

    status_M = 0;
    status_T = 0;
    t_sync_M = GPStime();
    t_sync_T = GPStime();

    //
    // Input section 
    //

    // Arrange TC inputs

    bool    AutoTE      = (bool)TC_DLR_GIF[0];   // Boolean allows Automatic TE
    double  EPH_max_age =       TC_DLR_GIF[1];   // Validity arc Ephemerides [s]
    int     RepRateTE   =  (int)TC_DLR_GIF[2];   // Repetition rate TE request
    double  time_window =       TC_DLR_GIF[3];   // Filters obs older than time_window [s]
    double  time_diff   =       TC_DLR_GIF[4];   // Max. time diff. to consider MAIN and TARGET obs simult. [s]
    double  PDOPmax     =       TC_DLR_GIF[5];   // Maximum PDOP
    int     nSATmin     =  (int)TC_DLR_GIF[6];   // Minimum number of tracked sats
    double  CN0min      =       TC_DLR_GIF[7];   // Minimum CN0


    // Store the current time

    t = GPStime(GPS_TIME[0],GPS_TIME[1]) ;

    //
    // Retrieve the data from the memory buffer (MEM_in)
    //

    // The memory buffer is indexed as follows:
    // [0,                     EPH_len-1]              - Complete set of EPH to be updated
    // [EPH_len,               EPH_len+  OBS_B_len-1]  - Buffer of last 3 valid OBS for MAIN
    // [EPH_len+  OBS_B_len,   EPH_len+2*OBS_B_len-1]  - Buffer of last 3 valid OBS for TARGET
    // [EPH_len+2*OBS_B_len]                           - Loop counter [0...RepRateTE]
    // [EPH_len+2*OBS_B_len+1]                         - Index with last MAIN TE PRN request
    // [EPH_len+2*OBS_B_len+2]                         - Index with last TARGET TE PRN request
    // [EPH_len+2*OBS_B_len+3, EPH_len+2*OBS_B_len+34] - Vector holds number of TE requests for PRNs
    // [EPH_len+2*OBS_B_len+35, EPH_len+2*OBS_B_len+35+nBits-1]         - Counter for status flag MAIN
    // [EPH_len+2*OBS_B_len+35+nBits, EPH_len+2*OBS_B_len+35+2*nBits-1] - Counter for status flag TARGET
    // [EPH_len+2*OBS_B_len+35+2*nBits]                - Byte indicates if MAIN status has at least once been ok
    // [EPH_len+2*OBS_B_len+36+2*nBits]                - Byte indicates if TARGET status has at least once been ok
    // [EPH_len+2*OBS_B_len+37+2*nBits]                - Where observations issued for MAIN?
    // [EPH_len+2*OBS_B_len+38+2*nBits]                - Where observations issued for TARGET?

    // Retrieve the complete set of ephemerides from the memory buffer
    for (int i=0; i<EPH_len; i++ ) DLR_GPS_EPH[i] = MEM_in[i] ;
    // Retrieve the observation buffer for MAIN and TARGET
    for (int i=0; i<OBS_B_len; i++ ){
      OBS_B_M[i] = MEM_in[EPH_len             + i];
      OBS_B_T[i] = MEM_in[EPH_len + OBS_B_len + i];
    };
    // Retrieve variables controlling TE requests
    LoopCounter   = (int)MEM_in[EPH_len+2*OBS_B_len];
    idx_TE_M      = (int)MEM_in[EPH_len+2*OBS_B_len+1];
    idx_TE_T      = (int)MEM_in[EPH_len+2*OBS_B_len+2];
    for (int i=0; i<32; i++) N_send_TE[i] = (int)MEM_in[EPH_len+2*OBS_B_len+3+i];
    // Retrieve counters for status flags. Counters denote number of calls in
    // which a certain communication or navigation validity check was unsuccessful.
    for (int i=0; i<Status::Nbits; i++) count_M[i] = (int)MEM_in[EPH_len+2*OBS_B_len+35+i];
    for (int i=0; i<Status::Nbits; i++) count_T[i] = (int)MEM_in[EPH_len+2*OBS_B_len+35+Status::Nbits+i];
    Buf_status_M  = (unsigned char)MEM_in[EPH_len+2*OBS_B_len+35+2*Status::Nbits];
    Buf_status_T  = (unsigned char)MEM_in[EPH_len+2*OBS_B_len+36+2*Status::Nbits];
    // Retrieve the booleans that indicate if observations were issued for
    // MAIN and TARGET
    MainD   = (bool)MEM_in[EPH_len+2*OBS_B_len+37+2*Status::Nbits];
    TargetD = (bool)MEM_in[EPH_len+2*OBS_B_len+38+2*Status::Nbits];


    //
    // Processing section 
    //

    // Process MAIN message

    // Character approach
    char* MSS_M1      = (char*)(GPS_msg_adr_MAIN[0]);
    int   MSS_len_M1  = (int)(GPS_msg_len_MAIN[0]); 
    char* MSS_M2      = (char*)(GPS_msg_adr_MAIN[1]);
    int   MSS_len_M2  = (int)(GPS_msg_len_MAIN[1]);     

    gif_winmondecoder(MSS_M2,MSS_len_M2,PDOPmax,nSATmin,CN0min,t_sync_M,OBS_M2,EPH_Ms2,count_M,status_M,Buf_status_M);
    gif_winmondecoder(MSS_M1,MSS_len_M1,PDOPmax,nSATmin,CN0min,t_sync_M,OBS_M1,EPH_Ms1,count_M,status_M,Buf_status_M);
    

    // Process TARGET message

    char* MSS_T1      = (char*)(GPS_msg_adr_TARGET[0]);
    int   MSS_len_T1  = (int)(GPS_msg_len_TARGET[0]);
    char* MSS_T2      = (char*)(GPS_msg_adr_TARGET[1]);
    int   MSS_len_T2  = (int)(GPS_msg_len_TARGET[1]);

    gif_winmondecoder(MSS_T2,MSS_len_T2,PDOPmax,nSATmin,CN0min,t_sync_T,OBS_T2,EPH_Ts2,count_T,status_T,Buf_status_T);
    gif_winmondecoder(MSS_T1,MSS_len_T1,PDOPmax,nSATmin,CN0min,t_sync_T,OBS_T1,EPH_Ts1,count_T,status_T,Buf_status_T);

    // Process observations

    gif_merge_obs(OBS_M1,OBS_M2,OBS_M);
    gif_merge_obs(OBS_T1,OBS_T2,OBS_T);
    gif_process_obs(OBS_M,OBS_T,t,time_window,time_diff,OBS_B_M,OBS_B_T,MainD,TargetD); 

    // Process ephemerides 

    gif_process_eph(DLR_GPS_EPH,EPH_Ms1,EPH_Ts1,EPH_Ms2,EPH_Ts2,t,EPH_max_age,EPH_list);


    // Generate Transmit Ephemeris (TE) message if obs. have no valid ephemerides

    gif_generate_TE(EPH_list,OBS_M,OBS_T,AutoTE,RepRateTE,LoopCounter,
      idx_TE_M,idx_TE_T,N_send_TE,TE_MAIN,TE_TARGET,
      count_M,status_M,count_T,status_T,Buf_status_M,Buf_status_T);  


    //
    // Output section 
    //

    //
    // Build the Memory block to be used in the next run
    //

    for (int i=0; i<EPH_len; i++ ) MEM_out[i] = DLR_GPS_EPH[i];  // EPH
    for (int i=0; i<OBS_B_len; i++ ){
      MEM_out[EPH_len + i]             = OBS_B_M[i];             // OBS
      MEM_out[EPH_len + OBS_B_len + i] = OBS_B_T[i];
    };
    // Retrieve variables controlling TE requests
    MEM_out[EPH_len+2*OBS_B_len]  = (double)LoopCounter;
    MEM_out[EPH_len+2*OBS_B_len+1] = (double)idx_TE_M;
    MEM_out[EPH_len+2*OBS_B_len+2] = (double)idx_TE_T;
    for (int i=0; i<32; i++ ) MEM_out[EPH_len+2*OBS_B_len+3+i] = (double)N_send_TE[i];
    // Retrieve counters for status flags. Counters denote number of calls in
    // which a certain communication or navigation validity check was unsuccessful.
    for (int i=0; i<Status::Nbits; i++) MEM_out[EPH_len+2*OBS_B_len+35+i] = (double)count_M[i];
    for (int i=0; i<Status::Nbits; i++) MEM_out[EPH_len+2*OBS_B_len+35+Status::Nbits+i] = (double)count_T[i];
    MEM_out[EPH_len+2*OBS_B_len+35+2*Status::Nbits] = (double)Buf_status_M;
    MEM_out[EPH_len+2*OBS_B_len+36+2*Status::Nbits] = (double)Buf_status_T;
    MEM_out[EPH_len+2*OBS_B_len+37+2*Status::Nbits] =   (double)MainD;      // Flags
    MEM_out[EPH_len+2*OBS_B_len+38+2*Status::Nbits] = (double)TargetD;

    // Output synchronization time

    TSync[0] = t_sync_M.CUCintsec();   // Number of seconds
    TSync[1] = t_sync_M.CUCmusec();    // Fractional part of seconds

    // Output the leap second as given by the receiver

    DLR_GPS_UTC[0]      = (int)DLR_GPS_MAIN_OBS[2] ;

    // Output observations for GOD

    for (int i=0; i<OBS_len; i++ ) {
      DLR_GPS_MAIN_OBS[i]   = OBS_M[i];
      DLR_GPS_TARGET_OBS[i] = OBS_T[i];
    };

    // Output GPS time as given by the receiver

    if (TargetD) {
      DLR_GPS_Obs_Time[0] = (int)DLR_GPS_TARGET_OBS[0];
      DLR_GPS_Obs_Time[1] = (int)DLR_GPS_TARGET_OBS[1];
    };

    if (MainD) {
      DLR_GPS_Obs_Time[0] = (int)DLR_GPS_MAIN_OBS[0];
      DLR_GPS_Obs_Time[1] = (int)DLR_GPS_MAIN_OBS[1];
    };

    // Output of ephemerides is done above in gif_process_eph

    // Output of telemetry

    DLR_TM_GIF[0] = status_M; 
    DLR_TM_GIF[1] = status_T; 
    DLR_TM_GIF[2] = Ntracked(OBS_M); 
    DLR_TM_GIF[3] = Ntracked(OBS_T); 
    DLR_TM_GIF[4] = Ncommon(OBS_M,OBS_T); 

    // Output of Transmit Ephemeris (TE) message 

    for (int i=0; i<TE_len; i++ ) ReqTE_MAIN[i] = (uint8_T)TE_MAIN[i];
    for (int i=0; i<TE_len; i++ ) ReqTE_TARGET[i] = (uint8_T)TE_TARGET[i];

    // Output of status flag 

    GPS_Status_MAIN[0] = status_M;
    GPS_Status_TARGET[0] = status_T;


    /* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
  }
}

