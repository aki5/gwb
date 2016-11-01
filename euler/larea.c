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

double    loopar(l)
Loop    *l;
{
    HalfEdge    *he;
    Vertex      *v1, *v2, *v3;
    vector        aa, bb, cc, dd, normal;

    dd[0] = dd[1] = dd[2] = 0.0;
    faceeq(l, normal);
    he = l->ledg;
    v1 = he->vtx;
    he = he->nxt;
    do
    {
        v2 = he->vtx;
        v3 = he->nxt->vtx;
        aa[0] = v2->vcoord[0] - v1->vcoord[0];
        aa[1] = v2->vcoord[1] - v1->vcoord[1];
        aa[2] = v2->vcoord[2] - v1->vcoord[2];
        bb[0] = v3->vcoord[0] - v1->vcoord[0];
        bb[1] = v3->vcoord[1] - v1->vcoord[1];
        bb[2] = v3->vcoord[2] - v1->vcoord[2];
        cross(cc, aa, bb);
        dd[0] += cc[0];
        dd[1] += cc[1];
        dd[2] += cc[2];
    }
    while((he = he->nxt) != l->ledg);
    return(0.5 * dot(normal, dd));
}
