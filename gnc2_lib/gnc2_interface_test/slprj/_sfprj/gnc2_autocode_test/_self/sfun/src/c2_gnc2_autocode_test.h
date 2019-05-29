#ifndef __c2_gnc2_autocode_test_h__
#define __c2_gnc2_autocode_test_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef struct_tag_s1m5B6NJK162FHK505r9TGE
#define struct_tag_s1m5B6NJK162FHK505r9TGE

struct tag_s1m5B6NJK162FHK505r9TGE
{
  real_T sc_mode;
  real_T quat_in[4];
  real_T w_body_radps[3];
  real_T hw_Nms[3];
  real_T quat_cmd[4];
  real_T w_body_cmd_radps[3];
  real_T sun_inertial_unit[3];
  real_T gps_epoch_s[2];
  real_T gps_time_s[2];
  real_T cmd_torque[3];
};

#endif                                 /*struct_tag_s1m5B6NJK162FHK505r9TGE*/

#ifndef typedef_c2_s1m5B6NJK162FHK505r9TGE
#define typedef_c2_s1m5B6NJK162FHK505r9TGE

typedef struct tag_s1m5B6NJK162FHK505r9TGE c2_s1m5B6NJK162FHK505r9TGE;

#endif                                 /*typedef_c2_s1m5B6NJK162FHK505r9TGE*/

#ifndef struct_tag_sK038USbKXHx7TyHj4tvcvF
#define struct_tag_sK038USbKXHx7TyHj4tvcvF

struct tag_sK038USbKXHx7TyHj4tvcvF
{
  c2_s1m5B6NJK162FHK505r9TGE ic;
  real_T sample_time_s;
  real_T N;
  real_T dt;
  real_T c_size;
  real_T Air_size;
  real_T Ajc_size;
  real_T Apr_size;
  real_T b_size;
  real_T Gir_size;
  real_T Gjc_size;
  real_T Gpr_size;
  real_T h_size;
  real_T q_size;
  real_T y_size;
  real_T l_dim;
  real_T soc_dim;
};

#endif                                 /*struct_tag_sK038USbKXHx7TyHj4tvcvF*/

#ifndef typedef_c2_sK038USbKXHx7TyHj4tvcvF
#define typedef_c2_sK038USbKXHx7TyHj4tvcvF

typedef struct tag_sK038USbKXHx7TyHj4tvcvF c2_sK038USbKXHx7TyHj4tvcvF;

#endif                                 /*typedef_c2_sK038USbKXHx7TyHj4tvcvF*/

#ifndef typedef_SFc2_gnc2_autocode_testInstanceStruct
#define typedef_SFc2_gnc2_autocode_testInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_gnc2_autocode_test;
  c2_sK038USbKXHx7TyHj4tvcvF c2_soac_params;
  real_T c2_G[117528];
  real_T c2_b_G[117528];
  real_T c2_c_G[117528];
  real_T c2_X[117528];
  real_T c2_s[117528];
  real_T c2_b_s[117528];
  real_T c2_A[38844];
  real_T c2_b_A[38844];
  real_T c2_c_A[38844];
  real_T c2_EH[10000];
  real_T c2_b_EH[10000];
  real_T c2_c_EH[10000];
  real_T c2_BE[3000];
  real_T c2_b_BE[3000];
  real_T c2_Glin[106904];
  real_T c2_Hv[33200];
  real_T c2_Hev[33200];
  real_T c2_Gquad[10624];
  real_T c2_dv58[10000];
  real_T c2_dv60[10000];
  real_T c2_Hw[9960];
  real_T c2_Hu[9960];
  real_T c2_c_BE[3000];
  real_T c2_y[117528];
  real_T c2_dv17[117528];
  real_T c2_b_y[106904];
  real_T c2_dv34[106904];
  real_T c2_b_X[38844];
  real_T c2_c_s[38844];
  real_T c2_d_s[38844];
  real_T c2_u[117528];
  real_T c2_b_u[106904];
  real_T c2_c_y[38844];
  real_T c2_dv15[38844];
  real_T c2_d_y[33200];
  real_T c2_dv35[33200];
  real_T c2_c_u[38844];
  real_T c2_d_u[33200];
  real_T (*c2_c_X)[100];
  real_T (*c2_U)[30];
  real_T *c2_e_s;
  real_T (*c2_J)[9];
  real_T (*c2_ME)[16];
  real_T (*c2_MI)[16];
  real_T *c2_T_max;
  real_T *c2_w_max;
  real_T *c2_s_max;
  real_T *c2_s_min;
  real_T *c2_w_v;
  real_T (*c2_d_X)[100];
  real_T (*c2_b_U)[30];
  real_T *c2_f_s;
  real_T (*c2_exitcode)[11];
  real_T (*c2_time)[10];
} SFc2_gnc2_autocode_testInstanceStruct;

#endif                                 /*typedef_SFc2_gnc2_autocode_testInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_gnc2_autocode_test_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c2_gnc2_autocode_test_get_check_sum(mxArray *plhs[]);
extern void c2_gnc2_autocode_test_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
