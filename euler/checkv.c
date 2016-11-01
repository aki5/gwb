#
# define NDEBUG

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

#include "gwb.h"
/*    assert.h    4.1    83/05/03    */

# ifndef NDEBUG
# define _assert(ex) {if (!(ex)){fprintf(stderr,"Assertion failed: file %s, line
 %d\n", __FILE__, __LINE__);abort();}}
# define assert(ex) {if (!(ex)){fprintf(stderr,"Assertion failed: file %s, line
 %d\n", __FILE__, __LINE__);abort();}}
# else
# define _assert(ex) ;
# define assert(ex) ;
# endif

void    checkv(s)
Solid    *s;
{
    Vertex        *v;
    HalfEdge    *he;
    int        maxtry;

    v = s->sverts;
    while(v)
    {
        he = v->vedge;
        maxtry = 50;
        if(he)
        do
        {
            assert(he->edg != NIL);
            assert(he->vtx == v);
            assert(maxtry-- > 0);
        }
        while((he = mate(he)->nxt) != v->vedge);
        v = v->nextv;
    }
}
