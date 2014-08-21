//  File    : winmon_reader.cpp
//
//  Abstract:
//
//      C++ S-function to read ascii file comprising winmon messages.
//
//
//  Input:
//
//      t : Desired epoch of the state  (2x1,double)
//
//  Outputs:
//
//      msg_addr:   adress of the msg in memory
//      msg_length: length of the msg
//
//  Parameters:
//
//      fileName:   name of file containing the messages
//      dt      :   sample time of the block (real)
//      VERBOSE :   verbose mode
//
//  Change log:
//
//      15.10.2008 JSA  created
//      02.06.2010 SDA  renamed
//                      added missing return statements in Sendbuffer
//                      removed unreferenced local variables
//                      added include mex.h for mexPrintf
//                      corrected typos in mexPrintf messages
//                      tuned time tolerance for message search
//     03.06.2010 SDA   first mex-compilation successfull
//                      reformatted
//                      removed hardcoded array size
//                      added safety check on pos==-1
//     04.06.2010 SDA   added myGetline to avoid problems with line endings
//     06.06.2010 SDA   added VERBOSE flag as parameter
//
//-----------------------------------------------------------------------------



#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include "mex.h"
#include "GPS_Time.h"
#include <math.h>

#define S_FUNCTION_LEVEL  2
#define S_FUNCTION_NAME   winmon_reader

#define IS_PARAM_DOUBLE(pVal) (mxIsNumeric(pVal) && !mxIsLogical(pVal) &&\
!mxIsEmpty(pVal) && !mxIsSparse(pVal) && !mxIsComplex(pVal) && mxIsDouble(pVal) )

#define IS_PARAM_UINT32(pVal) (mxIsNumeric(pVal) && !mxIsLogical(pVal) &&\
!mxIsEmpty(pVal) && !mxIsSparse(pVal) && !mxIsComplex(pVal) && mxIsUint32 (pVal) )

#define IS_PARAM_LOGICAL(pVal) (mxIsLogical(pVal) &&\
!mxIsEmpty(pVal) && !mxIsSparse(pVal) && !mxIsComplex(pVal) && mxIsDouble(pVal) )

#if !defined(TRUE)
#define TRUE       1
#endif
#if !defined(FALSE)
#define FALSE      0
#endif

#define NUM_PARAMS  3
#define NUM_INPUTS  1
#define NUM_OUTPUTS 2

#define VERBOSE ((bool) (*mxGetPr(ssGetSFcnParam(S, 2))))

#include "simstruc.h"

using namespace std;

const int       MAX_MSG_LEN = 2500;
const int       F40_len = 104;
const int       F62_len = 601;
const int       F48_len = 48;

const char      char_STX[2] = { (char) 0x02, 0 };
const char      char_ETX[2] = { (char) 0x03, 0 };
const string    STX = string(char_STX);
const string    ETX = string(char_ETX);
const string    STXF40 = STX + "F40";
const string    STXF14 = STX + "F14";
const string    STXF62 = STX + "F62";
const string    STXF48 = STX + "F48";


//=============================================================================
// Auxiliary functions
//=============================================================================

