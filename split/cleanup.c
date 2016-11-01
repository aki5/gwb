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

void    cleanup(s)
Solid    *s;
{
    Face        *f;
    Loop        *l;
    HalfEdge    *h;

    s->sedges = (Edge *) NIL;
    s->sverts = (Vertex *) NIL;
    f = s->sfaces;
    while(f)
    {
        l = f->floops;
        while(l)
        {
            h = l->ledg;
            do
            {
                if(h->edg != NIL)
                {
                    if(h == h->edg->he1)
                    {
                        addlist(EDGE, h->edg, s);
#ifdef TEST
printf("cleanup: add edge %d %d\n", h->vtx->vertexno, mate(h)->vtx->vertexno);
#endif
                    }
                    if(h == h->vtx->vedge)
                    {
                        addlist(VERTEX, h->vtx, s);
#ifdef TEST
printf("cleanup: add vertex %d\n", h->vtx->vertexno);
#endif
                    }
                }
                else
                {
                    addlist(VERTEX, h->vtx, s);
#ifdef TEST
printf("cleanup: add lone vertex %d\n", h->vtx->vertexno);
#endif
                }
                h = h->nxt;
            }
            while(h != l->ledg);
            l = l->nextl;
        }
        f = f->nextf;
    }
}
