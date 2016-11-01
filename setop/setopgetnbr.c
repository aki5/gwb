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

void      setopgetneighborhood(va, vb)
Vertex    *va, *vb;
{
     HalfEdge   *ha, *hb;
     double     d1, d2, d3, d4;
     int        na, nb, i, j;

     nnba = nbr_preproc(va, nba);
     nnbb = nbr_preproc(vb, nbb);
     nsectors = 0;
     for(i=0; i<nnba; i++)
     {
          for(j=0; j<nnbb; j++)
          {
               if(sectortest(i, j))
               {
                    ha = nba[i].he;
                    hb = nbb[j].he;
            d1 = dot(hb->wloop->lface->feq, nba[i].ref1);
                    d2 = dot(hb->wloop->lface->feq, nba[i].ref2);
                    d3 = dot(ha->wloop->lface->feq, nbb[j].ref1);
                    d4 = dot(ha->wloop->lface->feq, nbb[j].ref2);
                    sectors[nsectors].secta = i;
                    sectors[nsectors].sectb = j;
                    sectors[nsectors].s1a = comp(d1, 0.0, EPS);
                    sectors[nsectors].s2a = comp(d2, 0.0, EPS);
                    sectors[nsectors].s1b = comp(d3, 0.0, EPS);
                    sectors[nsectors].s2b = comp(d4, 0.0, EPS);
                    sectors[nsectors++].intersect = 1;
                }
           }
     }
}

int               nbr_preproc(v, n)
Vertex            *v;
struct nb         n[];
{
     vector       bisec;
     HalfEdge     *he;
     int          i;

     i = 0;
     he = v->vedge;
     do
     {
          n[i].he = he;
      vecminus(n[i].ref1, he->prv->vtx->vcoord, he->vtx->vcoord);
          vecminus(n[i].ref2, he->nxt->vtx->vcoord, he->vtx->vcoord);
          cross(n[i].ref12, n[i].ref1, n[i].ref2);
          /* check for "wide" sectors */
      if(vecnull(n[i].ref12, EPS) ||
         (dot(n[i].ref12, he->wloop->lface->feq) > 0.0))
      {
           /* wide sector! subdivide it into two non-wide ones */

           /* form the bisector of the wide sector */
           if(vecnull(n[i].ref12, EPS))
                inside(he, bisec);
           else
           {
                vecplus(bisec, n[i].ref1, n[i].ref2);
            bisec[0] = -bisec[0];
            bisec[1] = -bisec[1];
            bisec[2] = -bisec[2];
           }

           /* store the two small sectors ref1-bisec and bisec-ref2 */
               n[i+1].he = he;
           veccopy(n[i+1].ref2, n[i].ref2);
           veccopy(n[i+1].ref1, bisec);
           veccopy(n[i].ref2, bisec);
           cross(n[i].ref12, n[i].ref1, n[i].ref2);
               cross(n[i+1].ref12, n[i+1].ref1, n[i+1].ref2);
           i++;
      }
      i++;
     }
     while((he = mate(he)->nxt) != v->vedge);

     return(i);
}
