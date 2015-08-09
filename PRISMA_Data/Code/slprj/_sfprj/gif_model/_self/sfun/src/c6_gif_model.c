/* Include files */

#include <stddef.h>
#include "blas.h"
#include "gif_model_sfun.h"
#include "c6_gif_model.h"
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
static const char * c6_debug_family_names[12] = { "main", "trgt", "R_IJK",
  "N_IJK", "T_IJK", "rot_RTN_to_IJK", "rot_IJK_to_RTN", "nargin", "nargout",
  "main_state", "target_state", "rtn" };

/* Function Declarations */
static void initialize_c6_gif_model(SFc6_gif_modelInstanceStruct *chartInstance);
static void initialize_params_c6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance);
static void enable_c6_gif_model(SFc6_gif_modelInstanceStruct *chartInstance);
static void disable_c6_gif_model(SFc6_gif_modelInstanceStruct *chartInstance);
static void c6_update_debugger_state_c6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance);
static void set_sim_state_c6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance, const mxArray *c6_st);
static void finalize_c6_gif_model(SFc6_gif_modelInstanceStruct *chartInstance);
static void sf_c6_gif_model(SFc6_gif_modelInstanceStruct *chartInstance);
static void c6_chartstep_c6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance);
static void initSimStructsc6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance);
static void registerMessagesc6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber);
static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData);
static void c6_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_rtn, const char_T *c6_identifier, real_T c6_y[3]);
static void c6_b_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[3]);
static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static real_T c6_c_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_d_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[9]);
static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_e_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_e_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId,
  c6_sqIgkGf7JWLZgCaATJHsg3G *c6_y);
static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static void c6_info_helper(c6_ResolvedFunctionInfo c6_info[35]);
static real_T c6_norm(SFc6_gif_modelInstanceStruct *chartInstance, real_T c6_x[3]);
static void c6_cross(SFc6_gif_modelInstanceStruct *chartInstance, real_T c6_a[3],
                     real_T c6_b[3], real_T c6_c[3]);
static void c6_eml_scalar_eg(SFc6_gif_modelInstanceStruct *chartInstance);
static const mxArray *c6_f_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static int32_T c6_f_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static uint8_T c6_g_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_b_is_active_c6_gif_model, const char_T *c6_identifier);
static uint8_T c6_h_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void init_dsm_address_info(SFc6_gif_modelInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c6_gif_model(SFc6_gif_modelInstanceStruct *chartInstance)
{
  chartInstance->c6_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c6_is_active_c6_gif_model = 0U;
}

static void initialize_params_c6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance)
{
}

static void enable_c6_gif_model(SFc6_gif_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c6_gif_model(SFc6_gif_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c6_update_debugger_state_c6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance)
{
  const mxArray *c6_st;
  const mxArray *c6_y = NULL;
  int32_T c6_i0;
  real_T c6_u[3];
  const mxArray *c6_b_y = NULL;
  uint8_T c6_hoistedGlobal;
  uint8_T c6_b_u;
  const mxArray *c6_c_y = NULL;
  real_T (*c6_rtn)[3];
  c6_rtn = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_st = NULL;
  c6_st = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createcellarray(2), FALSE);
  for (c6_i0 = 0; c6_i0 < 3; c6_i0++) {
    c6_u[c6_i0] = (*c6_rtn)[c6_i0];
  }

  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c6_y, 0, c6_b_y);
  c6_hoistedGlobal = chartInstance->c6_is_active_c6_gif_model;
  c6_b_u = c6_hoistedGlobal;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 1, c6_c_y);
  sf_mex_assign(&c6_st, c6_y, FALSE);
  return c6_st;
}

static void set_sim_state_c6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance, const mxArray *c6_st)
{
  const mxArray *c6_u;
  real_T c6_dv0[3];
  int32_T c6_i1;
  real_T (*c6_rtn)[3];
  c6_rtn = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c6_doneDoubleBufferReInit = TRUE;
  c6_u = sf_mex_dup(c6_st);
  c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 0)), "rtn",
                      c6_dv0);
  for (c6_i1 = 0; c6_i1 < 3; c6_i1++) {
    (*c6_rtn)[c6_i1] = c6_dv0[c6_i1];
  }

  chartInstance->c6_is_active_c6_gif_model = c6_g_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 1)), "is_active_c6_gif_model");
  sf_mex_destroy(&c6_u);
  c6_update_debugger_state_c6_gif_model(chartInstance);
  sf_mex_destroy(&c6_st);
}

static void finalize_c6_gif_model(SFc6_gif_modelInstanceStruct *chartInstance)
{
}

