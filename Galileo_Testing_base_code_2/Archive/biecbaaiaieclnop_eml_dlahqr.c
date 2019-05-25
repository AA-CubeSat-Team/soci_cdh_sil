/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: biecbaaiaieclnop_eml_dlahqr.c
 *
 * Code generated for Simulink model 'gnc2_lib'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 14:12:23 2019
 */

#include "rtwtypes.h"
#include <math.h>
#include "cbaiohlfjeknbaim_xrot.h"
#include "jmglbiekmgdbbaai_xrot.h"
#include "lfkfaaaafknomohl_xdlanv2.h"
#include "ohdbdjecdjekngln_xzlarfg.h"
#include "biecbaaiaieclnop_eml_dlahqr.h"

/* Function for MATLAB Function: '<S1>/INITIALIZE' */
int32_T biecbaaiaieclnop_eml_dlahqr(real_T h[16], real_T z[16])
{
  int32_T info;
  real_T v[3];
  int32_T i;
  int32_T L;
  boolean_T goto150;
  int32_T k;
  real_T tst;
  real_T htmp1;
  real_T ab;
  real_T ba;
  real_T aa;
  real_T h12;
  int32_T m;
  int32_T nr;
  int32_T hoffset;
  real_T unusedU2;
  real_T unusedU3;
  real_T b_v[3];
  int32_T b_k;
  int32_T j;
  real_T b_y;
  real_T c_y;
  int32_T ix;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;
  boolean_T exitg4;
  boolean_T guard1 = false;
  info = 0;
  h[2] = 0.0;
  h[3] = 0.0;
  h[7] = 0.0;
  i = 3;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    L = 1;
    goto150 = false;
    ix = 0;
    exitg2 = false;
    while ((!exitg2) && (ix < 31)) {
      k = i;
      exitg4 = false;
      while ((!exitg4) && ((k + 1 > L) && (!(fabs(h[((k - 1) << 2) + k]) <=
                4.0083367200179456E-292)))) {
        tst = fabs(h[(((k - 1) << 2) + k) - 1]) + fabs(h[(k << 2) + k]);
        if (tst == 0.0) {
          if (k - 1 >= 1) {
            tst = fabs(h[(((k - 2) << 2) + k) - 1]);
          }

          if (k + 2 <= 4) {
            tst += fabs(h[((k << 2) + k) + 1]);
          }
        }

        guard1 = false;
        if (fabs(h[((k - 1) << 2) + k]) <= 2.2204460492503131E-16 * tst) {
          htmp1 = fabs(h[((k - 1) << 2) + k]);
          tst = fabs(h[((k << 2) + k) - 1]);
          if (htmp1 > tst) {
            ab = htmp1;
            ba = tst;
          } else {
            ab = tst;
            ba = htmp1;
          }

          htmp1 = fabs(h[(k << 2) + k]);
          tst = fabs(h[(((k - 1) << 2) + k) - 1] - h[(k << 2) + k]);
          if (htmp1 > tst) {
            aa = htmp1;
            htmp1 = tst;
          } else {
            aa = tst;
          }

          tst = aa + ab;
          if (ab / tst * ba <= fmax(4.0083367200179456E-292, aa / tst * htmp1 *
               2.2204460492503131E-16)) {
            exitg4 = true;
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }

        if (guard1) {
          k--;
        }
      }

      L = k + 1;
      if (k + 1 > 1) {
        h[k + ((k - 1) << 2)] = 0.0;
      }

      if (k + 1 >= i) {
        goto150 = true;
        exitg2 = true;
      } else {
        switch (ix) {
         case 10:
          tst = fabs(h[(((k + 1) << 2) + k) + 2]) + fabs(h[((k << 2) + k) + 1]);
          htmp1 = h[(k << 2) + k] + 0.75 * tst;
          h12 = -0.4375 * tst;
          aa = tst;
          ba = htmp1;
          break;

         case 20:
          tst = fabs(h[(((i - 2) << 2) + i) - 1]) + fabs(h[((i - 1) << 2) + i]);
          htmp1 = h[(i << 2) + i] + 0.75 * tst;
          h12 = -0.4375 * tst;
          aa = tst;
          ba = htmp1;
          break;

         default:
          htmp1 = h[(((i - 1) << 2) + i) - 1];
          aa = h[((i - 1) << 2) + i];
          h12 = h[((i << 2) + i) - 1];
          ba = h[(i << 2) + i];
          break;
        }

        tst = ((fabs(htmp1) + fabs(h12)) + fabs(aa)) + fabs(ba);
        if (tst == 0.0) {
          htmp1 = 0.0;
          ba = 0.0;
          ab = 0.0;
          aa = 0.0;
        } else {
          htmp1 /= tst;
          aa /= tst;
          h12 /= tst;
          ba /= tst;
          ab = (htmp1 + ba) / 2.0;
          htmp1 = (htmp1 - ab) * (ba - ab) - h12 * aa;
          aa = sqrt(fabs(htmp1));
          if (htmp1 >= 0.0) {
            htmp1 = ab * tst;
            ab = htmp1;
            ba = aa * tst;
            aa = -ba;
          } else {
            htmp1 = ab + aa;
            ab -= aa;
            if (fabs(htmp1 - ba) <= fabs(ab - ba)) {
              htmp1 *= tst;
              ab = htmp1;
            } else {
              ab *= tst;
              htmp1 = ab;
            }

            ba = 0.0;
            aa = 0.0;
          }
        }

        m = i - 1;
        exitg3 = false;
        while ((!exitg3) && (m >= k + 1)) {
          tst = (fabs(h[(((m - 1) << 2) + m) - 1] - ab) + fabs(aa)) + fabs(h[((m
            - 1) << 2) + m]);
          h12 = h[((m - 1) << 2) + m] / tst;
          v[0] = ((h[(((m - 1) << 2) + m) - 1] - ab) / tst * (h[(((m - 1) << 2)
                    + m) - 1] - htmp1) + h[((m << 2) + m) - 1] * h12) - aa / tst
            * ba;
          v[1] = (((h[(((m - 1) << 2) + m) - 1] + h[(m << 2) + m]) - htmp1) - ab)
            * h12;
          v[2] = h[((m << 2) + m) + 1] * h12;
          tst = (fabs(v[0]) + fabs(v[1])) + fabs(v[2]);
          h12 = v[0] / tst;
          v[0] /= tst;
          b_y = v[1] / tst;
          v[1] /= tst;
          c_y = v[2] / tst;
          v[2] /= tst;
          if ((k + 1 == m) || (fabs(h[(((m - 2) << 2) + m) - 1]) * (fabs(b_y) +
                fabs(c_y)) <= ((fabs(h[(((m - 2) << 2) + m) - 2]) + fabs(h[(((m
                     - 1) << 2) + m) - 1])) + fabs(h[(m << 2) + m])) *
                               (2.2204460492503131E-16 * fabs(h12)))) {
            exitg3 = true;
          } else {
            m--;
          }
        }

        for (b_k = m; b_k <= i; b_k++) {
          nr = (i - b_k) + 2;
          if (3 <= nr) {
            nr = 3;
          }

          if (b_k > m) {
            hoffset = ((b_k - 2) << 2) + b_k;
            for (j = -1; j + 2 <= nr; j++) {
              v[j + 1] = h[j + hoffset];
            }
          }

          htmp1 = v[0];
          b_v[0] = v[0];
          b_v[1] = v[1];
          b_v[2] = v[2];
          tst = ohdbdjecdjekngln_xzlarfg(nr, &htmp1, b_v);
          v[1] = b_v[1];
          v[2] = b_v[2];
          v[0] = htmp1;
          if (b_k > m) {
            h[(b_k + ((b_k - 2) << 2)) - 1] = htmp1;
            h[b_k + ((b_k - 2) << 2)] = 0.0;
            if (b_k < i) {
              h[(b_k + ((b_k - 2) << 2)) + 1] = 0.0;
            }
          } else {
            if (m > k + 1) {
              h[(b_k + ((b_k - 2) << 2)) - 1] *= 1.0 - tst;
            }
          }

          htmp1 = b_v[1];
          ab = tst * b_v[1];
          switch (nr) {
           case 3:
            ba = b_v[2];
            aa = tst * b_v[2];
            for (nr = b_k - 1; nr + 1 < 5; nr++) {
              h12 = (h[((nr << 2) + b_k) - 1] + h[(nr << 2) + b_k] * htmp1) + h
                [((nr << 2) + b_k) + 1] * ba;
              h[(b_k + (nr << 2)) - 1] -= h12 * tst;
              h[b_k + (nr << 2)] -= h12 * ab;
              h[(b_k + (nr << 2)) + 1] -= h12 * aa;
            }

            hoffset = b_k + 3;
            nr = i + 1;
            if (hoffset <= nr) {
              nr = hoffset;
            }

            for (hoffset = 0; hoffset + 1 <= nr; hoffset++) {
              h12 = (h[((b_k - 1) << 2) + hoffset] + h[(b_k << 2) + hoffset] *
                     htmp1) + h[((b_k + 1) << 2) + hoffset] * ba;
              h[hoffset + ((b_k - 1) << 2)] -= h12 * tst;
              h[hoffset + (b_k << 2)] -= h12 * ab;
              h[hoffset + ((b_k + 1) << 2)] -= h12 * aa;
            }

            h12 = (z[(b_k - 1) << 2] + z[b_k << 2] * b_v[1]) + z[(b_k + 1) << 2]
              * b_v[2];
            z[(b_k - 1) << 2] -= h12 * tst;
            z[b_k << 2] -= h12 * ab;
            z[(b_k + 1) << 2] -= h12 * aa;
            h12 = (z[((b_k - 1) << 2) + 1] + z[(b_k << 2) + 1] * b_v[1]) + z
              [((b_k + 1) << 2) + 1] * b_v[2];
            z[1 + ((b_k - 1) << 2)] -= h12 * tst;
            z[1 + (b_k << 2)] -= h12 * ab;
            z[1 + ((b_k + 1) << 2)] -= h12 * aa;
            h12 = (z[((b_k - 1) << 2) + 2] + z[(b_k << 2) + 2] * b_v[1]) + z
              [((b_k + 1) << 2) + 2] * b_v[2];
            z[2 + ((b_k - 1) << 2)] -= h12 * tst;
            z[2 + (b_k << 2)] -= h12 * ab;
            z[2 + ((b_k + 1) << 2)] -= h12 * aa;
            h12 = (z[((b_k - 1) << 2) + 3] + z[(b_k << 2) + 3] * b_v[1]) + z
              [((b_k + 1) << 2) + 3] * b_v[2];
            z[3 + ((b_k - 1) << 2)] -= h12 * tst;
            z[3 + (b_k << 2)] -= h12 * ab;
            z[3 + ((b_k + 1) << 2)] -= h12 * aa;
            break;

           case 2:
            for (nr = b_k - 1; nr + 1 < 5; nr++) {
              h12 = h[((nr << 2) + b_k) - 1] + h[(nr << 2) + b_k] * htmp1;
              h[(b_k + (nr << 2)) - 1] -= h12 * tst;
              h[b_k + (nr << 2)] -= h12 * ab;
            }

            for (nr = 0; nr + 1 <= i + 1; nr++) {
              h12 = h[((b_k - 1) << 2) + nr] + h[(b_k << 2) + nr] * htmp1;
              h[nr + ((b_k - 1) << 2)] -= h12 * tst;
              h[nr + (b_k << 2)] -= h12 * ab;
            }

            h12 = z[(b_k - 1) << 2] + z[b_k << 2] * b_v[1];
            z[(b_k - 1) << 2] -= h12 * tst;
            z[b_k << 2] -= h12 * ab;
            h12 = z[((b_k - 1) << 2) + 1] + z[(b_k << 2) + 1] * b_v[1];
            z[1 + ((b_k - 1) << 2)] -= h12 * tst;
            z[1 + (b_k << 2)] -= h12 * ab;
            h12 = z[((b_k - 1) << 2) + 2] + z[(b_k << 2) + 2] * b_v[1];
            z[2 + ((b_k - 1) << 2)] -= h12 * tst;
            z[2 + (b_k << 2)] -= h12 * ab;
            h12 = z[((b_k - 1) << 2) + 3] + z[(b_k << 2) + 3] * b_v[1];
            z[3 + ((b_k - 1) << 2)] -= h12 * tst;
            z[3 + (b_k << 2)] -= h12 * ab;
            break;
          }
        }

        ix++;
      }
    }

    if (!goto150) {
      info = i + 1;
      exitg1 = true;
    } else {
      if (!((i + 1 == L) || (!(L == i)))) {
        ab = h[(((i - 1) << 2) + i) - 1];
        ba = h[((i << 2) + i) - 1];
        aa = h[((i - 1) << 2) + i];
        h12 = h[(i << 2) + i];
        lfkfaaaafknomohl_xdlanv2(&ab, &ba, &aa, &h12, &b_y, &c_y, &unusedU2,
          &unusedU3, &tst, &htmp1);
        h[(i + ((i - 1) << 2)) - 1] = ab;
        h[(i + (i << 2)) - 1] = ba;
        h[i + ((i - 1) << 2)] = aa;
        h[i + (i << 2)] = h12;
        if (4 > i + 1) {
          jmglbiekmgdbbaai_xrot(3 - i, h, i + ((i + 1) << 2), (i + ((i + 1) << 2))
                                + 1, tst, htmp1);
        }

        cbaiohlfjeknbaim_xrot(i - 1, h, 1 + ((i - 1) << 2), 1 + (i << 2), tst,
                              htmp1);
        ix = (i - 1) << 2;
        i <<= 2;
        ab = tst * z[ix] + htmp1 * z[i];
        z[i] = tst * z[i] - htmp1 * z[ix];
        z[ix] = ab;
        i++;
        ix++;
        ab = tst * z[ix] + htmp1 * z[i];
        z[i] = tst * z[i] - htmp1 * z[ix];
        z[ix] = ab;
        i++;
        ix++;
        ab = tst * z[ix] + htmp1 * z[i];
        z[i] = tst * z[i] - htmp1 * z[ix];
        z[ix] = ab;
        i++;
        ix++;
        ab = tst * z[ix] + htmp1 * z[i];
        z[i] = tst * z[i] - htmp1 * z[ix];
        z[ix] = ab;
      }

      i = L - 2;
    }
  }

  return info;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
