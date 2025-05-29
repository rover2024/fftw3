/****************************************************************************
** CFI wrapped code from reading C file 'plan__cfic_tmp_new__.c'
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

// decl: void (struct plan_s *)
#define LORELIB_CFI_17(FP) LORELIB_CFI(17, FP)

// decl: void (struct plan_s *, enum wakefulness)
#define LORELIB_CFI_18(FP) LORELIB_CFI(18, FP)

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

/* "Plan: To bother about the best method of accomplishing an
   accidental result."  (Ambrose Bierce, The Enlarged Devil's
   Dictionary). */

plan *X(mkplan)(size_t size, const plan_adt *adt)
{
     plan *p = (plan *)MALLOC(size, PLANS);

     A(adt->destroy);
     p->adt = adt;
     X(ops_zero)(&p->ops);
     p->pcost = 0.0;
     p->wakefulness = SLEEPY;
     p->could_prune_now_p = 0;
     
     return p;
}

/*
 * destroy a plan
 */
void X(plan_destroy_internal)(plan *ego)
{
     if (ego) {
	  A(ego->wakefulness == SLEEPY);
          LORELIB_CFI_17(ego->adt->destroy)(ego);
	  X(ifree)(ego);
     }
}

/* dummy destroy routine for plans with no local state */
void X(plan_null_destroy)(plan *ego)
{
     UNUSED(ego);
     /* nothing */
}

void X(plan_awake)(plan *ego, enum wakefulness wakefulness)
{
     if (ego) {
	  A(((wakefulness == SLEEPY) ^ (ego->wakefulness == SLEEPY)));
	  
	  LORELIB_CFI_18(ego->adt->awake)(ego, wakefulness);
	  ego->wakefulness = wakefulness;
     }
}


//
// Original code end
//


