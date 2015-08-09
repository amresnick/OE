/* Include files */

#include "gif_model_sfun.h"
#include "gif_model_sfun_debug_macros.h"
#include "c1_gif_model.h"
#include "c3_gif_model.h"
#include "c4_gif_model.h"
#include "c5_gif_model.h"
#include "c6_gif_model.h"
#include "c7_gif_model.h"
#include "c8_gif_model.h"
#include "c9_gif_model.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _gif_modelMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void gif_model_initializer(void)
{
}

void gif_model_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_gif_model_method_dispatcher(SimStruct *simstructPtr, unsigned
  int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_gif_model_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_gif_model_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_gif_model_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_gif_model_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==6) {
    c6_gif_model_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==7) {
    c7_gif_model_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==8) {
    c8_gif_model_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==9) {
    c9_gif_model_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_gif_model_process_check_sum_call( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1268022120U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2246499946U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3730295406U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2115472725U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2045049875U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(64287385U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1590521267U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4232993571U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_gif_model_get_check_sum(mxArray *plhs[]);
          sf_c1_gif_model_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_gif_model_get_check_sum(mxArray *plhs[]);
          sf_c3_gif_model_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_gif_model_get_check_sum(mxArray *plhs[]);
          sf_c4_gif_model_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_gif_model_get_check_sum(mxArray *plhs[]);
          sf_c5_gif_model_get_check_sum(plhs);
          break;
        }

       case 6:
        {
          extern void sf_c6_gif_model_get_check_sum(mxArray *plhs[]);
          sf_c6_gif_model_get_check_sum(plhs);
          break;
        }

       case 7:
        {
          extern void sf_c7_gif_model_get_check_sum(mxArray *plhs[]);
          sf_c7_gif_model_get_check_sum(plhs);
          break;
        }

       case 8:
        {
          extern void sf_c8_gif_model_get_check_sum(mxArray *plhs[]);
          sf_c8_gif_model_get_check_sum(plhs);
          break;
        }

       case 9:
        {
          extern void sf_c9_gif_model_get_check_sum(mxArray *plhs[]);
          sf_c9_gif_model_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3564696471U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(678668628U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1090454852U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3896867807U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(568759817U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1202834838U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3020694660U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1546858337U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_gif_model_autoinheritance_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "bR4CYS9Ya9dmnLvtzIkxcE") == 0) {
          extern mxArray *sf_c1_gif_model_get_autoinheritance_info(void);
          plhs[0] = sf_c1_gif_model_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "fTSh6oxRbZE0exiDYLhju") == 0) {
          extern mxArray *sf_c3_gif_model_get_autoinheritance_info(void);
          plhs[0] = sf_c3_gif_model_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "bR4CYS9Ya9dmnLvtzIkxcE") == 0) {
          extern mxArray *sf_c4_gif_model_get_autoinheritance_info(void);
          plhs[0] = sf_c4_gif_model_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "fTSh6oxRbZE0exiDYLhju") == 0) {
          extern mxArray *sf_c5_gif_model_get_autoinheritance_info(void);
          plhs[0] = sf_c5_gif_model_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 6:
      {
        if (strcmp(aiChksum, "a4IUCwPExEhJu3YegvSUsD") == 0) {
          extern mxArray *sf_c6_gif_model_get_autoinheritance_info(void);
          plhs[0] = sf_c6_gif_model_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 7:
      {
        if (strcmp(aiChksum, "9JDc1j5ZztZ71VRtVptJaH") == 0) {
          extern mxArray *sf_c7_gif_model_get_autoinheritance_info(void);
          plhs[0] = sf_c7_gif_model_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 8:
      {
        if (strcmp(aiChksum, "aEmlRdcWta34xi3ci1BIHE") == 0) {
          extern mxArray *sf_c8_gif_model_get_autoinheritance_info(void);
          plhs[0] = sf_c8_gif_model_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 9:
      {
        if (strcmp(aiChksum, "2MdL4BPTIna67Di7MOb3RG") == 0) {
          extern mxArray *sf_c9_gif_model_get_autoinheritance_info(void);
          plhs[0] = sf_c9_gif_model_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_gif_model_get_eml_resolved_functions_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray *sf_c1_gif_model_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_gif_model_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray *sf_c3_gif_model_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_gif_model_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray *sf_c4_gif_model_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_gif_model_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray *sf_c5_gif_model_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_gif_model_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 6:
      {
        extern const mxArray *sf_c6_gif_model_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c6_gif_model_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 7:
      {
        extern const mxArray *sf_c7_gif_model_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c7_gif_model_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 8:
      {
        extern const mxArray *sf_c8_gif_model_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c8_gif_model_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 9:
      {
        extern const mxArray *sf_c9_gif_model_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c9_gif_model_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_gif_model_third_party_uses_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "7HjNslDLHSFGc1Iv5HLCLD") == 0) {
          extern mxArray *sf_c1_gif_model_third_party_uses_info(void);
          plhs[0] = sf_c1_gif_model_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "eyReHcIWb3qGPD7PaYH1tF") == 0) {
          extern mxArray *sf_c3_gif_model_third_party_uses_info(void);
          plhs[0] = sf_c3_gif_model_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "7HjNslDLHSFGc1Iv5HLCLD") == 0) {
          extern mxArray *sf_c4_gif_model_third_party_uses_info(void);
          plhs[0] = sf_c4_gif_model_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "eyReHcIWb3qGPD7PaYH1tF") == 0) {
          extern mxArray *sf_c5_gif_model_third_party_uses_info(void);
          plhs[0] = sf_c5_gif_model_third_party_uses_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "7ws4XobkucFnsea4OFpwqG") == 0) {
          extern mxArray *sf_c6_gif_model_third_party_uses_info(void);
          plhs[0] = sf_c6_gif_model_third_party_uses_info();
          break;
        }
      }

     case 7:
      {
        if (strcmp(tpChksum, "lShziEqI8eWDPZtmfi5gkF") == 0) {
          extern mxArray *sf_c7_gif_model_third_party_uses_info(void);
          plhs[0] = sf_c7_gif_model_third_party_uses_info();
          break;
        }
      }

     case 8:
      {
        if (strcmp(tpChksum, "iAm1qCZfEtGDbX2mAxVkSH") == 0) {
          extern mxArray *sf_c8_gif_model_third_party_uses_info(void);
          plhs[0] = sf_c8_gif_model_third_party_uses_info();
          break;
        }
      }

     case 9:
      {
        if (strcmp(tpChksum, "q5bs4X2BelDQwHWRgAIZzE") == 0) {
          extern mxArray *sf_c9_gif_model_third_party_uses_info(void);
          plhs[0] = sf_c9_gif_model_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void gif_model_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _gif_modelMachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "gif_model","sfun",0,8,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,_gif_modelMachineNumber_,0,
    0);
  sf_debug_set_machine_data_thresholds(debugInstance,_gif_modelMachineNumber_,0);
}

void gif_model_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_gif_model_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("gif_model",
      "gif_model");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_gif_model_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
