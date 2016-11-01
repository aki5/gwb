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

double  svolume(s)
Solid   *s;
{
        Face            *f;
        Loop            *l;
        HalfEdge        *he1, *he2;
        vector          c;
        double          res;

        res = 0.0;
        f = s->sfaces;
        while(f)
        {
                l = f->floops;
                while(l)
                {
                        he1 = l->ledg;
                        he2 = he1->nxt;
                        do
                        {
                                cross(c, he2->vtx->vcoord,
                                        he1->vtx->vcoord);
                                res += dot(he2->nxt->vtx->vcoord, c)

                                         / 6.0;
                        }
                        while((he2 = he2->nxt) != he1);
                        l = l->nextl;
                }
                f = f->nextf;
        }
        return(res);
}
