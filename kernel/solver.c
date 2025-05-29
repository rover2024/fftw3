/****************************************************************************
** CFI wrapped code from reading C file 'solver__cfic_tmp_new__.c'
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

// decl: void (struct planner_s *, struct solver_s *)
#define LORELIB_CFI_24(FP) LORELIB_CFI(24, FP)

// decl: void (struct solver_s *)
#define LORELIB_CFI_30(FP) LORELIB_CFI(30, FP)

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

solver *X(mksolver)(size_t size, const solver_adt *adt)
{
     solver *s = (solver *)MALLOC(size, SOLVERS);

     s->adt = adt;
     s->refcnt = 0;
     return s;
}

void X(solver_use)(solver *ego)
{
     ++ego->refcnt;
}

void X(solver_destroy)(solver *ego)
{
     if ((--ego->refcnt) == 0) {
	  if (ego->adt->destroy)
	       LORELIB_CFI_30(ego->adt->destroy)(ego);
          X(ifree)(ego);
     }
}

void X(solver_register)(planner *plnr, solver *s)
{
     LORELIB_CFI_24(plnr->adt->register_solver)(plnr, s);
}

//
// Original code end
//


