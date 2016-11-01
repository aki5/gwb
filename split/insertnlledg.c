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

#include "split.h"

void    insertnulledges()
{
        int             start, i;
        HalfEdge        *head, *tail;

        i = 0;
        while(!(nbr[i].cl == BELOW && nbr[(i+1)%nnbr].cl == ABOVE))
                if(++i == nnbr) return;
        start = i;
        head = nbr[(i+1)%nnbr].sector;
        while(1)
        {
                while(!(nbr[i].cl == ABOVE && nbr[(i+1)%nnbr].cl == BELOW))
                        i = (i+1) % nnbr;
                tail = nbr[(i+1)%nnbr].sector;
#ifdef TEST
printf("insertnulledges: insert from (%d %d) to (%d %d)\n",
head->vtx->vertexno, head->nxt->vtx->vertexno,
tail->vtx->vertexno, tail->nxt->vtx->vertexno);
#endif
                lmev(head, tail, ++maxv,
                        head->vtx->vcoord[0],
                        head->vtx->vcoord[1],
                        head->vtx->vcoord[2]);
                sone[nedg++] = head->prv->edg;
                while(!(nbr[i].cl == BELOW && nbr[(i+1)%nnbr].cl == ABOVE))
                {
                        i = (i+1) % nnbr;
                        if(i == start) return;
                }
               head = nbr[(i+1)%nnbr].sector;
        }
}
