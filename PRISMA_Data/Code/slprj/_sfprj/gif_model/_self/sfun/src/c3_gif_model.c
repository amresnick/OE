/* Include files */

#include <stddef.h>
#include "blas.h"
#include "gif_model_sfun.h"
#include "c3_gif_model.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "gif_model_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c3_debug_family_names[4] = { "nargin", "nargout", "obs",
  "state" };

/* Function Declarations */
static void initialize_c3_gif_model(SFc3_gif_modelInstanceStruct *chartInstance);
static void initialize_params_c3_gif_model(SFc3_gif_modelInstanceStruct
  *chartInstance);
static void enable_c3_gif_model(SFc3_gif_modelInstanceStruct *chartInstance);
static void disable_c3_gif_model(SFc3_gif_modelInstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_gif_model(SFc3_gif_modelInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c3_gif_model(SFc3_gif_modelInstanceStruct
  *chartInstance);
static void set_sim_state_c3_gif_model(SFc3_gif_modelInstanceStruct
  *chartInstance, const mxArray *c3_st);
static void finalize_c3_gif_model(SFc3_gif_modelInstanceStruct *chartInstance);
static void sf_c3_gif_model(SFc3_gif_modelInstanceStruct *chartInstance);
static void initSimStructsc3_gif_model(SFc3_gif_modelInstanceStruct
  *chartInstance);
static void registerMessagesc3_gif_model(SFc3_gif_modelInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static void c3_emlrt_marshallIn(SFc3_gif_modelInstanceStruct *chartInstance,
  const mxArray *c3_state, const char_T *c3_identifier, real_T c3_y[6]);
static void c3_b_emlrt_marshallIn(SFc3_gif_modelInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[6]);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_c_emlrt_marshallIn(SFc3_gif_modelInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_d_emlrt_marshallIn(SFc3_gif_modelInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static uint8_T c3_e_emlrt_marshallIn(SFc3_gif_modelInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_gif_model, const char_T *c3_identifier);
static uint8_T c3_f_emlrt_marshallIn(SFc3_gif_modelInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_gif_modelInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_gif_model(SFc3_gif_modelInstanceStruct *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_is_active_c3_gif_model = 0U;
}

static void initialize_params_c3_gif_model(SFc3_gif_modelInstanceStruct
  *chartInstance)
{
}

static void enable_c3_gif_model(SFc3_gif_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_gif_model(SFc3_gif_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c3_update_debugger_state_c3_gif_model(SFc3_gif_modelInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c3_gif_model(SFc3_gif_modelInstanceStruct
  *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  int32_T c3_i0;
  real_T c3_u[6];
  const mxArray *c3_b_y = NULL;
  uint8_T c3_hoistedGlobal;
  uint8_T c3_b_u;
  const mxArray *c3_c_y = NULL;
  real_T (*c3_state)[6];
  c3_state = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(2), FALSE);
  for (c3_i0 = 0; c3_i0 < 6; c3_i0++) {
    c3_u[c3_i0] = (*c3_state)[c3_i0];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_hoistedGlobal = chartInstance->c3_is_active_c3_gif_model;
  c3_b_u = c3_hoistedGlobal;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  sf_mex_assign(&c3_st, c3_y, FALSE);
  return c3_st;
}

static void set_sim_state_c3_gif_model(SFc3_gif_modelInstanceStruct
  *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  real_T c3_dv0[6];
  int32_T c3_i1;
  real_T (*c3_state)[6];
  c3_state = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = TRUE;
  c3_u = sf_mex_dup(c3_st);
  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)),
                      "state", c3_dv0);
  for (c3_i1 = 0; c3_i1 < 6; c3_i1++) {
    (*c3_state)[c3_i1] = c3_dv0[c3_i1];
  }

  chartInstance->c3_is_active_c3_gif_model = c3_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 1)), "is_active_c3_gif_model");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_gif_model(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_gif_model(SFc3_gif_modelInstanceStruct *chartInstance)
{
}

static void sf_c3_gif_model(SFc3_gif_modelInstanceStruct *chartInstance)
{
  int32_T c3_i2;
  int32_T c3_i3;
  int32_T c3_i4;
  real_T c3_obs[81];
  uint32_T c3_debug_family_var_map[4];
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 1.0;
  real_T c3_state[6];
  int32_T c3_i5;
  int32_T c3_i6;
  real_T (*c3_b_state)[6];
  real_T (*c3_b_obs)[81];
  c3_b_state = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_b_obs = (real_T (*)[81])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
  for (c3_i2 = 0; c3_i2 < 81; c3_i2++) {
    _SFD_DATA_RANGE_CHECK((*c3_b_obs)[c3_i2], 0U);
  }

  for (c3_i3 = 0; c3_i3 < 6; c3_i3++) {
    _SFD_DATA_RANGE_CHECK((*c3_b_state)[c3_i3], 1U);
  }

  chartInstance->c3_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
  for (c3_i4 = 0; c3_i4 < 81; c3_i4++) {
    c3_obs[c3_i4] = (*c3_b_obs)[c3_i4];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c3_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_c_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_c_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_obs, 2U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_state, 3U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 4);
  for (c3_i5 = 0; c3_i5 < 6; c3_i5++) {
    c3_state[c3_i5] = c3_obs[c3_i5 + 15];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c3_i6 = 0; c3_i6 < 6; c3_i6++) {
    (*c3_b_state)[c3_i6] = c3_state[c3_i6];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_gif_modelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc3_gif_model(SFc3_gif_modelInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc3_gif_model(SFc3_gif_modelInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i7;
  real_T c3_b_inData[6];
  int32_T c3_i8;
  real_T c3_u[6];
  const mxArray *c3_y = NULL;
  SFc3_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc3_gif_modelInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i7 = 0; c3_i7 < 6; c3_i7++) {
    c3_b_inData[c3_i7] = (*(real_T (*)[6])c3_inData)[c3_i7];
  }

  for (c3_i8 = 0; c3_i8 < 6; c3_i8++) {
    c3_u[c3_i8] = c3_b_inData[c3_i8];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_emlrt_marshallIn(SFc3_gif_modelInstanceStruct *chartInstance,
  const mxArray *c3_state, const char_T *c3_identifier, real_T c3_y[6])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_state), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_state);
}

static void c3_b_emlrt_marshallIn(SFc3_gif_modelInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[6])
{
  real_T c3_dv1[6];
  int32_T c3_i9;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv1, 1, 0, 0U, 1, 0U, 1, 6);
  for (c3_i9 = 0; c3_i9 < 6; c3_i9++) {
    c3_y[c3_i9] = c3_dv1[c3_i9];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_state;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[6];
  int32_T c3_i10;
  SFc3_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc3_gif_modelInstanceStruct *)chartInstanceVoid;
  c3_state = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_state), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_state);
  for (c3_i10 = 0; c3_i10 < 6; c3_i10++) {
    (*(real_T (*)[6])c3_outData)[c3_i10] = c3_y[c3_i10];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i11;
  real_T c3_b_inData[81];
  int32_T c3_i12;
  real_T c3_u[81];
  const mxArray *c3_y = NULL;
  SFc3_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc3_gif_modelInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i11 = 0; c3_i11 < 81; c3_i11++) {
    c3_b_inData[c3_i11] = (*(real_T (*)[81])c3_inData)[c3_i11];
  }

  for (c3_i12 = 0; c3_i12 < 81; c3_i12++) {
    c3_u[c3_i12] = c3_b_inData[c3_i12];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 81), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc3_gif_modelInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static real_T c3_c_emlrt_marshallIn(SFc3_gif_modelInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d0, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_nargout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc3_gif_modelInstanceStruct *)chartInstanceVoid;
  c3_nargout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout), &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_gif_model_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  sf_mex_assign(&c3_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c3_nameCaptureInfo;
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc3_gif_modelInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static int32_T c3_d_emlrt_marshallIn(SFc3_gif_modelInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i13;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i13, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i13;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc3_gif_modelInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static uint8_T c3_e_emlrt_marshallIn(SFc3_gif_modelInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_gif_model, const char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_gif_model), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_gif_model);
  return c3_y;
}

static uint8_T c3_f_emlrt_marshallIn(SFc3_gif_modelInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void init_dsm_address_info(SFc3_gif_modelInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c3_gif_model_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(865950394U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1093466922U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(956920775U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(532134106U);
}

mxArray *sf_c3_gif_model_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("fTSh6oxRbZE0exiDYLhju");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(81);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_gif_model_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c3_gif_model(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"state\",},{M[8],M[0],T\"is_active_c3_gif_model\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_gif_model_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_gif_modelInstanceStruct *chartInstance;
    chartInstance = (SFc3_gif_modelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _gif_modelMachineNumber_,
           3,
           1,
           1,
           2,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_gif_modelMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_gif_modelMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _gif_modelMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"obs");
          _SFD_SET_DATA_PROPS(1,2,0,1,"state");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,96);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 81;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)
            c3_sf_marshallIn);
        }

        {
          real_T (*c3_obs)[81];
          real_T (*c3_state)[6];
          c3_state = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
          c3_obs = (real_T (*)[81])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c3_obs);
          _SFD_SET_DATA_VALUE_PTR(1U, *c3_state);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _gif_modelMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "eyReHcIWb3qGPD7PaYH1tF";
}

static void sf_opaque_initialize_c3_gif_model(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_gif_modelInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c3_gif_model((SFc3_gif_modelInstanceStruct*)
    chartInstanceVar);
  initialize_c3_gif_model((SFc3_gif_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_gif_model(void *chartInstanceVar)
{
  enable_c3_gif_model((SFc3_gif_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_gif_model(void *chartInstanceVar)
{
  disable_c3_gif_model((SFc3_gif_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_gif_model(void *chartInstanceVar)
{
  sf_c3_gif_model((SFc3_gif_modelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_gif_model(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_gif_model((SFc3_gif_modelInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_gif_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c3_gif_model(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_gif_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_gif_model((SFc3_gif_modelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_gif_model(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_gif_model(S);
}

static void sf_opaque_set_sim_state_c3_gif_model(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c3_gif_model(S, st);
}

static void sf_opaque_terminate_c3_gif_model(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_gif_modelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_gif_model_optimization_info();
    }

    finalize_c3_gif_model((SFc3_gif_modelInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_gif_model((SFc3_gif_modelInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_gif_model(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_gif_model((SFc3_gif_modelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_gif_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_gif_model_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,3,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(320005477U));
  ssSetChecksum1(S,(2589215106U));
  ssSetChecksum2(S,(3189500917U));
  ssSetChecksum3(S,(650470917U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c3_gif_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_gif_model(SimStruct *S)
{
  SFc3_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc3_gif_modelInstanceStruct *)utMalloc(sizeof
    (SFc3_gif_modelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_gif_modelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_gif_model;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_gif_model;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_gif_model;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_gif_model;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_gif_model;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_gif_model;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_gif_model;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c3_gif_model;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_gif_model;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_gif_model;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_gif_model;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c3_gif_model_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_gif_model(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_gif_model(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_gif_model(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_gif_model_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
