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
# define TEST 1

void           join(h1, h2)
HalfEdge       *h1, *h2;
{
        Face    *oldf, *newf;

#ifdef TEST
printf("join edges (%d-%d) (%d-%d)\n",
h1->vtx->vertexno,
h1->nxt->vtx->vertexno,
h2->vtx->vertexno,
h2->nxt->vtx->vertexno);
#ifdef TESTLONG
facels(h1->wloop->lface, 1);
#endif
#endif

    oldf = h1->wloop->lface;
    newf = (Face *) NIL;
    if(h1->wloop == h2->wloop)
        {
                if(h1->prv->prv != h2)
            newf = lmef(h1, h2->nxt, ++maxf);
        }
        else
        {
                lmekr(h1, h2->nxt);
        }
        if(h1->nxt->nxt != h2)
    {
            lmef(h2, h1->nxt, ++maxf);
        if(newf && oldf->floops->nextl)
            laringmv(oldf, newf);
    }
}

void            cut(he)
HalfEdge        *he;
{
        if(he->edg->he1->wloop == he->edg->he2->wloop)
        {
                sonf[nfac++] = he->wloop->lface;
                lkemr(he->edg->he1, he->edg->he2);
        }
        else    lkef(he->edg->he1, he->edg->he2);
}
