/****************************************************************************
** CFI wrapped code from reading C file 'flops__cfic_tmp_new__.c'
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

// decl: double (const struct problem_s *, double, cost_kind)
#define LORELIB_CFI_1(FP) LORELIB_CFI(1, FP)

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

#include "api/api.h"

void X(flops)(const X(plan) p, double *add, double *mul, double *fma)
{
     planner *plnr = X(the_planner)();
     opcnt *o = &p->pln->ops;
     *add = o->add; *mul = o->mul; *fma = o->fma;
     if (plnr->cost_hook) {
	  *add = LORELIB_CFI_1(plnr->cost_hook)(p->prb, *add, COST_SUM);
	  *mul = LORELIB_CFI_1(plnr->cost_hook)(p->prb, *mul, COST_SUM);
	  *fma = LORELIB_CFI_1(plnr->cost_hook)(p->prb, *fma, COST_SUM);
     }
}

double X(estimate_cost)(const X(plan) p)
{
     return X(iestimate_cost)(X(the_planner)(), p->pln, p->prb);
}

double X(cost)(const X(plan) p)
{
     return p->pln->pcost;
}

//
// Original code end
//


