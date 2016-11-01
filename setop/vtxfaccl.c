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
# define TEST 1

/*
# define OUT 1
# define IN -1
# define ON 0
*/
# define OUT -1
# define IN 1
# define ON 0

# define MAXEDGESFORVERTEX 20

extern struct
{
        HalfEdge        *sector;
        int             cl;
}       nbr[MAXEDGESFORVERTEX];
extern int     nnbr;

void    s_reclassifyonsectors();
void    s_recledges();
void    s_insertnulledges();

void    vtxfacclassify(v, f, op, BvsA)
Vertex  *v;
Face    *f;
int     op;
int     BvsA;
{
#ifdef TEST
printf("vtxfaccl: classify vertex %d\n", v->vertexno);
#endif
        getneighborhood(v, f->feq);
#ifdef TEST
printneighborhood();
#endif
        s_reclassifyonsectors(f->feq, op, BvsA);
#ifdef TEST
printneighborhood();
#endif
        s_recledges();
#ifdef TEST
printneighborhood();
#endif
        s_insertnulledges(f, BvsA);
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
        if(nbr[i].cl == IN) printf("IN\n");
        if(nbr[i].cl == ON) printf("ON\n");
        if(nbr[i].cl == OUT) printf("OUT\n");
        }
}
#endif

void    s_reclassifyonsectors(SP, op, BvsA)
vector  SP;
int     op, BvsA;
{
        Face            *f;
        vector          c;
        double          d;
        int             i;

        for(i=0; i<nnbr; i++)
        {
        /* test coplanarity */
                f = mate(nbr[i].sector)->wloop->lface;
                cross(c, f->feq, SP);
                d = dot(c, c);
                if(comp(d, 0.0, EPS*EPS) == 0)
                {
                        d = dot(f->feq, SP);
            /* test orientation */
                        if(comp(d, 0.0, EPS) == 1)
                        {
                /* identical */
                if(BvsA)
                {
                    nbr[i].cl = (op == UNION) ? IN : OUT;
                    nbr[(i+1)%nnbr].cl =
                        (op == UNION) ? IN : OUT;
                }
                else
                {
                    nbr[i].cl = (op == UNION) ? OUT : IN;
                    nbr[(i+1)%nnbr].cl =
                        (op == UNION) ? OUT : IN;
                }
                        }
                        else
                        {
                /* opposite */
                if(BvsA)
                {
                    nbr[i].cl = (op == UNION) ? IN : OUT;
                    nbr[(i+1)%nnbr].cl =
                        (op == UNION) ? IN : OUT;
                }
                else
                {
                    nbr[i].cl = (op == UNION) ? IN : OUT;
                    nbr[(i+1)%nnbr].cl =
                        (op == UNION) ? IN : OUT;
                   }
                        }
                }
        }
}

void    s_recledges()
{
        int             i;

        for(i=0; i<nnbr; i++)
        {
                if(nbr[i].cl == ON)
                {
                        if(nbr[(nnbr+i-1)%nnbr].cl == IN)
                        {
                                if(nbr[(i+1)%nnbr].cl == IN)
                                        nbr[i].cl = IN;
                                else    nbr[i].cl = IN;
                        }
            else    /* OUT */
                        {
                                if(nbr[(i+1)%nnbr].cl == IN)
                                        nbr[i].cl = IN;
                                else    nbr[i].cl = OUT;
            }
                }
        }
}

void    s_insertnulledges(f, BvsA)
Face    *f;
int     BvsA;
{
        int             start, i;
        HalfEdge        *head, *tail;

        i = 0;
        while(!(nbr[i].cl == IN && nbr[(i+1)%nnbr].cl == OUT))
                if(++i == nnbr) return;
        start = i;
        head = mate(nbr[i].sector)->nxt;
        while(1)
        {
                while(!(nbr[i].cl == OUT && nbr[(i+1)%nnbr].cl == IN))
                        i = (i+1) % nnbr;
                tail = mate(nbr[i].sector)->nxt;
#ifdef TEST
printf("insertnulledges: insert from (%d %d) to (%d %d)\n",
head->vtx->vertexno, head->nxt->vtx->vertexno,
tail->vtx->vertexno, tail->nxt->vtx->vertexno);
#endif
                lmev(head, tail, ++maxv,
                        head->vtx->vcoord[0],
                        head->vtx->vcoord[1],
                        head->vtx->vcoord[2]);
                if(BvsA) soneb[nedgb++] = head->prv->edg;
                else sonea[nedga++] = head->prv->edg;
        makering(f,
                        head->vtx->vcoord[0],
                        head->vtx->vcoord[1],
                        head->vtx->vcoord[2],
                BvsA);

                while(!(nbr[i].cl == IN && nbr[(i+1)%nnbr].cl == OUT))
                {
                        i = (i+1) % nnbr;
                        if(i == start) return;
                }
        }
}
