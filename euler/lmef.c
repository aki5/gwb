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

Face            *lmef(he1, he2, nf)
HalfEdge        *he1, *he2;
Id        nf;
{
        Face            *newface;
        Loop            *newloop;
        Edge            *newedge;
        HalfEdge        *he, *nhe1, *nhe2, *temp;

        newface = (Face *)new(FACE, he1->wloop->lface->fsolid);
        newloop = (Loop *)new(LOOP, newface);
        newedge = (Edge *)new(EDGE, he1->wloop->lface->fsolid);
        newface->faceno = nf;
        newface->flout = newloop;

        he = he1;
        while(he != he2)
        {
                he->wloop = newloop;
                he = he->nxt;
        }

        nhe1 = addhe(newedge, he2->vtx, he1, MINUS);
        nhe2 = addhe(newedge, he1->vtx, he2, PLUS);

        nhe1->prv->nxt = nhe2;
        nhe2->prv->nxt = nhe1;
        temp = nhe1->prv;
        nhe1->prv = nhe2->prv;
        nhe2->prv = temp;

        newloop->ledg = nhe1;
        he2->wloop->ledg = nhe2;

    return(newface);
}
