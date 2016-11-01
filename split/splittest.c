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

main()
{
    Solid *s, *above, *below;
    vector sp;

    s = mvfs(1, 1, 20.0, 0.0, 0.0);
    mev(s, 1, 1, 2, 20.0, 10.0, 0.0);
    mev(s, 1, 2, 3, 10.0, 10.0, 0.0);
    mev(s, 1, 3, 4, 10.0, 20.0, 0.0);
    mev(s, 1, 4, 5, 0.0, 20.0, 0.0);
    mev(s, 1, 5, 6, 0.0, 0.0, 0.0);
    mef(s, 6, 1, 1, 2);
    sweep(fface(s, 1), 0.0, 0.0, 40.0);
    sp[0] = 0.0;
    sp[1] = 1.0;
    sp[2] = 0.0;
    sp[3] = -10.0;
    solidls(s, 2);
    split(s, sp, &above, &below);
    solidls(above, 1);
    solidls(below, 1);
}
