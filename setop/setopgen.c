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

void      setopgenerate(A, B)
Solid     *A, *B;
{
     Edge      *e;

     nvtx = nvtxa = nvtxb = 0;
     for(e = A->sedges; e != NIL; e = e->nexte)
          process_edge(e, B, 0);
     for(e = B->sedges; e != NIL; e = e->nexte)
          process_edge(e, A, 1);
}

void      process_edge(e, s, BvsA)
Edge      *e;
Solid     *s;
int       BvsA;
{
     Face      *f;

     for(f = s->sfaces; f != NIL; f = f->nextf)
          dosetopgenerate(e, f, BvsA);
}
