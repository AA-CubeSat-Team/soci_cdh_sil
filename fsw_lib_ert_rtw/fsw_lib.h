/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: fsw_lib.h
 *
 * Code generated for Simulink model 'fsw_lib'.
 *
 * Model version                  : 1.372
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Thu Mar  7 16:07:53 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Altera->SoC (ARM Cortex A)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_fsw_lib_h_
#define RTW_HEADER_fsw_lib_h_
#include <stddef.h>
#include "rtwtypes.h"
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef fsw_lib_COMMON_INCLUDES_
# define fsw_lib_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* fsw_lib_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#ifndef DEFINED_TYPEDEF_FOR_telecommands_
#define DEFINED_TYPEDEF_FOR_telecommands_

typedef struct {
  int8_T telecom[3];
  real_T MET_epoch;
  real_T MET;
} telecommands;

#endif

#ifndef DEFINED_TYPEDEF_FOR_sp2fsw_
#define DEFINED_TYPEDEF_FOR_sp2fsw_

typedef struct {
  real_T mag_vec_body_T[4];
  real_T gyro_omega_body_radps[4];
  real_T faceinsun_body_unit[3];
  real_T sun_vec_body_sunsensor[4];
  real_T orbit_tle[9];
  real_T GPS_time[2];
} sp2fsw;

#endif

#ifndef DEFINED_TYPEDEF_FOR_telemetry_
#define DEFINED_TYPEDEF_FOR_telemetry_

typedef struct {
  real_T sc_quat[4];
  real_T body_rates[3];
  int8_T sc_mode;

  /* indication that we meet the velocity pointing requirement */
  boolean_T vel_point;
  real_T quat_cmd[4];

  /* indication that the s/c is above the ground station and COM2 can commence */
  boolean_T sc_above_gs;
  boolean_T sc_in_sun;
  real_T mag_eci_unit[3];
  real_T pos_eci_km[3];
  real_T vel_eci_kmps[3];
  boolean_T gyro_valid;
} telemetry;

#endif

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  real_T RateTransition7[3];           /* '<S5>/Rate Transition7' */
  real_T RateTransition2[3];           /* '<S5>/Rate Transition2' */
  real_T RateTransition11[3];          /* '<S5>/Rate Transition11' */
  real_T u1[3];                        /* '<S9>/ 11' */
  real_T u0[36];                       /* '<S9>/ 10' */
  real_T u1_f[3];                      /* '<S10>/ 11' */
  real_T RateTransition1[3];           /* '<S7>/Rate Transition1' */
  real_T RateTransition2_b[3];         /* '<S7>/Rate Transition2' */
  real_T UnitDelay_DSTATE[4];          /* '<S9>/Unit Delay' */
  real_T UnitDelay1_DSTATE[3];         /* '<S9>/Unit Delay1' */
  real_T UnitDelay2_DSTATE[36];        /* '<S9>/Unit Delay2' */
  real_T UnitDelay_DSTATE_n[4];        /* '<S10>/Unit Delay' */
  real_T UnitDelay_DSTATE_b[3];        /* '<S33>/Unit Delay' */
  real_T UnitDelay_DSTATE_o[3];        /* '<S35>/Unit Delay' */
  real_T DiscreteTransferFcn_states[3];/* '<S35>/Discrete Transfer Fcn' */
  real_T UD_DSTATE[3];                 /* '<S49>/UD' */
  real_T DiscreteTimeIntegrator_DSTATE[3];/* '<S53>/Discrete-Time Integrator' */
  real_T UnitDelay_DSTATE_k[3];        /* '<S58>/Unit Delay' */
  real_T RateTransition7_1_Buffer0[4]; /* '<S1>/Rate Transition7' */
  real_T RateTransition7_2_Buffer0[3]; /* '<S1>/Rate Transition7' */
  real_T RateTransition7_5_Buffer0[4]; /* '<S1>/Rate Transition7' */
  real_T RateTransition7_8_Buffer0[3]; /* '<S1>/Rate Transition7' */
  real_T RateTransition4_Buffer0[3];   /* '<S1>/Rate Transition4' */
  real_T RateTransition7_Buffer0[3];   /* '<S5>/Rate Transition7' */
  real_T RateTransition2_Buffer0[3];   /* '<S5>/Rate Transition2' */
  real_T RateTransition11_Buffer0[3];  /* '<S5>/Rate Transition11' */
  real_T Product_DWORK4[9];            /* '<S54>/Product' */
  real_T RateTransition;               /* '<S36>/Rate Transition' */
  real_T RateTransition_Buffer0;       /* '<S36>/Rate Transition' */
  int32_T clockTickCounter;            /* '<S36>/Pulse Generator' */
  int8_T RateTransition1_n[3];         /* '<S1>/Rate Transition1' */
  int8_T RateTransition1_Buffer0[3];   /* '<S1>/Rate Transition1' */
  int8_T UnitDelay_DSTATE_g;           /* '<S6>/Unit Delay' */
  int8_T RateTransition7_3_Buffer0;    /* '<S1>/Rate Transition7' */
  boolean_T RateTransition7_4_Buffer0; /* '<S1>/Rate Transition7' */
  boolean_T RateTransition7_6_Buffer0; /* '<S1>/Rate Transition7' */
  boolean_T RateTransition7_7_Buffer0; /* '<S1>/Rate Transition7' */
  boolean_T RateTransition7_11_Buffer0;/* '<S1>/Rate Transition7' */
  boolean_T Relay_Mode;                /* '<S6>/Relay' */
  boolean_T Relay1_Mode;               /* '<S6>/Relay1' */
} DW;

