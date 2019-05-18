/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: iecbbimomgdjjekn_xnrm2.c
 *
 * Code generated for Simulink model 'gnc2_lib'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 14:12:23 2019
 */

#include "rtwtypes.h"
#include <math.h>
#include "iecbbimomgdjjekn_xnrm2.h"

/* Function for MATLAB Function: '<S1>/INITIALIZE' */
real_T iecbbimomgdjjekn_xnrm2(int32_T n, const real_T x[16], int32_T ix0)
{
  real_T y;
  real_T scale;
  int32_T kend;
  real_T absxk;
  real_T t;
  int32_T k;
  y = 0.0;
  if (!(n < 1)) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      scale = 2.2250738585072014E-308;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
