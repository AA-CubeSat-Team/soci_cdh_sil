/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: hdbaecbadjekpphd_xgehrd.c
 *
 * Code generated for Simulink model 'gnc2_lib0'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 17:57:19 2019
 */

#include "rtwtypes.h"
#include <math.h>
#include "iecbbimomgdjjekn_xnrm2.h"
#include "lfknecbacjmgaimo_xgerc.h"
#include "rt_hypotd_snf.h"
#include "hdbaecbadjekpphd_xgehrd.h"

/* Function for MATLAB Function: '<S1>/INITIALIZE' */
void hdbaecbadjekpphd_xgehrd(real_T a[16], real_T tau[3])
{
  real_T work[4];
  int32_T ia0;
  real_T alpha1;
  real_T xnorm;
  int32_T knt;
  int32_T rowleft;
  int32_T ia;
  int32_T iy;
  int32_T g;
  int32_T b_ia;
  int32_T jy;
  real_T temp;
  int32_T b_ix;
  int32_T exitg1;
  boolean_T exitg2;
  int32_T exitg3;
  boolean_T exitg4;
  int32_T exitg5;
  boolean_T exitg6;
  int32_T exitg7;
  boolean_T exitg8;
  int32_T exitg9;
  boolean_T exitg10;
  int32_T exitg11;
  boolean_T exitg12;
  work[0] = 0.0;
  work[1] = 0.0;
  work[2] = 0.0;
  work[3] = 0.0;
  ia0 = 3;
  alpha1 = a[1];
  temp = 0.0;
  xnorm = iecbbimomgdjjekn_xnrm2(2, a, 3);
  if (xnorm != 0.0) {
    xnorm = rt_hypotd_snf(a[1], xnorm);
    if (a[1] >= 0.0) {
      xnorm = -xnorm;
    }

    if (fabs(xnorm) < 1.0020841800044864E-292) {
      knt = 0;
      do {
        knt++;
        for (rowleft = 3; rowleft < 5; rowleft++) {
          a[rowleft - 1] *= 9.9792015476736E+291;
        }

        xnorm *= 9.9792015476736E+291;
        alpha1 *= 9.9792015476736E+291;
      } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

      xnorm = rt_hypotd_snf(alpha1, iecbbimomgdjjekn_xnrm2(2, a, 3));
      if (alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      temp = (xnorm - alpha1) / xnorm;
      alpha1 = 1.0 / (alpha1 - xnorm);
      while (ia0 <= 4) {
        a[ia0 - 1] *= alpha1;
        ia0++;
      }

      for (ia0 = 1; ia0 <= knt; ia0++) {
        xnorm *= 1.0020841800044864E-292;
      }

      alpha1 = xnorm;
    } else {
      temp = (xnorm - a[1]) / xnorm;
      alpha1 = 1.0 / (a[1] - xnorm);
      while (ia0 <= 4) {
        a[ia0 - 1] *= alpha1;
        ia0++;
      }

      alpha1 = xnorm;
    }
  }

  tau[0] = temp;
  a[1] = 1.0;
  jy = 1;
  if (temp != 0.0) {
    knt = 3;
    ia0 = 3;
    while ((knt > 0) && (a[ia0] == 0.0)) {
      knt--;
      ia0--;
    }

    ia0 = 4;
    exitg12 = false;
    while ((!exitg12) && (ia0 > 0)) {
      rowleft = 4 + ia0;
      ia = rowleft;
      do {
        exitg11 = 0;
        if (ia <= ((knt - 1) << 2) + rowleft) {
          if (a[ia - 1] != 0.0) {
            exitg11 = 1;
          } else {
            ia += 4;
          }
        } else {
          ia0--;
          exitg11 = 2;
        }
      } while (exitg11 == 0);

      if (exitg11 == 1) {
        exitg12 = true;
      }
    }
  } else {
    knt = 0;
    ia0 = 0;
  }

  if (knt > 0) {
    if (ia0 != 0) {
      for (rowleft = 1; rowleft <= ia0; rowleft++) {
        work[rowleft - 1] = 0.0;
      }

      rowleft = 1;
      ia = ((knt - 1) << 2) + 5;
      for (b_ix = 5; b_ix <= ia; b_ix += 4) {
        iy = 0;
        g = (b_ix + ia0) - 1;
        for (b_ia = b_ix; b_ia <= g; b_ia++) {
          work[iy] += a[b_ia - 1] * a[rowleft];
          iy++;
        }

        rowleft++;
      }
    }

    if (!(-temp == 0.0)) {
      rowleft = 4;
      for (ia = 1; ia <= knt; ia++) {
        if (a[jy] != 0.0) {
          temp = a[jy] * -tau[0];
          b_ix = 0;
          iy = ia0 + rowleft;
          for (g = rowleft; g + 1 <= iy; g++) {
            a[g] += work[b_ix] * temp;
            b_ix++;
          }
        }

        jy++;
        rowleft += 4;
      }
    }
  }

  if (tau[0] != 0.0) {
    knt = 3;
    ia0 = 3;
    while ((knt > 0) && (a[ia0] == 0.0)) {
      knt--;
      ia0--;
    }

    ia0 = 3;
    exitg10 = false;
    while ((!exitg10) && (ia0 > 0)) {
      jy = ((ia0 - 1) << 2) + 6;
      rowleft = jy;
      do {
        exitg9 = 0;
        if (rowleft <= (jy + knt) - 1) {
          if (a[rowleft - 1] != 0.0) {
            exitg9 = 1;
          } else {
            rowleft++;
          }
        } else {
          ia0--;
          exitg9 = 2;
        }
      } while (exitg9 == 0);

      if (exitg9 == 1) {
        exitg10 = true;
      }
    }
  } else {
    knt = 0;
    ia0 = 0;
  }

  if (knt > 0) {
    if (ia0 != 0) {
      for (jy = 1; jy <= ia0; jy++) {
        work[jy - 1] = 0.0;
      }

      jy = 0;
      rowleft = ((ia0 - 1) << 2) + 6;
      for (ia = 6; ia <= rowleft; ia += 4) {
        b_ix = 2;
        temp = 0.0;
        iy = (ia + knt) - 1;
        for (g = ia; g <= iy; g++) {
          temp += a[g - 1] * a[b_ix - 1];
          b_ix++;
        }

        work[jy] += temp;
        jy++;
      }
    }

    lfknecbacjmgaimo_xgerc(knt, ia0, -tau[0], 2, work, a, 6);
  }

  a[1] = alpha1;
  ia0 = 8;
  alpha1 = a[6];
  temp = 0.0;
  xnorm = iecbbimomgdjjekn_xnrm2(1, a, 8);
  if (xnorm != 0.0) {
    xnorm = rt_hypotd_snf(a[6], xnorm);
    if (a[6] >= 0.0) {
      xnorm = -xnorm;
    }

    if (fabs(xnorm) < 1.0020841800044864E-292) {
      knt = 0;
      do {
        knt++;
        rowleft = 8;
        while (rowleft <= 8) {
          a[7] *= 9.9792015476736E+291;
          rowleft = 9;
        }

        xnorm *= 9.9792015476736E+291;
        alpha1 *= 9.9792015476736E+291;
      } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

      xnorm = rt_hypotd_snf(alpha1, iecbbimomgdjjekn_xnrm2(1, a, 8));
      if (alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      temp = (xnorm - alpha1) / xnorm;
      alpha1 = 1.0 / (alpha1 - xnorm);
      while (ia0 <= 8) {
        a[7] *= alpha1;
        ia0 = 9;
      }

      for (ia0 = 1; ia0 <= knt; ia0++) {
        xnorm *= 1.0020841800044864E-292;
      }

      alpha1 = xnorm;
    } else {
      temp = (xnorm - a[6]) / xnorm;
      alpha1 = 1.0 / (a[6] - xnorm);
      while (ia0 <= 8) {
        a[7] *= alpha1;
        ia0 = 9;
      }

      alpha1 = xnorm;
    }
  }

  tau[1] = temp;
  a[6] = 1.0;
  jy = 6;
  if (temp != 0.0) {
    knt = 2;
    ia0 = 7;
    while ((knt > 0) && (a[ia0] == 0.0)) {
      knt--;
      ia0--;
    }

    ia0 = 4;
    exitg8 = false;
    while ((!exitg8) && (ia0 > 0)) {
      rowleft = 8 + ia0;
      ia = rowleft;
      do {
        exitg7 = 0;
        if (ia <= ((knt - 1) << 2) + rowleft) {
          if (a[ia - 1] != 0.0) {
            exitg7 = 1;
          } else {
            ia += 4;
          }
        } else {
          ia0--;
          exitg7 = 2;
        }
      } while (exitg7 == 0);

      if (exitg7 == 1) {
        exitg8 = true;
      }
    }
  } else {
    knt = 0;
    ia0 = 0;
  }

  if (knt > 0) {
    if (ia0 != 0) {
      for (rowleft = 1; rowleft <= ia0; rowleft++) {
        work[rowleft - 1] = 0.0;
      }

      rowleft = 6;
      ia = ((knt - 1) << 2) + 9;
      for (b_ix = 9; b_ix <= ia; b_ix += 4) {
        iy = 0;
        g = (b_ix + ia0) - 1;
        for (b_ia = b_ix; b_ia <= g; b_ia++) {
          work[iy] += a[b_ia - 1] * a[rowleft];
          iy++;
        }

        rowleft++;
      }
    }

    if (!(-temp == 0.0)) {
      rowleft = 8;
      for (ia = 1; ia <= knt; ia++) {
        if (a[jy] != 0.0) {
          temp = a[jy] * -tau[1];
          b_ix = 0;
          iy = ia0 + rowleft;
          for (g = rowleft; g + 1 <= iy; g++) {
            a[g] += work[b_ix] * temp;
            b_ix++;
          }
        }

        jy++;
        rowleft += 4;
      }
    }
  }

  if (tau[1] != 0.0) {
    knt = 2;
    ia0 = 7;
    while ((knt > 0) && (a[ia0] == 0.0)) {
      knt--;
      ia0--;
    }

    ia0 = 2;
    exitg6 = false;
    while ((!exitg6) && (ia0 > 0)) {
      jy = ((ia0 - 1) << 2) + 11;
      rowleft = jy;
      do {
        exitg5 = 0;
        if (rowleft <= (jy + knt) - 1) {
          if (a[rowleft - 1] != 0.0) {
            exitg5 = 1;
          } else {
            rowleft++;
          }
        } else {
          ia0--;
          exitg5 = 2;
        }
      } while (exitg5 == 0);

      if (exitg5 == 1) {
        exitg6 = true;
      }
    }
  } else {
    knt = 0;
    ia0 = 0;
  }

  if (knt > 0) {
    if (ia0 != 0) {
      for (jy = 1; jy <= ia0; jy++) {
        work[jy - 1] = 0.0;
      }

      jy = 0;
      rowleft = ((ia0 - 1) << 2) + 11;
      for (ia = 11; ia <= rowleft; ia += 4) {
        b_ix = 7;
        temp = 0.0;
        iy = (ia + knt) - 1;
        for (g = ia; g <= iy; g++) {
          temp += a[g - 1] * a[b_ix - 1];
          b_ix++;
        }

        work[jy] += temp;
        jy++;
      }
    }

    lfknecbacjmgaimo_xgerc(knt, ia0, -tau[1], 7, work, a, 11);
  }

  a[6] = alpha1;
  alpha1 = a[11];
  temp = 0.0;
  xnorm = iecbbimomgdjjekn_xnrm2(0, a, 12);
  if (xnorm != 0.0) {
    xnorm = rt_hypotd_snf(a[11], xnorm);
    if (a[11] >= 0.0) {
      xnorm = -xnorm;
    }

    if (fabs(xnorm) < 1.0020841800044864E-292) {
      knt = 0;
      do {
        knt++;
        xnorm *= 9.9792015476736E+291;
        alpha1 *= 9.9792015476736E+291;
      } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

      xnorm = rt_hypotd_snf(alpha1, iecbbimomgdjjekn_xnrm2(0, a, 12));
      if (alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      temp = (xnorm - alpha1) / xnorm;
      for (ia0 = 1; ia0 <= knt; ia0++) {
        xnorm *= 1.0020841800044864E-292;
      }

      alpha1 = xnorm;
    } else {
      temp = (xnorm - a[11]) / xnorm;
      alpha1 = xnorm;
    }
  }

  tau[2] = temp;
  a[11] = 1.0;
  jy = 11;
  if (temp != 0.0) {
    knt = 1;
    ia0 = 11;
    while ((knt > 0) && (a[ia0] == 0.0)) {
      knt = 0;
      ia0--;
    }

    ia0 = 4;
    exitg4 = false;
    while ((!exitg4) && (ia0 > 0)) {
      rowleft = 12 + ia0;
      ia = rowleft;
      do {
        exitg3 = 0;
        if (ia <= ((knt - 1) << 2) + rowleft) {
          if (a[ia - 1] != 0.0) {
            exitg3 = 1;
          } else {
            ia += 4;
          }
        } else {
          ia0--;
          exitg3 = 2;
        }
      } while (exitg3 == 0);

      if (exitg3 == 1) {
        exitg4 = true;
      }
    }
  } else {
    knt = 0;
    ia0 = 0;
  }

  if (knt > 0) {
    if (ia0 != 0) {
      for (rowleft = 1; rowleft <= ia0; rowleft++) {
        work[rowleft - 1] = 0.0;
      }

      rowleft = 11;
      b_ix = 13;
      while (b_ix <= 13) {
        iy = 0;
        g = ia0 + 12;
        for (b_ia = 13; b_ia <= g; b_ia++) {
          work[iy] += a[b_ia - 1] * a[rowleft];
          iy++;
        }

        rowleft++;
        b_ix = 17;
      }
    }

    if (!(-temp == 0.0)) {
      rowleft = 12;
      ia = 1;
      while (ia <= 1) {
        if (a[jy] != 0.0) {
          temp = a[jy] * -tau[2];
          b_ix = 0;
          iy = ia0 + rowleft;
          for (g = rowleft; g + 1 <= iy; g++) {
            a[g] += work[b_ix] * temp;
            b_ix++;
          }
        }

        jy++;
        rowleft += 4;
        ia = 2;
      }
    }
  }

  if (tau[2] != 0.0) {
    knt = 1;
    ia0 = 11;
    while ((knt > 0) && (a[ia0] == 0.0)) {
      knt = 0;
      ia0--;
    }

    ia0 = 1;
    exitg2 = false;
    while ((!exitg2) && (ia0 > 0)) {
      rowleft = 16;
      do {
        exitg1 = 0;
        if (rowleft <= knt + 15) {
          if (a[15] != 0.0) {
            exitg1 = 1;
          } else {
            rowleft = 17;
          }
        } else {
          ia0 = 0;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    knt = 0;
    ia0 = 0;
  }

  if (knt > 0) {
    if (ia0 != 0) {
      jy = 1;
      while (jy <= 1) {
        work[0] = 0.0;
        jy = 2;
      }

      jy = 0;
      ia = 16;
      while (ia <= 16) {
        b_ix = 12;
        temp = 0.0;
        g = 16;
        while (g <= 16) {
          temp += a[b_ix - 1] * a[15];
          b_ix++;
          g = 17;
        }

        work[jy] += temp;
        jy++;
        ia = 20;
      }
    }

    lfknecbacjmgaimo_xgerc(1, ia0, -tau[2], 12, work, a, 16);
  }

  a[11] = alpha1;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
