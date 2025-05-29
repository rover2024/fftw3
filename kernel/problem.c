/****************************************************************************
** CFI wrapped code from reading C file 'problem__cfic_tmp_new__.c'
**
** Created by: Lorelei CFI compiler
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

//
// CFI declarations begin
//
enum LoreLib_Constants {
    LoreLib_CFI_Count = 40,
};

struct LoreLib_HostLibraryContext {
    void *AddressBoundary;

    void (*HrtSetThreadCallback)(void *callback);
    void *HrtPThreadCreate;
    void *HrtPThreadExit;

    void *CFIs[LoreLib_CFI_Count];
};

__attribute__((visibility("default"))) struct LoreLib_HostLibraryContext LoreLib_HostLibCtx;

#define LORELIB_CFI(INDEX, FP)                                                                       \
    ({                                                                                               \
        typedef __typeof__(FP) _LORELIB_CFI_TYPE;                                                    \
        void *_lorelib_cfi_ret = (void *) (FP);                                                      \
        if ((unsigned long) _lorelib_cfi_ret < (unsigned long) LoreLib_HostLibCtx.AddressBoundary) { \
            LoreLib_HostLibCtx.HrtSetThreadCallback(_lorelib_cfi_ret);                               \
            _lorelib_cfi_ret = (void *) LoreLib_HostLibCtx.CFIs[INDEX - 1];                          \
        }                                                                                            \
        (_LORELIB_CFI_TYPE) _lorelib_cfi_ret;                                                        \
    })

// decl: void (struct printer_s *, const char *, ...)
#define LORELIB_CFI_27(FP) LORELIB_CFI(27, FP)

// decl: void (struct problem_s *)
#define LORELIB_CFI_29(FP) LORELIB_CFI(29, FP)

//
// CFI declarations end
//


//
// Original code begin
//
/*
 * Copyright (c) 2003, 2007-14 Matteo Frigo
 * Copyright (c) 2003, 2007-14 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#include "kernel/ifftw.h"

/* constructor */
problem *X(mkproblem)(size_t sz, const problem_adt *adt)
{
     problem *p = (problem *)MALLOC(sz, PROBLEMS);

     p->adt = adt;
     return p;
}

/* destructor */
void X(problem_destroy)(problem *ego)
{
     if (ego)
	  LORELIB_CFI_29(ego->adt->destroy)(ego);
}

/* management of unsolvable problems */
static void unsolvable_destroy(problem *ego)
{
     UNUSED(ego);
}

static void unsolvable_hash(const problem *p, md5 *m)
{
     UNUSED(p);
     X(md5puts)(m, "unsolvable");
}

static void unsolvable_print(const problem *ego, printer *p)
{
     UNUSED(ego);
     LORELIB_CFI_27(p->print)(p, "(unsolvable)");
}

static void unsolvable_zero(const problem *ego)
{
     UNUSED(ego);
}

static const problem_adt padt =
{
     PROBLEM_UNSOLVABLE,
     unsolvable_hash,
     unsolvable_zero,
     unsolvable_print,
     unsolvable_destroy
};

/* there is no point in malloc'ing this one */
static problem the_unsolvable_problem = { &padt };

problem *X(mkproblem_unsolvable)(void)
{
     return &the_unsolvable_problem;
}

//
// Original code end
//