static void sf_c6_gif_model(SFc6_gif_modelInstanceStruct *chartInstance)
{
  int32_T c6_i2;
  int32_T c6_i3;
  int32_T c6_i4;
  real_T (*c6_target_state)[6];
  real_T (*c6_rtn)[3];
  real_T (*c6_main_state)[6];
  c6_target_state = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c6_rtn = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_main_state = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, chartInstance->c6_sfEvent);
  for (c6_i2 = 0; c6_i2 < 6; c6_i2++) {
    _SFD_DATA_RANGE_CHECK((*c6_main_state)[c6_i2], 0U);
  }

  for (c6_i3 = 0; c6_i3 < 3; c6_i3++) {
    _SFD_DATA_RANGE_CHECK((*c6_rtn)[c6_i3], 1U);
  }

  for (c6_i4 = 0; c6_i4 < 6; c6_i4++) {
    _SFD_DATA_RANGE_CHECK((*c6_target_state)[c6_i4], 2U);
  }

  chartInstance->c6_sfEvent = CALL_EVENT;
  c6_chartstep_c6_gif_model(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_gif_modelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c6_chartstep_c6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance)
{
  int32_T c6_i5;
  real_T c6_main_state[6];
  int32_T c6_i6;
  real_T c6_target_state[6];
  uint32_T c6_debug_family_var_map[12];
  c6_sqIgkGf7JWLZgCaATJHsg3G c6_main;
  c6_sqIgkGf7JWLZgCaATJHsg3G c6_trgt;
  real_T c6_R_IJK[3];
  real_T c6_N_IJK[3];
  real_T c6_T_IJK[3];
  real_T c6_rot_RTN_to_IJK[9];
  real_T c6_rot_IJK_to_RTN[9];
  real_T c6_nargin = 2.0;
  real_T c6_nargout = 1.0;
  real_T c6_rtn[3];
  static c6_sqIgkGf7JWLZgCaATJHsg3G c6_r0 = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0
    }, { 0.0, 0.0, 0.0 } };

  int32_T c6_i7;
  int32_T c6_i8;
  int32_T c6_i9;
  int32_T c6_i10;
  int32_T c6_i11;
  real_T c6_A[3];
  int32_T c6_i12;
  real_T c6_b_main[3];
  real_T c6_B;
  real_T c6_y;
  real_T c6_b_y;
  int32_T c6_i13;
  int32_T c6_i14;
  real_T c6_c_main[3];
  int32_T c6_i15;
  real_T c6_d_main[3];
  int32_T c6_i16;
  real_T c6_e_main[3];
  int32_T c6_i17;
  real_T c6_f_main[3];
  real_T c6_C[3];
  int32_T c6_i18;
  real_T c6_b_C[3];
  real_T c6_b_B;
  real_T c6_c_y;
  real_T c6_d_y;
  int32_T c6_i19;
  int32_T c6_i20;
  real_T c6_b_N_IJK[3];
  int32_T c6_i21;
  real_T c6_b_R_IJK[3];
  real_T c6_dv1[3];
  int32_T c6_i22;
  int32_T c6_i23;
  int32_T c6_i24;
  int32_T c6_i25;
  int32_T c6_i26;
  int32_T c6_i27;
  int32_T c6_i28;
  int32_T c6_i29;
  int32_T c6_i30;
  real_T c6_a[9];
  int32_T c6_i31;
  int32_T c6_i32;
  int32_T c6_i33;
  int32_T c6_i34;
  int32_T c6_i35;
  int32_T c6_i36;
  int32_T c6_i37;
  int32_T c6_i38;
  int32_T c6_i39;
  int32_T c6_i40;
  int32_T c6_i41;
  int32_T c6_i42;
  int32_T c6_i43;
  int32_T c6_i44;
  int32_T c6_i45;
  int32_T c6_i46;
  int32_T c6_i47;
  int32_T c6_i48;
  int32_T c6_i49;
  int32_T c6_i50;
  int32_T c6_i51;
  int32_T c6_i52;
  int32_T c6_i53;
  real_T (*c6_b_rtn)[3];
  real_T (*c6_b_target_state)[6];
  real_T (*c6_b_main_state)[6];
  c6_b_target_state = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c6_b_rtn = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_b_main_state = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c6_sfEvent);
  for (c6_i5 = 0; c6_i5 < 6; c6_i5++) {
    c6_main_state[c6_i5] = (*c6_b_main_state)[c6_i5];
  }

  for (c6_i6 = 0; c6_i6 < 6; c6_i6++) {
    c6_target_state[c6_i6] = (*c6_b_target_state)[c6_i6];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 12U, c6_debug_family_names,
    c6_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_main, 0U, c6_e_sf_marshallOut,
    c6_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_trgt, 1U, c6_e_sf_marshallOut,
    c6_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_R_IJK, 2U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_N_IJK, 3U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_T_IJK, 4U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_rot_RTN_to_IJK, 5U,
    c6_d_sf_marshallOut, c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_rot_IJK_to_RTN, 6U,
    c6_d_sf_marshallOut, c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 7U, c6_c_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 8U, c6_c_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_main_state, 9U, c6_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_target_state, 10U, c6_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_rtn, 11U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 5);
  c6_main = c6_r0;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 6);
  c6_trgt = c6_r0;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 8);
  for (c6_i7 = 0; c6_i7 < 3; c6_i7++) {
    c6_main.pos[c6_i7] = c6_main_state[c6_i7];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 9);
  for (c6_i8 = 0; c6_i8 < 3; c6_i8++) {
    c6_main.vel[c6_i8] = c6_main_state[c6_i8 + 3];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 10);
  for (c6_i9 = 0; c6_i9 < 3; c6_i9++) {
    c6_trgt.pos[c6_i9] = c6_target_state[c6_i9];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 11);
  for (c6_i10 = 0; c6_i10 < 3; c6_i10++) {
    c6_trgt.vel[c6_i10] = c6_target_state[c6_i10 + 3];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 14);
  for (c6_i11 = 0; c6_i11 < 3; c6_i11++) {
    c6_A[c6_i11] = c6_main.pos[c6_i11];
  }

  for (c6_i12 = 0; c6_i12 < 3; c6_i12++) {
    c6_b_main[c6_i12] = c6_main.pos[c6_i12];
  }

  c6_B = c6_norm(chartInstance, c6_b_main);
  c6_y = c6_B;
  c6_b_y = c6_y;
  for (c6_i13 = 0; c6_i13 < 3; c6_i13++) {
    c6_R_IJK[c6_i13] = c6_A[c6_i13] / c6_b_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 15);
  for (c6_i14 = 0; c6_i14 < 3; c6_i14++) {
    c6_c_main[c6_i14] = c6_main.pos[c6_i14];
  }

  for (c6_i15 = 0; c6_i15 < 3; c6_i15++) {
    c6_d_main[c6_i15] = c6_main.vel[c6_i15];
  }

  c6_cross(chartInstance, c6_c_main, c6_d_main, c6_A);
  for (c6_i16 = 0; c6_i16 < 3; c6_i16++) {
    c6_e_main[c6_i16] = c6_main.pos[c6_i16];
  }

  for (c6_i17 = 0; c6_i17 < 3; c6_i17++) {
    c6_f_main[c6_i17] = c6_main.vel[c6_i17];
  }

  c6_cross(chartInstance, c6_e_main, c6_f_main, c6_C);
  for (c6_i18 = 0; c6_i18 < 3; c6_i18++) {
    c6_b_C[c6_i18] = c6_C[c6_i18];
  }

  c6_b_B = c6_norm(chartInstance, c6_b_C);
  c6_c_y = c6_b_B;
  c6_d_y = c6_c_y;
  for (c6_i19 = 0; c6_i19 < 3; c6_i19++) {
    c6_N_IJK[c6_i19] = c6_A[c6_i19] / c6_d_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 16);
  for (c6_i20 = 0; c6_i20 < 3; c6_i20++) {
    c6_b_N_IJK[c6_i20] = c6_N_IJK[c6_i20];
  }

  for (c6_i21 = 0; c6_i21 < 3; c6_i21++) {
    c6_b_R_IJK[c6_i21] = c6_R_IJK[c6_i21];
  }

  c6_cross(chartInstance, c6_b_N_IJK, c6_b_R_IJK, c6_dv1);
  for (c6_i22 = 0; c6_i22 < 3; c6_i22++) {
    c6_T_IJK[c6_i22] = c6_dv1[c6_i22];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 18);
  for (c6_i23 = 0; c6_i23 < 3; c6_i23++) {
    c6_rot_RTN_to_IJK[c6_i23] = c6_R_IJK[c6_i23];
  }

  for (c6_i24 = 0; c6_i24 < 3; c6_i24++) {
    c6_rot_RTN_to_IJK[c6_i24 + 3] = c6_T_IJK[c6_i24];
  }

  for (c6_i25 = 0; c6_i25 < 3; c6_i25++) {
    c6_rot_RTN_to_IJK[c6_i25 + 6] = c6_N_IJK[c6_i25];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 19);
  c6_i26 = 0;
  for (c6_i27 = 0; c6_i27 < 3; c6_i27++) {
    c6_i28 = 0;
    for (c6_i29 = 0; c6_i29 < 3; c6_i29++) {
      c6_rot_IJK_to_RTN[c6_i29 + c6_i26] = c6_rot_RTN_to_IJK[c6_i28 + c6_i27];
      c6_i28 += 3;
    }

    c6_i26 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 25);
  for (c6_i30 = 0; c6_i30 < 9; c6_i30++) {
    c6_a[c6_i30] = c6_rot_IJK_to_RTN[c6_i30];
  }

  for (c6_i31 = 0; c6_i31 < 3; c6_i31++) {
    c6_A[c6_i31] = c6_main.pos[c6_i31];
  }

  c6_eml_scalar_eg(chartInstance);
  c6_eml_scalar_eg(chartInstance);
  for (c6_i32 = 0; c6_i32 < 3; c6_i32++) {
    c6_main.pos_RTN[c6_i32] = 0.0;
  }

  for (c6_i33 = 0; c6_i33 < 3; c6_i33++) {
    c6_main.pos_RTN[c6_i33] = 0.0;
  }

  for (c6_i34 = 0; c6_i34 < 3; c6_i34++) {
    c6_C[c6_i34] = c6_main.pos_RTN[c6_i34];
  }

  for (c6_i35 = 0; c6_i35 < 3; c6_i35++) {
    c6_main.pos_RTN[c6_i35] = c6_C[c6_i35];
  }

  for (c6_i36 = 0; c6_i36 < 3; c6_i36++) {
    c6_C[c6_i36] = c6_main.pos_RTN[c6_i36];
  }

  for (c6_i37 = 0; c6_i37 < 3; c6_i37++) {
    c6_main.pos_RTN[c6_i37] = c6_C[c6_i37];
  }

  for (c6_i38 = 0; c6_i38 < 3; c6_i38++) {
    c6_main.pos_RTN[c6_i38] = 0.0;
    c6_i39 = 0;
    for (c6_i40 = 0; c6_i40 < 3; c6_i40++) {
      c6_main.pos_RTN[c6_i38] += c6_a[c6_i39 + c6_i38] * c6_A[c6_i40];
      c6_i39 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 26);
  for (c6_i41 = 0; c6_i41 < 9; c6_i41++) {
    c6_a[c6_i41] = c6_rot_IJK_to_RTN[c6_i41];
  }

  for (c6_i42 = 0; c6_i42 < 3; c6_i42++) {
    c6_A[c6_i42] = c6_trgt.pos[c6_i42];
  }

  c6_eml_scalar_eg(chartInstance);
  c6_eml_scalar_eg(chartInstance);
  for (c6_i43 = 0; c6_i43 < 3; c6_i43++) {
    c6_trgt.pos_RTN[c6_i43] = 0.0;
  }

  for (c6_i44 = 0; c6_i44 < 3; c6_i44++) {
    c6_trgt.pos_RTN[c6_i44] = 0.0;
  }

  for (c6_i45 = 0; c6_i45 < 3; c6_i45++) {
    c6_C[c6_i45] = c6_trgt.pos_RTN[c6_i45];
  }

  for (c6_i46 = 0; c6_i46 < 3; c6_i46++) {
    c6_trgt.pos_RTN[c6_i46] = c6_C[c6_i46];
  }

  for (c6_i47 = 0; c6_i47 < 3; c6_i47++) {
    c6_C[c6_i47] = c6_trgt.pos_RTN[c6_i47];
  }

  for (c6_i48 = 0; c6_i48 < 3; c6_i48++) {
    c6_trgt.pos_RTN[c6_i48] = c6_C[c6_i48];
  }

  for (c6_i49 = 0; c6_i49 < 3; c6_i49++) {
    c6_trgt.pos_RTN[c6_i49] = 0.0;
    c6_i50 = 0;
    for (c6_i51 = 0; c6_i51 < 3; c6_i51++) {
      c6_trgt.pos_RTN[c6_i49] += c6_a[c6_i50 + c6_i49] * c6_A[c6_i51];
      c6_i50 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 27);
  for (c6_i52 = 0; c6_i52 < 3; c6_i52++) {
    c6_rtn[c6_i52] = c6_trgt.pos_RTN[c6_i52] - c6_main.pos_RTN[c6_i52];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, -27);
  _SFD_SYMBOL_SCOPE_POP();
  for (c6_i53 = 0; c6_i53 < 3; c6_i53++) {
    (*c6_b_rtn)[c6_i53] = c6_rtn[c6_i53];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c6_sfEvent);
}

static void initSimStructsc6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc6_gif_model(SFc6_gif_modelInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber)
{
}

static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i54;
  real_T c6_b_inData[3];
  int32_T c6_i55;
  real_T c6_u[3];
  const mxArray *c6_y = NULL;
  SFc6_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc6_gif_modelInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  for (c6_i54 = 0; c6_i54 < 3; c6_i54++) {
    c6_b_inData[c6_i54] = (*(real_T (*)[3])c6_inData)[c6_i54];
  }

  for (c6_i55 = 0; c6_i55 < 3; c6_i55++) {
    c6_u[c6_i55] = c6_b_inData[c6_i55];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static void c6_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_rtn, const char_T *c6_identifier, real_T c6_y[3])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_rtn), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_rtn);
}

