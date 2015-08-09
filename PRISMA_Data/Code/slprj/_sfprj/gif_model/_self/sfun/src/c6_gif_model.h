#ifndef __c6_gif_model_h__
#define __c6_gif_model_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_sqIgkGf7JWLZgCaATJHsg3G
#define struct_sqIgkGf7JWLZgCaATJHsg3G

struct sqIgkGf7JWLZgCaATJHsg3G
{
  real_T pos_RTN[3];
  real_T pos[3];
  real_T vel[3];
};

#endif                                 /*struct_sqIgkGf7JWLZgCaATJHsg3G*/

#ifndef typedef_c6_sqIgkGf7JWLZgCaATJHsg3G
#define typedef_c6_sqIgkGf7JWLZgCaATJHsg3G

typedef struct sqIgkGf7JWLZgCaATJHsg3G c6_sqIgkGf7JWLZgCaATJHsg3G;

#endif                                 /*typedef_c6_sqIgkGf7JWLZgCaATJHsg3G*/

#ifndef typedef_c6_ResolvedFunctionInfo
#define typedef_c6_ResolvedFunctionInfo

typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} c6_ResolvedFunctionInfo;

#endif                                 /*typedef_c6_ResolvedFunctionInfo*/

#ifndef typedef_SFc6_gif_modelInstanceStruct
#define typedef_SFc6_gif_modelInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c6_sfEvent;
  boolean_T c6_isStable;
  boolean_T c6_doneDoubleBufferReInit;
  uint8_T c6_is_active_c6_gif_model;
} SFc6_gif_modelInstanceStruct;

#endif                                 /*typedef_SFc6_gif_modelInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c6_gif_model_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c6_gif_model_get_check_sum(mxArray *plhs[]);
extern void c6_gif_model_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
