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

void    merge2(s1, s2)
Solid   *s1, *s2;
{
    Face    *f;
    Edge    *e;
    Vertex    *v;

        while(f = s2->sfaces)
        {
                dellist(FACE, f, s2);
                addlist(FACE, f, s1);
        }
        while(e = s2->sedges)
        {
                dellist(EDGE, e, s2);
                addlist(EDGE, e, s1);
        }
        while(v = s2->sverts)
        {
                dellist(VERTEX, v, s2);
                addlist(VERTEX, v, s1);
        }
        del(SOLID, s2, NIL);
}
