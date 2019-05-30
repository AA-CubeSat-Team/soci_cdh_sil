/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: nglnimohlfkfphln_norm.c
 *
 * Code generated for Simulink model 'gnc2_lib0'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 17:57:19 2019
 */

#include "rtwtypes.h"
#include <math.h>
#include "nglnimohlfkfphln_norm.h"

/* Function for MATLAB Function: '<S1>/SOLVE' */
real_T nglnimohlfkfphln_norm(const real_T x[100])
{
  real_T y;
  int32_T k;
  y = 0.0;
  for (k = 0; k < 100; k++) {
    y += fabs(x[k]);
  }

  return y;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
