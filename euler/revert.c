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

void    revert(s)
Solid    *s;
{
    Face             *f;
    Loop            *l;
    register HalfEdge    *he, *henxt;
    Vertex            *prev, *sav;

    f = s->sfaces;
    while(f)
    {
        l = f->floops;
        while(l)
        {
            he = l->ledg;
            do
            {
                /* revert the direction */
                henxt = he->nxt;
                he->nxt = he->prv;
                he->prv = henxt;
                he = henxt;
            }
            while(he != l->ledg);
            prev = he->prv->vtx;
            do
            {
                sav = he->vtx;
                he->vtx = prev;
                he->vtx->vedge = he;
                prev = sav;
                he = he->nxt;
            }
            while(he != l->ledg);
            l = l->nextl;
        }
        f = f->nextf;
    }
}
