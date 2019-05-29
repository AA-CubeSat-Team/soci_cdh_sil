/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ohdbngdjimopdbim_mldivide.c
 *
 * Code generated for Simulink model 'gnc2_interface_lib0'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May 24 16:44:58 2019
 */

#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include "ohdbngdjimopdbim_mldivide.h"

/* Function for MATLAB Function: '<S1>/INTERP' */
void ohdbngdjimopdbim_mldivide(const real_T A[9], const real_T B_0[3], real_T Y
  [3])
{
  real_T b_A[9];
  int32_T r1;
  int32_T r2;
  int32_T r3;
  real_T maxval;
  real_T a21;
  int32_T rtemp;
  memcpy(&b_A[0], &A[0], 9U * sizeof(real_T));
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = fabs(A[0]);
  a21 = fabs(A[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if (fabs(A[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  b_A[r2] = A[r2] / A[r1];
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
  Y[1] = B_0[r2] - B_0[r1] * b_A[r2];
  Y[2] = (B_0[r3] - B_0[r1] * b_A[r3]) - b_A[3 + r3] * Y[1];
  Y[2] /= b_A[6 + r3];
  Y[0] = B_0[r1] - b_A[6 + r1] * Y[2];
  Y[1] -= b_A[6 + r2] * Y[2];
  Y[1] /= b_A[3 + r2];
  Y[0] -= b_A[3 + r1] * Y[1];
  Y[0] /= b_A[r1];
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
