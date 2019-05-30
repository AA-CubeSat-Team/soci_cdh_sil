/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: baiegdbacjmgjekn_xungorghr.c
 *
 * Code generated for Simulink model 'gnc2_lib0'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 17:57:19 2019
 */

#include "rtwtypes.h"
#include "lfknecbacjmgaimo_xgerc.h"
#include "baiegdbacjmgjekn_xungorghr.h"

/* Function for MATLAB Function: '<S1>/INITIALIZE' */
void baiegdbacjmgjekn_xungorghr(int32_T n, int32_T ilo, int32_T ihi, real_T A[16],
  int32_T ia0, const real_T tau[3], int32_T itau0)
{
  int32_T nh;
  int32_T ia;
  int32_T f_i;
  int32_T itau;
  real_T work[4];
  int32_T iaii;
  int32_T lastv;
  int32_T lastc;
  int32_T coltop;
  int32_T c_ia;
  int32_T ix;
  real_T b_c;
  int32_T iac;
  int32_T d;
  int32_T d_ia;
  int32_T exitg1;
  boolean_T exitg2;
  if (n != 0) {
    nh = ihi - ilo;
    for (itau = ihi; itau >= ilo + 1; itau--) {
      ia = (((itau - 1) << 2) + ia0) - 2;
      for (f_i = 1; f_i < itau; f_i++) {
        A[ia + f_i] = 0.0;
      }

      for (f_i = itau + 1; f_i <= ihi; f_i++) {
        A[ia + f_i] = A[(ia + f_i) - 4];
      }

      for (f_i = ihi + 1; f_i <= n; f_i++) {
        A[ia + f_i] = 0.0;
      }
    }

    for (itau = 0; itau + 1 <= ilo; itau++) {
      ia = ((itau << 2) + ia0) - 1;
      for (f_i = 1; f_i <= n; f_i++) {
        A[(ia + f_i) - 1] = 0.0;
      }

      A[ia + itau] = 1.0;
    }

    for (itau = ihi; itau + 1 <= n; itau++) {
      ia = ((itau << 2) + ia0) - 1;
      for (f_i = 1; f_i <= n; f_i++) {
        A[(ia + f_i) - 1] = 0.0;
      }

      A[ia + itau] = 1.0;
    }

    ia = (ia0 + ilo) + (ilo << 2);
    if (!(nh < 1)) {
      for (itau = nh; itau < nh; itau++) {
        f_i = (itau << 2) + ia;
        for (iaii = 0; iaii < nh; iaii++) {
          A[(f_i + iaii) - 1] = 0.0;
        }

        A[(f_i + itau) - 1] = 1.0;
      }

      itau = ((itau0 + ilo) + nh) - 3;
      work[0] = 0.0;
      work[1] = 0.0;
      work[2] = 0.0;
      work[3] = 0.0;
      for (f_i = nh; f_i >= 1; f_i--) {
        iaii = ((((f_i - 1) << 2) + ia) + f_i) - 1;
        if (f_i < nh) {
          A[iaii - 1] = 1.0;
          lastv = (nh - f_i) + 1;
          if (tau[itau] != 0.0) {
            lastc = iaii + lastv;
            while ((lastv > 0) && (A[lastc - 2] == 0.0)) {
              lastv--;
              lastc--;
            }

            lastc = nh - f_i;
            exitg2 = false;
            while ((!exitg2) && (lastc > 0)) {
              coltop = (((lastc - 1) << 2) + iaii) + 4;
              c_ia = coltop;
              do {
                exitg1 = 0;
                if (c_ia <= (coltop + lastv) - 1) {
                  if (A[c_ia - 1] != 0.0) {
                    exitg1 = 1;
                  } else {
                    c_ia++;
                  }
                } else {
                  lastc--;
                  exitg1 = 2;
                }
              } while (exitg1 == 0);

              if (exitg1 == 1) {
                exitg2 = true;
              }
            }
          } else {
            lastv = 0;
            lastc = 0;
          }

          if (lastv > 0) {
            if (lastc != 0) {
              for (coltop = 1; coltop <= lastc; coltop++) {
                work[coltop - 1] = 0.0;
              }

              coltop = 0;
              c_ia = (((lastc - 1) << 2) + iaii) + 4;
              for (iac = iaii + 4; iac <= c_ia; iac += 4) {
                ix = iaii;
                b_c = 0.0;
                d = (iac + lastv) - 1;
                for (d_ia = iac; d_ia <= d; d_ia++) {
                  b_c += A[d_ia - 1] * A[ix - 1];
                  ix++;
                }

                work[coltop] += b_c;
                coltop++;
              }
            }

            lfknecbacjmgaimo_xgerc(lastv, lastc, -tau[itau], iaii, work, A, iaii
              + 4);
          }

          lastv = (iaii + nh) - f_i;
          for (lastc = iaii; lastc + 1 <= lastv; lastc++) {
            A[lastc] *= -tau[itau];
          }
        }

        A[iaii - 1] = 1.0 - tau[itau];
        for (lastv = 1; lastv < f_i; lastv++) {
          A[(iaii - lastv) - 1] = 0.0;
        }

        itau--;
      }
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
