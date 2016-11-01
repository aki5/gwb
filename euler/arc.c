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

void    arc(s, f, v, cx, cy, rad, h, phi1, phi2, n)
Solid   *s;
Id      f, v;
float   cx, cy, rad, h, phi1, phi2;
int     n;
{
        float   x, y, angle, inc;
        Id      prev;
        int     i;

        angle = phi1 * PI / 180.0;
        inc = (phi2 - phi1) * PI / (180.0 * n);
        prev = v;
        getmaxnames(s);
        for(i = 0; i < n; i++)
        {
                angle += inc;
                x = cx + cos(angle) * rad;
                y = cy + sin(angle) * rad;
                mev(s, f, prev, ++maxv, x, y, h);
                prev = maxv;
        }
}

void    getmaxnames(s)
Solid   *s;
{
        Vertex  *v;
        Face    *f;

        for(v = s->sverts, maxv = 0; v != NIL; v = v->nextv)
                if(v->vertexno > maxv) maxv = v->vertexno;
        for(f = s->sfaces, maxf = 0; f != NIL; f = f->nextf)
                if(f->faceno > maxf) maxf = f->faceno;
}
