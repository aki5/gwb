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
# define TESTALL 1

int Gtestspecials;

int     setop(A, B, res, op)
Solid   *A, *B, **res;
int     op;
{
        Face    *f;

        for(f = A->sfaces; f != NIL; f = f->nextf)
                faceeq(f->flout, f->feq);
        for(f = B->sfaces; f != NIL; f = f->nextf)
                faceeq(f->flout, f->feq);
        getmaxnames(A);
        updmaxnames(B);
#ifdef TESTALL
solidls(A, 2);
solidls(B, 2);
#endif
    Gtestspecials = 1;
        setopgenerate(A, B);
    Gtestspecials = 0;
#ifdef TESTALL
solidls(A, 2);
solidls(B, 2);
#endif
        setopclassify(op);
        if(nedga == 0)
        {
                printf("setop: no intersections found\n");
                return(0);
        }
#ifdef TESTALL
solidls(A, 2);
solidls(B, 2);
#endif
#ifdef ECHO
{
int i;
printf("Set of null edges\n");
for(i=0; i<nedga; i++)
printf("(%d,%d) (%d,%d)\n",
sonea[i]->he1->vtx->vertexno, sonea[i]->he2->vtx->vertexno,
soneb[i]->he1->vtx->vertexno, soneb[i]->he2->vtx->vertexno);
}
#endif
        setopconnect();
#ifdef TESTALL
solidls(A, 2);
solidls(B, 2);
#endif
#ifdef ECHO
{
  int i;
  printf("Set of null faces\n");
  for(i=0; i<nfaca; i++)
  {
    facels(sonfa[i]);
    facels(sonfb[i]);
  }
}
#endif
        setopfinish(A, B, res, op);
    return(1);
}
