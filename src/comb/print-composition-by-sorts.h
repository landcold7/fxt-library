#if !defined HAVE_PRINT_COMPOSITION_BY_SORTS_H__
#define HAVE_PRINT_COMPOSITION_BY_SORTS_H__
// This file is part of the FXT library.
// Copyright (C) 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// comb/print-composition-by-sorts.cc:
void print_composition_with_sorts(const char *bla, const ulong *va,
                                  const ulong *vs, ulong m);
void print_rev_composition_with_sorts(const char *bla, const ulong *va,
                                      const ulong *vs, ulong m);
void print_composition_by_sorts(const char *bla, const ulong *va,
                                const ulong *vs, ulong m);

#endif  // !defined HAVE_PRINT_COMPOSITION_BY_SORTS_H__