static void c6_b_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[3])
{
  real_T c6_dv2[3];
  int32_T c6_i56;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv2, 1, 0, 0U, 1, 0U, 1, 3);
  for (c6_i56 = 0; c6_i56 < 3; c6_i56++) {
    c6_y[c6_i56] = c6_dv2[c6_i56];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_rtn;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[3];
  int32_T c6_i57;
  SFc6_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc6_gif_modelInstanceStruct *)chartInstanceVoid;
  c6_rtn = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_rtn), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_rtn);
  for (c6_i57 = 0; c6_i57 < 3; c6_i57++) {
    (*(real_T (*)[3])c6_outData)[c6_i57] = c6_y[c6_i57];
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i58;
  real_T c6_b_inData[6];
  int32_T c6_i59;
  real_T c6_u[6];
  const mxArray *c6_y = NULL;
  SFc6_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc6_gif_modelInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  for (c6_i58 = 0; c6_i58 < 6; c6_i58++) {
    c6_b_inData[c6_i58] = (*(real_T (*)[6])c6_inData)[c6_i58];
  }

  for (c6_i59 = 0; c6_i59 < 6; c6_i59++) {
    c6_u[c6_i59] = c6_b_inData[c6_i59];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  real_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc6_gif_modelInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(real_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static real_T c6_c_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  real_T c6_y;
  real_T c6_d0;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_d0, 1, 0, 0U, 0, 0U, 0);
  c6_y = c6_d0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_nargout;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y;
  SFc6_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc6_gif_modelInstanceStruct *)chartInstanceVoid;
  c6_nargout = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_nargout), &c6_thisId);
  sf_mex_destroy(&c6_nargout);
  *(real_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i60;
  int32_T c6_i61;
  int32_T c6_i62;
  real_T c6_b_inData[9];
  int32_T c6_i63;
  int32_T c6_i64;
  int32_T c6_i65;
  real_T c6_u[9];
  const mxArray *c6_y = NULL;
  SFc6_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc6_gif_modelInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_i60 = 0;
  for (c6_i61 = 0; c6_i61 < 3; c6_i61++) {
    for (c6_i62 = 0; c6_i62 < 3; c6_i62++) {
      c6_b_inData[c6_i62 + c6_i60] = (*(real_T (*)[9])c6_inData)[c6_i62 + c6_i60];
    }

    c6_i60 += 3;
  }

  c6_i63 = 0;
  for (c6_i64 = 0; c6_i64 < 3; c6_i64++) {
    for (c6_i65 = 0; c6_i65 < 3; c6_i65++) {
      c6_u[c6_i65 + c6_i63] = c6_b_inData[c6_i65 + c6_i63];
    }

    c6_i63 += 3;
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static void c6_d_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[9])
{
  real_T c6_dv3[9];
  int32_T c6_i66;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv3, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c6_i66 = 0; c6_i66 < 9; c6_i66++) {
    c6_y[c6_i66] = c6_dv3[c6_i66];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_rot_IJK_to_RTN;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[9];
  int32_T c6_i67;
  int32_T c6_i68;
  int32_T c6_i69;
  SFc6_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc6_gif_modelInstanceStruct *)chartInstanceVoid;
  c6_rot_IJK_to_RTN = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_rot_IJK_to_RTN), &c6_thisId,
                        c6_y);
  sf_mex_destroy(&c6_rot_IJK_to_RTN);
  c6_i67 = 0;
  for (c6_i68 = 0; c6_i68 < 3; c6_i68++) {
    for (c6_i69 = 0; c6_i69 < 3; c6_i69++) {
      (*(real_T (*)[9])c6_outData)[c6_i69 + c6_i67] = c6_y[c6_i69 + c6_i67];
    }

    c6_i67 += 3;
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_e_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  c6_sqIgkGf7JWLZgCaATJHsg3G c6_u;
  const mxArray *c6_y = NULL;
  int32_T c6_i70;
  real_T c6_b_u[3];
  const mxArray *c6_b_y = NULL;
  int32_T c6_i71;
  real_T c6_c_u[3];
  const mxArray *c6_c_y = NULL;
  int32_T c6_i72;
  real_T c6_d_u[3];
  const mxArray *c6_d_y = NULL;
  SFc6_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc6_gif_modelInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(c6_sqIgkGf7JWLZgCaATJHsg3G *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createstruct("structure", 2, 1, 1), FALSE);
  for (c6_i70 = 0; c6_i70 < 3; c6_i70++) {
    c6_b_u[c6_i70] = c6_u.pos_RTN[c6_i70];
  }

  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", c6_b_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_addfield(c6_y, c6_b_y, "pos_RTN", "pos_RTN", 0);
  for (c6_i71 = 0; c6_i71 < 3; c6_i71++) {
    c6_c_u[c6_i71] = c6_u.pos[c6_i71];
  }

  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", c6_c_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_addfield(c6_y, c6_c_y, "pos", "pos", 0);
  for (c6_i72 = 0; c6_i72 < 3; c6_i72++) {
    c6_d_u[c6_i72] = c6_u.vel[c6_i72];
  }

  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", c6_d_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_addfield(c6_y, c6_d_y, "vel", "vel", 0);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static void c6_e_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId,
  c6_sqIgkGf7JWLZgCaATJHsg3G *c6_y)
{
  emlrtMsgIdentifier c6_thisId;
  static const char * c6_fieldNames[3] = { "pos_RTN", "pos", "vel" };

  c6_thisId.fParent = c6_parentId;
  sf_mex_check_struct(c6_parentId, c6_u, 3, c6_fieldNames, 0U, 0);
  c6_thisId.fIdentifier = "pos_RTN";
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c6_u,
    "pos_RTN", "pos_RTN", 0)), &c6_thisId, c6_y->pos_RTN);
  c6_thisId.fIdentifier = "pos";
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c6_u, "pos",
    "pos", 0)), &c6_thisId, c6_y->pos);
  c6_thisId.fIdentifier = "vel";
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c6_u, "vel",
    "vel", 0)), &c6_thisId, c6_y->vel);
  sf_mex_destroy(&c6_u);
}

