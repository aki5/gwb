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

# include    "gwb.h"

extern unsigned    nodesize[];

void    del(what, which, where)
int     what;
Node    *which;
Node    *where;
{
    switch(what)
    {
        case SOLID:
            break;
        case FACE:
            dellist(FACE, which, where);
            break;
        case LOOP:
            dellist(LOOP, which, where);
            break;
        case EDGE:
            dellist(EDGE, which, where);
            break;
        case HALFEDGE:
            break;
        case VERTEX:
            dellist(VERTEX, which, where);
            break;
    }
    free(which);
}

/* how many bytes does s use ? */
int    bytesused(s)
Solid    *s;
{
    Face        *f;
    Loop        *l;
    HalfEdge    *he;
    int        used;

    used = nodesize[SOLID];

    f = s->sfaces;
    while(f)
    {
        used += nodesize[FACE];
        l = f->floops;
        while(l)
        {
            used += nodesize[LOOP];
            he = l->ledg;
            do
            {
                used += nodesize[HALFEDGE];
                if(he->edg)
                    if(he == he->edg->he1)
                        used += nodesize[EDGE];
                if(he == he->vtx->vedge)
                    used += nodesize[VERTEX];
            }
            while((he = he->nxt) != l->ledg);
            l = l->nextl;
        }
        f = f->nextf;
    }
    return(used);
}
