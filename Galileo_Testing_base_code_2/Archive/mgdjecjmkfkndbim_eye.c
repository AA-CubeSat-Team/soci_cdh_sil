/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: mgdjecjmkfkndbim_eye.c
 *
 * Code generated for Simulink model 'gnc2_lib'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 14:12:23 2019
 */

#include "rtwtypes.h"
#include <string.h>
#include "mgdjecjmkfkndbim_eye.h"

/* Function for MATLAB Function: '<S1>/SOLVE' */
void mgdjecjmkfkndbim_eye(real_T I[900])
{
  int32_T k;
  memset(&I[0], 0, 900U * sizeof(real_T));
  for (k = 0; k < 30; k++) {
    I[k + 30 * k] = 1.0;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