static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_trgt;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  c6_sqIgkGf7JWLZgCaATJHsg3G c6_y;
  SFc6_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc6_gif_modelInstanceStruct *)chartInstanceVoid;
  c6_trgt = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_trgt), &c6_thisId, &c6_y);
  sf_mex_destroy(&c6_trgt);
  *(c6_sqIgkGf7JWLZgCaATJHsg3G *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

const mxArray *sf_c6_gif_model_get_eml_resolved_functions_info(void)
{
  const mxArray *c6_nameCaptureInfo;
  c6_ResolvedFunctionInfo c6_info[35];
  const mxArray *c6_m0 = NULL;
  int32_T c6_i73;
  c6_ResolvedFunctionInfo *c6_r1;
  c6_nameCaptureInfo = NULL;
  c6_nameCaptureInfo = NULL;
  c6_info_helper(c6_info);
  sf_mex_assign(&c6_m0, sf_mex_createstruct("nameCaptureInfo", 1, 35), FALSE);
  for (c6_i73 = 0; c6_i73 < 35; c6_i73++) {
    c6_r1 = &c6_info[c6_i73];
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r1->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c6_r1->context)), "context", "nameCaptureInfo",
                    c6_i73);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r1->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c6_r1->name)), "name", "nameCaptureInfo", c6_i73);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r1->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c6_r1->dominantType)), "dominantType",
                    "nameCaptureInfo", c6_i73);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r1->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c6_r1->resolved)), "resolved", "nameCaptureInfo",
                    c6_i73);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r1->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c6_i73);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r1->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c6_i73);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r1->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c6_i73);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r1->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c6_i73);
  }

  sf_mex_assign(&c6_nameCaptureInfo, c6_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c6_nameCaptureInfo);
  return c6_nameCaptureInfo;
}

