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

Face    *fface(s, fn)
Solid   *s;
Id      fn;
{
        Face    *f;

        f = s->sfaces;
        while(f)
        {
                if(f->faceno == fn)
                        return(f);
                f = f->nextf;
        }
        return((Face *) NIL);
}

HalfEdge        *fhe1(f, vn)
Face            *f;
Id              vn;
{
        Loop        *l;
    HalfEdge    *h;

    l = f->floops;
    while(l)
    {
        h = l->ledg;
        do
        {
            if(h->vtx->vertexno == vn)
                return(h);
        }
        while((h = h->nxt) != l->ledg);
        l = l->nextl;
    }
    return((HalfEdge *) NIL);
}

HalfEdge        *fhe2(f, vn1, vn2)
Face            *f;
Id              vn1, vn2;
{
        Loop        *l;
    HalfEdge    *h;

    l = f->floops;
    while(l)
    {
        h = l->ledg;
        do
        {
            if(h->vtx->vertexno == vn1 &&
               h->nxt->vtx->vertexno == vn2)
                return(h);
        }
        while((h = h->nxt) != l->ledg);
        l = l->nextl;
    }
    return((HalfEdge *) NIL);
}
