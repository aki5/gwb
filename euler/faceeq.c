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

int     faceeq(l, eq)
Loop    *l;
vector  eq;
{
        HalfEdge        *he;
        double          a, b, c, norm;
        double          xi, yi, zi, xj, yj, zj, xc, yc, zc;
        int             length;

        a = b = c = xc = yc = zc = 0.0;
        length = 0;
        he = l->ledg;
        do
        {
                xi = he->vtx->vcoord[0];
                yi = he->vtx->vcoord[1];
                zi = he->vtx->vcoord[2];
                xj = he->nxt->vtx->vcoord[0];
                yj = he->nxt->vtx->vcoord[1];
                zj = he->nxt->vtx->vcoord[2];
                a += (yi - yj) * (zi + zj);
                b += (zi - zj) * (xi + xj);
                c += (xi - xj) * (yi + yj);
                xc += xi;
                yc += yi;
                zc += zi;
                length++;
        }
        while((he = he->nxt) != l->ledg);

        if((norm = sqrt(a*a + b*b + c*c)) != 0.0)
        {
                eq[0] = a / norm;
                eq[1] = b / norm;
                eq[2] = c / norm;
                eq[3] = (eq[0]*xc + eq[1]*yc + eq[2]*zc) / (-length);
        return(SUCCESS);
        }
        else
        {
                printf("faceeq: null face %d\n", l->lface->faceno);
                return(ERROR);
        }
}
