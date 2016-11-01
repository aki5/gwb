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

# include    "gwb.h"

void            lkef(h1, h2)
HalfEdge        *h1, *h2;
{
    Face            *f1, *f2;
    Loop            *l, *l1, *l2;
    register HalfEdge    *he;

Solid *s;
s = h1->wloop->lface->fsolid;
    l1 = h1->wloop;
    f1 = l1->lface;
    l2 = h2->wloop;
    f2 = l2->lface;

    while(l = f2->floops)
    {
        dellist(LOOP, (Node *)l, (Node *)f2);
        addlist(LOOP, (Node *)l, (Node *)f1);
    }

    he = l2->ledg;
    do
    {
        he->wloop = l1;
    }
    while((he = he->nxt) != l2->ledg);

    h1->prv->nxt = h2;
    h2->prv->nxt = h1;
    he = h2->prv;
    h2->prv = h1->prv;
    h1->prv = he;

    delhe(h2);
    delhe(h1);

    h2->vtx->vedge = h1->nxt;
    if(!h2->vtx->vedge->edg) h2->vtx->vedge = (HalfEdge *)NIL;
    h1->vtx->vedge = h2->nxt;
    if(!h1->vtx->vedge->edg) h1->vtx->vedge = (HalfEdge *)NIL;

    l1->ledg = h1->nxt;

    del(FACE, (Node *)f2, (Node *)f1->fsolid);
    del(LOOP, (Node *)l2, (Node *)f1);
    del(EDGE, (Node *)h2->edg, (Node *)f1->fsolid);
#ifdef TEST
checkv(s);
#endif
}
