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

void    scannames(s)
Solid    *s;
{
    register Vertex        *v;
    register Face        *f;

    maxv = maxf = 0;
    v = s->sverts;
    while(v)
    {
        if(v->vertexno > maxv) maxv = v->vertexno;
        v = v->nextv;
    }
    f = s->sfaces;
    while(f)
    {
        if(f->faceno > maxf) maxf = f->faceno;
        f = f->nextf;
    }
}
