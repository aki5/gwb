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

    s = block(10.0, 15.0, 20.0);
    sweep(fface(s, 1), 0.0, 0.0, 20.0);
    sp[0] = 0.0;
    sp[1] = 0.0;
    sp[2] = 1.0;
    sp[3] = -20.0;
    solidls(s, 2);
    split(s, sp, &above, &below);
    solidls(above, 1);
    solidls(below, 1);
}
