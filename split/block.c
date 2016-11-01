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

Solid   *block(dx, dy, dz)
float   dx, dy, dz;
{
        Solid        *s;

        s = mvfs(1, 1, 0.0, 0.0, 0.0);
        mev(s, 1, 1, 2, dx, 0.0, 0.0);
        mev(s, 1, 2, 3, dx, dy, 0.0);
        mev(s, 1, 3, 4, 0.0, dy, 0.0);
        mef(s, 1, 4, 1, 2);
        sweep(fface(s, 1), 0.0, 0.0, dz);
        return(s);
}
