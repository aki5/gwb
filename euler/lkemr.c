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

void            lkemr(h1, h2)
HalfEdge        *h1, *h2;
{
    register HalfEdge    *h3, *h4;
    Loop            *nl;
    Loop            *ol;
    Edge            *killedge;

#ifdef TEST
Solid *s;
s = h1->wloop->lface->fsolid;
#endif
    ol = h1->wloop;
    nl = (Loop *) new(LOOP, (Node *)ol->lface);
    killedge = h1->edg;

    h3 = h1->nxt;
    h1->nxt = h2->nxt;
    h2->nxt->prv = h1;
    h2->nxt = h3;
    h3->prv = h2;

    h4 = h2;
    do
    {
        h4->wloop = nl;
    }
    while((h4 = h4->nxt) != h2);

    ol->ledg = h3 = delhe(h1);
    nl->ledg = h4 = delhe(h2);

    h3->vtx->vedge = (h3->edg) ? h3 : (HalfEdge *)NIL;
    h4->vtx->vedge = (h4->edg) ? h4 : (HalfEdge *)NIL;
    h3->nxt->vtx->vedge = (h3->nxt->edg) ? h3->nxt : (HalfEdge *)NIL;
    h4->nxt->vtx->vedge = (h4->nxt->edg) ? h4->nxt : (HalfEdge *)NIL;

    del(EDGE, (Node *)killedge, ol->lface->fsolid);
#ifdef TEST
checkv(s);
#endif
}
