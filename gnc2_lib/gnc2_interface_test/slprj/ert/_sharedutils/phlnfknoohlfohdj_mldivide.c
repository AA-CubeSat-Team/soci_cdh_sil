/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: phlnfknoohlfohdj_mldivide.c
 *
 * Code generated for Simulink model 'gnc2_lib0'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 17:57:19 2019
 */

#include "rtwtypes.h"
#include <string.h>
#include "aiekglfkjmoplfcb_xgetrf.h"
#include "phlnfknoohlfohdj_mldivide.h"

/* Function for MATLAB Function: '<S1>/SOLVE' */
void phlnfknoohlfohdj_mldivide(const real_T A[100], real_T B_3[10])
{
  real_T temp;
  real_T b_A[100];
  int32_T ipiv[10];
  int32_T info;
  int32_T b_kAcol;
  int32_T b_i;
  memcpy(&b_A[0], &A[0], 100U * sizeof(real_T));
  aiekglfkjmoplfcb_xgetrf(b_A, ipiv, &info);
  for (info = 0; info < 9; info++) {
    if (info + 1 != ipiv[info]) {
      temp = B_3[info];
      B_3[info] = B_3[ipiv[info] - 1];
      B_3[ipiv[info] - 1] = temp;
    }
  }

  for (info = 0; info < 10; info++) {
    b_kAcol = 10 * info;
    if (B_3[info] != 0.0) {
      for (b_i = info + 1; b_i + 1 < 11; b_i++) {
        B_3[b_i] -= b_A[b_i + b_kAcol] * B_3[info];
      }
    }
  }

  for (info = 9; info >= 0; info += -1) {
    b_kAcol = 10 * info;
    if (B_3[info] != 0.0) {
      B_3[info] /= b_A[info + b_kAcol];
      for (b_i = 0; b_i + 1 <= info; b_i++) {
        B_3[b_i] -= b_A[b_i + b_kAcol] * B_3[info];
      }
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
