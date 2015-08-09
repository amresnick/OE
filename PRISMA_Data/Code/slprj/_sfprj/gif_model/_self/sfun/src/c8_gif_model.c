/* Include files */

#include <stddef.h>
#include "blas.h"
#include "gif_model_sfun.h"
#include "c8_gif_model.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "gif_model_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c8_debug_family_names[5] = { "nargin", "nargout", "obs",
  "delayed_obs", "out" };

/* Function Declarations */
static void initialize_c8_gif_model(SFc8_gif_modelInstanceStruct *chartInstance);
static void initialize_params_c8_gif_model(SFc8_gif_modelInstanceStruct
  *chartInstance);
static void enable_c8_gif_model(SFc8_gif_modelInstanceStruct *chartInstance);
static void disable_c8_gif_model(SFc8_gif_modelInstanceStruct *chartInstance);
static void c8_update_debugger_state_c8_gif_model(SFc8_gif_modelInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c8_gif_model(SFc8_gif_modelInstanceStruct
  *chartInstance);
static void set_sim_state_c8_gif_model(SFc8_gif_modelInstanceStruct
  *chartInstance, const mxArray *c8_st);
static void finalize_c8_gif_model(SFc8_gif_modelInstanceStruct *chartInstance);
static void sf_c8_gif_model(SFc8_gif_modelInstanceStruct *chartInstance);
static void initSimStructsc8_gif_model(SFc8_gif_modelInstanceStruct
  *chartInstance);
static void registerMessagesc8_gif_model(SFc8_gif_modelInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber);
static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData);
static void c8_emlrt_marshallIn(SFc8_gif_modelInstanceStruct *chartInstance,
  const mxArray *c8_out, const char_T *c8_identifier, real_T c8_y[81]);
static void c8_b_emlrt_marshallIn(SFc8_gif_modelInstanceStruct *chartInstance,
  const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId, real_T c8_y[81]);
static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static real_T c8_c_emlrt_marshallIn(SFc8_gif_modelInstanceStruct *chartInstance,
  const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static int32_T c8_d_emlrt_marshallIn(SFc8_gif_modelInstanceStruct *chartInstance,
  const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static uint8_T c8_e_emlrt_marshallIn(SFc8_gif_modelInstanceStruct *chartInstance,
  const mxArray *c8_b_is_active_c8_gif_model, const char_T *c8_identifier);
static uint8_T c8_f_emlrt_marshallIn(SFc8_gif_modelInstanceStruct *chartInstance,
  const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void init_dsm_address_info(SFc8_gif_modelInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c8_gif_model(SFc8_gif_modelInstanceStruct *chartInstance)
{
  chartInstance->c8_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c8_is_active_c8_gif_model = 0U;
}

static void initialize_params_c8_gif_model(SFc8_gif_modelInstanceStruct
  *chartInstance)
{
}

static void enable_c8_gif_model(SFc8_gif_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c8_gif_model(SFc8_gif_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c8_update_debugger_state_c8_gif_model(SFc8_gif_modelInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c8_gif_model(SFc8_gif_modelInstanceStruct
  *chartInstance)
{
  const mxArray *c8_st;
  const mxArray *c8_y = NULL;
  int32_T c8_i0;
  real_T c8_u[81];
  const mxArray *c8_b_y = NULL;
  uint8_T c8_hoistedGlobal;
  uint8_T c8_b_u;
  const mxArray *c8_c_y = NULL;
  real_T (*c8_out)[81];
  c8_out = (real_T (*)[81])ssGetOutputPortSignal(chartInstance->S, 1);
  c8_st = NULL;
  c8_st = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_createcellarray(2), FALSE);
  for (c8_i0 = 0; c8_i0 < 81; c8_i0++) {
    c8_u[c8_i0] = (*c8_out)[c8_i0];
  }

  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 81), FALSE);
  sf_mex_setcell(c8_y, 0, c8_b_y);
  c8_hoistedGlobal = chartInstance->c8_is_active_c8_gif_model;
  c8_b_u = c8_hoistedGlobal;
  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c8_y, 1, c8_c_y);
  sf_mex_assign(&c8_st, c8_y, FALSE);
  return c8_st;
}

static void set_sim_state_c8_gif_model(SFc8_gif_modelInstanceStruct
  *chartInstance, const mxArray *c8_st)
{
  const mxArray *c8_u;
  real_T c8_dv0[81];
  int32_T c8_i1;
  real_T (*c8_out)[81];
  c8_out = (real_T (*)[81])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c8_doneDoubleBufferReInit = TRUE;
  c8_u = sf_mex_dup(c8_st);
  c8_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 0)), "out",
                      c8_dv0);
  for (c8_i1 = 0; c8_i1 < 81; c8_i1++) {
    (*c8_out)[c8_i1] = c8_dv0[c8_i1];
  }

  chartInstance->c8_is_active_c8_gif_model = c8_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c8_u, 1)), "is_active_c8_gif_model");
  sf_mex_destroy(&c8_u);
  c8_update_debugger_state_c8_gif_model(chartInstance);
  sf_mex_destroy(&c8_st);
}

