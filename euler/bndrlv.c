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

HalfEdge        *hithe;
Vertex          *hitvertex;

int     bndrlv(l, v)
Loop    *l;
Vertex  *v;
{
        HalfEdge        *he;

     he = l->ledg;
    do
    {
        if(contvv(he->vtx, v))
        {
            hitvertex = he->vtx;
            hithe = NIL;
            return(3);
        }
    }
    while((he = he->nxt) != l->ledg);
    he = l->ledg;
    do
    {
        if(contev(he->vtx, he->nxt->vtx, v))
        {
            hitvertex = NIL;
            hithe = he;
            return(2);
        }
    }
    while((he = he->nxt) != l->ledg);
        return(0);
}
