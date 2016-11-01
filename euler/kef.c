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

int     kef(s, v1, v2, fno)
Solid   *s;
Id      v1, v2, fno;
{
    Face        *f;
    HalfEdge    *he;

    /* find the objects, check that they exist */
    if(!(f = fface(s, fno)))
    {
        fprintf(stderr, "kef: face %d not found\n", fno);
        return(ERROR);
    }

    if(!(he = fhe2(f, v1, v2)))
        if(!(he = fhe2(f, v2, v1)))
        {
            fprintf(stderr, "kef: edge %d-%d not found\n", v1, v2);
            return(ERROR);
        }


    /* call lkef() to do the real job */
    lkef(he, mate(he));

    return(SUCCESS);
}
