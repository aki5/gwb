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

# include "split.h"

void    classify(S, Above, Below)
Solid   *S, *Above, *Below;
{
        int             i;

        for(i = 0; i < nfac; i++)
        {
                movefac(sonf[i], Above);
                movefac(sonf[nfac+i], Below);
        }
}

void    movefac(f, s)
Face    *f;
Solid   *s;
{
        Loop            *l;
        HalfEdge        *he;
        Face            *f2;

        dellist(FACE, f, f->fsolid);
        addlist(FACE, f, s);
        l = f->floops;
        while(l)
        {
                he = l->ledg;
                do
                {
                        f2 = mate(he)->wloop->lface;
                        if(f2->fsolid != s)
                                movefac(f2, s);
                }
                while((he = he->nxt) != l->ledg);
                l = l->nextl;
        }
}
