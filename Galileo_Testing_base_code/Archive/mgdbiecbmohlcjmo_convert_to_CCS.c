/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: mgdbiecbmohlcjmo_convert_to_CCS.c
 *
 * Code generated for Simulink model 'gnc2_lib'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 14:12:23 2019
 */

#include "rtwtypes.h"
#include <string.h>
#include "ohlnfkfchlnoaimo_my_find.h"
#include "mgdbiecbmohlcjmo_convert_to_CCS.h"

/*
 * Function for MATLAB Function: '<S1>/SOLVE'
 * function [Xir,Xjc,Xpr] = convert_to_CCS(X,Xir_size)
 */
void mgdbiecbmohlcjmo_convert_to_CCS(const real_T X_2[38844], real_T Xir[1278],
  real_T Xjc[333], real_T Xpr[1278])
{
  int32_T col;
  int32_T k;
  int32_T b_k;

  /* '<S3>:1:314' [Xir,Xpr] = my_find(X,Xir_size); */
  ohlnfkfchlnoaimo_my_find(X_2, Xir, Xpr);

  /* '<S3>:1:315' Xjc = zeros(size(X,2)+1,1); */
  memset(&Xjc[0], 0, 333U * sizeof(real_T));

  /* '<S3>:1:316' for col = 2:size(X,2) */
  for (col = 0; col < 331; col++) {
    /* '<S3>:1:317' Xjc(col) = Xjc(col-1)+nnz(X(:,col-1)); */
    k = 0;
    for (b_k = 0; b_k < 117; b_k++) {
      if (X_2[117 * col + b_k] != 0.0) {
        k++;
      }
    }

    Xjc[col + 1] = Xjc[col] + (real_T)k;
  }

  /* '<S3>:1:319' Xjc(end) = nnz(X); */
  col = 0;
  for (k = 0; k < 38844; k++) {
    if (X_2[k] != 0.0) {
      col++;
    }
  }

  Xjc[332] = col;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
