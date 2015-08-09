/* Include files */

#include <stddef.h>
#include "blas.h"
#include "gif_model_sfun.h"
#include "c4_gif_model.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "gif_model_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c4_debug_family_names[10] = { "R", "rot_xyz_to_ijk", "w",
  "nargin", "nargout", "pos_xyz", "theta", "vel_xyz", "pos_ijk", "vel_ijk" };

/* Function Declarations */
static void initialize_c4_gif_model(SFc4_gif_modelInstanceStruct *chartInstance);
static void initialize_params_c4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance);
static void enable_c4_gif_model(SFc4_gif_modelInstanceStruct *chartInstance);
static void disable_c4_gif_model(SFc4_gif_modelInstanceStruct *chartInstance);
static void c4_update_debugger_state_c4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance);
static void set_sim_state_c4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance, const mxArray *c4_st);
static void finalize_c4_gif_model(SFc4_gif_modelInstanceStruct *chartInstance);
static void sf_c4_gif_model(SFc4_gif_modelInstanceStruct *chartInstance);
static void c4_chartstep_c4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance);
static void initSimStructsc4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance);
static void registerMessagesc4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static void c4_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_vel_ijk, const char_T *c4_identifier, real_T c4_y[3]);
static void c4_b_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[3]);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_c_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_d_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[9]);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[15]);
static void c4_eml_scalar_eg(SFc4_gif_modelInstanceStruct *chartInstance);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_e_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static uint8_T c4_f_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_gif_model, const char_T *c4_identifier);
static uint8_T c4_g_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void init_dsm_address_info(SFc4_gif_modelInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c4_gif_model(SFc4_gif_modelInstanceStruct *chartInstance)
{
  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c4_is_active_c4_gif_model = 0U;
}

static void initialize_params_c4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance)
{
}

static void enable_c4_gif_model(SFc4_gif_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c4_gif_model(SFc4_gif_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c4_update_debugger_state_c4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  int32_T c4_i0;
  real_T c4_u[3];
  const mxArray *c4_b_y = NULL;
  int32_T c4_i1;
  real_T c4_b_u[3];
  const mxArray *c4_c_y = NULL;
  uint8_T c4_hoistedGlobal;
  uint8_T c4_c_u;
  const mxArray *c4_d_y = NULL;
  real_T (*c4_vel_ijk)[3];
  real_T (*c4_pos_ijk)[3];
  c4_vel_ijk = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c4_pos_ijk = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellarray(3), FALSE);
  for (c4_i0 = 0; c4_i0 < 3; c4_i0++) {
    c4_u[c4_i0] = (*c4_pos_ijk)[c4_i0];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  for (c4_i1 = 0; c4_i1 < 3; c4_i1++) {
    c4_b_u[c4_i1] = (*c4_vel_ijk)[c4_i1];
  }

  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_hoistedGlobal = chartInstance->c4_is_active_c4_gif_model;
  c4_c_u = c4_hoistedGlobal;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c4_y, 2, c4_d_y);
  sf_mex_assign(&c4_st, c4_y, FALSE);
  return c4_st;
}

