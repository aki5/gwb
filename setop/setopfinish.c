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
# define RESULT 1

void    setopfinish(a, b, res, op)
Solid   *a, *b, **res;
int     op;
{
        int             i, j;
        Face            *f;
        Solid           *bina;

#ifdef ECHO
printf("Enter setop_finish()\n");
#endif

        /* step 6: modify null faces into pairs of null faces */
        for(i=0; i<nfaca; i++)
        {
                /* save the new faces */
                sonfa[nfaca+i] =
                        lmfkrh(sonfa[i]->floops->nextl, ++maxf);
                sonfb[nfacb+i] =
                        lmfkrh(sonfb[i]->floops->nextl, ++maxf);
        }

#ifdef ECHO
printf("step 6:\n");
#endif
#ifdef TEST5
solidls(a, 0);
solidls(b, 0);
printf("null faces (out)\n");
for(i=0; i<nfaca; i++)
{
        facels(sonfa[i], 0);
        facels(sonfb[i], 0);
}
printf("null faces (in)\n");
for(i=0; i<nfaca; i++)
{
        facels(sonfa[nfaca+i], 0);
        facels(sonfb[nfaca+i], 0);
}
#endif

        /* step 8: construct the desired result */

#ifdef OLDSETOP
        *res = (Solid *) new(NIL, SOLID);
#else
        *res = (Solid *) new(SOLID, NIL);
#endif
        switch(op)
        {
                case UNION:
                          for(i=0; i<nfaca; i++)
                          {
                                  movefac(sonfa[i], *res);
                                  movefac(sonfb[i], *res);
#ifdef ECHO
printf("intersection polygon %d\n", i);
#endif
                          }
                          cleanup(*res);
#ifdef ECHO
printf("step 8:\n");
#endif
#ifdef TEST6
solidls(*res, 0);
#endif
                          /* glue null faces */
                          for(i=0; i<nfaca; i++)
                          {
                                  lkfmrh(sonfa[i], sonfb[i]);
                                  loopglue(sonfa[i]);
                          }
                          break;

                  case INTERSECT:
                          for(i=0; i<nfaca; i++)
                          {
                                  movefac(sonfa[i+nfaca], *res);
                                  movefac(sonfb[i+nfacb], *res);
#ifdef ECHO
printf("intersection polygon %d\n", i);
#endif
                          }
                          cleanup(*res);
#ifdef ECHO
printf("step 8:\n");
#endif
#ifdef TEST6
solidls(*res, 0);
#endif
                          for(i=0; i<nfaca; i++)
                          {
                                  lkfmrh(sonfa[nfaca+i], sonfb[nfaca+i]);
                                  loopglue(sonfa[nfaca+i]);
                          }
                          break;

                  case DIFFERENCE:
                          /* create temporary solid */
#ifdef OLDSETOP
              bina = (Solid *) new(NIL, SOLID);
#else
              bina = (Solid *) new(SOLID, NIL);
#endif
                          for(i=0; i<nfaca; i++)
                          {
                                  movefac(sonfa[i], *res);
                                  movefac(sonfb[i+nfacb], bina);
#ifdef ECHO
printf("intersection polygon %d\n", i);
#endif
                          }
                          /* revert the topology of bina */
                          revert(bina);
                          merge2(*res, bina);
                          cleanup(*res);
#ifdef ECHO
printf("step 8:\n");
#endif
#ifdef TEST6
solidls(*res, 0);
#endif
                          /* glue null faces */
                          for(i=0; i<nfaca; i++)
                          {
                                  lkfmrh(sonfa[i], sonfb[nfaca+i]);
                                  loopglue(sonfa[i]);
                          }
                          break;
        }

#ifdef ECHO
#ifdef RESULT
printf("result of ");
if(op == DIFFERENCE) printf("DIFFERENCE:\n");
if(op == INTERSECT) printf("INTERSECT:\n");
if(op == UNION) printf("UNION:\n");
solidls(*res, 2);
#endif
printf("exit setop_finish\n");
#endif
}
