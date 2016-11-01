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

void    listneighbors(v)
Vertex  *v;
{
        HalfEdge        *adj;

        adj = v->vedge;
        if(adj)
                do
                {
                        printf("%d ", adj->nxt->vtx->vertexno);
                }
                while((adj = mate(adj)->nxt) != v->vedge);
        else    printf("no adjacent vertices");
        printf("\n");
}