static void c6_info_helper(c6_ResolvedFunctionInfo c6_info[35])
{
  c6_info[0].context = "";
  c6_info[0].name = "norm";
  c6_info[0].dominantType = "double";
  c6_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c6_info[0].fileTimeLo = 1336554494U;
  c6_info[0].fileTimeHi = 0U;
  c6_info[0].mFileTimeLo = 0U;
  c6_info[0].mFileTimeHi = 0U;
  c6_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c6_info[1].name = "eml_index_class";
  c6_info[1].dominantType = "";
  c6_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[1].fileTimeLo = 1323202978U;
  c6_info[1].fileTimeHi = 0U;
  c6_info[1].mFileTimeLo = 0U;
  c6_info[1].mFileTimeHi = 0U;
  c6_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c6_info[2].name = "eml_xnrm2";
  c6_info[2].dominantType = "double";
  c6_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c6_info[2].fileTimeLo = 1299109176U;
  c6_info[2].fileTimeHi = 0U;
  c6_info[2].mFileTimeLo = 0U;
  c6_info[2].mFileTimeHi = 0U;
  c6_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c6_info[3].name = "eml_blas_inline";
  c6_info[3].dominantType = "";
  c6_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c6_info[3].fileTimeLo = 1299109168U;
  c6_info[3].fileTimeHi = 0U;
  c6_info[3].mFileTimeLo = 0U;
  c6_info[3].mFileTimeHi = 0U;
  c6_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c6_info[4].name = "eml_index_class";
  c6_info[4].dominantType = "";
  c6_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[4].fileTimeLo = 1323202978U;
  c6_info[4].fileTimeHi = 0U;
  c6_info[4].mFileTimeLo = 0U;
  c6_info[4].mFileTimeHi = 0U;
  c6_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c6_info[5].name = "eml_refblas_xnrm2";
  c6_info[5].dominantType = "double";
  c6_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[5].fileTimeLo = 1299109184U;
  c6_info[5].fileTimeHi = 0U;
  c6_info[5].mFileTimeLo = 0U;
  c6_info[5].mFileTimeHi = 0U;
  c6_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[6].name = "realmin";
  c6_info[6].dominantType = "char";
  c6_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c6_info[6].fileTimeLo = 1307683642U;
  c6_info[6].fileTimeHi = 0U;
  c6_info[6].mFileTimeLo = 0U;
  c6_info[6].mFileTimeHi = 0U;
  c6_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c6_info[7].name = "eml_realmin";
  c6_info[7].dominantType = "char";
  c6_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c6_info[7].fileTimeLo = 1307683644U;
  c6_info[7].fileTimeHi = 0U;
  c6_info[7].mFileTimeLo = 0U;
  c6_info[7].mFileTimeHi = 0U;
  c6_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c6_info[8].name = "eml_float_model";
  c6_info[8].dominantType = "char";
  c6_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c6_info[8].fileTimeLo = 1326760396U;
  c6_info[8].fileTimeHi = 0U;
  c6_info[8].mFileTimeLo = 0U;
  c6_info[8].mFileTimeHi = 0U;
  c6_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[9].name = "eml_index_class";
  c6_info[9].dominantType = "";
  c6_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[9].fileTimeLo = 1323202978U;
  c6_info[9].fileTimeHi = 0U;
  c6_info[9].mFileTimeLo = 0U;
  c6_info[9].mFileTimeHi = 0U;
  c6_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[10].name = "eml_index_minus";
  c6_info[10].dominantType = "double";
  c6_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c6_info[10].fileTimeLo = 1286851178U;
  c6_info[10].fileTimeHi = 0U;
  c6_info[10].mFileTimeLo = 0U;
  c6_info[10].mFileTimeHi = 0U;
  c6_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c6_info[11].name = "eml_index_class";
  c6_info[11].dominantType = "";
  c6_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[11].fileTimeLo = 1323202978U;
  c6_info[11].fileTimeHi = 0U;
  c6_info[11].mFileTimeLo = 0U;
  c6_info[11].mFileTimeHi = 0U;
  c6_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[12].name = "eml_index_times";
  c6_info[12].dominantType = "coder.internal.indexInt";
  c6_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c6_info[12].fileTimeLo = 1286851180U;
  c6_info[12].fileTimeHi = 0U;
  c6_info[12].mFileTimeLo = 0U;
  c6_info[12].mFileTimeHi = 0U;
  c6_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c6_info[13].name = "eml_index_class";
  c6_info[13].dominantType = "";
  c6_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[13].fileTimeLo = 1323202978U;
  c6_info[13].fileTimeHi = 0U;
  c6_info[13].mFileTimeLo = 0U;
  c6_info[13].mFileTimeHi = 0U;
  c6_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[14].name = "eml_index_plus";
  c6_info[14].dominantType = "coder.internal.indexInt";
  c6_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c6_info[14].fileTimeLo = 1286851178U;
  c6_info[14].fileTimeHi = 0U;
  c6_info[14].mFileTimeLo = 0U;
  c6_info[14].mFileTimeHi = 0U;
  c6_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c6_info[15].name = "eml_index_class";
  c6_info[15].dominantType = "";
  c6_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[15].fileTimeLo = 1323202978U;
  c6_info[15].fileTimeHi = 0U;
  c6_info[15].mFileTimeLo = 0U;
  c6_info[15].mFileTimeHi = 0U;
  c6_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[16].name = "eml_int_forloop_overflow_check";
  c6_info[16].dominantType = "";
  c6_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c6_info[16].fileTimeLo = 1346542740U;
  c6_info[16].fileTimeHi = 0U;
  c6_info[16].mFileTimeLo = 0U;
  c6_info[16].mFileTimeHi = 0U;
  c6_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c6_info[17].name = "intmax";
  c6_info[17].dominantType = "char";
  c6_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c6_info[17].fileTimeLo = 1311287716U;
  c6_info[17].fileTimeHi = 0U;
  c6_info[17].mFileTimeLo = 0U;
  c6_info[17].mFileTimeHi = 0U;
  c6_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c6_info[18].name = "abs";
  c6_info[18].dominantType = "double";
  c6_info[18].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c6_info[18].fileTimeLo = 1343862766U;
  c6_info[18].fileTimeHi = 0U;
  c6_info[18].mFileTimeLo = 0U;
  c6_info[18].mFileTimeHi = 0U;
  c6_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c6_info[19].name = "eml_scalar_abs";
  c6_info[19].dominantType = "double";
  c6_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c6_info[19].fileTimeLo = 1286851112U;
  c6_info[19].fileTimeHi = 0U;
  c6_info[19].mFileTimeLo = 0U;
  c6_info[19].mFileTimeHi = 0U;
  c6_info[20].context = "";
  c6_info[20].name = "mrdivide";
  c6_info[20].dominantType = "double";
  c6_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c6_info[20].fileTimeLo = 1357983948U;
  c6_info[20].fileTimeHi = 0U;
  c6_info[20].mFileTimeLo = 1319762366U;
  c6_info[20].mFileTimeHi = 0U;
  c6_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c6_info[21].name = "rdivide";
  c6_info[21].dominantType = "double";
  c6_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c6_info[21].fileTimeLo = 1346542788U;
  c6_info[21].fileTimeHi = 0U;
  c6_info[21].mFileTimeLo = 0U;
  c6_info[21].mFileTimeHi = 0U;
  c6_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c6_info[22].name = "eml_scalexp_compatible";
  c6_info[22].dominantType = "double";
  c6_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c6_info[22].fileTimeLo = 1286851196U;
  c6_info[22].fileTimeHi = 0U;
  c6_info[22].mFileTimeLo = 0U;
  c6_info[22].mFileTimeHi = 0U;
  c6_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c6_info[23].name = "eml_div";
  c6_info[23].dominantType = "double";
  c6_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c6_info[23].fileTimeLo = 1313380210U;
  c6_info[23].fileTimeHi = 0U;
  c6_info[23].mFileTimeLo = 0U;
  c6_info[23].mFileTimeHi = 0U;
  c6_info[24].context = "";
  c6_info[24].name = "cross";
  c6_info[24].dominantType = "double";
  c6_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c6_info[24].fileTimeLo = 1286851242U;
  c6_info[24].fileTimeHi = 0U;
  c6_info[24].mFileTimeLo = 0U;
  c6_info[24].mFileTimeHi = 0U;
  c6_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c6_info[25].name = "mtimes";
  c6_info[25].dominantType = "double";
  c6_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[25].fileTimeLo = 1289552092U;
  c6_info[25].fileTimeHi = 0U;
  c6_info[25].mFileTimeLo = 0U;
  c6_info[25].mFileTimeHi = 0U;
  c6_info[26].context = "";
  c6_info[26].name = "mtimes";
  c6_info[26].dominantType = "double";
  c6_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[26].fileTimeLo = 1289552092U;
  c6_info[26].fileTimeHi = 0U;
  c6_info[26].mFileTimeLo = 0U;
  c6_info[26].mFileTimeHi = 0U;
  c6_info[27].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[27].name = "eml_index_class";
  c6_info[27].dominantType = "";
  c6_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[27].fileTimeLo = 1323202978U;
  c6_info[27].fileTimeHi = 0U;
  c6_info[27].mFileTimeLo = 0U;
  c6_info[27].mFileTimeHi = 0U;
  c6_info[28].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[28].name = "eml_scalar_eg";
  c6_info[28].dominantType = "double";
  c6_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[28].fileTimeLo = 1286851196U;
  c6_info[28].fileTimeHi = 0U;
  c6_info[28].mFileTimeLo = 0U;
  c6_info[28].mFileTimeHi = 0U;
  c6_info[29].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[29].name = "eml_xgemm";
  c6_info[29].dominantType = "char";
  c6_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c6_info[29].fileTimeLo = 1299109172U;
  c6_info[29].fileTimeHi = 0U;
  c6_info[29].mFileTimeLo = 0U;
  c6_info[29].mFileTimeHi = 0U;
  c6_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c6_info[30].name = "eml_blas_inline";
  c6_info[30].dominantType = "";
  c6_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c6_info[30].fileTimeLo = 1299109168U;
  c6_info[30].fileTimeHi = 0U;
  c6_info[30].mFileTimeLo = 0U;
  c6_info[30].mFileTimeHi = 0U;
  c6_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c6_info[31].name = "mtimes";
  c6_info[31].dominantType = "double";
  c6_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[31].fileTimeLo = 1289552092U;
  c6_info[31].fileTimeHi = 0U;
  c6_info[31].mFileTimeLo = 0U;
  c6_info[31].mFileTimeHi = 0U;
  c6_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c6_info[32].name = "eml_index_class";
  c6_info[32].dominantType = "";
  c6_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[32].fileTimeLo = 1323202978U;
  c6_info[32].fileTimeHi = 0U;
  c6_info[32].mFileTimeLo = 0U;
  c6_info[32].mFileTimeHi = 0U;
  c6_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c6_info[33].name = "eml_scalar_eg";
  c6_info[33].dominantType = "double";
  c6_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[33].fileTimeLo = 1286851196U;
  c6_info[33].fileTimeHi = 0U;
  c6_info[33].mFileTimeLo = 0U;
  c6_info[33].mFileTimeHi = 0U;
  c6_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c6_info[34].name = "eml_refblas_xgemm";
  c6_info[34].dominantType = "char";
  c6_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c6_info[34].fileTimeLo = 1299109174U;
  c6_info[34].fileTimeHi = 0U;
  c6_info[34].mFileTimeLo = 0U;
  c6_info[34].mFileTimeHi = 0U;
}

