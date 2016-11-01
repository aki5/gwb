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

/*
**    Geometric WorkBench V 0.6
**
**    Copyright (c) 1984 TEKES-Project, Helsinki Univ. of Tech.
**
**    separ.c
**    - version 0.1
**
**    Create null edges and store them into lone
**
**    History:
**    - combined from earlier pieces (Spring 1984, MaM)
**    - modified to take null edges already inserted into account
**      (April 1986, MaM)
**
**    Testing:
**    - TEST        Echo operation
**    - TESTALL    List faces after operation
*/

/* separate edge-sequence from ... to */
void        separ1(from, to, type)
HalfEdge    *from, *to;
int        type;
{
#ifdef TEST
printf("separ1: from <%d,%d> to <%d,%d>\n",
from->vtx->vertexno, from->nxt->vtx->vertexno,
to->vtx->vertexno, to->nxt->vtx->vertexno);
#endif

    /* recover from null edges already inserted */
    if(nulledge(from->prv) && strutnulledge(from->prv))
    {
#ifdef TEST
printf("separ1: strut null edge at front of from\n");
#endif
        /* look at orientation */
        if(from->prv == from->prv->edg->he2)
        {
            from = from->prv->prv;
#ifdef TEST
printf("separ1: new from <%d,%d>\n",
from->vtx->vertexno, from->nxt->vtx->vertexno);
#endif
        }
    }
    if(nulledge(to->prv) && strutnulledge(to->prv))
    {
#ifdef TEST
printf("separ1: null edge at front of to\n");
#endif
        if(to->prv == to->prv->edg->he1)
        {
            to = to->prv->prv;
#ifdef TEST
printf("separ1: new to <%d,%d>\n",
to->vtx->vertexno, to->nxt->vtx->vertexno);
#endif
        }
    }
    if(from->vtx != to->vtx)
    {
        if(from->prv == mate(to->prv))
        {
            from = from->prv;
#ifdef TEST
printf("separ1: split null edge at front of from, to\n");
printf("separ1: new from <%d,%d>",
from->vtx->vertexno, from->nxt->vtx->vertexno);
#endif
        }
        else if(from->prv->vtx == to->vtx)
        {
            from = from->prv;
#ifdef TEST
printf("separ1: split null edge at front of from\n");
printf("separ1: new from <%d,%d>",
from->vtx->vertexno, from->nxt->vtx->vertexno);
#endif
        }
        else if(to->prv->vtx == from->vtx)
        {
            to = to->prv;
#ifdef TEST
printf("separ1: split null edge at front of to\n");
printf("separ1: new to <%d,%d>",
to->vtx->vertexno, to->nxt->vtx->vertexno);
#endif
        }
    }

    lmev(from, to, ++maxv,
        from->vtx->vcoord[0],
        from->vtx->vcoord[1],
        from->vtx->vcoord[2]);

#ifdef TESTALL
facels(from->wloop->lface, 0);
#endif

    if(type == 0)    sonea[nedga++] = from->prv->edg;
    else        soneb[nedgb++] = from->prv->edg;
}

/* separate `interior' of the face of he */
void        separ2(he, type, orient)
HalfEdge    *he;
int        type, orient;
{
    HalfEdge    *tmp;

#ifdef TEST
printf("separ2: from %d in face %d\n",
he->vtx->vertexno, he->wloop->lface->faceno);
#endif

    /* recover from null edges inserted */
    if(nulledge(he->prv))
    {
        if(((he->prv == he->prv->edg->he1) && orient) ||
           ((he->prv == he->prv->edg->he2) && !orient))
        {
            he = he->prv;
#ifdef TEST
printf("separ2: new from %d\n", he->vtx->vertexno);
#endif
        }
    }

    lmev(he, he, ++maxv, he->vtx->vcoord[0], he->vtx->vcoord[1],
        he->vtx->vcoord[2]);

    /* a piece of Black Art: reverse orientation of the null edge */
    if(orient)
    {
#ifdef TEST
printf("separ2: reverse orientation\n");
#endif
        tmp = he->prv->edg->he1;
        he->prv->edg->he1 = he->prv->edg->he2;
        he->prv->edg->he2 = tmp;
    }

#ifdef TESTALL
facels(he->wloop->lface, 0);
#endif

    if(type == 0)    sonea[nedga++] = he->prv->edg;
    else        soneb[nedgb++] = he->prv->edg;
}

/* add ring null edge */
void    makering(f, x, y, z, type)
Face    *f;
double    x, y, z;
int    type;
{
    HalfEdge    *he1, *he2;

#ifdef TEST
printf("makering: add ring into face %d\n", f->faceno);
#endif
    lmev(f->flout->ledg, f->flout->ledg, ++maxv, x, y, z);
    he1 = f->flout->ledg->prv;
    lmev(he1, he1, ++maxv, x, y, z);
    he2 = he1->prv;
    lkemr(he1->prv->prv->prv, he1);

#ifdef TESTALL
facels(f, 0);
#endif

    if(type == 1)    sonea[nedga++] = he2->edg;
    else        soneb[nedgb++] = he2->edg;
}

int         nulledge(he)
HalfEdge        *he;
{
    return(vecequal(he->vtx->vcoord, he->nxt->vtx->vcoord), 0.0);
}

int        strutnulledge(he)
HalfEdge    *he;
{
    if(/* length > 2 && */ he == mate(he)->nxt || he == mate(he)->prv)
        return(1);
    return(0);
}

