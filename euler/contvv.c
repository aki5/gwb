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

int    contvv(v1, v2)
Vertex    *v1, *v2;
{
    double    v[3];
    double    diff;

    v[0] = v1->vcoord[0] - v2->vcoord[0];
    v[1] = v1->vcoord[1] - v2->vcoord[1];
    v[2] = v1->vcoord[2] - v2->vcoord[2];

    diff = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    return(diff < EPS);
}
