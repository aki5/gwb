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

int     mev(s, fn, vn1, vn2, x, y, z)
Solid   *s;
Id      fn, vn1, vn2;
float   x, y, z;
{
        Face            *oldface;
        HalfEdge        *he;

        if((oldface = fface(s, fn)) == NIL)
        {
                fprintf(stderr,
                        "mev: face %d not found\n", fn);
                return(ERROR);
        }
        if((he = fhe1(oldface, vn1)) == NIL)
        {
                fprintf(stderr,
                        "mev: vertex %d not found in face %d\n",
                                 vn1, fn);
                return(ERROR);
        }

        lmev(he, he, vn2, x, y, z);

        return(SUCCESS);
}
