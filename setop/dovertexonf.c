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

extern HalfEdge *hithe;
extern Vertex *hitvertex;

void      dovertexonface(v, f, BvsA)
Vertex    *v;
Face      *f;
int       BvsA;
{
     int           cont;

     cont = contfv(f, v);
#ifdef TEST
printf("test vertex %d: cont = %d\n", v->vertexno, cont);
#endif
     if(cont == 1)
     {
          addsovf(v, f, BvsA);
     }
     else if(cont == 2)
     {
          lmev(hithe, mate(hithe)->nxt, ++maxv,
               v->vcoord[0], v->vcoord[1], v->vcoord[2]);
          addsovv(v, hithe->vtx, BvsA);
     }
     else if(cont == 3)
     {
          addsovv(v, hitvertex, BvsA);
     }
}
