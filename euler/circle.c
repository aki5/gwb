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

#include "gwb.h"

Solid   *circle(cx, cy, rad, h, n)
float   cx, cy, rad, h;
int     n;
{
        Solid        *s;

        s = mvfs(1, 1, cx+rad, cy, h);
        arc(s, 1, 1, cx, cy, rad, h, 0.0, ((n-1)*360.0/n), n-1);
        mef(s, n, 1, 1, 2);
        return(s);
}