#ifdef __cplusplus
extern "C"
{
#endif

//-----------------------------------------------------------------------------
// Parameter Check functions
//-----------------------------------------------------------------------------
  

//-----------------------------------------------------------------------------
//  Function: IsRealScalar
//
//  Abstract:
//      Verifiy that the mxArray is a real scalar.

static boolean_T IsRealScalar(const mxArray *m)
{
  if ( IS_PARAM_DOUBLE(m) &&  mxGetNumberOfElements(m) == 1 )
  {
    real_T *data = (real_T *)mxGetPr(m);
    if (!mxIsFinite(data[0])) return(FALSE);
    return(TRUE);
  } else {
    return(FALSE);
  }
}

//-----------------------------------------------------------------------------
//  Function: IsVectorofDouble
//
//  Abstract:
//      Verifiy that the mxArray is a vector of size n.

static boolean_T IsVectorofDouble(const mxArray *m,int n)
{
  if ( IS_PARAM_DOUBLE(m) &&  mxGetNumberOfElements(m) == n )
  {
    real_T *data = (real_T *)mxGetPr(m);
    if (!mxIsFinite(data[0])) return(FALSE);
    return(TRUE);
  } else {
    return(FALSE);
  }
}

//-----------------------------------------------------------------------------
//  Function: IsLogical
//
//  Abstract:
//      Verifiy that the mxArray is a logical value.

static boolean_T IsLogical(const mxArray *m)
{
  if ( IS_PARAM_LOGICAL(m) &&  mxGetNumberOfElements(m) == 1 )
  {
    real_T *data = (real_T *)mxGetPr(m);
    if (!mxIsFinite(data[0])) return(FALSE);
    return(TRUE);
  } else {
    return(FALSE);
  }
}

//-----------------------------------------------------------------------------
//  Function: IsString
//
//  Abstract:
//    Verifiy that the mxArray is a string.

static boolean_T IsString(const mxArray *m)
{
  if (

#ifndef RT      
          mxIsChar(m) && 
#endif    
         (mxGetM(m) == 1 || mxGetN(m) == 1 )) {
    return(TRUE);
  } else {
    return(FALSE);
  }
}

//-----------------------------------------------------------------------------
//  Function: GetString
//
//  Abstract:
//      Get a C string from an input Simulink string.

static char *GetString(const mxArray *m)
{
  int_T buflen, status;
  char *s;

  buflen   = (mxGetM(m) * mxGetN(m) * sizeof(mxChar)) + 1;
  s        = (char *) mxCalloc(buflen, sizeof(char));
  status   = mxGetString(m, s, buflen);
  
  return(s);
}

//-----------------------------------------------------------------------------
//  Function: GetMsgTime
//      Get the epoch of a time-tagged msg
//      Return true if succeded, false otherwise
//-----------------------------------------------------------------------------

bool GetMsgTime(string Msg, GPStime &t)
{
  int     start_F40, end_F40;
  int     start_F62, end_F62;
  int     start_F48, end_F48;
  string  F40, F62, F48;
  int     GPSweek;
  double  GPSseconds;

  start_F40 = Msg.find(STXF40, 0);
  if(start_F40 != -1) end_F40 = Msg.find(ETX, start_F40 + 1);
  if(end_F40 != -1 && (end_F40 - start_F40) == (F40_len - 1))
  {
    F40 = Msg.substr(start_F40, F40_len);
    GPSweek = atoi(F40.substr(4, 4).c_str());
    GPSseconds = atof(F40.substr(8, 12).c_str());
    t = GPStime(GPSweek, GPSseconds);
    return true;
  }

  start_F62 = Msg.find(STXF62, 0);
  if(start_F62 != -1) end_F62 = Msg.find(ETX, start_F62 + 1);
  if(end_F62 != -1 && (end_F62 - start_F62) == (F62_len - 1))
  {
    F62 = Msg.substr(start_F62, F62_len);
    GPSweek = atoi(F62.substr(4, 4).c_str());
    GPSseconds = atof(F62.substr(8, 12).c_str());
    t = GPStime(GPSweek, GPSseconds);
    return true;
  }

  start_F48 = Msg.find(STXF48, 0);
  if(start_F48 != -1) end_F48 = Msg.find(ETX, start_F48 + 1);
  if(end_F48 != -1 && (end_F48 - start_F48) == (F48_len - 1))
  {
    F48 = Msg.substr(start_F48, F48_len);
    GPSweek = atoi(F48.substr(4, 4).c_str());
    GPSseconds = atof(F48.substr(8, 8).c_str());
    t = GPStime(GPSweek, GPSseconds);
    return true;
  }

  return false;
};
//-----------------------------------------------------------------------------
//  Function: Sendbuffer
//      Extract and send string buffer of proper size
//-----------------------------------------------------------------------------

bool Sendbuffer
(
  vector<string>  *msg_list,
  unsigned int    *msg_length,
  char            *msg,
  SimStruct       *S
)
{
  int idx_msg = 0;
  int offset = 0;

  if(msg_list->size() > 0)
  {
    if VERBOSE mexPrintf("Buffer comprises %d msg. \n", msg_list->size());

    *msg_length = 0;
    while(idx_msg < msg_list->size())
    { // how many msg can be sent?
      if(*msg_length + (*msg_list)[idx_msg].size() > MAX_MSG_LEN)
        break;
      *msg_length += (*msg_list)[idx_msg].size();
      idx_msg++;
    }

    if VERBOSE{ if(idx_msg == msg_list->size())
        mexPrintf("all the msg of the buffer can be sent now. \n");
      else
        mexPrintf("only %d msg of the buffer can be sent now. \n", idx_msg);
    };

    for(int i = 0; i < idx_msg; i++)
    {
      sprintf(msg + offset, "%s", (*msg_list)[i].c_str());
      offset += (*msg_list)[i].size();
    }

    msg_list->erase(msg_list->begin(), msg_list->begin() + idx_msg);  // remove idx_msg elements of the list
    return true;
  }
  else
  {
    if VERBOSE mexPrintf("Empty buffer. Nothing to be sent \n");

    msg[0] = '\0';
    *msg_length = (uint32_T) (0);
    return false;
  }
}

//-----------------------------------------------------------------------------
//  Function: myGetline
//      Use standard function getline exploiting start and end characters of winmon
//      messages as line delimiters. This avoids handling ambiguous line endings.
//-----------------------------------------------------------------------------

void myGetline(ifstream *myfile, string &line)
{
  getline(*myfile, line, char_STX[0]);
  getline(*myfile, line, char_ETX[0]);

  // At this stage line is guaranteed to be comprised between STX and ETX
  line = char_STX[0] + line + char_ETX[0];

  // At this stage line is guaranteed not to contain any ending characters
  return;
}

//=============================================================================
// Function: mdlCheckParameters
//=============================================================================

#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)

static void mdlCheckParameters(SimStruct *S)
{
  if(!IsString(ssGetSFcnParam(S, 0)))
  {
    ssSetErrorStatus
    (
      S, "1st parameter to S-function must be a non-empty cell of strings"
    );
    return;
  }

  if(!IsRealScalar(ssGetSFcnParam(S, 1)))
  {
    ssSetErrorStatus
    (
      S, "2nd parameter to S-function must be a real finite scalar"
    );
    return;
  }

  if(!IsRealScalar(ssGetSFcnParam(S, 2)))
  {
    ssSetErrorStatus(S, "3rd parameter to S-function must be a logical value");
    return;
  }
}
#endif

//=============================================================================
// Function: mdlInitializeSizes
//=============================================================================

static void mdlInitializeSizes(SimStruct *S)
{

  //Check parameters
  ssSetNumSFcnParams(S, NUM_PARAMS);  // Number of expected parameters
#if defined(MATLAB_MEX_FILE)
  if(ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S))
  {
    mdlCheckParameters(S);
    if(ssGetErrorStatus(S) != NULL)
      return;
  }
  else
  {
    return; // Parameter mismatch will be reported by Simulink
  }
#endif

  //States
  ssSetNumContStates(S, 0);
  ssSetNumDiscStates(S, 0);

  //Input ports
  if(!ssSetNumInputPorts(S, NUM_INPUTS))
    return;
  ssSetInputPortWidth(S, 0, 2); //Width
  ssSetInputPortDataType(S, 0, SS_DOUBLE);  //Data Type
  ssSetInputPortRequiredContiguous(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 0, 1);

  //Output ports
  if(!ssSetNumOutputPorts(S, NUM_OUTPUTS))
    return;
  ssSetOutputPortWidth(S, 0, 1);            //Width
  ssSetOutputPortWidth(S, 1, 1);
  ssSetOutputPortDataType(S, 0, SS_UINT32); //Data Type
  ssSetOutputPortDataType(S, 1, SS_UINT32);

  ssSetNumSampleTimes(S, 1);

  ssSetNumRWork(S, 0);
  ssSetNumIWork(S, 0);
  ssSetNumPWork(S, 4);  //reserve elements in the pointers vector
  ssSetNumModes(S, 0);  //to store a C++ object
  ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE));
}