static real_T c6_norm(SFc6_gif_modelInstanceStruct *chartInstance, real_T c6_x[3])
{
  real_T c6_y;
  real_T c6_scale;
  int32_T c6_k;
  int32_T c6_b_k;
  real_T c6_b_x;
  real_T c6_c_x;
  real_T c6_absxk;
  real_T c6_t;
  c6_y = 0.0;
  c6_scale = 2.2250738585072014E-308;
  for (c6_k = 1; c6_k < 4; c6_k++) {
    c6_b_k = c6_k;
    c6_b_x = c6_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c6_b_k), 1, 3, 1, 0) - 1];
    c6_c_x = c6_b_x;
    c6_absxk = muDoubleScalarAbs(c6_c_x);
    if (c6_absxk > c6_scale) {
      c6_t = c6_scale / c6_absxk;
      c6_y = 1.0 + c6_y * c6_t * c6_t;
      c6_scale = c6_absxk;
    } else {
      c6_t = c6_absxk / c6_scale;
      c6_y += c6_t * c6_t;
    }
  }

  return c6_scale * muDoubleScalarSqrt(c6_y);
}

static void c6_cross(SFc6_gif_modelInstanceStruct *chartInstance, real_T c6_a[3],
                     real_T c6_b[3], real_T c6_c[3])
{
  real_T c6_b_a;
  real_T c6_b_b;
  real_T c6_y;
  real_T c6_c_a;
  real_T c6_c_b;
  real_T c6_b_y;
  real_T c6_c1;
  real_T c6_d_a;
  real_T c6_d_b;
  real_T c6_c_y;
  real_T c6_e_a;
  real_T c6_e_b;
  real_T c6_d_y;
  real_T c6_c2;
  real_T c6_f_a;
  real_T c6_f_b;
  real_T c6_e_y;
  real_T c6_g_a;
  real_T c6_g_b;
  real_T c6_f_y;
  real_T c6_c3;
  c6_b_a = c6_a[1];
  c6_b_b = c6_b[2];
  c6_y = c6_b_a * c6_b_b;
  c6_c_a = c6_a[2];
  c6_c_b = c6_b[1];
  c6_b_y = c6_c_a * c6_c_b;
  c6_c1 = c6_y - c6_b_y;
  c6_d_a = c6_a[2];
  c6_d_b = c6_b[0];
  c6_c_y = c6_d_a * c6_d_b;
  c6_e_a = c6_a[0];
  c6_e_b = c6_b[2];
  c6_d_y = c6_e_a * c6_e_b;
  c6_c2 = c6_c_y - c6_d_y;
  c6_f_a = c6_a[0];
  c6_f_b = c6_b[1];
  c6_e_y = c6_f_a * c6_f_b;
  c6_g_a = c6_a[1];
  c6_g_b = c6_b[0];
  c6_f_y = c6_g_a * c6_g_b;
  c6_c3 = c6_e_y - c6_f_y;
  c6_c[0] = c6_c1;
  c6_c[1] = c6_c2;
  c6_c[2] = c6_c3;
}

