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

int    contfv(f, v)
Face    *f;
Vertex    *v;
{
    int    drop;

    faceeq(f->flout, f->feq);
    drop = dropcoord(f->feq);
    return(contfv2(f, v, drop));
}

int    contfv2(f, v, drop)
Face    *f;
Vertex    *v;
int    drop;
{
    Loop    *l;
    int    cont;

    cont = contlv(f->flout, v, drop);

    if(cont == 0)
        return(0);
    if(cont > 1)
        return(cont);

    l = f->floops;
    while(l)
    {
        if((l != f->flout) && l->ledg->nxt->nxt != l->ledg)
        {
            cont = contlv(l, v, drop);
            if(cont == 1) return(0);
            if(cont > 1) return(cont);
        }
        l = l->nextl;
    }
    return(1);
}
