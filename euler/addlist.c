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

void    addlist(what, which, where)
int     what;
Node    *which, *where;
{
        switch(what)
        {
                case FACE:
                        which->f.nextf = where->s.sfaces;
                        which->f.prevf = (Face *) NIL;
                        if(where->s.sfaces)
                                where->s.sfaces->prevf = (Face *) which;
                        where->s.sfaces = (Face *) which;
                        which->f.fsolid = (Solid *) where;
                        break;
                case LOOP:
                        which->l.nextl = where->f.floops;
                        which->l.prevl = (Loop *) NIL;
                        if(where->f.floops)
                                where->f.floops->prevl = (Loop *) which;
                        where->f.floops = (Loop *) which;
                        which->l.lface = (Face *) where;
                        break;
                case EDGE:
                        which->e.nexte = where->s.sedges;
                        which->e.preve = (Edge *) NIL;
                        if(where->s.sedges)
                                where->s.sedges->preve = (Edge *) which;
                        where->s.sedges = (Edge *) which;
                        break;
                case VERTEX:
                        which->v.nextv = where->s.sverts;
                        which->v.prevv = (Vertex *) NIL;
                        if(where->s.sverts)
                                where->s.sverts->prevv = (Vertex *) which;
                        where->s.sverts = (Vertex *) which;
                        break;
        }
}