static void set_sim_state_c4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance, const mxArray *c4_st)
{
  const mxArray *c4_u;
  real_T c4_dv0[3];
  int32_T c4_i2;
  real_T c4_dv1[3];
  int32_T c4_i3;
  real_T (*c4_pos_ijk)[3];
  real_T (*c4_vel_ijk)[3];
  c4_vel_ijk = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c4_pos_ijk = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c4_doneDoubleBufferReInit = TRUE;
  c4_u = sf_mex_dup(c4_st);
  c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 0)),
                      "pos_ijk", c4_dv0);
  for (c4_i2 = 0; c4_i2 < 3; c4_i2++) {
    (*c4_pos_ijk)[c4_i2] = c4_dv0[c4_i2];
  }

  c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 1)),
                      "vel_ijk", c4_dv1);
  for (c4_i3 = 0; c4_i3 < 3; c4_i3++) {
    (*c4_vel_ijk)[c4_i3] = c4_dv1[c4_i3];
  }

  chartInstance->c4_is_active_c4_gif_model = c4_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c4_u, 2)), "is_active_c4_gif_model");
  sf_mex_destroy(&c4_u);
  c4_update_debugger_state_c4_gif_model(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_gif_model(SFc4_gif_modelInstanceStruct *chartInstance)
{
}

static void sf_c4_gif_model(SFc4_gif_modelInstanceStruct *chartInstance)
{
  int32_T c4_i4;
  int32_T c4_i5;
  int32_T c4_i6;
  int32_T c4_i7;
  real_T *c4_theta;
  real_T (*c4_vel_ijk)[3];
  real_T (*c4_vel_xyz)[3];
  real_T (*c4_pos_ijk)[3];
  real_T (*c4_pos_xyz)[3];
  c4_vel_ijk = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c4_vel_xyz = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c4_pos_ijk = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_theta = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c4_pos_xyz = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, chartInstance->c4_sfEvent);
  for (c4_i4 = 0; c4_i4 < 3; c4_i4++) {
    _SFD_DATA_RANGE_CHECK((*c4_pos_xyz)[c4_i4], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*c4_theta, 1U);
  for (c4_i5 = 0; c4_i5 < 3; c4_i5++) {
    _SFD_DATA_RANGE_CHECK((*c4_pos_ijk)[c4_i5], 2U);
  }

  for (c4_i6 = 0; c4_i6 < 3; c4_i6++) {
    _SFD_DATA_RANGE_CHECK((*c4_vel_xyz)[c4_i6], 3U);
  }

  for (c4_i7 = 0; c4_i7 < 3; c4_i7++) {
    _SFD_DATA_RANGE_CHECK((*c4_vel_ijk)[c4_i7], 4U);
  }

  chartInstance->c4_sfEvent = CALL_EVENT;
  c4_chartstep_c4_gif_model(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_gif_modelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c4_chartstep_c4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance)
{
  real_T c4_hoistedGlobal;
  int32_T c4_i8;
  real_T c4_pos_xyz[3];
  real_T c4_theta;
  int32_T c4_i9;
  real_T c4_vel_xyz[3];
  uint32_T c4_debug_family_var_map[10];
  real_T c4_R[9];
  real_T c4_rot_xyz_to_ijk[9];
  real_T c4_w[3];
  real_T c4_nargin = 3.0;
  real_T c4_nargout = 2.0;
  real_T c4_pos_ijk[3];
  real_T c4_vel_ijk[3];
  real_T c4_x;
  real_T c4_b_x;
  real_T c4_c_x;
  real_T c4_d_x;
  real_T c4_e_x;
  real_T c4_f_x;
  real_T c4_g_x;
  real_T c4_h_x;
  int32_T c4_i10;
  int32_T c4_i11;
  static real_T c4_dv2[3] = { 0.0, 0.0, 1.0 };

  int32_T c4_i12;
  int32_T c4_i13;
  int32_T c4_i14;
  int32_T c4_i15;
  int32_T c4_i16;
  real_T c4_a[9];
  int32_T c4_i17;
  real_T c4_b[3];
  int32_T c4_i18;
  int32_T c4_i19;
  int32_T c4_i20;
  real_T c4_C[3];
  int32_T c4_i21;
  int32_T c4_i22;
  int32_T c4_i23;
  int32_T c4_i24;
  int32_T c4_i25;
  int32_T c4_i26;
  int32_T c4_i27;
  real_T c4_b_a[3];
  int32_T c4_i28;
  real_T c4_c_a;
  real_T c4_b_b;
  real_T c4_y;
  real_T c4_d_a;
  real_T c4_c_b;
  real_T c4_b_y;
  real_T c4_c1;
  real_T c4_e_a;
  real_T c4_d_b;
  real_T c4_c_y;
  real_T c4_f_a;
  real_T c4_e_b;
  real_T c4_d_y;
  real_T c4_c2;
  real_T c4_g_a;
  real_T c4_f_b;
  real_T c4_e_y;
  real_T c4_h_a;
  real_T c4_g_b;
  real_T c4_f_y;
  real_T c4_c3;
  int32_T c4_i29;
  int32_T c4_i30;
  int32_T c4_i31;
  int32_T c4_i32;
  int32_T c4_i33;
  int32_T c4_i34;
  int32_T c4_i35;
  int32_T c4_i36;
  int32_T c4_i37;
  int32_T c4_i38;
  int32_T c4_i39;
  int32_T c4_i40;
  int32_T c4_i41;
  real_T *c4_b_theta;
  real_T (*c4_b_pos_ijk)[3];
  real_T (*c4_b_vel_ijk)[3];
  real_T (*c4_b_vel_xyz)[3];
  real_T (*c4_b_pos_xyz)[3];
  c4_b_vel_ijk = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c4_b_vel_xyz = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c4_b_pos_ijk = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_b_theta = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c4_b_pos_xyz = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c4_sfEvent);
  c4_hoistedGlobal = *c4_b_theta;
  for (c4_i8 = 0; c4_i8 < 3; c4_i8++) {
    c4_pos_xyz[c4_i8] = (*c4_b_pos_xyz)[c4_i8];
  }

  c4_theta = c4_hoistedGlobal;
  for (c4_i9 = 0; c4_i9 < 3; c4_i9++) {
    c4_vel_xyz[c4_i9] = (*c4_b_vel_xyz)[c4_i9];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c4_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_R, 0U, c4_c_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_rot_xyz_to_ijk, 1U,
    c4_c_sf_marshallOut, c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_w, 2U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 3U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 4U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_pos_xyz, 5U, c4_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_theta, 6U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_vel_xyz, 7U, c4_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_pos_ijk, 8U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_vel_ijk, 9U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 5);
  c4_x = c4_theta;
  c4_b_x = c4_x;
  c4_b_x = muDoubleScalarCos(c4_b_x);
  c4_c_x = c4_theta;
  c4_d_x = c4_c_x;
  c4_d_x = muDoubleScalarSin(c4_d_x);
  c4_e_x = c4_theta;
  c4_f_x = c4_e_x;
  c4_f_x = muDoubleScalarSin(c4_f_x);
  c4_g_x = c4_theta;
  c4_h_x = c4_g_x;
  c4_h_x = muDoubleScalarCos(c4_h_x);
  c4_R[0] = c4_b_x;
  c4_R[3] = c4_d_x;
  c4_R[6] = 0.0;
  c4_R[1] = -c4_f_x;
  c4_R[4] = c4_h_x;
  c4_R[7] = 0.0;
  c4_i10 = 0;
  for (c4_i11 = 0; c4_i11 < 3; c4_i11++) {
    c4_R[c4_i10 + 2] = c4_dv2[c4_i11];
    c4_i10 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 8);
  c4_i12 = 0;
  for (c4_i13 = 0; c4_i13 < 3; c4_i13++) {
    c4_i14 = 0;
    for (c4_i15 = 0; c4_i15 < 3; c4_i15++) {
      c4_rot_xyz_to_ijk[c4_i15 + c4_i12] = c4_R[c4_i14 + c4_i13];
      c4_i14 += 3;
    }

    c4_i12 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 9);
  for (c4_i16 = 0; c4_i16 < 9; c4_i16++) {
    c4_a[c4_i16] = c4_rot_xyz_to_ijk[c4_i16];
  }

  for (c4_i17 = 0; c4_i17 < 3; c4_i17++) {
    c4_b[c4_i17] = c4_pos_xyz[c4_i17];
  }

  c4_eml_scalar_eg(chartInstance);
  c4_eml_scalar_eg(chartInstance);
  for (c4_i18 = 0; c4_i18 < 3; c4_i18++) {
    c4_pos_ijk[c4_i18] = 0.0;
  }

  for (c4_i19 = 0; c4_i19 < 3; c4_i19++) {
    c4_pos_ijk[c4_i19] = 0.0;
  }

  for (c4_i20 = 0; c4_i20 < 3; c4_i20++) {
    c4_C[c4_i20] = c4_pos_ijk[c4_i20];
  }

  for (c4_i21 = 0; c4_i21 < 3; c4_i21++) {
    c4_pos_ijk[c4_i21] = c4_C[c4_i21];
  }

  for (c4_i22 = 0; c4_i22 < 3; c4_i22++) {
    c4_C[c4_i22] = c4_pos_ijk[c4_i22];
  }

  for (c4_i23 = 0; c4_i23 < 3; c4_i23++) {
    c4_pos_ijk[c4_i23] = c4_C[c4_i23];
  }

  for (c4_i24 = 0; c4_i24 < 3; c4_i24++) {
    c4_pos_ijk[c4_i24] = 0.0;
    c4_i25 = 0;
    for (c4_i26 = 0; c4_i26 < 3; c4_i26++) {
      c4_pos_ijk[c4_i24] += c4_a[c4_i25 + c4_i24] * c4_b[c4_i26];
      c4_i25 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 11);
  c4_w[0] = 0.0;
  c4_w[1] = 0.0;
  c4_w[2] = c4_theta;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 12);
  for (c4_i27 = 0; c4_i27 < 3; c4_i27++) {
    c4_b_a[c4_i27] = c4_w[c4_i27];
  }

  for (c4_i28 = 0; c4_i28 < 3; c4_i28++) {
    c4_b[c4_i28] = c4_pos_xyz[c4_i28];
  }

  c4_c_a = c4_b_a[1];
  c4_b_b = c4_b[2];
  c4_y = c4_c_a * c4_b_b;
  c4_d_a = c4_b_a[2];
  c4_c_b = c4_b[1];
  c4_b_y = c4_d_a * c4_c_b;
  c4_c1 = c4_y - c4_b_y;
  c4_e_a = c4_b_a[2];
  c4_d_b = c4_b[0];
  c4_c_y = c4_e_a * c4_d_b;
  c4_f_a = c4_b_a[0];
  c4_e_b = c4_b[2];
  c4_d_y = c4_f_a * c4_e_b;
  c4_c2 = c4_c_y - c4_d_y;
  c4_g_a = c4_b_a[0];
  c4_f_b = c4_b[1];
  c4_e_y = c4_g_a * c4_f_b;
  c4_h_a = c4_b_a[1];
  c4_g_b = c4_b[0];
  c4_f_y = c4_h_a * c4_g_b;
  c4_c3 = c4_e_y - c4_f_y;
  c4_b_a[0] = c4_c1;
  c4_b_a[1] = c4_c2;
  c4_b_a[2] = c4_c3;
  for (c4_i29 = 0; c4_i29 < 9; c4_i29++) {
    c4_a[c4_i29] = c4_rot_xyz_to_ijk[c4_i29];
  }

  for (c4_i30 = 0; c4_i30 < 3; c4_i30++) {
    c4_b_a[c4_i30] += c4_vel_xyz[c4_i30];
  }

  c4_eml_scalar_eg(chartInstance);
  c4_eml_scalar_eg(chartInstance);
  for (c4_i31 = 0; c4_i31 < 3; c4_i31++) {
    c4_vel_ijk[c4_i31] = 0.0;
  }

  for (c4_i32 = 0; c4_i32 < 3; c4_i32++) {
    c4_vel_ijk[c4_i32] = 0.0;
  }

  for (c4_i33 = 0; c4_i33 < 3; c4_i33++) {
    c4_C[c4_i33] = c4_vel_ijk[c4_i33];
  }

  for (c4_i34 = 0; c4_i34 < 3; c4_i34++) {
    c4_vel_ijk[c4_i34] = c4_C[c4_i34];
  }

  for (c4_i35 = 0; c4_i35 < 3; c4_i35++) {
    c4_C[c4_i35] = c4_vel_ijk[c4_i35];
  }

  for (c4_i36 = 0; c4_i36 < 3; c4_i36++) {
    c4_vel_ijk[c4_i36] = c4_C[c4_i36];
  }

  for (c4_i37 = 0; c4_i37 < 3; c4_i37++) {
    c4_vel_ijk[c4_i37] = 0.0;
    c4_i38 = 0;
    for (c4_i39 = 0; c4_i39 < 3; c4_i39++) {
      c4_vel_ijk[c4_i37] += c4_a[c4_i38 + c4_i37] * c4_b_a[c4_i39];
      c4_i38 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -12);
  _SFD_SYMBOL_SCOPE_POP();
  for (c4_i40 = 0; c4_i40 < 3; c4_i40++) {
    (*c4_b_pos_ijk)[c4_i40] = c4_pos_ijk[c4_i40];
  }

  for (c4_i41 = 0; c4_i41 < 3; c4_i41++) {
    (*c4_b_vel_ijk)[c4_i41] = c4_vel_ijk[c4_i41];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c4_sfEvent);
}

static void initSimStructsc4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc4_gif_model(SFc4_gif_modelInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber)
{
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i42;
  real_T c4_b_inData[3];
  int32_T c4_i43;
  real_T c4_u[3];
  const mxArray *c4_y = NULL;
  SFc4_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc4_gif_modelInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i42 = 0; c4_i42 < 3; c4_i42++) {
    c4_b_inData[c4_i42] = (*(real_T (*)[3])c4_inData)[c4_i42];
  }

  for (c4_i43 = 0; c4_i43 < 3; c4_i43++) {
    c4_u[c4_i43] = c4_b_inData[c4_i43];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static void c4_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_vel_ijk, const char_T *c4_identifier, real_T c4_y[3])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_vel_ijk), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_vel_ijk);
}

