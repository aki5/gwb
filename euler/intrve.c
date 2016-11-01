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

int     intrve(v1, v2, v3, t)
Vertex  *v1, *v2, *v3;
double  *t;
{
        Vertex  testv;
        float   r1[3], r2[3], r1r1, tprime;

        r1[0] = v2->vcoord[0] - v1->vcoord[0];
        r1[1] = v2->vcoord[1] - v1->vcoord[1];
        r1[2] = v2->vcoord[2] - v1->vcoord[2];

        r1r1 = dot(r1, r1);
        if(r1r1 < EPS*EPS)
        {
                *t = 0.0;
                return(contvv(v1, v3));
        }
        else
        {
                r2[0] = v3->vcoord[0] - v1->vcoord[0];
                r2[1] = v3->vcoord[1] - v1->vcoord[1];
                r2[2] = v3->vcoord[2] - v1->vcoord[2];
                tprime = dot(r1, r2) / r1r1;
                testv.vcoord[0] = v1->vcoord[0] + tprime * r1[0];
                testv.vcoord[1] = v1->vcoord[1] + tprime * r1[1];
                testv.vcoord[2] = v1->vcoord[2] + tprime * r1[2];
                *t = tprime;
                return(contvv(&testv, v3));
        }
}

int     contev(v1, v2, v3)
Vertex  *v1, *v2, *v3;
{
        double  t;

        if(intrve(v1, v2, v3, &t))
                if(t >= (-EPS) && t <= (1.0+EPS))
                        return(1);
        return(0);
}