/* Invariant block signals (auto storage) */
typedef struct {
  const real_T Product1[36];           /* '<S11>/Product1' */
} ConstB;

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: fsw_params.control.sun_point.prop_gain
   * Referenced by: '<S37>/prop_gain'
   */
  real_T prop_gain_Gain[9];

  /* Expression: fsw_params.control.sun_point.drv_gain
   * Referenced by: '<S37>/drv_gain'
   */
  real_T drv_gain_Gain[9];

  /* Expression: fsw_params.estimation.ic.error_cov
   * Referenced by: '<S9>/Unit Delay2'
   */
  real_T UnitDelay2_InitialCondition[36];

  /* Expression: fsw_params.estimation.meas_cov
   * Referenced by: '<S9>/Constant1'
   */
  real_T Constant1_Value[36];

  /* Expression: fsw_params.control.pd_controller.p_gain
   * Referenced by: '<S34>/Constant'
   */
  real_T Constant_Value_p[9];

  /* Expression: fsw_params.control.pd_controller.d_gain
   * Referenced by: '<S34>/Constant1'
   */
  real_T Constant1_Value_l[9];

  /* Pooled Parameter (Expression: fsw_params.actuators.reaction_wheel.inertia_matrix)
   * Referenced by:
   *   '<S33>/RW_inertia'
   *   '<S40>/wheel_inertia'
   *   '<S53>/Constant'
   */
  real_T pooled23[9];

  /* Expression: fsw_params.control.bdot.gain_matrix
   * Referenced by: '<S35>/gain matrix'
   */
  real_T gainmatrix_Value[9];

  /* Expression: fsw_params.sensor_processing.magnetometer.process_matrix
   * Referenced by: '<S50>/Constant1'
   */
  real_T Constant1_Value_o[9];
} ConstP;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  boolean_T MT_valid[3];               /* '<Root>/MT_valid' */
  boolean_T RW_valid[3];               /* '<Root>/RW_valid' */
  boolean_T RW_pwr[3];                 /* '<Root>/RW_pwr' */
  boolean_T MT_pwr[3];                 /* '<Root>/MT_pwr' */
  real_T RW_rpm[3];                    /* '<Root>/RW_rpm' */
  boolean_T thruster_on;               /* '<Root>/thruster_on' */
  int8_T telecom[3];                   /* '<Root>/telecom' */
  real_T MET_epoch;                    /* '<Root>/MET_epoch' */
  real_T MET;                          /* '<Root>/MET' */
  real_T mag_vec_body_T[4];            /* '<Root>/mag_vec_body_T' */
  real_T gyro_omega_body_radps[4];     /* '<Root>/gyro_omega_body_radps' */
  real_T faceinsun_body_unit[3];       /* '<Root>/faceinsun_body_unit' */
  real_T sun_vec_body_sunsensor[4];    /* '<Root>/sun_vec_body_sunsensor' */
  real_T orbit_tle[9];                 /* '<Root>/orbit_tle' */
  real_T GPS_time[2];                  /* '<Root>/GPS_time' */
} ExtU;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T sc_quat[4];                   /* '<Root>/sc_quat' */
  real_T body_rates[3];                /* '<Root>/body_rates' */
  int8_T sc_mode;                      /* '<Root>/sc_mode' */
  boolean_T vel_point;                 /* '<Root>/vel_point' */
  real_T quat_cmd[4];                  /* '<Root>/quat_cmd' */
  boolean_T sc_above_gs;               /* '<Root>/sc_above_gs' */
  boolean_T sc_in_sun;                 /* '<Root>/sc_in_sun' */
  real_T mag_eci_unit[3];              /* '<Root>/mag_eci_unit' */
  real_T pos_eci_km[3];                /* '<Root>/pos_eci_km' */
  real_T vel_eci_kmps[3];              /* '<Root>/vel_eci_kmps' */
  boolean_T gyro_valid;                /* '<Root>/gyro_valid' */
  real_T cmd_RW_rpm[3];                /* '<Root>/cmd_RW_rpm' */
  int8_T cmd_MT_dv[3];                 /* '<Root>/cmd_MT_dv' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID0_2;
      uint8_T TID1_2;
      uint8_T TID2_3;
    } RateInteraction;
  } Timing;
};

/* Block signals and states (auto storage) */
extern DW rtDW;