static void c4_b_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[3])
{
  real_T c4_dv3[3];
  int32_T c4_i44;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv3, 1, 0, 0U, 1, 0U, 1, 3);
  for (c4_i44 = 0; c4_i44 < 3; c4_i44++) {
    c4_y[c4_i44] = c4_dv3[c4_i44];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_vel_ijk;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[3];
  int32_T c4_i45;
  SFc4_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc4_gif_modelInstanceStruct *)chartInstanceVoid;
  c4_vel_ijk = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_vel_ijk), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_vel_ijk);
  for (c4_i45 = 0; c4_i45 < 3; c4_i45++) {
    (*(real_T (*)[3])c4_outData)[c4_i45] = c4_y[c4_i45];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc4_gif_modelInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static real_T c4_c_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d0;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d0, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_nargout;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc4_gif_modelInstanceStruct *)chartInstanceVoid;
  c4_nargout = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_nargout), &c4_thisId);
  sf_mex_destroy(&c4_nargout);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i46;
  int32_T c4_i47;
  int32_T c4_i48;
  real_T c4_b_inData[9];
  int32_T c4_i49;
  int32_T c4_i50;
  int32_T c4_i51;
  real_T c4_u[9];
  const mxArray *c4_y = NULL;
  SFc4_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc4_gif_modelInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i46 = 0;
  for (c4_i47 = 0; c4_i47 < 3; c4_i47++) {
    for (c4_i48 = 0; c4_i48 < 3; c4_i48++) {
      c4_b_inData[c4_i48 + c4_i46] = (*(real_T (*)[9])c4_inData)[c4_i48 + c4_i46];
    }

    c4_i46 += 3;
  }

  c4_i49 = 0;
  for (c4_i50 = 0; c4_i50 < 3; c4_i50++) {
    for (c4_i51 = 0; c4_i51 < 3; c4_i51++) {
      c4_u[c4_i51 + c4_i49] = c4_b_inData[c4_i51 + c4_i49];
    }

    c4_i49 += 3;
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static void c4_d_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[9])
{
  real_T c4_dv4[9];
  int32_T c4_i52;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv4, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c4_i52 = 0; c4_i52 < 9; c4_i52++) {
    c4_y[c4_i52] = c4_dv4[c4_i52];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_rot_xyz_to_ijk;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[9];
  int32_T c4_i53;
  int32_T c4_i54;
  int32_T c4_i55;
  SFc4_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc4_gif_modelInstanceStruct *)chartInstanceVoid;
  c4_rot_xyz_to_ijk = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_rot_xyz_to_ijk), &c4_thisId,
                        c4_y);
  sf_mex_destroy(&c4_rot_xyz_to_ijk);
  c4_i53 = 0;
  for (c4_i54 = 0; c4_i54 < 3; c4_i54++) {
    for (c4_i55 = 0; c4_i55 < 3; c4_i55++) {
      (*(real_T (*)[9])c4_outData)[c4_i55 + c4_i53] = c4_y[c4_i55 + c4_i53];
    }

    c4_i53 += 3;
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

const mxArray *sf_c4_gif_model_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo;
  c4_ResolvedFunctionInfo c4_info[15];
  const mxArray *c4_m0 = NULL;
  int32_T c4_i56;
  c4_ResolvedFunctionInfo *c4_r0;
  c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  c4_info_helper(c4_info);
  sf_mex_assign(&c4_m0, sf_mex_createstruct("nameCaptureInfo", 1, 15), FALSE);
  for (c4_i56 = 0; c4_i56 < 15; c4_i56++) {
    c4_r0 = &c4_info[c4_i56];
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->context)), "context", "nameCaptureInfo",
                    c4_i56);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c4_r0->name)), "name", "nameCaptureInfo", c4_i56);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c4_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c4_i56);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->resolved)), "resolved", "nameCaptureInfo",
                    c4_i56);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c4_i56);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c4_i56);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c4_i56);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c4_i56);
  }

  sf_mex_assign(&c4_nameCaptureInfo, c4_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c4_nameCaptureInfo);
  return c4_nameCaptureInfo;
}

