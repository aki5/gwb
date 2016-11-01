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
# define ECHO 1

extern HalfEdge *hithe;
extern Vertex *hitvertex;

void      dosetopgenerate(e, f, BvsA)
Edge      *e;
Face      *f;
int       BvsA;
{
     Vertex        *v1, *v2;
     double        d1, d2, t, x, y, z;
     int           s1, s2, cont;

     v1 = e->he1->vtx;
     v2 = e->he2->vtx;
     s1 = comp((d1 = dist(v1->vcoord, f->feq)), 0.0, EPS);
     s2 = comp((d2 = dist(v2->vcoord, f->feq)), 0.0, EPS);
#ifdef TEST
printf("test edge %d-%d vs. face %d: d1, d2 = %f (%d) %f (%d)\n",
v1->vertexno, v2->vertexno, f->faceno, d1, s1, d2, s2);
#endif
     if(s1 == -1 && s2 == 1 || s1 == 1 && s2 == -1)
     {
          t = d1 / (d1 - d2);
          x = v1->vcoord[0] + t*(v2->vcoord[0]-v1->vcoord[0]);
          y = v1->vcoord[1] + t*(v2->vcoord[1]-v1->vcoord[1]);
          z = v1->vcoord[2] + t*(v2->vcoord[2]-v1->vcoord[2]);
          cont = contfp(f, x, y, z);
#ifdef TEST
printf("cont = %d\n", cont);
#endif
          if(cont == 1)
          {
               lmev(e->he1, e->he2->nxt, ++maxv, x, y, z);
               addsovf(e->he1->vtx, f, BvsA);
           process_edge(e->he1->prv->edg, f->fsolid, BvsA);
          }
          else if(cont == 2)
          {
               lmev(e->he1, e->he2->nxt, ++maxv, x, y, z);
               lmev(hithe, mate(hithe)->nxt, ++maxv, x, y, z);
               addsovv(e->he1->vtx, hithe->vtx, BvsA);
           process_edge(e->he1->prv->edg, f->fsolid, BvsA);
          }
          else if(cont == 3)
          {
               lmev(e->he1, e->he2->nxt, ++maxv, x, y, z);
               addsovv(e->he1->vtx, hitvertex, BvsA);
           process_edge(e->he1->prv->edg, f->fsolid, BvsA);
          }
     }
     else
     {
          if(s1 == 0)
               dovertexonface(v1, f, BvsA);
          if(s2 == 0)
               dovertexonface(v2, f, BvsA);
     }
}

void      addsovf(v, f, BvsA)
Vertex    *v;
Face      *f;
int       BvsA;
{
      int     i;

      if(BvsA)
      {
      for(i=0; i<nvtxb; i++)
          if(sonvb[i].v == v && sonvb[i].f == f)
          return;
          sonvb[nvtxb].v = v;
          sonvb[nvtxb++].f = f;
#ifdef ECHO
printf("setop: vertex of B: %d on face of A: %d\n", v->vertexno, f->faceno);
#endif
      }
      else
      {
      for(i=0; i<nvtxa; i++)
          if(sonva[i].v == v && sonva[i].f == f)
          return;
      sonva[nvtxa].v = v;
      sonva[nvtxa++].f = f;
#ifdef ECHO
printf("setop: vertex of A: %d on face of B: %d\n", v->vertexno, f->faceno);
#endif
      }
}

void      addsovv(v1, v2, BvsA)
Vertex    *v1, *v2;
int       BvsA;
{
      int     i;

      if(BvsA)
      {
      for(i=0; i<nvtx; i++)
          if(sonvv[i].vb == v1 && sonvv[i].va == v2)
          return;
          sonvv[nvtx].vb = v1;
          sonvv[nvtx++].va = v2;
#ifdef ECHO
printf("setop: coincident vertices: (B) %d (A) %d\n", v2->vertexno,
 v1->vertexno);
#endif
      }
      else
      {
      for(i=0; i<nvtx; i++)
          if(sonvv[i].vb == v2 && sonvv[i].va == v1)
          return;
          sonvv[nvtx].vb = v2;
          sonvv[nvtx++].va = v1;
#ifdef ECHO
printf("setop: coincident vertices: (A) %d (B) %d\n", v1->vertexno,
 v2->vertexno);
#endif
      }
}
