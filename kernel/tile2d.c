/****************************************************************************
** CFI wrapped code from reading C file 'tile2d__cfic_tmp_new__.c'
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

// decl: void (long, long, long, long, void *)
#define LORELIB_CFI_16(FP) LORELIB_CFI(16, FP)

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

/* out of place 2D copy routines */
#include "kernel/ifftw.h"

void X(tile2d)(INT n0l, INT n0u, INT n1l, INT n1u, INT tilesz,
	       void (*f)(INT n0l, INT n0u, INT n1l, INT n1u, void *args),
	       void *args)
{
     INT d0, d1;

     A(tilesz > 0); /* infinite loops otherwise */
     
 tail:
     d0 = n0u - n0l;
     d1 = n1u - n1l;

     if (d0 >= d1 && d0 > tilesz) {
	  INT n0m = (n0u + n0l) / 2;
	  X(tile2d)(n0l, n0m, n1l, n1u, tilesz, f, args);
	  n0l = n0m; goto tail;
     } else if (/* d1 >= d0 && */ d1 > tilesz) {
	  INT n1m = (n1u + n1l) / 2;
	  X(tile2d)(n0l, n0u, n1l, n1m, tilesz, f, args);
	  n1l = n1m; goto tail;
     } else {
	  LORELIB_CFI_16(f)(n0l, n0u, n1l, n1u, args);
     }
}

INT X(compute_tilesz)(INT vl, int how_many_tiles_in_cache)
{
     return X(isqrt)(CACHESIZE / 
		     (((INT)sizeof(R)) * vl * (INT)how_many_tiles_in_cache));
}

//
// Original code end
//