static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[15])
{
  c4_info[0].context = "";
  c4_info[0].name = "cos";
  c4_info[0].dominantType = "double";
  c4_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c4_info[0].fileTimeLo = 1343862772U;
  c4_info[0].fileTimeHi = 0U;
  c4_info[0].mFileTimeLo = 0U;
  c4_info[0].mFileTimeHi = 0U;
  c4_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c4_info[1].name = "eml_scalar_cos";
  c4_info[1].dominantType = "double";
  c4_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c4_info[1].fileTimeLo = 1286851122U;
  c4_info[1].fileTimeHi = 0U;
  c4_info[1].mFileTimeLo = 0U;
  c4_info[1].mFileTimeHi = 0U;
  c4_info[2].context = "";
  c4_info[2].name = "sin";
  c4_info[2].dominantType = "double";
  c4_info[2].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c4_info[2].fileTimeLo = 1343862786U;
  c4_info[2].fileTimeHi = 0U;
  c4_info[2].mFileTimeLo = 0U;
  c4_info[2].mFileTimeHi = 0U;
  c4_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c4_info[3].name = "eml_scalar_sin";
  c4_info[3].dominantType = "double";
  c4_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c4_info[3].fileTimeLo = 1286851136U;
  c4_info[3].fileTimeHi = 0U;
  c4_info[3].mFileTimeLo = 0U;
  c4_info[3].mFileTimeHi = 0U;
  c4_info[4].context = "";
  c4_info[4].name = "mtimes";
  c4_info[4].dominantType = "double";
  c4_info[4].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[4].fileTimeLo = 1289552092U;
  c4_info[4].fileTimeHi = 0U;
  c4_info[4].mFileTimeLo = 0U;
  c4_info[4].mFileTimeHi = 0U;
  c4_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[5].name = "eml_index_class";
  c4_info[5].dominantType = "";
  c4_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[5].fileTimeLo = 1323202978U;
  c4_info[5].fileTimeHi = 0U;
  c4_info[5].mFileTimeLo = 0U;
  c4_info[5].mFileTimeHi = 0U;
  c4_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[6].name = "eml_scalar_eg";
  c4_info[6].dominantType = "double";
  c4_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c4_info[6].fileTimeLo = 1286851196U;
  c4_info[6].fileTimeHi = 0U;
  c4_info[6].mFileTimeLo = 0U;
  c4_info[6].mFileTimeHi = 0U;
  c4_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[7].name = "eml_xgemm";
  c4_info[7].dominantType = "char";
  c4_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c4_info[7].fileTimeLo = 1299109172U;
  c4_info[7].fileTimeHi = 0U;
  c4_info[7].mFileTimeLo = 0U;
  c4_info[7].mFileTimeHi = 0U;
  c4_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c4_info[8].name = "eml_blas_inline";
  c4_info[8].dominantType = "";
  c4_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c4_info[8].fileTimeLo = 1299109168U;
  c4_info[8].fileTimeHi = 0U;
  c4_info[8].mFileTimeLo = 0U;
  c4_info[8].mFileTimeHi = 0U;
  c4_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c4_info[9].name = "mtimes";
  c4_info[9].dominantType = "double";
  c4_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[9].fileTimeLo = 1289552092U;
  c4_info[9].fileTimeHi = 0U;
  c4_info[9].mFileTimeLo = 0U;
  c4_info[9].mFileTimeHi = 0U;
  c4_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c4_info[10].name = "eml_index_class";
  c4_info[10].dominantType = "";
  c4_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[10].fileTimeLo = 1323202978U;
  c4_info[10].fileTimeHi = 0U;
  c4_info[10].mFileTimeLo = 0U;
  c4_info[10].mFileTimeHi = 0U;
  c4_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c4_info[11].name = "eml_scalar_eg";
  c4_info[11].dominantType = "double";
  c4_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c4_info[11].fileTimeLo = 1286851196U;
  c4_info[11].fileTimeHi = 0U;
  c4_info[11].mFileTimeLo = 0U;
  c4_info[11].mFileTimeHi = 0U;
  c4_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c4_info[12].name = "eml_refblas_xgemm";
  c4_info[12].dominantType = "char";
  c4_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c4_info[12].fileTimeLo = 1299109174U;
  c4_info[12].fileTimeHi = 0U;
  c4_info[12].mFileTimeLo = 0U;
  c4_info[12].mFileTimeHi = 0U;
  c4_info[13].context = "";
  c4_info[13].name = "cross";
  c4_info[13].dominantType = "double";
  c4_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c4_info[13].fileTimeLo = 1286851242U;
  c4_info[13].fileTimeHi = 0U;
  c4_info[13].mFileTimeLo = 0U;
  c4_info[13].mFileTimeHi = 0U;
  c4_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c4_info[14].name = "mtimes";
  c4_info[14].dominantType = "double";
  c4_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[14].fileTimeLo = 1289552092U;
  c4_info[14].fileTimeHi = 0U;
  c4_info[14].mFileTimeLo = 0U;
  c4_info[14].mFileTimeHi = 0U;
}