static void c6_eml_scalar_eg(SFc6_gif_modelInstanceStruct *chartInstance)
{
}

static const mxArray *c6_f_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc6_gif_modelInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(int32_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static int32_T c6_f_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  int32_T c6_y;
  int32_T c6_i74;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_i74, 1, 6, 0U, 0, 0U, 0);
  c6_y = c6_i74;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_sfEvent;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  int32_T c6_y;
  SFc6_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc6_gif_modelInstanceStruct *)chartInstanceVoid;
  c6_b_sfEvent = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_sfEvent),
    &c6_thisId);
  sf_mex_destroy(&c6_b_sfEvent);
  *(int32_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static uint8_T c6_g_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_b_is_active_c6_gif_model, const char_T *c6_identifier)
{
  uint8_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_is_active_c6_gif_model), &c6_thisId);
  sf_mex_destroy(&c6_b_is_active_c6_gif_model);
  return c6_y;
}

static uint8_T c6_h_emlrt_marshallIn(SFc6_gif_modelInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint8_T c6_y;
  uint8_T c6_u0;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u0, 1, 3, 0U, 0, 0U, 0);
  c6_y = c6_u0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void init_dsm_address_info(SFc6_gif_modelInstanceStruct *chartInstance)
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

void sf_c6_gif_model_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1353191230U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3381538772U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1289208091U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(727294526U);
}

