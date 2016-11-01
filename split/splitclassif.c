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

void    splitclassify(SP)
vector  SP;
{
        int     i;

        nedg = 0;
        for(i=0; i<nvtx; i++)
        {
#ifdef TEST
printf("splitclassify: classify vertex %d\n", soov[i]->vertexno);
#endif
                getneighborhood(soov[i], SP);
#ifdef TEST
printneighborhood();
#endif
                reclassifyonsectors(SP);
#ifdef TEST
printneighborhood();
#endif
                reclassifyonedges();
#ifdef TEST
printneighborhood();
#endif
                insertnulledges();
        }
}

#ifdef TEST
printneighborhood()
{
        int i;

        printf("neighborhood:\n");
    for(i=0; i<nnbr; i++)
    {
            printf("  neighbor vtx %d, class = ",
               nbr[i].sector->nxt->vtx->vertexno);
        if(nbr[i].cl == BELOW) printf("BELOW\n");
        if(nbr[i].cl == ON) printf("ON\n");
        if(nbr[i].cl == ABOVE) printf("ABOVE\n");
        }
}
#endif

