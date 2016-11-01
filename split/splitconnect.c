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

void    splitconnect()
{
        Edge            *nextedge, *getnextnulledge();
    HalfEdge        *h1, *h2, *canjoin();

        nfac = 0;
        sortnulledges();
        while(nextedge = getnextnulledge())
        {
        if(h1 = canjoin(nextedge->he1))
        {
            join(h1, nextedge->he1);
            if(!isloose(mate(h1)))
                cut(h1);
        }
        if(h2 = canjoin(nextedge->he2))
        {
            join(h2, nextedge->he2);
            if(!isloose(mate(h2)))
                cut(h2);
        }
        if(h1 && h2)
        {
            cut(nextedge->he1);
        }
        }
}

static HalfEdge *ends[30];
static int      nend;

HalfEdge        *canjoin(he)
HalfEdge    *he;
{
    HalfEdge    *ret;
        int             i, j;

    for(i = 0; i<nend; i++)
            if(neighbor(he, ends[i]))
        {
            ret = ends[i];
            for(j=i+1; j<nend; j++)
                ends[j-1] = ends[j];
            nend--;
            return(ret);
        }
        ends[nend++] = he;
    return((HalfEdge *) NIL);
}

int             isloose(he)
HalfEdge        *he;
{
        register int    i;

    for(i=0; i<nend; i++)
           if(ends[i] == he)
               return(1);
    return(0);
}
