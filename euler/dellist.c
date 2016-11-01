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

void    dellist(what, which, where)
int    what;
Node    *which, *where;
{
    switch(what)
    {
        case FACE:
            if(which->f.prevf)
                which->f.prevf->nextf = which->f.nextf;
            if(which->f.nextf)
                which->f.nextf->prevf = which->f.prevf;
            if((Face *) which == where->s.sfaces)
                where->s.sfaces = which->f.nextf;
            break;
        case LOOP:
            if(which->l.prevl)
                which->l.prevl->nextl = which->l.nextl;
            if(which->l.nextl)
                which->l.nextl->prevl = which->l.prevl;
            if((Loop *) which == where->f.floops)
                where->f.floops = which->l.nextl;
            break;
        case EDGE:
            if(which->e.preve)
                which->e.preve->nexte = which->e.nexte;
            if(which->e.nexte)
                which->e.nexte->preve = which->e.preve;
            if((Edge *) which == where->s.sedges)
                where->s.sedges = which->e.nexte;
            break;
        case VERTEX:
            if(which->v.prevv)
                which->v.prevv->nextv = which->v.nextv;
            if(which->v.nextv)
                which->v.nextv->prevv = which->v.prevv;
            if((Vertex *) which == where->s.sverts)
                where->s.sverts = which->v.nextv;
            break;
    }
}
