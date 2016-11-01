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

# include "setop.h"

void    cuta(), cutb();

void    setopconnect()
{
        Edge            *nextedgea, *nextedgeb;
        HalfEdge        *h1a, *h2a, *h1b, *h2b;

        nfaca = nfacb = 0;
        ssortnulledges();
        while(sgetnextnulledge(&nextedgea, &nextedgeb))
        {
                if(scanjoin(nextedgea->he1, nextedgeb->he2, &h1a, &h2b))
                {
                        join(h1a, nextedgea->he1);
                        if(!isloosea(mate(h1a)))
                                cuta(h1a);
                        join(h2b, nextedgeb->he2);
                        if(!islooseb(mate(h2b)))
                                cutb(h2b);
                }
                if(scanjoin(nextedgea->he2, nextedgeb->he1, &h2a, &h1b))
                {
                        join(h2a, nextedgea->he2);
                        if(!isloosea(mate(h2a)))
                                cuta(h2a);
                        join(h1b, nextedgeb->he1);
                        if(!islooseb(mate(h1b)))
                                cutb(h1b);
                }
                if(h1a && h1b && h2a && h2b)
                {
                        cuta(nextedgea->he1);
                        cutb(nextedgeb->he1);
                }
        }
}

static HalfEdge *endsa[30];
static HalfEdge *endsb[30];
static int      nenda;
static int      nendb;

int             scanjoin(hea, heb, reta, retb)
HalfEdge        *hea, *heb, **reta, **retb;
{
        int             i, j;

#ifdef TEST
printf("scanjoin: (%d,%d) (%d,%d)\n",
hea->vtx->vertexno, hea->nxt->vtx->vertexno,
heb->vtx->vertexno, heb->nxt->vtx->vertexno);
#endif
        for(i = 0; i<nenda; i++)
        {
#ifdef TEST
printf("vs. (%d,%d) (%d,%d): %d %d\n",
endsa[i]->vtx->vertexno, endsa[i]->nxt->vtx->vertexno,
endsb[i]->vtx->vertexno, endsb[i]->nxt->vtx->vertexno,
neighbor(hea, endsa[i]), neighbor(heb, endsb[i]));
#endif
                if(neighbor(hea, endsa[i]) && neighbor(heb, endsb[i]))
                {
                        *reta = endsa[i];
                        *retb = endsb[i];
                        for(j=i+1; j<nenda; j++)
                        {
                                endsa[j-1] = endsa[j];
                                endsb[j-1] = endsb[j];
                        }
                        nenda--;
                        nendb--;
                        return(1);
                }
        }
        endsa[nenda++] = hea;
        endsb[nendb++] = heb;
        *reta = NIL;
        *retb = NIL;
        return(0);
}

int             isloosea(he)
HalfEdge        *he;
{
        register int    i;

        for(i=0; i<nenda; i++)
               if(endsa[i] == he)
                       return(1);
        return(0);
}

int             islooseb(he)
HalfEdge        *he;
{
        register int    i;

        for(i=0; i<nendb; i++)
               if(endsb[i] == he)
                       return(1);
        return(0);
}

void            cuta(he)
HalfEdge        *he;
{
        if(he->edg->he1->wloop == he->edg->he2->wloop)
        {
                sonfa[nfaca++] = he->wloop->lface;
                lkemr(he->edg->he2, he->edg->he1);
        }
        else    lkef(he->edg->he1, he->edg->he2);
}

void            cutb(he)
HalfEdge        *he;
{
        if(he->edg->he1->wloop == he->edg->he2->wloop)
        {
                sonfb[nfacb++] = he->wloop->lface;
                lkemr(he->edg->he2, he->edg->he1);
        }
        else    lkef(he->edg->he1, he->edg->he2);
}