static void c4_eml_scalar_eg(SFc4_gif_modelInstanceStruct *chartInstance)
{
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc4_gif_modelInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static int32_T c4_e_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i57;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i57, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i57;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc4_gif_modelInstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static uint8_T c4_f_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_gif_model, const char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_is_active_c4_gif_model), &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_gif_model);
  return c4_y;
}

static uint8_T c4_g_emlrt_marshallIn(SFc4_gif_modelInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void init_dsm_address_info(SFc4_gif_modelInstanceStruct *chartInstance)
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

void sf_c4_gif_model_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3064282630U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3236908403U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2231514760U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(348115303U);
}

mxArray *sf_c4_gif_model_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("bR4CYS9Ya9dmnLvtzIkxcE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
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
      pr[0] = (double)(1);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
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
      pr[0] = (double)(3);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c4_gif_model_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c4_gif_model(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"pos_ijk\",},{M[1],M[8],T\"vel_ijk\",},{M[8],M[0],T\"is_active_c4_gif_model\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_gif_model_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_gif_modelInstanceStruct *chartInstance;
    chartInstance = (SFc4_gif_modelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _gif_modelMachineNumber_,
           4,
           1,
           1,
           5,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"pos_xyz");
          _SFD_SET_DATA_PROPS(1,1,1,0,"theta");
          _SFD_SET_DATA_PROPS(2,2,0,1,"pos_ijk");
          _SFD_SET_DATA_PROPS(3,1,1,0,"vel_xyz");
          _SFD_SET_DATA_PROPS(4,2,0,1,"vel_ijk");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,343);
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
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)
            c4_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)
            c4_sf_marshallIn);
        }

        {
          real_T *c4_theta;
          real_T (*c4_pos_xyz)[3];
          real_T (*c4_pos_ijk)[3];
          real_T (*c4_vel_xyz)[3];
          real_T (*c4_vel_ijk)[3];
          c4_vel_ijk = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
          c4_vel_xyz = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c4_pos_ijk = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c4_theta = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c4_pos_xyz = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c4_pos_xyz);
          _SFD_SET_DATA_VALUE_PTR(1U, c4_theta);
          _SFD_SET_DATA_VALUE_PTR(2U, *c4_pos_ijk);
          _SFD_SET_DATA_VALUE_PTR(3U, *c4_vel_xyz);
          _SFD_SET_DATA_VALUE_PTR(4U, *c4_vel_ijk);
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
  return "7HjNslDLHSFGc1Iv5HLCLD";
}

