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

HalfEdge        *addhe(e, v, where, sign)
Edge            *e;
Vertex          *v;
HalfEdge        *where;
int             sign;
{
        HalfEdge        *he;

        if(where->edg == NIL)
        {
                he = where;
        }
        else
        {
                he = (HalfEdge *) new(HALFEDGE, NIL);
                where->prv->nxt = he;
                he->prv = where->prv;
                where->prv = he;
                he->nxt = where;
        }

        he->edg = e;
        he->vtx = v;
        he->wloop = where->wloop;
    if(sign == PLUS)
            e->he1 = he;
    else    e->he2 = he;

    return(he);
}
