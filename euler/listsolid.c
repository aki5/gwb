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

#include "gwb.h"

void    listsolid(s)
Solid   *s;
{
     Face         *f;
     Loop         *l;
     HalfEdge     *he;

     f = s->sfaces;
     while(f)
     {
          printf("face %d:\n", f->faceno);
          l = f->floops;
          while(l)
          {
               printf("loop:");
               he = l->ledg;
               do
               {
                    printf(" %d: (%f %f %f)",
                           he->vtx->vertexno, he->vtx->vcoord[0],
                           he->vtx->vcoord[1], he->vtx->vcoord[2]);
               }
               while((he = he->nxt) != l->ledg);
               printf("\n");
               l = l->nextl;
          }
          f = f->nextf;
     }
}
