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

# define MAXSECTORS 100

/*
# define OUT 1
# define IN -1
# define ON 0
*/
# define OUT -1
# define IN 1
# define ON 0

extern struct nb
{
    HalfEdge    *he;
    vector        ref1;
    vector        ref2;
    vector        ref12;
} nba[MAXSECTORS], nbb[MAXSECTORS];
extern int    nnba, nnbb;

extern struct
{
        int        secta, sectb;
    int             s1a, s2a;
    int             s1b, s2b;
    int             intersect;
}       sectors[MAXSECTORS];
extern int    nsectors;

void    sinsertnulledges()
{
    HalfEdge    *ha1, *ha2, *hb1, *hb2;
    int         i = 0;

    while(1)
    {
        while(sectors[i].intersect == 0)
            if(++i == nsectors) return;
        if(sectors[i].s1a == OUT)
                ha1 = nba[sectors[i].secta].he;
    else    ha2 = nba[sectors[i].secta].he;
        if(sectors[i].s1b == IN)
                hb1 = nbb[sectors[i++].sectb].he;
    else    hb2 = nbb[sectors[i++].sectb].he;

        while(sectors[i].intersect == 0)
            if(++i == nsectors) return;
        if(sectors[i].s1a == OUT)
                ha1 = nba[sectors[i].secta].he;
    else    ha2 = nba[sectors[i].secta].he;
        if(sectors[i].s1b == IN)
                hb1 = nbb[sectors[i++].sectb].he;
    else    hb2 = nbb[sectors[i++].sectb].he;

        if(ha1 == ha2)
        {
            separ2(ha1, 0, getorient(ha1, hb1, hb2));
            separ1(hb1, hb2, 1);
        }
        else if(hb1 == hb2)
        {
            separ2(hb1, 1, getorient(hb1, ha2, ha1));
            separ1(ha2, ha1, 0);
        }
        else
        {
            separ1(ha2, ha1, 0);
            separ1(hb1, hb2, 1);
        }
        if(i == nsectors) return;
    }
}

int             getorient(ref, he1, he2)
HalfEdge        *ref, *he1, *he2;
{
        HalfEdge        *mhe1, *mhe2;
        int             retcode;

        mhe1 = mate(he1)->nxt;
        mhe2 = mate(he2)->nxt;
        if(mhe1 != he2 && mhe2 == he1)
                retcode = convexedg(he2);
        else    retcode = convexedg(he1);
        if(sectorwide(mhe1, 0) == 1 && sectorwide(ref, 0) == 1)
                retcode = 1-retcode;
        return(1-retcode);
}

int              convexedg(he)
HalfEdge         *he;
{
        HalfEdge        *h2;
        vector          dir, cr;

        h2 = he->nxt;
        if(nulledge(he)) h2 = h2->nxt;
        vecminus(dir, h2->vtx->vcoord, he->vtx->vcoord);
        cross(cr, he->wloop->lface->feq, mate(he)->wloop->lface->feq);
        if(vecnull(cr, EPS)) return(1);
        return(dot(dir, cr) < 0.0);
}

vector       ref1[2], ref2[2], ref12[2];

int          sectorwide(he, ind)
HalfEdge     *he;
int          ind;
{
      vecminus(ref1[ind], he->prv->vtx->vcoord, he->vtx->vcoord);
      vecminus(ref2[ind], he->nxt->vtx->vcoord, he->vtx->vcoord);
      cross(ref12[ind], ref1[ind], ref2[ind]);
      if(vecnull(ref12[ind], EPS)) return(1);
      return((dot(ref12[ind], he->wloop->lface->feq) > 0.0) ? 0 : 1 /*1 : 0*/);
}
