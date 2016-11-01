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

Solid   *mvfs(fn, vn, x, y, z)
Id      fn, vn;
float   x, y, z;
{
        Solid           *newsolid;
        Face            *newface;
        Vertex          *newvertex;
        HalfEdge        *newhe;
        Loop            *newloop;

    newsolid = (Solid *) new(SOLID, NIL);
        newface = (Face *) new(FACE, newsolid);
        newloop = (Loop *) new(LOOP, newface);
        newvertex = (Vertex *) new(VERTEX, newsolid);
        newhe = (HalfEdge *) new(HALFEDGE, NIL);

        newface->faceno = fn;
        newface->flout = newloop;
        newloop->ledg = newhe;
    newhe->wloop = newloop;
    newhe->nxt = newhe->prv = newhe;
    newhe->vtx = newvertex;
    newhe->edg = NIL;
        newvertex->vertexno = vn;
        newvertex->vcoord[0] = x;
        newvertex->vcoord[1] = y;
        newvertex->vcoord[2] = z;
        newvertex->vcoord[3] = 1.0;

        return(newsolid);
}
