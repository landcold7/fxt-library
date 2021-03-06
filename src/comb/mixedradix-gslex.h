#if !defined HAVE_MIXEDRADIX_GSLEX_H__
#define HAVE_MIXEDRADIX_GSLEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"
#include "comb/is-mixedradix-num.h"
#include "comb/mixedradix-aux.h"
#include "fxttypes.h"

// Cf. comb/mixedradix-subset-lex.h for subset-lex order.

class mixedradix_gslex
// Mixed radix numbers in gslex (generalized, subset-lexicographic) order.
// Loopless generation.
{
 public:
  ulong n_;    // n-digit numbers
  ulong tr_;   // current track
  ulong *a_;   // digits
  ulong *m1_;  // m1[k] == radix-1 at position k

 private:  // have pointer data
  mixedradix_gslex(const mixedradix_gslex &) = delete;
  mixedradix_gslex &operator=(const mixedradix_gslex &) = delete;

 public:
  explicit mixedradix_gslex(ulong n, ulong mm, const ulong *m = nullptr) {
    n_ = n;
    a_ = new ulong[n_ + 1];
    m1_ = new ulong[n_ + 1];
    a_[n_] = 1;   // sentinel !=0
    m1_[n_] = 0;  // sentinel

    mixedradix_init(n_, mm, m, m1_);
    first();
  }

  ~mixedradix_gslex() {
    delete[] a_;
    delete[] m1_;
  }

  const ulong *data() const { return a_; }
  const ulong *nines() const { return m1_; }
  ulong num_digits() const { return n_; }

  void first() {
    for (ulong k = 0; k < n_; ++k) a_[k] = 0;
    a_[0] = 1;
    tr_ = 0;
  }

  //    void last()
  //    {
  //        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
  //        tr_ = ( n_ ? n_ - 1 : 0 );
  //    }

  bool next()
  // Loopless algorithm.
  {
    if (tr_ == n_) return false;  // current is last

    ulong d = a_[tr_];

    if (d != m1_[tr_])  // can increment
    {
      a_[tr_] = d + 1;
      if (tr_ != 0) {
        a_[0] = 1;
        tr_ = 0;
      }

      return true;
    }

    a_[tr_] = 0;

    const ulong t1 = tr_ + 1;
    ulong d1 = a_[t1];

    if (d1 == 0) {
      a_[t1] = 1;
      a_[0] = 1;
      tr_ = 0;
      return true;
    }

    ++tr_;
    return true;
  }

  void print(const char *bla, bool dfz = false) const
  // If dfz is true then Dots are printed For Zeros.
  {
    print_mixedradix(bla, a_, n_, dfz);
  }

  void print_nines(const char *bla) const {
    print_mixedradix(bla, m1_, n_, false);
  }

  ulong to_num() const
  // Return (integer) value of mixed radix number.
  {
    return mixedradix2num(a_, m1_, n_);
  }

  bool OK() const {
    if (!is_mixedradix_num(a_, n_, m1_)) return false;
    return true;
  }
};
// -------------------------

#endif  // !defined HAVE_MIXEDRADIX_GSLEX_H__
