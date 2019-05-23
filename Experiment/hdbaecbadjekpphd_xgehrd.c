/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: hdbaecbadjekpphd_xgehrd.c
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
#include "lfknecbacjmgaimo_xgerc.h"
#include "rt_hypotd_snf.h"
#include "hdbaecbadjekpphd_xgehrd.h"

/* Function for MATLAB Function: '<S1>/INITIALIZE' */
void hdbaecbadjekpphd_xgehrd(real_T a[16], real_T tau[3])
{
  real_T work[4];
  real_T alpha1;
  real_T b;
  real_T xnorm;
  int32_T knt;
  int32_T lastc;
  int32_T rowleft;
  int32_T iy;
  int32_T iac;
  int32_T g;
  int32_T b_ia;
  int32_T jy;
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
  alpha1 = a[1];
  b = 0.0;
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
        for (lastc = 3; lastc < 5; lastc++) {
          a[lastc - 1] *= 9.9792015476736E+291;
        }

        xnorm *= 9.9792015476736E+291;
        alpha1 *= 9.9792015476736E+291;
      } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

      xnorm = rt_hypotd_snf(alpha1, iecbbimomgdjjekn_xnrm2(2, a, 3));
      if (alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      b = (xnorm - alpha1) / xnorm;
      alpha1 = 1.0 / (alpha1 - xnorm);
      for (lastc = 3; lastc < 5; lastc++) {
        a[lastc - 1] *= alpha1;
      }

      for (lastc = 1; lastc <= knt; lastc++) {
        xnorm *= 1.0020841800044864E-292;
      }

      alpha1 = xnorm;
    } else {
      b = (xnorm - a[1]) / xnorm;
      alpha1 = 1.0 / (a[1] - xnorm);
      for (knt = 3; knt < 5; knt++) {
        a[knt - 1] *= alpha1;
      }

      alpha1 = xnorm;
    }
  }

  tau[0] = b;
  a[1] = 1.0;
  if (b != 0.0) {
    knt = 3;
    lastc = 3;
    while ((knt > 0) && (a[lastc] == 0.0)) {
      knt--;
      lastc--;
    }

    lastc = 4;
    exitg12 = false;
    while ((!exitg12) && (lastc > 0)) {
      rowleft = 4 + lastc;
      jy = rowleft;
      do {
        exitg11 = 0;
        if (jy <= ((knt - 1) << 2) + rowleft) {
          if (a[jy - 1] != 0.0) {
            exitg11 = 1;
          } else {
            jy += 4;
          }
        } else {
          lastc--;
          exitg11 = 2;
        }
      } while (exitg11 == 0);

      if (exitg11 == 1) {
        exitg12 = true;
      }
    }
  } else {
    knt = 0;
    lastc = 0;
  }

  if (knt > 0) {
    if (lastc != 0) {
      for (rowleft = 1; rowleft <= lastc; rowleft++) {
        work[rowleft - 1] = 0.0;
      }

      rowleft = 1;
      jy = ((knt - 1) << 2) + 5;
      for (iac = 5; iac <= jy; iac += 4) {
        iy = 0;
        g = (iac + lastc) - 1;
        for (b_ia = iac; b_ia <= g; b_ia++) {
          work[iy] += a[b_ia - 1] * a[rowleft];
          iy++;
        }

        rowleft++;
      }
    }

    if (!(-b == 0.0)) {
      rowleft = 4;
      jy = 1;
      for (iac = 1; iac <= knt; iac++) {
        if (a[jy] != 0.0) {
          xnorm = a[jy] * -b;
          iy = 0;
          g = lastc + rowleft;
          for (b_ia = rowleft; b_ia + 1 <= g; b_ia++) {
            a[b_ia] += work[iy] * xnorm;
            iy++;
          }
        }

        jy++;
        rowleft += 4;
      }
    }
  }

  if (b != 0.0) {
    knt = 3;
    lastc = 3;
    while ((knt > 0) && (a[lastc] == 0.0)) {
      knt--;
      lastc--;
    }

    lastc = 3;
    exitg10 = false;
    while ((!exitg10) && (lastc > 0)) {
      rowleft = ((lastc - 1) << 2) + 6;
      jy = rowleft;
      do {
        exitg9 = 0;
        if (jy <= (rowleft + knt) - 1) {
          if (a[jy - 1] != 0.0) {
            exitg9 = 1;
          } else {
            jy++;
          }
        } else {
          lastc--;
          exitg9 = 2;
        }
      } while (exitg9 == 0);

      if (exitg9 == 1) {
        exitg10 = true;
      }
    }
  } else {
    knt = 0;
    lastc = 0;
  }

  if (knt > 0) {
    if (lastc != 0) {
      for (rowleft = 1; rowleft <= lastc; rowleft++) {
        work[rowleft - 1] = 0.0;
      }

      rowleft = 0;
      jy = ((lastc - 1) << 2) + 6;
      for (iac = 6; iac <= jy; iac += 4) {
        iy = 2;
        xnorm = 0.0;
        g = (iac + knt) - 1;
        for (b_ia = iac; b_ia <= g; b_ia++) {
          xnorm += a[b_ia - 1] * a[iy - 1];
          iy++;
        }

        work[rowleft] += xnorm;
        rowleft++;
      }
    }

    lfknecbacjmgaimo_xgerc(knt, lastc, -b, 2, work, a, 6);
  }

  a[1] = alpha1;
  alpha1 = a[6];
  b = 0.0;
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
        lastc = 8;
        while (lastc <= 8) {
          a[7] *= 9.9792015476736E+291;
          lastc = 9;
        }

        xnorm *= 9.9792015476736E+291;
        alpha1 *= 9.9792015476736E+291;
      } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

      xnorm = rt_hypotd_snf(alpha1, iecbbimomgdjjekn_xnrm2(1, a, 8));
      if (alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      b = (xnorm - alpha1) / xnorm;
      alpha1 = 1.0 / (alpha1 - xnorm);
      lastc = 8;
      while (lastc <= 8) {
        a[7] *= alpha1;
        lastc = 9;
      }

      for (lastc = 1; lastc <= knt; lastc++) {
        xnorm *= 1.0020841800044864E-292;
      }

      alpha1 = xnorm;
    } else {
      b = (xnorm - a[6]) / xnorm;
      alpha1 = 1.0 / (a[6] - xnorm);
      knt = 8;
      while (knt <= 8) {
        a[7] *= alpha1;
        knt = 9;
      }

      alpha1 = xnorm;
    }
  }

  tau[1] = b;
  a[6] = 1.0;
  if (b != 0.0) {
    knt = 2;
    lastc = 7;
    while ((knt > 0) && (a[lastc] == 0.0)) {
      knt--;
      lastc--;
    }

    lastc = 4;
    exitg8 = false;
    while ((!exitg8) && (lastc > 0)) {
      rowleft = 8 + lastc;
      jy = rowleft;
      do {
        exitg7 = 0;
        if (jy <= ((knt - 1) << 2) + rowleft) {
          if (a[jy - 1] != 0.0) {
            exitg7 = 1;
          } else {
            jy += 4;
          }
        } else {
          lastc--;
          exitg7 = 2;
        }
      } while (exitg7 == 0);

      if (exitg7 == 1) {
        exitg8 = true;
      }
    }
  } else {
    knt = 0;
    lastc = 0;
  }

  if (knt > 0) {
    if (lastc != 0) {
      for (rowleft = 1; rowleft <= lastc; rowleft++) {
        work[rowleft - 1] = 0.0;
      }

      rowleft = 6;
      jy = ((knt - 1) << 2) + 9;
      for (iac = 9; iac <= jy; iac += 4) {
        iy = 0;
        g = (iac + lastc) - 1;
        for (b_ia = iac; b_ia <= g; b_ia++) {
          work[iy] += a[b_ia - 1] * a[rowleft];
          iy++;
        }

        rowleft++;
      }
    }

    if (!(-b == 0.0)) {
      rowleft = 8;
      jy = 6;
      for (iac = 1; iac <= knt; iac++) {
        if (a[jy] != 0.0) {
          xnorm = a[jy] * -b;
          iy = 0;
          g = lastc + rowleft;
          for (b_ia = rowleft; b_ia + 1 <= g; b_ia++) {
            a[b_ia] += work[iy] * xnorm;
            iy++;
          }
        }

        jy++;
        rowleft += 4;
      }
    }
  }

  if (b != 0.0) {
    knt = 2;
    lastc = 7;
    while ((knt > 0) && (a[lastc] == 0.0)) {
      knt--;
      lastc--;
    }

    lastc = 2;
    exitg6 = false;
    while ((!exitg6) && (lastc > 0)) {
      rowleft = ((lastc - 1) << 2) + 11;
      jy = rowleft;
      do {
        exitg5 = 0;
        if (jy <= (rowleft + knt) - 1) {
          if (a[jy - 1] != 0.0) {
            exitg5 = 1;
          } else {
            jy++;
          }
        } else {
          lastc--;
          exitg5 = 2;
        }
      } while (exitg5 == 0);

      if (exitg5 == 1) {
        exitg6 = true;
      }
    }
  } else {
    knt = 0;
    lastc = 0;
  }

  if (knt > 0) {
    if (lastc != 0) {
      for (rowleft = 1; rowleft <= lastc; rowleft++) {
        work[rowleft - 1] = 0.0;
      }

      rowleft = 0;
      jy = ((lastc - 1) << 2) + 11;
      for (iac = 11; iac <= jy; iac += 4) {
        iy = 7;
        xnorm = 0.0;
        g = (iac + knt) - 1;
        for (b_ia = iac; b_ia <= g; b_ia++) {
          xnorm += a[b_ia - 1] * a[iy - 1];
          iy++;
        }

        work[rowleft] += xnorm;
        rowleft++;
      }
    }

    lfknecbacjmgaimo_xgerc(knt, lastc, -b, 7, work, a, 11);
  }

  a[6] = alpha1;
  alpha1 = a[11];
  b = 0.0;
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

      b = (xnorm - alpha1) / xnorm;
      for (lastc = 1; lastc <= knt; lastc++) {
        xnorm *= 1.0020841800044864E-292;
      }

      alpha1 = xnorm;
    } else {
      b = (xnorm - a[11]) / xnorm;
      alpha1 = xnorm;
    }
  }

  tau[2] = b;
  a[11] = 1.0;
  if (b != 0.0) {
    knt = 1;
    lastc = 11;
    while ((knt > 0) && (a[lastc] == 0.0)) {
      knt = 0;
      lastc--;
    }

    lastc = 4;
    exitg4 = false;
    while ((!exitg4) && (lastc > 0)) {
      rowleft = 12 + lastc;
      jy = rowleft;
      do {
        exitg3 = 0;
        if (jy <= ((knt - 1) << 2) + rowleft) {
          if (a[jy - 1] != 0.0) {
            exitg3 = 1;
          } else {
            jy += 4;
          }
        } else {
          lastc--;
          exitg3 = 2;
        }
      } while (exitg3 == 0);

      if (exitg3 == 1) {
        exitg4 = true;
      }
    }
  } else {
    knt = 0;
    lastc = 0;
  }

  if (knt > 0) {
    if (lastc != 0) {
      for (rowleft = 1; rowleft <= lastc; rowleft++) {
        work[rowleft - 1] = 0.0;
      }

      rowleft = 11;
      iac = 13;
      while (iac <= 13) {
        iy = 0;
        g = lastc + 12;
        for (b_ia = 13; b_ia <= g; b_ia++) {
          work[iy] += a[b_ia - 1] * a[rowleft];
          iy++;
        }

        rowleft++;
        iac = 17;
      }
    }

    if (!(-b == 0.0)) {
      rowleft = 12;
      jy = 11;
      iac = 1;
      while (iac <= 1) {
        if (a[jy] != 0.0) {
          xnorm = a[jy] * -b;
          iy = 0;
          g = lastc + rowleft;
          for (b_ia = rowleft; b_ia + 1 <= g; b_ia++) {
            a[b_ia] += work[iy] * xnorm;
            iy++;
          }
        }

        jy++;
        rowleft += 4;
        iac = 2;
      }
    }
  }

  if (b != 0.0) {
    knt = 1;
    lastc = 11;
    while ((knt > 0) && (a[lastc] == 0.0)) {
      knt = 0;
      lastc--;
    }

    lastc = 1;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      jy = 16;
      do {
        exitg1 = 0;
        if (jy <= knt + 15) {
          if (a[15] != 0.0) {
            exitg1 = 1;
          } else {
            jy = 17;
          }
        } else {
          lastc = 0;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    knt = 0;
    lastc = 0;
  }

  if (knt > 0) {
    if (lastc != 0) {
      rowleft = 1;
      while (rowleft <= 1) {
        work[0] = 0.0;
        rowleft = 2;
      }

      rowleft = 0;
      iac = 16;
      while (iac <= 16) {
        iy = 12;
        xnorm = 0.0;
        b_ia = 16;
        while (b_ia <= 16) {
          xnorm += a[iy - 1] * a[15];
          iy++;
          b_ia = 17;
        }

        work[rowleft] += xnorm;
        rowleft++;
        iac = 20;
      }
    }

    lfknecbacjmgaimo_xgerc(1, lastc, -b, 12, work, a, 16);
  }

  a[11] = alpha1;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
