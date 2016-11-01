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

int    mef(s, vert1, vert2, fac1, fac2)
Solid    *s;
Id    vert1, vert2;
Id    fac1, fac2;
{
    Face            *oldface, *newface;
    register HalfEdge    *he1, *he2;

    if(!(oldface = fface(s, fac1)))
    {
        fprintf(stderr, "mef: face %d not found\n", fac1);
        return(ERROR);
    }

    /* get vert1 */
    if(!(he1 = fhe1(oldface, vert1)))
    {
        fprintf(stderr, "mef: vertex %d not found\n", vert1);
        return(ERROR);
    }

    /* get the next occurance of vert2 */
    he2 = he1;
    if(he2->vtx->vertexno != vert2)
    do
    {
        he2 = he2->nxt;
        if(he2 == he1)
        {
            fprintf(stderr, "mef: vertex %d not found\n",
                vert2);
            return(ERROR);
        }
    }
    while(he2->vtx->vertexno != vert2);

    newface = lmef(he1, he2, fac2);

    return(SUCCESS);
}
