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

void           lmekr(he1, he2)
HalfEdge       *he1, *he2;
{
    Edge            *n_ed;
    register HalfEdge    *n_he1, *n_he2;
    Face            *f;
    Loop            *l1, *l2;

    l1 = he1->wloop;
    l2 = he2->wloop;
    f = l1->lface;

    n_he1 = l2->ledg;
    do
    {
        n_he1->wloop = l1;
    }
    while((n_he1 = n_he1->nxt) != l2->ledg);

    n_ed = (Edge *) new(EDGE, f->fsolid);

    n_he1 = addhe(n_ed, he1->vtx, he1, PLUS);
    n_he2 = addhe(n_ed, he2->vtx, he2, MINUS);

    n_he1->nxt = he2;
    n_he2->nxt = he1;
    he2->prv = n_he1;
    he1->prv = n_he2;

    if(f->flout == l2) f->flout = l1;

    del(LOOP, l2, l2->lface);
}
