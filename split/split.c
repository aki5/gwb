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

void    split(S, SP, Above, Below)
Solid   *S, **Above, **Below;
vector  SP;
{
        Face    *f;

        for(f = S->sfaces; f != NIL; f = f->nextf)
                faceeq(f->flout, f->feq);
        getmaxnames(S);

#ifdef TEST
printf("split: equation = ");
vecprint(SP);
#endif
        splitgenerate(S, SP);
#ifdef TEST
printf("split: %d on-vertices found\n", nvtx);
solidls(S, 1);
#endif
        splitclassify(SP);
#ifdef TEST
printf("split: %d null edges generated\n", nedg);
printf("split: set of null edges:\n");
{
  int i;
  for(i=0; i<nedg; i++)
    printf("%d %d\n", sone[i]->he1->vtx->vertexno,
       sone[i]->he2->vtx->vertexno);
}
solidls(S, 1);
#endif
        if(nedg == 0)
        {
                printf("split: no intersections found\n");
                return;
        }
        splitconnect();
#ifdef TEST
printf("split: %d null faces generated\n", nfac);
printf("split: set of null faces:\n");
{
  int i;
  for(i=0; i<nfac; i++)
    facels(sonf[i]);
}
solidls(S, 1);
#endif
        splitfinish(S, Above, Below);
}