//=============================================================================
// Function: mdlInitializeSampleTimes
//=============================================================================

static void mdlInitializeSampleTimes(SimStruct *S)
{
  ssSetSampleTime(S, 0, *mxGetPr(ssGetSFcnParam(S, 1)));
  ssSetOffsetTime(S, 0, 0.0);
  ssSetModelReferenceSampleTimeDefaultInheritance(S);
}

//=============================================================================
// Function: mdlStart
//=============================================================================

#define MDL_START // Change to #undef to remove function
#if defined(MDL_START)

static void mdlStart(SimStruct *S)
{
  string  fileName = string(GetString(ssGetSFcnParam(S, 0)));

  ssGetPWork(S)[0] = (void *) new ifstream;
  ssGetPWork(S)[1] = (void *) new char[MAX_MSG_LEN];  // allocate the space of the msg
  ssGetPWork(S)[2] = (void *) new vector<string>;
  ssGetPWork(S)[3] = (void *) new double;

  ifstream  *myfile = (ifstream *) ssGetPWork(S)[0];
  double    *DT = (double *) ssGetPWork(S)[3];

  myfile->open(fileName.c_str(), ifstream::in);
  if(!myfile->is_open())
    ssSetErrorStatus(S, "Could not open ascii file containing the messages");

  // initialization: set the beginning of file to the first available time information
  int     line_nb = 0;
  int     pos;
  string  line;
  GPStime t_msg;
  GPStime t_msg_aft;

  while(!myfile->eof())
  {
    pos = myfile->tellg();
    if(pos == -1)
    {
      if VERBOSE mexPrintf
        (
          "searching first pointer position in file failed - pos=%d \n",
          pos
        );
      break;
    }

    myGetline(myfile, line);
    if VERBOSE mexPrintf
      (
        "initialization : searching for next time-tagged msg: %s \n",
        line.c_str()
      );

    if(GetMsgTime(line, t_msg))
    {
      if VERBOSE mexPrintf
        (
          "Found time-tagged msg (line=%d) t=[%d,%f] time-tagged msg=%s \n",
          line_nb,
          t_msg.week(),
          t_msg.secs(),
          line.c_str()
        );

      myfile->seekg(pos);
      break;
    }

    line_nb++;
  }

  while(!myfile->eof())
  {
    pos = myfile->tellg();
    if(pos == -1)
    {
      if VERBOSE mexPrintf
        (
          "searching second pointer position in file failed - pos=%d \n",
          pos
        );

      break;
    }

    myGetline(myfile, line);
    if VERBOSE mexPrintf
      (
        "initialization : searching for next next time-tagged msg: %s \n",
        line.c_str()
      );

    if(GetMsgTime(line, t_msg_aft) && (t_msg_aft > t_msg + 0.5))
    {
      if VERBOSE mexPrintf
        (
          "Found time-tagged msg (line=%d) t=[%d,%f] time-tagged msg=%s \n",
          line_nb,
          t_msg_aft.week(),
          t_msg_aft.secs(),
          line.c_str()
        );

      DT[0] = floor(t_msg_aft - t_msg) + 1.0;
      if VERBOSE mexPrintf("Estimated sample time is DT=%f \n", DT[0]);

      myfile->seekg(pos);
      break;
    }

    line_nb++;
  }

  if(myfile->eof())
    ssSetErrorStatus(S, "No time-tagged msg has been found.");
}
#endif

