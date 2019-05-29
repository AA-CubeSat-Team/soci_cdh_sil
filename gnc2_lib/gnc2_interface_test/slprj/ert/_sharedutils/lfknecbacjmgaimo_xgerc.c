/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lfknecbacjmgaimo_xgerc.c
 *
 * Code generated for Simulink model 'gnc2_lib0'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 17:57:19 2019
 */

#include "rtwtypes.h"
#include "lfknecbacjmgaimo_xgerc.h"

/* Function for MATLAB Function: '<S1>/INITIALIZE' */
void lfknecbacjmgaimo_xgerc(int32_T m, int32_T n, real_T alpha1, int32_T ix0,
  const real_T y[4], real_T A[16], int32_T ia0)
{
  int32_T jA;
  int32_T jy;
  real_T temp;
  int32_T ix;
  int32_T j;
  int32_T b;
  int32_T ijA;
  if (!(alpha1 == 0.0)) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 1; j <= n; j++) {
      if (y[jy] != 0.0) {
        temp = y[jy] * alpha1;
        ix = ix0;
        b = m + jA;
        for (ijA = jA; ijA + 1 <= b; ijA++) {
          A[ijA] += A[ix - 1] * temp;
          ix++;
        }
      }

      jy++;
      jA += 4;
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
