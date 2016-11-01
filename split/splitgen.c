#
# define TEST 1

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

void     splitgenerate(S, SP)
Solid    *S;
vector   SP;
{
     Edge          *e;
     HalfEdge      *he;
     Vertex        *v1, *v2;
     double        d1, d2, t, x, y, z;
     int           s1, s2;

     nvtx = 0;
     for(e = S->sedges; e != NIL; e = e->nexte)
     {
          v1 = e->he1->vtx;
          v2 = e->he2->vtx;
          d1 = dist(v1->vcoord, SP);
          d2 = dist(v2->vcoord, SP);
          s1 = comp(d1, 0.0, EPS);
          s2 = comp(d2, 0.0, EPS);
          if(s1 == -1 && s2 == 1 || s1 == 1 && s2 == -1)
          {
               t = d1 / (d1 - d2);
               x = v1->vcoord[0] + t*(v2->vcoord[0]-v1->vcoord[0]);
               y = v1->vcoord[1] + t*(v2->vcoord[1]-v1->vcoord[1]);
               z = v1->vcoord[2] + t*(v2->vcoord[2]-v1->vcoord[2]);
#ifdef TEST
printf("splitgenerate: subdivide edge %d %d\n", v1->vertexno, v2->vertexno);
#endif
               lmev(e->he1, (he = e->he2->nxt), ++maxv, x, y, z);
               addsoov(he->prv->vtx);
          }
          else
          {
               if(s1 == 0) addsoov(v1);
               if(s2 == 0) addsoov(v2);
          }
     }
}

void      addsoov(v)
Vertex    *v;
{
     int       i;

     for(i=0; i<nvtx; i++)
          if(soov[i] == v) return;
     soov[nvtx++] = v;
#ifdef TEST
printf("splitgenerate: relevent vertex  %d: %d\n", nvtx, v->vertexno);
#endif
}