//=============================================================================
// Function: mdlOutputs
//=============================================================================

static void mdlOutputs(SimStruct *S, int_T tid)
{
  ifstream        *myfile = (ifstream *) ssGetPWork(S)[0];
  char            *msg = (char *) ssGetPWork(S)[1];
  vector<string>  *msg_list = (vector<string> *) ssGetPWork(S)[2];
  double          *DT = (double *) ssGetPWork(S)[3];
  GPStime         t_msg;
  uint32_T        *msg_addr = (uint32_T *) ssGetOutputPortRealSignal(S, 0);
  *msg_addr = (uint32_T) msg;

  uint32_T  *msg_length = (uint32_T *) ssGetOutputPortRealSignal(S, 1);
  string    line;
  real_T   *T_GPS = (real_T *) ssGetInputPortRealSignal(S, 0);
  GPStime   t_in = GPStime(int(T_GPS[0]), T_GPS[1]);

  if VERBOSE mexPrintf
    (
      "        ******************    \nEntering the output function. Input time = [%d,%f] \n",
      t_in.week(),
      t_in.secs()
    );

  // retrieve the time of the first msg (which is always a time-tagged msg)
  int pos = myfile->tellg();
  myGetline(myfile, line);
  myfile->seekg(pos);

  if(!GetMsgTime(line, t_msg))
    ssSetErrorStatus
    (
      S,
      "Unexpected error. The first msg must be a valid time-tagged msg."
    );

  // the action to be performed depends on the time of the first msg
  if(t_msg <= t_in - DT[0]) // msg are too old. Set the position in file corresponding to the input time
  {
    if VERBOSE mexPrintf("searching in the file for time-tagged msg at epoch as close as possible to external input time. \n");

    int line_nb = 0;
    int pos;
    while(!myfile->eof())
    {
      pos = myfile->tellg();
      myGetline(myfile, line);
      if((GetMsgTime(line, t_msg)) && (t_msg > t_in- DT[0]))
      {
        if VERBOSE mexPrintf
          (
            "Found time-tagged msg (line=%d) close to input time t=[%d,%f] time-tagged msg=%s \n",
            line_nb,
            t_msg.week(),
            t_msg.secs(),
            line.c_str()
          );

        myfile->seekg(pos);
        break;
      }

      line_nb++;
    }

    if(myfile->eof())
      ssSetErrorStatus
      (
        S,
        "No msg corresponding to the input time has been found."
      );
  }
  if(fabs(t_msg - t_in) <= DT[0])
  { // found a msg synchronized (tolerance equals message sample time) with the external clock.
    if VERBOSE mexPrintf("Synchronization : The time of the first msg in the file corresponds to the external time\n");

    pos = myfile->tellg();

    int line_nb = 0;
    while(!myfile->eof())
    {
      myGetline(myfile, line);
      if(GetMsgTime(line, t_msg) && (t_msg - t_in > DT[0] / 2.0))
      {
        if VERBOSE mexPrintf
          (
            "Found next time-tagged msg (line=%d) t=[%d,%f] time-tagged msg=%s \n",
            line_nb,
            t_msg.week(),
            t_msg.secs(),
            line.c_str()
          );

        myfile->seekg(pos);
        break;
      }

      line_nb++;
    }

    if(myfile->eof())
      ssSetErrorStatus(S, "No message anymore in the log ascii file.");

    // put all msg until next time-tagged msg in the buffer
    for(int i = 0; i < line_nb; i++)
    {
      myGetline(myfile, line);
      msg_list->push_back(line);
    }

    // send the msg stored in the buffer
    Sendbuffer(msg_list, msg_length, msg, S);
  }
  else if(t_msg > t_in) // if necessary try to get rid of msg stored in the buffer
    Sendbuffer(msg_list, msg_length, msg, S);

  if VERBOSE{ mexPrintf("End of the function call. The buffer now comprises: \n");
    for(unsigned int i = 0; i < msg_list->size(); i++)
      mexPrintf(" -> %s \n", (*msg_list)[i].c_str());
  }

  if(msg_list->size() > 9)
  {
    ssSetErrorStatus
    (
      S,
      "Unexpected error. Buffer size surprisingly high. Please check manually if this behavior is correct."
    );
  }
}

//=============================================================================
// Function: mdlTerminate
//=============================================================================

static void mdlTerminate(SimStruct *S)
{

  //Free allocated memory
  ifstream        *myfile = (ifstream *) ssGetPWork(S)[0];
  char            *msg = (char *) ssGetPWork(S)[1];
  vector<string>  *msg_list = (vector<string> *) ssGetPWork(S)[2];
  double          *DT = (double *) ssGetPWork(S)[3];
  myfile->close();
  delete myfile;
  delete msg;
  delete msg_list;
  delete DT;
}

//=============================================================================
// Required S-function trailer
//=============================================================================

#ifdef MATLAB_MEX_FILE  
#include "simulink.c"   
#else
#include "cg_sfun.h"  
#endif
#ifdef __cplusplus
} // end of extern "C" scope
#endif
