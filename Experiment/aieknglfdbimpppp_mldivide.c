/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: aieknglfdbimpppp_mldivide.c
 *
 * Code generated for Simulink model 'gnc2_lib'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 14:12:23 2019
 */

#include "rtwtypes.h"
#include <string.h>
#include "aiekglfkjmoplfcb_xgetrf.h"
#include "aieknglfdbimpppp_mldivide.h"

/* Function for MATLAB Function: '<S1>/SOLVE' */
void aieknglfdbimpppp_mldivide(const real_T A[100], real_T B_2[30])
{
  real_T temp;
  real_T b_A[100];
  int32_T ipiv[10];
  int32_T info;
  int32_T b_jBcol;
  int32_T b_kAcol;
  int32_T b_k;
  int32_T b_i;
  memcpy(&b_A[0], &A[0], 100U * sizeof(real_T));
  aiekglfkjmoplfcb_xgetrf(b_A, ipiv, &info);
  for (info = 0; info < 9; info++) {
    if (info + 1 != ipiv[info]) {
      b_jBcol = ipiv[info] - 1;
      temp = B_2[info];
      B_2[info] = B_2[b_jBcol];
      B_2[b_jBcol] = temp;
      temp = B_2[info + 10];
      B_2[info + 10] = B_2[b_jBcol + 10];
      B_2[b_jBcol + 10] = temp;
      temp = B_2[info + 20];
      B_2[info + 20] = B_2[b_jBcol + 20];
      B_2[b_jBcol + 20] = temp;
    }
  }

  for (info = 0; info < 3; info++) {
    b_jBcol = 10 * info;
    for (b_k = 0; b_k < 10; b_k++) {
      b_kAcol = 10 * b_k;
      if (B_2[b_k + b_jBcol] != 0.0) {
        for (b_i = b_k + 1; b_i + 1 < 11; b_i++) {
          B_2[b_i + b_jBcol] -= B_2[b_k + b_jBcol] * b_A[b_i + b_kAcol];
        }
      }
    }
  }

  for (info = 0; info < 3; info++) {
    b_jBcol = 10 * info;
    for (b_k = 9; b_k >= 0; b_k += -1) {
      b_kAcol = 10 * b_k;
      if (B_2[b_k + b_jBcol] != 0.0) {
        B_2[b_k + b_jBcol] /= b_A[b_k + b_kAcol];
        for (b_i = 0; b_i + 1 <= b_k; b_i++) {
          B_2[b_i + b_jBcol] -= B_2[b_k + b_jBcol] * b_A[b_i + b_kAcol];
        }
      }
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
