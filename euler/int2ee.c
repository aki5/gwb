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

int     int2ee(v1, v2, v3, v4, drop, t1, t2)
Vertex  *v1, *v2, *v3, *v4;
int     drop;
double  *t1, *t2;
{
        double  D1, D2, D, a1, a2, b1, b2, c1, c2;

        switch(drop)
        {
                case X:
                        a1 = v2->vcoord[1] - v1->vcoord[1];
                        a2 = v2->vcoord[2] - v1->vcoord[2];
                        b1 = v3->vcoord[1] - v4->vcoord[1];
                        b2 = v3->vcoord[2] - v4->vcoord[2];
                        break;
                case Y:
                        a1 = v2->vcoord[0] - v1->vcoord[0];
                        a2 = v2->vcoord[2] - v1->vcoord[2];
                        b1 = v3->vcoord[0] - v4->vcoord[0];
                        b2 = v3->vcoord[2] - v4->vcoord[2];
                        break;
                case Z:
                        a1 = v2->vcoord[0] - v1->vcoord[0];
                        a2 = v2->vcoord[1] - v1->vcoord[1];
                        b1 = v3->vcoord[0] - v4->vcoord[0];
                        b2 = v3->vcoord[1] - v4->vcoord[1];
                        break;
        }

        D = a1*b2 - a2*b1;
        if(comp(D, 0.0, EPS) == 0)
                return(0);
        else
        {
                switch(drop)
                {
                        case X:
                                c1 = v1->vcoord[1] - v3->vcoord[1];
                                c2 = v1->vcoord[2] - v3->vcoord[2];
                                break;
                        case Y:
                                c1 = v1->vcoord[0] - v3->vcoord[0];
                                c2 = v1->vcoord[2] - v3->vcoord[2];
                                break;
                        case Z:
                                c1 = v1->vcoord[0] - v3->vcoord[0];
                                c2 = v1->vcoord[1] - v3->vcoord[1];
                                break;
                }
                D1 = c2*b1 - c1*b2;
                D2 = a2*c1 - a1*c2;
                *t1 = D1/D;
                *t2 = D2/D;
                return(1);
        }
}
