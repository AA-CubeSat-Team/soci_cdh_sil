/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: fsw_lib_data.c
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

#include "fsw_lib.h"

/* Invariant block signals (auto storage) */
const ConstB rtConstB = {
  { 1.0000000033333333E-14, 0.0, 0.0, 5.0000000000000014E-22, 0.0, 0.0, 0.0,
    1.0000000033333333E-14, 0.0, 0.0, 5.0000000000000014E-22, 0.0, 0.0, 0.0,
    1.0000000033333333E-14, 0.0, 0.0, 5.0000000000000014E-22,
    5.0000000000000014E-22, 0.0, 0.0, 1.0000000000000001E-20, 0.0, 0.0, 0.0,
    5.0000000000000014E-22, 0.0, 0.0, 1.0000000000000001E-20, 0.0, 0.0, 0.0,
    5.0000000000000014E-22, 0.0, 0.0, 1.0000000000000001E-20 }/* '<S11>/Product1' */
};

/* Constant parameters (auto storage) */
const ConstP rtConstP = {
  /* Expression: fsw_params.control.sun_point.prop_gain
   * Referenced by: '<S37>/prop_gain'
   */
  { 0.00013343733574733489, -1.9279601064428787E-7, -2.9186267803965119E-7,
    -1.9279601064428787E-7, 0.00013646871758634115, 2.8124503658179443E-8,
    -2.9186267803965119E-7, 2.8124503658179443E-8, 2.9296007382602984E-5 },

  /* Expression: fsw_params.control.sun_point.drv_gain
   * Referenced by: '<S37>/drv_gain'
   */
  { 0.0042474423154402431, -6.1368876204872168E-6, -9.2902775828097711E-6,
    -6.1368876204872168E-6, 0.0043439341962556123, 8.9523075584107035E-7,
    -9.2902775828097711E-6, 8.9523075584107035E-7, 0.00093252087755958473 },

  /* Expression: fsw_params.estimation.ic.error_cov
   * Referenced by: '<S9>/Unit Delay2'
   */
  { 3.0462E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 3.0462E-6, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 3.0462E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 9.4018E-13, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 9.4018E-13, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 9.4018E-13 },

  /* Expression: fsw_params.estimation.meas_cov
   * Referenced by: '<S9>/Constant1'
   */
  { 2.3108643209372979E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.3108643209372979E-7,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.3108643209372979E-7, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.05, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.05, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.05 },

  /* Expression: fsw_params.control.pd_controller.p_gain
   * Referenced by: '<S34>/Constant'
   */
  { 0.00053374934298933954, -7.7118404257715147E-7, -1.1674507121586048E-6,
    -7.7118404257715147E-7, 0.00054587487034536458, 1.1249801463271777E-7,
    -1.1674507121586048E-6, 1.1249801463271777E-7, 0.00011718402953041194 },

  /* Expression: fsw_params.control.pd_controller.d_gain
   * Referenced by: '<S34>/Constant1'
   */
  { 0.0084948846308804862, -1.2273775240974434E-5, -1.8580555165619542E-5,
    -1.2273775240974434E-5, 0.0086878683925112245, 1.7904615116821407E-6,
    -1.8580555165619542E-5, 1.7904615116821407E-6, 0.0018650417551191695 },

  /* Pooled Parameter (Expression: fsw_params.actuators.reaction_wheel.inertia_matrix)
   * Referenced by:
   *   '<S33>/RW_inertia'
   *   '<S40>/wheel_inertia'
   *   '<S53>/Constant'
   */
  { 1.788E-6, 0.0, 0.0, 0.0, 1.788E-6, 0.0, 0.0, 0.0, 1.788E-6 },

  /* Expression: fsw_params.control.bdot.gain_matrix
   * Referenced by: '<S35>/gain matrix'
   */
  { -133333.33333333334, 0.0, 0.0, 0.0, -133333.33333333334, 0.0, 0.0, 0.0,
    -117647.05882352941 },

  /* Expression: fsw_params.sensor_processing.magnetometer.process_matrix
   * Referenced by: '<S50>/Constant1'
   */
  { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
