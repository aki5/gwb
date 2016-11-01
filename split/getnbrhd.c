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

void    getneighborhood(vtx, SP)
Vertex  *vtx;
vector  SP;
{
        HalfEdge        *he;
        vector          bisect;
        double          d;

        nnbr = 0;
        he = vtx->vedge;
        do
        {
                 nbr[nnbr].sector = he;
                 d = dist(he->nxt->vtx->vcoord, SP);
                 nbr[nnbr++].cl = comp(d, 0.0, EPS);
                 if(iswide(he))
                 {
                     bisector(he, bisect);
                     nbr[nnbr].sector = he;
                     d = dist(bisect, SP);
                    /*
                     nbr[nnbr++].cl = comp(d, 0.0, EPS);
                    */
                    nbr[nnbr].cl = nbr[nnbr-1].cl;
                    nbr[nnbr-1].cl = comp(d, 0.0, EPS);
                     nnbr++;
                 }
        }
        while((he = mate(he)->nxt) != vtx->vedge);
}