static void sf_opaque_initialize_c4_gif_model(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_gif_modelInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c4_gif_model((SFc4_gif_modelInstanceStruct*)
    chartInstanceVar);
  initialize_c4_gif_model((SFc4_gif_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_gif_model(void *chartInstanceVar)
{
  enable_c4_gif_model((SFc4_gif_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_gif_model(void *chartInstanceVar)
{
  disable_c4_gif_model((SFc4_gif_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c4_gif_model(void *chartInstanceVar)
{
  sf_c4_gif_model((SFc4_gif_modelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c4_gif_model(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c4_gif_model((SFc4_gif_modelInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_gif_model();/* state var info */
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

extern void sf_internal_set_sim_state_c4_gif_model(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_gif_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c4_gif_model((SFc4_gif_modelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c4_gif_model(SimStruct* S)
{
  return sf_internal_get_sim_state_c4_gif_model(S);
}

static void sf_opaque_set_sim_state_c4_gif_model(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c4_gif_model(S, st);
}

static void sf_opaque_terminate_c4_gif_model(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_gif_modelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_gif_model_optimization_info();
    }

    finalize_c4_gif_model((SFc4_gif_modelInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_gif_model((SFc4_gif_modelInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_gif_model(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c4_gif_model((SFc4_gif_modelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_gif_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_gif_model_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,4,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,4);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(464102897U));
  ssSetChecksum1(S,(197846328U));
  ssSetChecksum2(S,(1591269243U));
  ssSetChecksum3(S,(1110214453U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c4_gif_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_gif_model(SimStruct *S)
{
  SFc4_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc4_gif_modelInstanceStruct *)utMalloc(sizeof
    (SFc4_gif_modelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_gif_modelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c4_gif_model;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c4_gif_model;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c4_gif_model;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_gif_model;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_gif_model;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c4_gif_model;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c4_gif_model;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c4_gif_model;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_gif_model;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_gif_model;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_gif_model;
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

void c4_gif_model_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_gif_model(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_gif_model(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_gif_model(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_gif_model_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
