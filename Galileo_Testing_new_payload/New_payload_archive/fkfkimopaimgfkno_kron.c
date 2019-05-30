/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: fkfkimopaimgfkno_kron.c
 *
 * Code generated for Simulink model 'gnc2_lib0'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 17:57:19 2019
 */

#include "rtwtypes.h"
#include "fkfkimopaimgfkno_kron.h"

/* Function for MATLAB Function: '<S1>/SOLVE' */
void fkfkimopaimgfkno_kron(const real_T A[100], const real_T B_1[30], real_T K
  [3000])
{
  int32_T kidx;
  int32_T b_j1;
  int32_T j2;
  int32_T i1;
  kidx = -1;
  for (b_j1 = 0; b_j1 < 10; b_j1++) {
    for (j2 = 0; j2 < 10; j2++) {
      for (i1 = 0; i1 < 10; i1++) {
        kidx++;
        K[kidx] = A[10 * b_j1 + i1] * B_1[3 * j2];
        kidx++;
        K[kidx] = A[10 * b_j1 + i1] * B_1[3 * j2 + 1];
        kidx++;
        K[kidx] = A[10 * b_j1 + i1] * B_1[3 * j2 + 2];
      }
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
