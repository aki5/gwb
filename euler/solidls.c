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

void    solidls(s, sw)
Solid   *s;
int     sw;
{
    Face        *f;
    Loop        *l;
    Vertex        *v;
    Edge        *e;
    HalfEdge    *he;

    printf("Faces:\n");
    f = s->sfaces;
    while(f)
    {
        facels(f, sw);
        f = f->nextf;
    }

    if(sw>1)
    {
        printf("vertices:");
        v = s->sverts;
        while(v)
        {
            putchar('\n');
            printf("%d <%5.1f, %5.1f, %5.1f, %5.1f>",
                v->vertexno, v->vcoord[0], v->vcoord[1],
                v->vcoord[2], v->vcoord[3]);
            if(sw>2)
            {
                he = v->vedge;
                if(he)
                {
                    do
                    {
                        e = he->edg;
                        if(he == e->he1)
                            printf(" +");
                        else    printf(" -");
                        printf("<%d,%d>",
                        e->he1->vtx->vertexno,
                        e->he2->vtx->vertexno);
                    }
                    while((he = mate(he)->nxt) != v->vedge);
                }
            }
            v = v->nextv;
        }
        putchar('\n');
        printf("Edges: <v1, v2, f1, f2>");
        f = s->sfaces;
        while(f)
        {
            l = f->floops;
            while(l)
            {
                he = l->ledg;
                do
                {
                    if(e = he->edg)
                    {
                        if(he == e->he1)
                        {
                        putchar('\n');
                        printf("<%d, %d, %d, %d>",
                        e->he1->vtx->vertexno,
                        e->he2->vtx->vertexno,
                        e->he1->wloop->lface->faceno,
                        e->he2->wloop->lface->faceno);
                        }
                    }
                }
                while((he = he->nxt) != l->ledg);
                l = l->nextl;
            }
            f = f->nextf;
        }
    }
    putchar('\n');
}

facels(f, sw)
Face *f;
int sw;
{
    Loop        *l;
    Vertex        *v;
    Edge        *e;
    HalfEdge    *he;
    register int    i;
    int        breakline;

    breakline = 8;
    if(sw > 2) breakline = 4;

    printf("Face no. %d:    ", f->faceno);

    l = f->floops;
    while(l)
    {
        he = l->ledg;
        i = 0;
        do
        {
            v = he->vtx;
            e = he->edg;
            if(sw > 2 && e)
            {
                if(he == e->he1)
                    printf("%d +(%d,%d)-> ",
                        v->vertexno,
                        e->he1->vtx->vertexno,
                        e->he2->vtx->vertexno);
                else    printf("%d -(%d,%d)-> ",
                        v->vertexno,
                        e->he1->vtx->vertexno,
                        e->he2->vtx->vertexno);
            }
            else printf("%d -> ", v->vertexno);
            if((++i)%breakline == 0)
                printf("\n        ");
        }
        while((he = he->nxt) != l->ledg);
        if(l == f->flout)
            printf("<outer>\n");
        else    printf("<inner>\n");

        l = l->nextl;
        if(l) printf("        ");
    }
    printf("equation: ");
    vecprint(f->feq);
}
