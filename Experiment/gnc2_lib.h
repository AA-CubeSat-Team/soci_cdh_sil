/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: gnc2_lib.h
 *
 * Code generated for Simulink model 'gnc2_lib'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 14:12:23 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. RAM efficiency
 *    2. Execution efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_gnc2_lib_h_
#define RTW_HEADER_gnc2_lib_h_
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#ifndef gnc2_lib_COMMON_INCLUDES_
# define gnc2_lib_COMMON_INCLUDES_
#include "rtwtypes.h"
//#include "rtw_continuous.h"
//#include "rtw_solver.h"
#include "ecos.h"
#endif                                 /* gnc2_lib_COMMON_INCLUDES_ */

/* Child system includes */
#include "gnc2_lib.h"
#include "baiegdbacjmgjekn_xungorghr.h"
#include "biecbaaiaieclnop_eml_dlahqr.h"
#include "fcbafcjedbimfkfc_inv.h"
#include "fkfkimopaimgfkno_kron.h"
#include "gdbifkfcbaimlfkn_norm.h"
#include "hdbaecbadjekpphd_xgehrd.h"
#include "knohcbaaphlnkfcb_convert_to_CCS.h"
#include "mgdbiecbmohlcjmo_convert_to_CCS.h"
#include "mgdjecjmkfkndbim_eye.h"
#include "nglnimohlfkfphln_norm.h"
#include "nohdopppmohdjmoh_eye.h"
#include "pphlkfcjfcjmiekf_foh.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#ifndef DEFINED_TYPEDEF_FOR_struct_AcnLvokJNhWXokknGroaEE_
#define DEFINED_TYPEDEF_FOR_struct_AcnLvokJNhWXokknGroaEE_

typedef struct {
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
} struct_AcnLvokJNhWXokknGroaEE;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_A6pyUWfZ73Ou2cfAMckM4_
#define DEFINED_TYPEDEF_FOR_struct_A6pyUWfZ73Ou2cfAMckM4_

typedef struct {
  struct_AcnLvokJNhWXokknGroaEE ic;
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
} struct_A6pyUWfZ73Ou2cfAMckM4;

#endif

/* Custom Type definition for MATLAB Function: '<S1>/SOLVE' */
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

#ifndef typedef_s1m5B6NJK162FHK505r9TGE
#define typedef_s1m5B6NJK162FHK505r9TGE

typedef struct tag_s1m5B6NJK162FHK505r9TGE s1m5B6NJK162FHK505r9TGE;

#endif                                 /*typedef_s1m5B6NJK162FHK505r9TGE*/

#ifndef struct_tag_sK038USbKXHx7TyHj4tvcvF
#define struct_tag_sK038USbKXHx7TyHj4tvcvF

struct tag_sK038USbKXHx7TyHj4tvcvF
{
  s1m5B6NJK162FHK505r9TGE ic;
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

#ifndef typedef_sK038USbKXHx7TyHj4tvcvF
#define typedef_sK038USbKXHx7TyHj4tvcvF

typedef struct tag_sK038USbKXHx7TyHj4tvcvF sK038USbKXHx7TyHj4tvcvF;

#endif                                 /*typedef_sK038USbKXHx7TyHj4tvcvF*/

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  real_T rtb_TmpSignalConversionAtGprO_m[674];
  real_T rtb_TmpSignalConversionAtAprO_c[1278];
  real_T EH[10000];
  real_T BE[3000];
  real_T G[117528];
  real_T A[38844];
  real_T Air[1278];
  real_T Apr[1278];
  real_T Gir[674];
  real_T Gpr[674];
  real_T Hw[9960];
  real_T Hu[9960];
  real_T Hv[33200];
  real_T Hev[33200];
  real_T dv0[10000];
  real_T dv1[10000];
  real_T dv2[900];
  real_T dv3[3000];
  int32_T rtb_DataTypeConversion9_k[1278];
} DW;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T quat_init[4];                 /* '<Root>/quat_init' */
  real_T hw_Nms_init[3];               /* '<Root>/hw_Nms_init' */
  real_T w_radps_init[3];              /* '<Root>/w_radps_init' */
  real_T quat_final[4];                /* '<Root>/quat_final' */
  real_T w_radps_final[3];             /* '<Root>/w_radps_final' */
  real_T sun_unit_inertial[3];         /* '<Root>/sun_unit_inertial' */
} ExtU;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T opt_state[100];               /* '<Root>/opt_state' */
  real_T opt_ctrl_Nm[30];              /* '<Root>/opt_ctrl_Nm' */
  real_T final_time_s;                 /* '<Root>/final_time_s' */
  real_T exitcode[11];                 /* '<Root>/exitcode' */
  real_T sol_times_s[10];              /* '<Root>/sol_times_s' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (auto storage) */
extern DW rtDW;

/* External inputs (root inport signals with auto storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void gnc2_lib_initialize(void);
extern void gnc2_lib_step(void);
extern void gnc2_lib_terminate(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S4>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S4>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S4>/Data Type Conversion13' : Eliminate redundant data type conversion
 * Block '<S4>/Data Type Conversion14' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('gnc2_autocode_test/gnc2_lib')    - opens subsystem gnc2_autocode_test/gnc2_lib
 * hilite_system('gnc2_autocode_test/gnc2_lib/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'gnc2_autocode_test'
 * '<S1>'   : 'gnc2_autocode_test/gnc2_lib'
 * '<S2>'   : 'gnc2_autocode_test/gnc2_lib/INITIALIZE'
 * '<S3>'   : 'gnc2_autocode_test/gnc2_lib/SOLVE'
 * '<S4>'   : 'gnc2_autocode_test/gnc2_lib/call to ECOS SOCP solver (compiled C function)'
 */
#endif                                 /* RTW_HEADER_gnc2_lib_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
