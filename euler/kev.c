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

# include    "gwb.h"

int     kev(s, fnr, v1, v2)
Solid   *s;
Id      fnr, v1, v2;
{
    Face            *f;
    register HalfEdge    *he1, *he2;

    /* find needed objects, check existence */
    if(!(f = fface(s, fnr)))
    {
        fprintf(stderr, "kev: face %d not found\n", fnr);
        return(ERROR);
    }
    if(!(he1 = fhe2(f, v1, v2)))
    {
        fprintf(stderr, "kev: edge %d-%d not found\n", v1, v2);
        return(ERROR);
    }

    he2 = mate(he1);

    /* check that edge occurs in only one loop */
    if(he1->wloop != he2->wloop)
    {
        fprintf(stderr, "kev: edge %d-%d not in same loop\n", v1, v2);
        return(ERROR);
    }

    /* check that v2 is an endpoint */
    if(he1->nxt != he2)
    {
        fprintf(stderr, "kev: vertex %d is not an endpoint\n", v2);
        return(ERROR);
    }

    /* call lkev() to do the real work */
    lkev(he2, he1);

    return(SUCCESS);
}