static void finalize_c8_gif_model(SFc8_gif_modelInstanceStruct *chartInstance)
{
}

static void sf_c8_gif_model(SFc8_gif_modelInstanceStruct *chartInstance)
{
  int32_T c8_i2;
  int32_T c8_i3;
  int32_T c8_i4;
  int32_T c8_i5;
  real_T c8_obs[81];
  int32_T c8_i6;
  real_T c8_delayed_obs[81];
  uint32_T c8_debug_family_var_map[5];
  real_T c8_nargin = 2.0;
  real_T c8_nargout = 1.0;
  real_T c8_out[81];
  int32_T c8_i7;
  boolean_T c8_varargin_1[3];
  boolean_T c8_mtmp;
  int32_T c8_ix;
  int32_T c8_b_ix;
  boolean_T c8_a;
  boolean_T c8_b;
  boolean_T c8_p;
  boolean_T c8_b_mtmp;
  boolean_T c8_minval;
  int32_T c8_i8;
  int32_T c8_i9;
  int32_T c8_i10;
  real_T (*c8_b_out)[81];
  real_T (*c8_b_delayed_obs)[81];
  real_T (*c8_b_obs)[81];
  c8_b_delayed_obs = (real_T (*)[81])ssGetInputPortSignal(chartInstance->S, 1);
  c8_b_out = (real_T (*)[81])ssGetOutputPortSignal(chartInstance->S, 1);
  c8_b_obs = (real_T (*)[81])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 6U, chartInstance->c8_sfEvent);
  for (c8_i2 = 0; c8_i2 < 81; c8_i2++) {
    _SFD_DATA_RANGE_CHECK((*c8_b_obs)[c8_i2], 0U);
  }

  for (c8_i3 = 0; c8_i3 < 81; c8_i3++) {
    _SFD_DATA_RANGE_CHECK((*c8_b_out)[c8_i3], 1U);
  }

  for (c8_i4 = 0; c8_i4 < 81; c8_i4++) {
    _SFD_DATA_RANGE_CHECK((*c8_b_delayed_obs)[c8_i4], 2U);
  }

  chartInstance->c8_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 6U, chartInstance->c8_sfEvent);
  for (c8_i5 = 0; c8_i5 < 81; c8_i5++) {
    c8_obs[c8_i5] = (*c8_b_obs)[c8_i5];
  }

  for (c8_i6 = 0; c8_i6 < 81; c8_i6++) {
    c8_delayed_obs[c8_i6] = (*c8_b_delayed_obs)[c8_i6];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 5U, 5U, c8_debug_family_names,
    c8_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargin, 0U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargout, 1U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_obs, 2U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_delayed_obs, 3U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_out, 4U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 4);
  for (c8_i7 = 0; c8_i7 < 3; c8_i7++) {
    c8_varargin_1[c8_i7] = (c8_obs[c8_i7 + 15] == 0.0);
  }

  c8_mtmp = c8_varargin_1[0];
  for (c8_ix = 2; c8_ix < 4; c8_ix++) {
    c8_b_ix = c8_ix;
    c8_a = c8_varargin_1[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c8_b_ix), 1, 3, 1, 0) - 1];
    c8_b = c8_mtmp;
    c8_p = ((int32_T)c8_a < (int32_T)c8_b);
    if (c8_p) {
      c8_mtmp = c8_varargin_1[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c8_b_ix), 1, 3, 1, 0) - 1];
    }
  }

  c8_b_mtmp = c8_mtmp;
  c8_minval = c8_b_mtmp;
  if (CV_EML_IF(0, 1, 0, (real_T)c8_minval == 1.0)) {
    _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 5);
    for (c8_i8 = 0; c8_i8 < 81; c8_i8++) {
      c8_out[c8_i8] = c8_delayed_obs[c8_i8];
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 7);
    for (c8_i9 = 0; c8_i9 < 81; c8_i9++) {
      c8_out[c8_i9] = c8_obs[c8_i9];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, -7);
  _SFD_SYMBOL_SCOPE_POP();
  for (c8_i10 = 0; c8_i10 < 81; c8_i10++) {
    (*c8_b_out)[c8_i10] = c8_out[c8_i10];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c8_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_gif_modelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc8_gif_model(SFc8_gif_modelInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc8_gif_model(SFc8_gif_modelInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber)
{
}

static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i11;
  real_T c8_b_inData[81];
  int32_T c8_i12;
  real_T c8_u[81];
  const mxArray *c8_y = NULL;
  SFc8_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc8_gif_modelInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  for (c8_i11 = 0; c8_i11 < 81; c8_i11++) {
    c8_b_inData[c8_i11] = (*(real_T (*)[81])c8_inData)[c8_i11];
  }

  for (c8_i12 = 0; c8_i12 < 81; c8_i12++) {
    c8_u[c8_i12] = c8_b_inData[c8_i12];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 81), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static void c8_emlrt_marshallIn(SFc8_gif_modelInstanceStruct *chartInstance,
  const mxArray *c8_out, const char_T *c8_identifier, real_T c8_y[81])
{
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_out), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_out);
}

