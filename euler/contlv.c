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

int    contlv(l, v, drop)
Loop    *l;
Vertex    *v;
int    drop;
{
    HalfEdge    *he1, *he2;
    Vertex         aux;
    double        t1, t2;
    int        intersections, intr, c1, c2;

#ifdef TEST
printf("contlv: vertex %d vs. face %d\n", v->vertexno, l->lface->faceno);
#endif
    if((intr = bndrlv(l, v)) > 0)
               return(intr);

    he2 = l->ledg;
label:
    aux.vcoord[0] = (he2->vtx->vcoord[0] + he2->nxt->vtx->vcoord[0]) / 2.0;
    aux.vcoord[1] = (he2->vtx->vcoord[1] + he2->nxt->vtx->vcoord[1]) / 2.0;
    aux.vcoord[2] = (he2->vtx->vcoord[2] + he2->nxt->vtx->vcoord[2]) / 2.0;
    he1 = l->ledg;
    intersections = 0;
    do
    {
        intr = int2ee(v, &aux, he1->vtx, he1->nxt->vtx,
                              drop, &t1, &t2);
        if(intr == 1)
        {
            c1 = comp(t2, 0.0, EPS);
            c2 = comp(t2, 1.0, EPS);
            if(c1 == 0 || c2 == 0)
            {
                he2 = he2->nxt;
                if(he2 == l->ledg) return(ERROR);
                goto label;
            }
            if(c1 == 1 && c2 == -1)
                if(t1 >= 0.0) intersections++;
        }
    }
    while((he1 = he1->nxt) != l->ledg);
#ifdef TEST
printf("contlv: intersections = %d\n", intersections);
#endif
    intersections = intersections % 2;
    return(intersections);
}
