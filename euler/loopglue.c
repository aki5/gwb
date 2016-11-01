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

void    loopglue(fac)
Face    *fac;
{
        HalfEdge        *h1, *h2, *h1next;

#ifdef TEST
Solid *s;
s = fac->fsolid;
#endif

        h1 = fac->floops->ledg;
        h2 = fac->floops->nextl->ledg;
        while(!match(h1, h2)) h2 = h2->nxt;
        lmekr(h1, h2);
#ifdef TEST
printf("lmekr: "); solidls(s, 2);
#endif
        lkev(h1->prv, h2->prv);
#ifdef TEST
printf("lkev: "); solidls(s, 2);
#endif
        while(h1->nxt != h2)
        {
                h1next = h1->nxt;
                lmef(h1->nxt, h1->prv, -1);
#ifdef TEST
printf("lmef: "); solidls(s, 2);
#endif
                lkev(h1->nxt, mate(h1->nxt));
#ifdef TEST
printf("lkev: "); solidls(s, 2);
#endif
                lkef(mate(h1), h1);
#ifdef TEST
printf("lkef: "); solidls(s, 2);
#endif
                h1 = h1next;
        }
        lkef(mate(h1), h1);
#ifdef TEST
printf("lkef: "); solidls(s, 2);
#endif
}

int             match(h1, h2)
HalfEdge        *h1, *h2;
{
        return(contvv(h1->vtx, h2->vtx));
}
