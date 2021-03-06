// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <cmath>  // M_PI

#include "aux0/csincos.h"
#include "complextype.h"
#include "fxttypes.h"
#include "perm/revbinpermute.h"

// static const ulong RX = 4;
static const ulong LX = 2;

void fft_dif4l(Complex *f, ulong ldn, int is)
// Decimation in frequency (DIF) radix-4 FFT
// Non-optimized learners version
{
  double s2pi = (is > 0 ? 2.0 * M_PI : -2.0 * M_PI);

  const ulong n = (1UL << ldn);
  for (ulong ldm = ldn; ldm >= LX; ldm -= LX) {
    ulong m = (1UL << ldm);
    ulong m4 = (m >> LX);
    double ph0 = s2pi / (double)m;

    for (ulong j = 0; j < m4; j++) {
      double phi = (double)j * ph0;
      Complex e = SinCos(phi);
      Complex e2 = SinCos(2.0 * phi);
      Complex e3 = SinCos(3.0 * phi);

      for (ulong r = 0; r < n; r += m) {
        ulong i0 = j + r;
        ulong i1 = i0 + m4;
        ulong i2 = i1 + m4;
        ulong i3 = i2 + m4;

        Complex a0 = f[i0];
        Complex a1 = f[i1];
        Complex a2 = f[i2];
        Complex a3 = f[i3];

        Complex t0 = (a0 + a2) + (a1 + a3);
        Complex t2 = (a0 + a2) - (a1 + a3);

        Complex t1 = (a0 - a2) + Complex(0, is) * (a1 - a3);
        Complex t3 = (a0 - a2) - Complex(0, is) * (a1 - a3);

        t1 *= e;
        t2 *= e2;
        t3 *= e3;

        f[i0] = t0;
        f[i1] = t2;  // (!)
        f[i2] = t1;  // (!)
        f[i3] = t3;
      }
    }
  }

  if ((ldn & 1) != 0)  // n is not a power of 4, need a radix-2 step
  {
    for (ulong r = 0; r < n; r += 2) {
      Complex a0 = f[r];
      Complex a1 = f[r + 1];

      f[r] = a0 + a1;
      f[r + 1] = a0 - a1;
    }
  }

  revbin_permute(f, n);
}
// -------------------------
