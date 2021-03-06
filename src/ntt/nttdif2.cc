// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/sumdiff.h"
#include "fxttypes.h"
#include "ntt/ntt.h"
#include "perm/revbinpermute.h"

void ntt_dif2_core(mod *f, ulong ldn, int is)
// Auxiliary routine for ntt_dif2().
// Decimation in frequency (DIF) radix-2 NTT.
// Output data is in revbin_permuted order.
// ldn := base-2 logarithm of the array length.
// is := sign of the transform
{
  const ulong n = (1UL << ldn);
  mod dw = mod::root2pow((int)(is > 0 ? ldn : -ldn));

  for (ulong ldm = ldn; ldm > 1; --ldm) {
    const ulong m = (1UL << ldm);
    const ulong mh = (m >> 1);

    mod w = mod::one;

    for (ulong j = 0; j < mh; ++j) {
      for (ulong r = 0; r < n; r += m) {
        const ulong t1 = r + j;
        const ulong t2 = t1 + mh;

        mod v = f[t2];
        mod u = f[t1];

        f[t1] = (u + v);
        f[t2] = (u - v) * w;
      }
      w *= dw;
    }
    dw *= dw;
  }

  for (ulong i = 0; i < n; i += 2) sumdiff(f[i], f[i + 1]);
}
// -------------------------

void ntt_dif2(mod *f, ulong ldn, int is)
// Radix-2 decimation in frequency (DIF) NTT
{
  ntt_dif2_core(f, ldn, is);
  revbin_permute(f, 1UL << ldn);
}
// -------------------------
