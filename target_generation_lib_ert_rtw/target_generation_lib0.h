/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: target_generation_lib0.h
 *
 * Code generated for Simulink model 'target_generation_lib0'.
 *
 * Model version                  : 1.39
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 16:50:56 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_target_generation_lib0_h_
#define RTW_HEADER_target_generation_lib0_h_
#include <math.h>
#include <string.h>
#ifndef target_generation_lib0_COMMON_INCLUDES_
# define target_generation_lib0_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* target_generation_lib0_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T sc_mode;                      /* '<Root>/sc_mode' */
  real_T sc2sun_eci_unit[3];           /* '<Root>/sc2sun_eci_unit' */
  real_T vel_eci_kmps[3];              /* '<Root>/vel_eci_kmps' */
  real_T sc2gs_eci_unit[3];            /* '<Root>/sc2gs_eci_unit' */
  real_T orbit_tle[9];                 /* '<Root>/orbit_tle' */
  real_T sc_quat[4];                   /* '<Root>/sc_quat' */
} ExtU;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T quat_cmd[4];                  /* '<Root>/quat_cmd' */
  real_T omega_cmd_radps[3];           /* '<Root>/omega_cmd_radps' */
  real_T flag;                         /* '<Root>/flag' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* External inputs (root inport signals with auto storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void target_generation_lib0_initialize(void);
extern void target_generation_lib0_step(void);
extern void target_generation_lib0_terminate(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition2' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition3' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition4' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition5' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition6' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition7' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition8' : Eliminated since input and output rates are identical
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
 * hilite_system('target_generation_test/target_generation_lib')    - opens subsystem target_generation_test/target_generation_lib
 * hilite_system('target_generation_test/target_generation_lib/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'target_generation_test'
 * '<S1>'   : 'target_generation_test/target_generation_lib'
 * '<S2>'   : 'target_generation_test/target_generation_lib/MATLAB Function'
 * '<S3>'   : 'target_generation_test/target_generation_lib/MATLAB Function2'
 */
#endif                                 /* RTW_HEADER_target_generation_lib0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