/* External inputs (root inport signals with auto storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY rtY;
extern const ConstB rtConstB;          /* constant block i/o */

/* Constant parameters (auto storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void fsw_lib_initialize(void);
extern void fsw_lib_step0(void);
extern void fsw_lib_step1(void);
extern void fsw_lib_step2(void);
extern void fsw_lib_step3(void);
extern void fsw_lib_terminate(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Rate Transition2' : Unused code path elimination
 * Block '<S2>/Rate Transition3' : Unused code path elimination
 * Block '<S2>/Rate Transition6' : Unused code path elimination
 * Block '<S9>/Extract Diagonal' : Unused code path elimination
 * Block '<S9>/Rate Transition10' : Unused code path elimination
 * Block '<S9>/Reshape2' : Unused code path elimination
 * Block '<S9>/Reshape3' : Unused code path elimination
 * Block '<S49>/Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/Rate Transition10' : Unused code path elimination
 * Block '<S5>/Rate Transition4' : Unused code path elimination
 * Block '<S5>/Rate Transition8' : Unused code path elimination
 * Block '<S7>/Rate Transition8' : Unused code path elimination
 * Block '<S122>/Constant1' : Unused code path elimination
 * Block '<S122>/Constant10' : Unused code path elimination
 * Block '<S122>/Constant2' : Unused code path elimination
 * Block '<S122>/Constant26' : Unused code path elimination
 * Block '<S122>/Constant3' : Unused code path elimination
 * Block '<S122>/Constant4' : Unused code path elimination
 * Block '<S122>/Constant5' : Unused code path elimination
 * Block '<S122>/Constant6' : Unused code path elimination
 * Block '<S122>/Constant7' : Unused code path elimination
 * Block '<S122>/Constant8' : Unused code path elimination
 * Block '<S122>/Constant9' : Unused code path elimination
 * Block '<S127>/Product' : Unused code path elimination
 * Block '<S127>/Product1' : Unused code path elimination
 * Block '<S127>/Product2' : Unused code path elimination
 * Block '<S127>/Product3' : Unused code path elimination
 * Block '<S127>/Sum' : Unused code path elimination
 * Block '<S128>/Product' : Unused code path elimination
 * Block '<S128>/Product1' : Unused code path elimination
 * Block '<S128>/Product2' : Unused code path elimination
 * Block '<S128>/Product3' : Unused code path elimination
 * Block '<S128>/Sum' : Unused code path elimination
 * Block '<S129>/Product' : Unused code path elimination
 * Block '<S129>/Product1' : Unused code path elimination
 * Block '<S129>/Product2' : Unused code path elimination
 * Block '<S129>/Product3' : Unused code path elimination
 * Block '<S129>/Sum' : Unused code path elimination
 * Block '<S1>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition10' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition11' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition3' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition5' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition8' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition9' : Eliminated since input and output rates are identical
 * Block '<S2>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S2>/Rate Transition4' : Eliminated since input and output rates are identical
 * Block '<S2>/Rate Transition5' : Eliminated since input and output rates are identical
 * Block '<S3>/ ' : Eliminated since input and output rates are identical
 * Block '<S9>/ ' : Eliminated since input and output rates are identical
 * Block '<S9>/ 1' : Eliminated since input and output rates are identical
 * Block '<S9>/ 2' : Eliminated since input and output rates are identical
 * Block '<S9>/ 3' : Eliminated since input and output rates are identical
 * Block '<S9>/ 4' : Eliminated since input and output rates are identical
 * Block '<S9>/ 5' : Eliminated since input and output rates are identical
 * Block '<S9>/ 6' : Eliminated since input and output rates are identical
 * Block '<S9>/ 7' : Eliminated since input and output rates are identical
 * Block '<S9>/ 8' : Eliminated since input and output rates are identical
 * Block '<S9>/Rate Transition2' : Eliminated since input and output rates are identical
 * Block '<S9>/Rate Transition3' : Eliminated since input and output rates are identical
 * Block '<S9>/Reshape1' : Reshape block reduction
 * Block '<S9>/Reshape4' : Reshape block reduction
 * Block '<S10>/ 1' : Eliminated since input and output rates are identical
 * Block '<S10>/ 2' : Eliminated since input and output rates are identical
 * Block '<S10>/ 4' : Eliminated since input and output rates are identical
 * Block '<S10>/ 5' : Eliminated since input and output rates are identical
 * Block '<S10>/ 6' : Eliminated since input and output rates are identical
 * Block '<S10>/Rate Transition2' : Eliminated since input and output rates are identical
 * Block '<S33>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S33>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S33>/Rate Transition2' : Eliminated since input and output rates are identical
 * Block '<S33>/Rate Transition3' : Eliminated since input and output rates are identical
 * Block '<S34>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S34>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S34>/Rate Transition2' : Eliminated since input and output rates are identical
 * Block '<S34>/Rate Transition4' : Eliminated since input and output rates are identical
 * Block '<S34>/Rate Transition5' : Eliminated since input and output rates are identical
 * Block '<S35>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S35>/Rate Transition2' : Eliminated since input and output rates are identical
 * Block '<S35>/Rate Transition4' : Eliminated since input and output rates are identical
 * Block '<S55>/Reshape' : Reshape block reduction
 * Block '<S37>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S37>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S37>/Rate Transition2' : Eliminated since input and output rates are identical
 * Block '<S37>/Rate Transition3' : Eliminated since input and output rates are identical
 * Block '<S37>/Rate Transition4' : Eliminated since input and output rates are identical
 * Block '<S5>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S5>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S5>/Rate Transition3' : Eliminated since input and output rates are identical
 * Block '<S5>/Rate Transition5' : Eliminated since input and output rates are identical
 * Block '<S5>/Rate Transition6' : Eliminated since input and output rates are identical
 * Block '<S5>/Rate Transition9' : Eliminated since input and output rates are identical
 * Block '<S86>/Reshape (9) to [3x3] column-major' : Reshape block reduction
 * Block '<S97>/Reshape (9) to [3x3] column-major' : Reshape block reduction
 * Block '<S7>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S7>/Rate Transition3' : Eliminated since input and output rates are identical
 * Block '<S7>/Rate Transition4' : Eliminated since input and output rates are identical
 * Block '<S7>/Rate Transition5' : Eliminated since input and output rates are identical
 * Block '<S7>/Rate Transition6' : Eliminated since input and output rates are identical
 * Block '<S7>/Rate Transition7' : Eliminated since input and output rates are identical
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
 * hilite_system('adcs_sim_main/Flightsoftware/fsw_lib')    - opens subsystem adcs_sim_main/Flightsoftware/fsw_lib
 * hilite_system('adcs_sim_main/Flightsoftware/fsw_lib/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'adcs_sim_main/Flightsoftware'
 * '<S1>'   : 'adcs_sim_main/Flightsoftware/fsw_lib'
 * '<S2>'   : 'adcs_sim_main/Flightsoftware/fsw_lib/actuator_processing'
 * '<S3>'   : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib'
 * '<S4>'   : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation'
 * '<S5>'   : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib'
 * '<S6>'   : 'adcs_sim_main/Flightsoftware/fsw_lib/mode_selecction'
 * '<S7>'   : 'adcs_sim_main/Flightsoftware/fsw_lib/target_generation_lib'
 * '<S8>'   : 'adcs_sim_main/Flightsoftware/fsw_lib/telemetry_lib'
 * '<S9>'   : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF '
 * '<S10>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/TRIAD_coarse_estimator'
 * '<S11>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Propagate Step '
 * '<S12>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Update Step '
 * '<S13>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Propagate Step /Quaternion Normalize'
 * '<S14>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Propagate Step /propagate_quat'
 * '<S15>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Propagate Step /state_transition'
 * '<S16>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Propagate Step /Quaternion Normalize/Quaternion Modulus'
 * '<S17>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Propagate Step /Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S18>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Update Step /If Action Subsystem'
 * '<S19>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Update Step /If Action Subsystem1'
 * '<S20>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Update Step /If Action Subsystem/convert_inertial_body'
 * '<S21>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Update Step /If Action Subsystem/covariance_update'
 * '<S22>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Update Step /If Action Subsystem/kalman_gain'
 * '<S23>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Update Step /If Action Subsystem/observation_matrix'
 * '<S24>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/Estimation_EKF /Update Step /If Action Subsystem/update_state '
 * '<S25>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/TRIAD_coarse_estimator/Passthrough'
 * '<S26>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/TRIAD_coarse_estimator/TRIAD '
 * '<S27>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/TRIAD_coarse_estimator/TRIAD /Cross Product'
 * '<S28>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/TRIAD_coarse_estimator/TRIAD /Cross Product1'
 * '<S29>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/TRIAD_coarse_estimator/TRIAD /Cross Product2'
 * '<S30>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/TRIAD_coarse_estimator/TRIAD /Cross Product3'
 * '<S31>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/attitude_estimation_lib/TRIAD_coarse_estimator/TRIAD /MATLAB Function3'
 * '<S32>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/Control Selection'
 * '<S33>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/Momentum unloading'
 * '<S34>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/PD Control'
 * '<S35>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/bdot_controller_lib'
 * '<S36>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/command_processing'
 * '<S37>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/sun_point_lib'
 * '<S38>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/Control Selection/MATLAB Function'
 * '<S39>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/Momentum unloading/Cross Product'
 * '<S40>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/Momentum unloading/momentum_ref'
 * '<S41>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/PD Control/Quaternion Inverse'
 * '<S42>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/PD Control/Quaternion Multiplication'
 * '<S43>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/PD Control/Quaternion Inverse/Quaternion Conjugate'
 * '<S44>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/PD Control/Quaternion Inverse/Quaternion Norm'
 * '<S45>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/PD Control/Quaternion Multiplication/q0'
 * '<S46>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/PD Control/Quaternion Multiplication/q1'
 * '<S47>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/PD Control/Quaternion Multiplication/q2'
 * '<S48>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/PD Control/Quaternion Multiplication/q3'
 * '<S49>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/bdot_controller_lib/Discrete Derivative'
 * '<S50>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/bdot_controller_lib/Signal Processing'
 * '<S51>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/command_processing/Compare To Constant'
 * '<S52>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/command_processing/dipole-2-digVal'
 * '<S53>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/command_processing/torque-2-RPM'
 * '<S54>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/command_processing/torque-2-RPM/Invert  3x3 Matrix'
 * '<S55>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/command_processing/torque-2-RPM/Invert  3x3 Matrix/Determinant of 3x3 Matrix'
 * '<S56>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/sun_point_lib/Compare To Constant'
 * '<S57>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/sun_point_lib/Compare To Constant1'
 * '<S58>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/sun_point_lib/compute_error'
 * '<S59>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/sun_point_lib/compute_error/3x3 Cross Product'
 * '<S60>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/sun_point_lib/compute_error/3x3 Cross Product/Subsystem'
 * '<S61>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/command_generation/sun_point_lib/compute_error/3x3 Cross Product/Subsystem1'
 * '<S62>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction'
 * '<S63>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/mag_vec_LS_lib'
 * '<S64>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/mag_vec_lib'
 * '<S65>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/sgp4_lib_fsw'
 * '<S66>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/sun_vector_lib'
 * '<S67>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/time_coord_rotation_lib'
 * '<S68>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib'
 * '<S69>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position'
 * '<S70>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/MATLAB Function1'
 * '<S71>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED'
 * '<S72>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED1'
 * '<S73>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Geodetic to  Geocentric Latitude'
 * '<S74>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/LatLong wrap'
 * '<S75>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Radius at Geocentric Latitude'
 * '<S76>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED/A11'
 * '<S77>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED/A12'
 * '<S78>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED/A13'
 * '<S79>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED/A21'
 * '<S80>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED/A22'
 * '<S81>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED/A23'
 * '<S82>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED/A31'
 * '<S83>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED/A32'
 * '<S84>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED/A33'
 * '<S85>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED/Angle Conversion'
 * '<S86>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED/Create Transformation Matrix'
 * '<S87>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED1/A11'
 * '<S88>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED1/A12'
 * '<S89>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED1/A13'
 * '<S90>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED1/A21'
 * '<S91>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED1/A22'
 * '<S92>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED1/A23'
 * '<S93>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED1/A31'
 * '<S94>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED1/A32'
 * '<S95>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED1/A33'
 * '<S96>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED1/Angle Conversion'
 * '<S97>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Direction Cosine Matrix ECI to NED1/Create Transformation Matrix'
 * '<S98>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Geodetic to  Geocentric Latitude/Conversion'
 * '<S99>'  : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Geodetic to  Geocentric Latitude/Conversion1'
 * '<S100>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Geodetic to  Geocentric Latitude/Conversion2'
 * '<S101>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Geodetic to  Geocentric Latitude/Latitude Wrap 90'
 * '<S102>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Geodetic to  Geocentric Latitude/Radius at Geocentric Latitude'
 * '<S103>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Geodetic to  Geocentric Latitude/Radius at Geocentric Latitude/Conversion'
 * '<S104>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/LatLong wrap/Latitude Wrap 90'
 * '<S105>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/LatLong wrap/Wrap Longitude'
 * '<S106>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/LatLong wrap/Latitude Wrap 90/Compare To Constant'
 * '<S107>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/LatLong wrap/Latitude Wrap 90/Wrap Angle 180'
 * '<S108>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/LatLong wrap/Latitude Wrap 90/Wrap Angle 180/Compare To Constant'
 * '<S109>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/LatLong wrap/Wrap Longitude/Compare To Constant'
 * '<S110>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/gs_prediction/gs_prediction_lib/LLA to ECEF Position/Radius at Geocentric Latitude/Conversion'
 * '<S111>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/sgp4_lib_fsw/MATLAB Function'
 * '<S112>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/sun_vector_lib/MATLAB Function'
 * '<S113>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/sun_vector_lib/MATLAB Function1'
 * '<S114>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/time_coord_rotation_lib/coord_rotations_lib'
 * '<S115>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/time_coord_rotation_lib/time_conversion_lib'
 * '<S116>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/time_coord_rotation_lib/coord_rotations_lib/MATLAB Function'
 * '<S117>' : 'adcs_sim_main/Flightsoftware/fsw_lib/env_estimation_lib/time_coord_rotation_lib/time_conversion_lib/time-conversion-lib'
 * '<S118>' : 'adcs_sim_main/Flightsoftware/fsw_lib/mode_selecction/Compare To Constant'
 * '<S119>' : 'adcs_sim_main/Flightsoftware/fsw_lib/mode_selecction/MATLAB Function'
 * '<S120>' : 'adcs_sim_main/Flightsoftware/fsw_lib/target_generation_lib/MATLAB Function'
 * '<S121>' : 'adcs_sim_main/Flightsoftware/fsw_lib/target_generation_lib/MATLAB Function2'
 * '<S122>' : 'adcs_sim_main/Flightsoftware/fsw_lib/telemetry_lib/bus_stub_telemetry'
 * '<S123>' : 'adcs_sim_main/Flightsoftware/fsw_lib/telemetry_lib/quat_degerr_check_lib'
 * '<S124>' : 'adcs_sim_main/Flightsoftware/fsw_lib/telemetry_lib/quat_degerr_check_lib/Quaternion Conjugate'
 * '<S125>' : 'adcs_sim_main/Flightsoftware/fsw_lib/telemetry_lib/quat_degerr_check_lib/Quaternion Multiplication'
 * '<S126>' : 'adcs_sim_main/Flightsoftware/fsw_lib/telemetry_lib/quat_degerr_check_lib/Quaternion Multiplication/q0'
 * '<S127>' : 'adcs_sim_main/Flightsoftware/fsw_lib/telemetry_lib/quat_degerr_check_lib/Quaternion Multiplication/q1'
 * '<S128>' : 'adcs_sim_main/Flightsoftware/fsw_lib/telemetry_lib/quat_degerr_check_lib/Quaternion Multiplication/q2'
 * '<S129>' : 'adcs_sim_main/Flightsoftware/fsw_lib/telemetry_lib/quat_degerr_check_lib/Quaternion Multiplication/q3'
 */
#endif                                 /* RTW_HEADER_fsw_lib_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
