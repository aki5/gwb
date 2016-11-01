#

/*
**    Geometric WorkBench
**
**    Copyright (c) 1988
**    Martti Mantyla, Helsinki University of Technology
**
**    This software is NOT released to public domain, but a
**    permission is granted to inspect the code and use it, or
**    portions of it for research or educational purposes, provided
**    that this notice is not removed or modified.  Commercial
**    exploitation is disallowed.
**
**    THE SOFTWARE IS PROVIDED "AS IS" WITH NO WARRANTY OF ANY KIND.
**    THE AUTHOR SPECIFICALLY DISCLAIMS ANY EXPRESS OR IMPLIED
**    WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE AND ANY WARRANTY
**    OF MERCHANTABILITY.
*/

# include "setop.h"

void    setopclassify(op)
int     op;
{
        int     i;

        nedga = nedgb = 0;
    for(i=0; i<nvtxa; i++)
                vtxfacclassify(sonva[i].v, sonva[i].f, op, 0);
    for(i=0; i<nvtxb; i++)
                vtxfacclassify(sonvb[i].v, sonvb[i].f, op, 1);
    for(i=0; i<nvtx; i++)
                vtxvtxclassify(sonvv[i].va, sonvv[i].vb, op);
}
