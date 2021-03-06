
#include "comb/perm-trotter.h"

//#include "comb/fact2perm.h"

//#include "perm/perm2ccf.h"
//#include "perm/printcycles.h"
//#include "perm/permq.h"
//#include "perm/perm-genus.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"
#include "nextarg.h"

//% Generate all permutations in strong minimal-change order using Trotter's
//algorithm. % Smallest element moves most often.

//#define TIMING  // uncomment to disable printing

int main(int argc, char **argv) {
  ulong n = 4;
  NXARG(n, "Permutations of n elements.");
  bool bq = 0;
  NXARG(bq, "Whether to go backwards.");

  perm_trotter P(n);
  if (bq) P.last();

#ifdef TIMING
#ifdef PERM_TROTTER_OPT
  cout << "PERM_TROTTER_OPT is defined." << endl;
#endif
  ulong ct = 0;
  if (!bq) {
    cout << "forward:" << endl;
    do {
      ++ct;
    } while (P.next());
  } else {
    cout << "backward:" << endl;
    do {
      ++ct;
    } while (P.prev());
  }
  cout << "ct=" << ct << endl;

#else  // TIMING

  const bool dfz = true;  // whether to print dots for zeros

  ulong ct = 0;
  //    ulong fc[32];
  do {
#if 0
//        if ( ! is_involution(P.data(), n) )  continue;
//        if ( ! is_simple(P.data(), n) )  continue;

        { ulong cpi[n];
            if ( 0 != perm_genus(P.data(), n, cpi) )  continue;
        }
#endif
    cout << setw(4) << ct << ":";
    ++ct;

    P.print("    ", dfz);

    ulong sw1, sw2;
    P.get_swap(sw1, sw2);
    cout << "    (" << sw1 << ", " << sw2 << ") ";

    P.print_inv("    ", dfz);

    // print directions:
    cout << "    ";
    for (ulong j = 0; j < n; ++j) cout << " " << (P.d_[j] == 1 ? '+' : '-');

    //        perm2ffact(P.invdata(), n, fc);
    //        print_mixedradix("  fc = ", fc, n-1);
    //        print_cycles("    ", P.data(), n);
    //        print_ccf("    ", P.data(), n);

    cout << endl;
  } while ((!bq ? P.next() : P.prev()));
  cout << " ct=" << ct << endl;
#endif  // TIMING

  return 0;
}
// -------------------------

/*
Timing: (Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz)
GCC 8.3.0

time ./bin 13 0
arg 1: 13 == n  [Permutations of n elements.]  default=4
arg 2: 0 == bq  [Whether to go backwards.]  default=0
PERM_TROTTER_OPT is defined.
forward:
ct=6227020800
./bin 13 0  14.66s user 0.00s system 99% cpu 14.658 total
 ==> 6227020800 / 14.66 == 424,762,673 per second

time ./bin 13 1
arg 1: 13 == n  [Permutations of n elements.]  default=4
arg 2: 1 == bq  [Whether to go backwards.]  default=0
PERM_TROTTER_OPT is defined.
backward:
ct=6227020800
./bin 13 1  14.70s user 0.00s system 99% cpu 14.703 total
 ==> 6227020800 / 14.70 == 423,606,857 per second


time ./bin 13 0
arg 1: 13 == n  [Permutations of n elements.]  default=4
arg 2: 0 == bq  [Whether to go backwards.]  default=0
forward:
ct=6227020800
./bin 13 0  26.82s user 0.00s system 99% cpu 26.821 total

time ./bin 13 1
arg 1: 13 == n  [Permutations of n elements.]  default=4
arg 2: 1 == bq  [Whether to go backwards.]  default=0
backward:
ct=6227020800
./bin 13 1  28.45s user 0.00s system 99% cpu 28.458 total

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 13 0
PERM_TROTTER_OPT is defined.
forward:
ct=6227020800
./bin 13 0  12.52s user 0.00s system 99% cpu 12.518 total
 ==> 6227020800/12.52 == 497,365,878 per second

 time ./bin 13 1
arg 1: 13 == n  [Permutations of n elements (n>=1).]  default=4
arg 2: 1 == bq  [Whether to go backwards.]  default=0
PERM_TROTTER_OPT is defined.
backward:
ct=6227020800
./bin 13 1  13.28s user 0.00s system 99% cpu 13.285 total
 ==> 6227020800/13.28 == 468,902,168 per second


 ---- Regression with GCC 4.8.0:

 time ./bin 13 0
arg 1: 13 == n  [Permutations of n elements.]  default=4
arg 2: 0 == bq  [Whether to go backwards.]  default=0
PERM_TROTTER_OPT is defined.
forward:
ct=6227020800
./bin 13 0  27.82s user 0.01s system 99% cpu 27.835 total
 ==> 6227020800/27.82 == 223,832,523 per second

 time ./bin 13 1
arg 1: 13 == n  [Permutations of n elements.]  default=4
arg 2: 1 == bq  [Whether to go backwards.]  default=0
PERM_TROTTER_OPT is defined.
backward:
ct=6227020800
./bin 13 1  29.83s user 0.00s system 99% cpu 29.840 total
 ==> 6227020800/29.83 == 208,750,278 per second

*/

/*
BENCHARGS=13 0
BENCHARGS=13 1
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-trotter-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-trotter-demo.cc DEMOFLAGS=-DTIMING"
/// End:
