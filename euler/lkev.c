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

void            lkev(he1, he2)
HalfEdge        *he1, *he2;
{
    HalfEdge     *he;

#ifdef TEST
Solid *s;
s = he1->wloop->lface->fsolid;
#endif
    he = he2->nxt;
    while(he != he1)
    {
        he->vtx = he2->vtx;
        he = mate(he)->nxt;
    }

    he1->wloop->ledg = delhe(he1);
    he2->wloop->ledg = delhe(he2);
    he2->vtx->vedge = he2->nxt;
    if(!he2->vtx->vedge->edg) he2->vtx->vedge = (HalfEdge *)NIL;

    del(EDGE, (Node *)he1->edg, (Node *)he1->wloop->lface->fsolid);
    del(VERTEX, (Node *)he1->vtx, (Node *)he1->wloop->lface->fsolid);
#ifdef TEST
checkv(s);
#endif
}
