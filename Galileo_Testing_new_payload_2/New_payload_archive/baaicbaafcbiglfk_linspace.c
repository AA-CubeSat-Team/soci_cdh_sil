/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: baaicbaafcbiglfk_linspace.c
 *
 * Code generated for Simulink model 'gnc2_lib0'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 17:57:19 2019
 */

#include "rtwtypes.h"
#include <math.h>
#include "baaicbaafcbiglfk_linspace.h"

/* Function for MATLAB Function: '<S1>/SOLVE' */
void baaicbaafcbiglfk_linspace(real_T d1, real_T d2, real_T y[10])
{
  real_T delta1;
  real_T delta2;
  int32_T b_k;
  y[9] = d2;
  y[0] = d1;
  if (((d1 < 0.0) != (d2 < 0.0)) && ((fabs(d1) > 8.9884656743115785E+307) ||
       (fabs(d2) > 8.9884656743115785E+307))) {
    delta1 = d1 / 9.0;
    delta2 = d2 / 9.0;
    for (b_k = 0; b_k < 8; b_k++) {
      y[1 + b_k] = ((1.0 + (real_T)b_k) * delta2 + d1) - (1.0 + (real_T)b_k) *
        delta1;
    }
  } else {
    delta1 = (d2 - d1) / 9.0;
    for (b_k = 0; b_k < 8; b_k++) {
      y[1 + b_k] = (1.0 + (real_T)b_k) * delta1 + d1;
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