static void c8_b_emlrt_marshallIn(SFc8_gif_modelInstanceStruct *chartInstance,
  const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId, real_T c8_y[81])
{
  real_T c8_dv1[81];
  int32_T c8_i13;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv1, 1, 0, 0U, 1, 0U, 1, 81);
  for (c8_i13 = 0; c8_i13 < 81; c8_i13++) {
    c8_y[c8_i13] = c8_dv1[c8_i13];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_out;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[81];
  int32_T c8_i14;
  SFc8_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc8_gif_modelInstanceStruct *)chartInstanceVoid;
  c8_out = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_out), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_out);
  for (c8_i14 = 0; c8_i14 < 81; c8_i14++) {
    (*(real_T (*)[81])c8_outData)[c8_i14] = c8_y[c8_i14];
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  real_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc8_gif_modelInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(real_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static real_T c8_c_emlrt_marshallIn(SFc8_gif_modelInstanceStruct *chartInstance,
  const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  real_T c8_y;
  real_T c8_d0;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_d0, 1, 0, 0U, 0, 0U, 0);
  c8_y = c8_d0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_nargout;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y;
  SFc8_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc8_gif_modelInstanceStruct *)chartInstanceVoid;
  c8_nargout = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_nargout), &c8_thisId);
  sf_mex_destroy(&c8_nargout);
  *(real_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

const mxArray *sf_c8_gif_model_get_eml_resolved_functions_info(void)
{
  const mxArray *c8_nameCaptureInfo;
  c8_ResolvedFunctionInfo c8_info[12];
  c8_ResolvedFunctionInfo (*c8_b_info)[12];
  const mxArray *c8_m0 = NULL;
  int32_T c8_i15;
  c8_ResolvedFunctionInfo *c8_r0;
  c8_nameCaptureInfo = NULL;
  c8_nameCaptureInfo = NULL;
  c8_b_info = (c8_ResolvedFunctionInfo (*)[12])c8_info;
  (*c8_b_info)[0].context = "";
  (*c8_b_info)[0].name = "min";
  (*c8_b_info)[0].dominantType = "logical";
  (*c8_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  (*c8_b_info)[0].fileTimeLo = 1311287718U;
  (*c8_b_info)[0].fileTimeHi = 0U;
  (*c8_b_info)[0].mFileTimeLo = 0U;
  (*c8_b_info)[0].mFileTimeHi = 0U;
  (*c8_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  (*c8_b_info)[1].name = "eml_min_or_max";
  (*c8_b_info)[1].dominantType = "char";
  (*c8_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  (*c8_b_info)[1].fileTimeLo = 1334103890U;
  (*c8_b_info)[1].fileTimeHi = 0U;
  (*c8_b_info)[1].mFileTimeLo = 0U;
  (*c8_b_info)[1].mFileTimeHi = 0U;
  (*c8_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum";
  (*c8_b_info)[2].name = "eml_const_nonsingleton_dim";
  (*c8_b_info)[2].dominantType = "logical";
  (*c8_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m";
  (*c8_b_info)[2].fileTimeLo = 1286851096U;
  (*c8_b_info)[2].fileTimeHi = 0U;
  (*c8_b_info)[2].mFileTimeLo = 0U;
  (*c8_b_info)[2].mFileTimeHi = 0U;
  (*c8_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum";
  (*c8_b_info)[3].name = "eml_scalar_eg";
  (*c8_b_info)[3].dominantType = "logical";
  (*c8_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c8_b_info)[3].fileTimeLo = 1286851196U;
  (*c8_b_info)[3].fileTimeHi = 0U;
  (*c8_b_info)[3].mFileTimeLo = 0U;
  (*c8_b_info)[3].mFileTimeHi = 0U;
  (*c8_b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum";
  (*c8_b_info)[4].name = "eml_index_class";
  (*c8_b_info)[4].dominantType = "";
  (*c8_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  (*c8_b_info)[4].fileTimeLo = 1323202978U;
  (*c8_b_info)[4].fileTimeHi = 0U;
  (*c8_b_info)[4].mFileTimeLo = 0U;
  (*c8_b_info)[4].mFileTimeHi = 0U;
  (*c8_b_info)[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub";
  (*c8_b_info)[5].name = "eml_index_class";
  (*c8_b_info)[5].dominantType = "";
  (*c8_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  (*c8_b_info)[5].fileTimeLo = 1323202978U;
  (*c8_b_info)[5].fileTimeHi = 0U;
  (*c8_b_info)[5].mFileTimeLo = 0U;
  (*c8_b_info)[5].mFileTimeHi = 0U;
  (*c8_b_info)[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub";
  (*c8_b_info)[6].name = "isnan";
  (*c8_b_info)[6].dominantType = "logical";
  (*c8_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  (*c8_b_info)[6].fileTimeLo = 1286851160U;
  (*c8_b_info)[6].fileTimeHi = 0U;
  (*c8_b_info)[6].mFileTimeLo = 0U;
  (*c8_b_info)[6].mFileTimeHi = 0U;
  (*c8_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub";
  (*c8_b_info)[7].name = "eml_index_plus";
  (*c8_b_info)[7].dominantType = "coder.internal.indexInt";
  (*c8_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  (*c8_b_info)[7].fileTimeLo = 1286851178U;
  (*c8_b_info)[7].fileTimeHi = 0U;
  (*c8_b_info)[7].mFileTimeLo = 0U;
  (*c8_b_info)[7].mFileTimeHi = 0U;
  (*c8_b_info)[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  (*c8_b_info)[8].name = "eml_index_class";
  (*c8_b_info)[8].dominantType = "";
  (*c8_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  (*c8_b_info)[8].fileTimeLo = 1323202978U;
  (*c8_b_info)[8].fileTimeHi = 0U;
  (*c8_b_info)[8].mFileTimeLo = 0U;
  (*c8_b_info)[8].mFileTimeHi = 0U;
  (*c8_b_info)[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub";
  (*c8_b_info)[9].name = "eml_int_forloop_overflow_check";
  (*c8_b_info)[9].dominantType = "";
  (*c8_b_info)[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  (*c8_b_info)[9].fileTimeLo = 1346542740U;
  (*c8_b_info)[9].fileTimeHi = 0U;
  (*c8_b_info)[9].mFileTimeLo = 0U;
  (*c8_b_info)[9].mFileTimeHi = 0U;
  (*c8_b_info)[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  (*c8_b_info)[10].name = "intmax";
  (*c8_b_info)[10].dominantType = "char";
  (*c8_b_info)[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  (*c8_b_info)[10].fileTimeLo = 1311287716U;
  (*c8_b_info)[10].fileTimeHi = 0U;
  (*c8_b_info)[10].mFileTimeLo = 0U;
  (*c8_b_info)[10].mFileTimeHi = 0U;
  (*c8_b_info)[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub";
  (*c8_b_info)[11].name = "eml_relop";
  (*c8_b_info)[11].dominantType = "function_handle";
  (*c8_b_info)[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_relop.m";
  (*c8_b_info)[11].fileTimeLo = 1342483582U;
  (*c8_b_info)[11].fileTimeHi = 0U;
  (*c8_b_info)[11].mFileTimeLo = 0U;
  (*c8_b_info)[11].mFileTimeHi = 0U;
  sf_mex_assign(&c8_m0, sf_mex_createstruct("nameCaptureInfo", 1, 12), FALSE);
  for (c8_i15 = 0; c8_i15 < 12; c8_i15++) {
    c8_r0 = &c8_info[c8_i15];
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->context)), "context", "nameCaptureInfo",
                    c8_i15);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c8_r0->name)), "name", "nameCaptureInfo", c8_i15);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c8_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c8_i15);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->resolved)), "resolved", "nameCaptureInfo",
                    c8_i15);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c8_i15);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c8_i15);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c8_i15);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c8_i15);
  }

  sf_mex_assign(&c8_nameCaptureInfo, c8_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c8_nameCaptureInfo);
  return c8_nameCaptureInfo;
}

static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc8_gif_modelInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(int32_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static int32_T c8_d_emlrt_marshallIn(SFc8_gif_modelInstanceStruct *chartInstance,
  const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int32_T c8_y;
  int32_T c8_i16;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_i16, 1, 6, 0U, 0, 0U, 0);
  c8_y = c8_i16;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_b_sfEvent;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  int32_T c8_y;
  SFc8_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc8_gif_modelInstanceStruct *)chartInstanceVoid;
  c8_b_sfEvent = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_sfEvent),
    &c8_thisId);
  sf_mex_destroy(&c8_b_sfEvent);
  *(int32_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static uint8_T c8_e_emlrt_marshallIn(SFc8_gif_modelInstanceStruct *chartInstance,
  const mxArray *c8_b_is_active_c8_gif_model, const char_T *c8_identifier)
{
  uint8_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c8_b_is_active_c8_gif_model), &c8_thisId);
  sf_mex_destroy(&c8_b_is_active_c8_gif_model);
  return c8_y;
}

static uint8_T c8_f_emlrt_marshallIn(SFc8_gif_modelInstanceStruct *chartInstance,
  const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  uint8_T c8_u0;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_u0, 1, 3, 0U, 0, 0U, 0);
  c8_y = c8_u0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void init_dsm_address_info(SFc8_gif_modelInstanceStruct *chartInstance)
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

void sf_c8_gif_model_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3772163916U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(857699375U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3598758110U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(238004889U);
}

mxArray *sf_c8_gif_model_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("aEmlRdcWta34xi3ci1BIHE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(81);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c8_gif_model_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c8_gif_model(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"out\",},{M[8],M[0],T\"is_active_c8_gif_model\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c8_gif_model_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc8_gif_modelInstanceStruct *chartInstance;
    chartInstance = (SFc8_gif_modelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _gif_modelMachineNumber_,
           8,
           1,
           1,
           3,
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
          _SFD_SET_DATA_PROPS(1,2,0,1,"out");
          _SFD_SET_DATA_PROPS(2,1,1,0,"delayed_obs");
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
        _SFD_CV_INIT_EML(0,1,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,173);
        _SFD_CV_INIT_EML_IF(0,1,0,91,122,146,169);
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
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 81;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)
            c8_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 81;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c8_obs)[81];
          real_T (*c8_out)[81];
          real_T (*c8_delayed_obs)[81];
          c8_delayed_obs = (real_T (*)[81])ssGetInputPortSignal(chartInstance->S,
            1);
          c8_out = (real_T (*)[81])ssGetOutputPortSignal(chartInstance->S, 1);
          c8_obs = (real_T (*)[81])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c8_obs);
          _SFD_SET_DATA_VALUE_PTR(1U, *c8_out);
          _SFD_SET_DATA_VALUE_PTR(2U, *c8_delayed_obs);
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
  return "iAm1qCZfEtGDbX2mAxVkSH";
}

static void sf_opaque_initialize_c8_gif_model(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc8_gif_modelInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c8_gif_model((SFc8_gif_modelInstanceStruct*)
    chartInstanceVar);
  initialize_c8_gif_model((SFc8_gif_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c8_gif_model(void *chartInstanceVar)
{
  enable_c8_gif_model((SFc8_gif_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c8_gif_model(void *chartInstanceVar)
{
  disable_c8_gif_model((SFc8_gif_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c8_gif_model(void *chartInstanceVar)
{
  sf_c8_gif_model((SFc8_gif_modelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c8_gif_model(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c8_gif_model((SFc8_gif_modelInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_gif_model();/* state var info */
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

extern void sf_internal_set_sim_state_c8_gif_model(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_gif_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c8_gif_model((SFc8_gif_modelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c8_gif_model(SimStruct* S)
{
  return sf_internal_get_sim_state_c8_gif_model(S);
}

static void sf_opaque_set_sim_state_c8_gif_model(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c8_gif_model(S, st);
}

static void sf_opaque_terminate_c8_gif_model(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc8_gif_modelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_gif_model_optimization_info();
    }

    finalize_c8_gif_model((SFc8_gif_modelInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc8_gif_model((SFc8_gif_modelInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c8_gif_model(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c8_gif_model((SFc8_gif_modelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c8_gif_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_gif_model_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      8);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,8,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,8,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,8);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,8,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,8,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,8);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2764110813U));
  ssSetChecksum1(S,(3405706906U));
  ssSetChecksum2(S,(97159038U));
  ssSetChecksum3(S,(957473738U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c8_gif_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c8_gif_model(SimStruct *S)
{
  SFc8_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc8_gif_modelInstanceStruct *)utMalloc(sizeof
    (SFc8_gif_modelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc8_gif_modelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c8_gif_model;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c8_gif_model;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c8_gif_model;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c8_gif_model;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c8_gif_model;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c8_gif_model;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c8_gif_model;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c8_gif_model;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c8_gif_model;
  chartInstance->chartInfo.mdlStart = mdlStart_c8_gif_model;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c8_gif_model;
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

void c8_gif_model_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c8_gif_model(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c8_gif_model(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c8_gif_model(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c8_gif_model_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
