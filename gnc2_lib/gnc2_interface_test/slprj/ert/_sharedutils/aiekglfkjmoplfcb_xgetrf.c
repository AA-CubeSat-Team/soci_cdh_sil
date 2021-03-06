/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: aiekglfkjmoplfcb_xgetrf.c
 *
 * Code generated for Simulink model 'gnc2_lib0'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 17:57:19 2019
 */

#include "rtwtypes.h"
#include <math.h>
#include "aiekglfkjmoplfcb_xgetrf.h"

/* Function for MATLAB Function: '<S1>/SOLVE' */
void aiekglfkjmoplfcb_xgetrf(real_T A[100], int32_T ipiv[10], int32_T *info)
{
  int32_T j;
  int32_T c;
  int32_T ix;
  real_T smax;
  real_T s;
  int32_T k;
  int32_T iy;
  int32_T c_ix;
  int32_T d;
  int32_T ijA;
  for (j = 0; j < 10; j++) {
    ipiv[j] = 1 + j;
  }

  *info = 0;
  for (j = 0; j < 9; j++) {
    c = j * 11;
    iy = 0;
    ix = c;
    smax = fabs(A[c]);
    for (k = 2; k <= 10 - j; k++) {
      ix++;
      s = fabs(A[ix]);
      if (s > smax) {
        iy = k - 1;
        smax = s;
      }
    }

    if (A[c + iy] != 0.0) {
      if (iy != 0) {
        ipiv[j] = (j + iy) + 1;
        ix = j;
        iy += j;
        for (k = 0; k < 10; k++) {
          smax = A[ix];
          A[ix] = A[iy];
          A[iy] = smax;
          ix += 10;
          iy += 10;
        }
      }

      iy = (c - j) + 10;
      for (ix = c + 1; ix + 1 <= iy; ix++) {
        A[ix] /= A[c];
      }
    } else {
      *info = j + 1;
    }

    iy = c;
    ix = c + 10;
    for (k = 1; k <= 9 - j; k++) {
      smax = A[ix];
      if (A[ix] != 0.0) {
        c_ix = c + 1;
        d = (iy - j) + 20;
        for (ijA = 11 + iy; ijA + 1 <= d; ijA++) {
          A[ijA] += A[c_ix] * -smax;
          c_ix++;
        }
      }

      ix += 10;
      iy += 10;
    }
  }

  if ((*info == 0) && (!(A[99] != 0.0))) {
    *info = 10;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
