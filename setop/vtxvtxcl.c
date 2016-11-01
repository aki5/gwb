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

# define MAXSECTORS 100

/*
# define OUT 1
# define IN -1
# define ON 0
*/
# define OUT -1
# define IN 1
# define ON 0

/* storage for preprocessed vertex neighborhoods */
struct nb
{
    HalfEdge    *he;
    vector        ref1;
    vector        ref2;
    vector        ref12;
} nba[MAXSECTORS], nbb[MAXSECTORS];
int    nnba, nnbb;

struct
{
        int        secta, sectb;
    int             s1a, s2a;
    int             s1b, s2b;
    int             intersect;
}       sectors[MAXSECTORS];
int    nsectors;

void    vtxvtxclassify(va, vb, op)
Vertex  *va, *vb;
int     op;
{
        setopgetneighborhood(va, vb);
setopprintneighborhood(va, vb);
    sreclsectors(op);
setopprintneighborhood(va, vb);
        srecledges(op);
setopprintneighborhood(va, vb);
    sinsertnulledges();
}

setopprintneighborhood(va, vb)
Vertex  *va, *vb;
{
    int    i, secta, sectb;

    printf("vertex neighborhood info of %d, %d\n",
        va->vertexno, vb->vertexno);

    for(i=0; i<nsectors; i++)
    {
        if(sectors[i].intersect)
        {
            secta = sectors[i].secta;
            printf("%d: %d %d %d ",
                    secta,
                nba[secta].he->prv->vtx->vertexno,
                nba[secta].he->vtx->vertexno,
                nba[secta].he->nxt->vtx->vertexno);
            if(sectors[i].s1a == OUT)
                printf("(OUT-");
            if(sectors[i].s1a == ON)
                printf("(ON-");
            if(sectors[i].s1a == IN)
                printf("(IN-");
            if(sectors[i].s2a == OUT)
                printf("OUT)");
            if(sectors[i].s2a == ON)
                printf("ON)");
            if(sectors[i].s2a == IN)
                printf("IN)");

            sectb = sectors[i].sectb;
            printf(" %d: %d %d %d ",
                    sectb,
                nbb[sectb].he->prv->vtx->vertexno,
                nbb[sectb].he->vtx->vertexno,
                nbb[sectb].he->nxt->vtx->vertexno);
            if(sectors[i].s1b == OUT)
                printf("(OUT-");
            if(sectors[i].s1b == ON)
                printf("(ON-");
            if(sectors[i].s1b == IN)
                printf("(IN-");
            if(sectors[i].s2b == OUT)
                printf("OUT)");
            if(sectors[i].s2b == ON)
                printf("ON)");
            if(sectors[i].s2b == IN)
                printf("IN)");
            putchar('\n');
            fflush(stdout);
        }
    }
}
