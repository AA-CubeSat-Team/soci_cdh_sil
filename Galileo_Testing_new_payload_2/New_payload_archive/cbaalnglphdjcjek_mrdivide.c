/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: cbaalnglphdjcjek_mrdivide.c
 *
 * Code generated for Simulink model 'gnc2_lib0'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 17:57:19 2019
 */

#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include "cbaalnglphdjcjek_mrdivide.h"

/* Function for MATLAB Function: '<S1>/SOLVE' */
void cbaalnglphdjcjek_mrdivide(const real_T A[9], const real_T B_0[9], real_T y
  [9])
{
  real_T b_A[9];
  int32_T r1;
  int32_T r2;
  int32_T r3;
  real_T maxval;
  real_T a21;
  int32_T rtemp;
  memcpy(&b_A[0], &B_0[0], 9U * sizeof(real_T));
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = fabs(B_0[0]);
  a21 = fabs(B_0[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if (fabs(B_0[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  b_A[r2] = B_0[r2] / B_0[r1];
  b_A[r3] /= b_A[r1];
  b_A[3 + r2] -= b_A[3 + r1] * b_A[r2];
  b_A[3 + r3] -= b_A[3 + r1] * b_A[r3];
  b_A[6 + r2] -= b_A[6 + r1] * b_A[r2];
  b_A[6 + r3] -= b_A[6 + r1] * b_A[r3];
  if (fabs(b_A[3 + r3]) > fabs(b_A[3 + r2])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  b_A[3 + r3] /= b_A[3 + r2];
  b_A[6 + r3] -= b_A[3 + r3] * b_A[6 + r2];
  y[3 * r1] = A[0] / b_A[r1];
  y[3 * r2] = A[3] - y[3 * r1] * b_A[3 + r1];
  y[3 * r3] = A[6] - y[3 * r1] * b_A[6 + r1];
  y[3 * r2] /= b_A[3 + r2];
  y[3 * r3] -= y[3 * r2] * b_A[6 + r2];
  y[3 * r3] /= b_A[6 + r3];
  y[3 * r2] -= y[3 * r3] * b_A[3 + r3];
  y[3 * r1] -= y[3 * r3] * b_A[r3];
  y[3 * r1] -= y[3 * r2] * b_A[r2];
  y[1 + 3 * r1] = A[1] / b_A[r1];
  y[1 + 3 * r2] = A[4] - y[3 * r1 + 1] * b_A[3 + r1];
  y[1 + 3 * r3] = A[7] - y[3 * r1 + 1] * b_A[6 + r1];
  y[1 + 3 * r2] /= b_A[3 + r2];
  y[1 + 3 * r3] -= y[3 * r2 + 1] * b_A[6 + r2];
  y[1 + 3 * r3] /= b_A[6 + r3];
  y[1 + 3 * r2] -= y[3 * r3 + 1] * b_A[3 + r3];
  y[1 + 3 * r1] -= y[3 * r3 + 1] * b_A[r3];
  y[1 + 3 * r1] -= y[3 * r2 + 1] * b_A[r2];
  y[2 + 3 * r1] = A[2] / b_A[r1];
  y[2 + 3 * r2] = A[5] - y[3 * r1 + 2] * b_A[3 + r1];
  y[2 + 3 * r3] = A[8] - y[3 * r1 + 2] * b_A[6 + r1];
  y[2 + 3 * r2] /= b_A[3 + r2];
  y[2 + 3 * r3] -= y[3 * r2 + 2] * b_A[6 + r2];
  y[2 + 3 * r3] /= b_A[6 + r3];
  y[2 + 3 * r2] -= y[3 * r3 + 2] * b_A[3 + r3];
  y[2 + 3 * r1] -= y[3 * r3 + 2] * b_A[r3];
  y[2 + 3 * r1] -= y[3 * r2 + 2] * b_A[r2];
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
