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

void    aringmv(), lringmv(), laringmv();

void    ringmv(s, v1, v2, f1, f2, out)
Solid    *s;
int    v1, v2, f1, f2;
int    out;
{
    Face        *ff1, *ff2;
    HalfEdge    *dum;

    ff1 = fface(s, f1);
    ff2 = fface(s, f2);
    if(v2) dum = fhe2(ff1, v1, v2);
    else   dum = fhe1(ff1, v1);
    if(!dum)
    {
        fprintf(stderr, "ringmv: no edge <%d,%d> found in face %d\n",
            v1, v2, f1);
        abort();
    }
    lringmv(ff1, ff2, dum->wloop, out);
}

void    lringmv(f1, f2, l, out)
Face    *f1, *f2;
Loop    *l;
int    out;
{
    dellist(LOOP, l, f1);
    addlist(LOOP, l, f2);
    if(out) f2->flout = l;
}

void    aringmv(s, f1, f2)
Solid    *s;
int    f1, f2;
{
    laringmv(fface(s, f1), fface(s, f2));
}

void    laringmv(f1, f2)
Face    *f1, *f2;
{
    vector        tmp;
    int        drop, in;
    Loop        *ring;
    Loop        *l;

    faceeq(f1->flout, f1->feq);
    drop = dropcoord(f1->feq);
    l = f1->floops;
    while(l)
    {
        if((ring = l) != f1->flout)
        {
            l = l->nextl;
            in = contfv2(f1, ring->ledg->vtx, drop);
            if(!in)
            {
                dellist(LOOP, ring, f1);
                addlist(LOOP, ring, f2);
            }
        }
        else l = l->nextl;
    }
}
