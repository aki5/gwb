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

# include "gwb.h"

void    sweep(fac, dx, dy, dz)
Face    *fac;
float   dx, dy, dz;
{
        Loop            *l;
        HalfEdge        *first, *scan;
        Vertex          *v;

        getmaxnames(fac->fsolid);
        l = fac->floops;
        while(l)
        {
                first = l->ledg;
                scan = first->nxt;
                v = scan->vtx;
                lmev(scan, scan, ++maxv,
                        v->vcoord[0] + dx,
                        v->vcoord[1] + dy,
                        v->vcoord[2] + dz);
                while(scan != first)
                {
                        v = scan->nxt->vtx;
                        lmev(scan->nxt, scan->nxt, ++maxv,
                                v->vcoord[0] + dx,
                                v->vcoord[1] + dy,
                                v->vcoord[2] + dz);
                        lmef(scan->prv, scan->nxt->nxt, ++maxf);
                        scan = mate(scan->nxt)->nxt;
                }
                lmef(scan->prv, scan->nxt->nxt, ++maxf);
                l = l->nextl;
        }
}
