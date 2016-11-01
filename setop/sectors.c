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

# define MAXSECTORS 100

extern struct nb
{
     HalfEdge  *he;
     vector    ref1;
     vector    ref2;
     vector    ref12;
} nba[MAXSECTORS], nbb[MAXSECTORS];

int  sectortest(i, j)
int  i, j;
{
     vector    intrs;
     HalfEdge  *h1, *h2;
     int       c1, c2;

     h1 = nba[i].he;
     h2 = nbb[j].he;

     cross(intrs, h1->wloop->lface->feq, h2->wloop->lface->feq);
     if(vecnull(intrs, EPS))
          return(sectoroverlap(h1, h2));
     c1 = sctrwithin(intrs, nba[i].ref1, nba[i].ref2, nba[i].ref12);
     c2 = sctrwithin(intrs, nbb[j].ref1, nbb[j].ref2, nbb[j].ref12);
     if(c1 && c2) return(1);
     else
     {
     intrs[0] = -intrs[0];
     intrs[1] = -intrs[1];
     intrs[2] = -intrs[2];
     c1 = sctrwithin(intrs, nba[i].ref1, nba[i].ref2, nba[i].ref12);
     c2 = sctrwithin(intrs, nbb[j].ref1, nbb[j].ref2, nbb[j].ref12);
     if(c1 && c2) return(1);
     }
     return(0);
}

int          sctrwithin(dir, ref1, ref2, ref12)
vector       dir, ref1, ref2, ref12;
{
     vector  c1, c2;
     int     t1, t2;

     cross(c1, ref1, dir);
     if(vecnull(c1, EPS))
          return(dot(ref1, dir) > 0.0);
     cross(c2, dir, ref2);
     if(vecnull(c2, EPS))
          return(dot(ref2, dir) > 0.0);
     t1 = comp(dot(c1, ref12), 0.0, EPS*EPS);
     t2 = comp(dot(c2, ref12), 0.0, EPS*EPS);
     return(t1>0 && t2>0);
}

int             sectoroverlap(h1, h2)
HalfEdge        *h1, *h2;
{
         return(1);
}
