/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: cjmgngdjaiecmgln_my_find.c
 *
 * Code generated for Simulink model 'gnc2_lib'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 14:12:23 2019
 */

#include "rtwtypes.h"
#include <string.h>
#include "cjmgngdjaiecmgln_my_find.h"

/*
 * Function for MATLAB Function: '<S1>/SOLVE'
 * function [Xir,Xpr] = my_find(X,Xir_size)
 */
void cjmgngdjaiecmgln_my_find(const real_T X_5[117528], real_T Xir[674], real_T
  Xpr[674])
{
  uint32_T id;
  int32_T row;
  int32_T n;
  int32_T k;

  /* '<S3>:1:324' [n,m] = size(X); */
  /* '<S3>:1:325' Xir   = zeros(Xir_size,1); */
  /* '<S3>:1:326' Xpr   = zeros(Xir_size,1); */
  memset(&Xir[0], 0, 674U * sizeof(real_T));
  memset(&Xpr[0], 0, 674U * sizeof(real_T));

  /* '<S3>:1:327' X_nnz = nnz(X); */
  n = 0;
  for (k = 0; k < 117528; k++) {
    if (X_5[k] != 0.0) {
      n++;
    }
  }

  /* '<S3>:1:328' id = 1; */
  id = 1U;

  /* '<S3>:1:329' for col = 1:m */
  for (k = 0; k < 332; k++) {
    /* '<S3>:1:330' for row = 1:n */
    for (row = 0; row < 354; row++) {
      /* '<S3>:1:331' if ((X(row,col)~=0) && (id<X_nnz+1)) */
      if ((X_5[354 * k + row] != 0.0) && (id < (real_T)n + 1.0)) {
        /* '<S3>:1:332' Xir(id) = row-1; */
        Xir[(int32_T)id - 1] = (1.0 + (real_T)row) - 1.0;

        /*  zero based row indexing */
        /* '<S3>:1:333' Xpr(id) = X(row,col); */
        Xpr[(int32_T)id - 1] = X_5[354 * k + row];

        /* '<S3>:1:334' id = id + 1; */
        id++;
      }
    }
  }

  /*  function [ Mir,Mjc,Mpr ] = convert_to_CCS( M ) */
  /*  %#codegen */
  /*  [Mir,~,Mpr] = find(M); */
  /*  Mir = Mir - 1; % CCS uses zero-based row indexing */
  /*  Mjc = zeros(size(M,2)+1,1); */
  /*  for col = 2:size(M,2) */
  /*      Mjc(col) = Mjc(col-1)+nnz(M(:,col-1)); */
  /*  end */
  /*  Mjc(end) = length(find(M~=0)); */
  /*   */
  /*  end */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
