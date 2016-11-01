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

void            lmev(he1, he2, vn, x, y, z)
HalfEdge        *he1, *he2;
Id              vn;
float           x, y, z;
{
        HalfEdge        *he;
        Vertex          *newvertex;
        Edge            *newedge;

#ifdef TEST
Solid *s;
s = he1->wloop->lface->fsolid;
#endif
        newedge = (Edge *) new(EDGE, he1->wloop->lface->fsolid);
        newvertex = (Vertex *) new(VERTEX, he1->wloop->lface->fsolid);
        newvertex->vcoord[0] = x;
        newvertex->vcoord[1] = y;
        newvertex->vcoord[2] = z;
        newvertex->vcoord[3] = 1.0;
        newvertex->vertexno = vn;

        he = he1;
        while(he != he2)
        {
                he->vtx = newvertex;
                he = mate(he)->nxt;
        }

        addhe(newedge, he2->vtx, he1, MINUS);
        addhe(newedge, newvertex, he2, PLUS);

        newvertex->vedge = he2->prv;
        he2->vtx->vedge = he2;
#ifdef TEST
checkv(s);
#endif
}