mxArray *sf_c6_gif_model_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("a4IUCwPExEhJu3YegvSUsD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c6_gif_model_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c6_gif_model(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"rtn\",},{M[8],M[0],T\"is_active_c6_gif_model\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c6_gif_model_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc6_gif_modelInstanceStruct *chartInstance;
    chartInstance = (SFc6_gif_modelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _gif_modelMachineNumber_,
           6,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"main_state");
          _SFD_SET_DATA_PROPS(1,2,0,1,"rtn");
          _SFD_SET_DATA_PROPS(2,1,1,0,"target_state");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,947);
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
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)
            c6_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c6_main_state)[6];
          real_T (*c6_rtn)[3];
          real_T (*c6_target_state)[6];
          c6_target_state = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S,
            1);
          c6_rtn = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c6_main_state = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S,
            0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c6_main_state);
          _SFD_SET_DATA_VALUE_PTR(1U, *c6_rtn);
          _SFD_SET_DATA_VALUE_PTR(2U, *c6_target_state);
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
  return "7ws4XobkucFnsea4OFpwqG";
}

static void sf_opaque_initialize_c6_gif_model(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc6_gif_modelInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c6_gif_model((SFc6_gif_modelInstanceStruct*)
    chartInstanceVar);
  initialize_c6_gif_model((SFc6_gif_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c6_gif_model(void *chartInstanceVar)
{
  enable_c6_gif_model((SFc6_gif_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c6_gif_model(void *chartInstanceVar)
{
  disable_c6_gif_model((SFc6_gif_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c6_gif_model(void *chartInstanceVar)
{
  sf_c6_gif_model((SFc6_gif_modelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c6_gif_model(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c6_gif_model((SFc6_gif_modelInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_gif_model();/* state var info */
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

extern void sf_internal_set_sim_state_c6_gif_model(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_gif_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c6_gif_model((SFc6_gif_modelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c6_gif_model(SimStruct* S)
{
  return sf_internal_get_sim_state_c6_gif_model(S);
}

static void sf_opaque_set_sim_state_c6_gif_model(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c6_gif_model(S, st);
}

static void sf_opaque_terminate_c6_gif_model(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc6_gif_modelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_gif_model_optimization_info();
    }

    finalize_c6_gif_model((SFc6_gif_modelInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc6_gif_model((SFc6_gif_modelInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c6_gif_model(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c6_gif_model((SFc6_gif_modelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c6_gif_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_gif_model_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      6);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,6,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,6,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,6);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,6,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,6,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,6);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1142080979U));
  ssSetChecksum1(S,(504440657U));
  ssSetChecksum2(S,(1726592877U));
  ssSetChecksum3(S,(2649004359U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c6_gif_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c6_gif_model(SimStruct *S)
{
  SFc6_gif_modelInstanceStruct *chartInstance;
  chartInstance = (SFc6_gif_modelInstanceStruct *)utMalloc(sizeof
    (SFc6_gif_modelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc6_gif_modelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c6_gif_model;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c6_gif_model;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c6_gif_model;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c6_gif_model;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c6_gif_model;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c6_gif_model;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c6_gif_model;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c6_gif_model;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c6_gif_model;
  chartInstance->chartInfo.mdlStart = mdlStart_c6_gif_model;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c6_gif_model;
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

void c6_gif_model_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c6_gif_model(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c6_gif_model(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c6_gif_model(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c6_gif_model_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
