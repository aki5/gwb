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

# include "split.h"

void    reclassifyonsectors(SP)
vector  SP;
{
        Face            *f;
        vector          c;
        double          d;
        int             i;

        for(i=0; i<nnbr; i++)
        {
                f = nbr[i].sector->wloop->lface;
                cross(c, f->feq, SP);
                d = dot(c, c);
                if(comp(d, 0.0, EPS*EPS) == 0)
                {
                        d = dot(f->feq, SP);
                        if(comp(d, 0.0, EPS) == 1)
                        {
                               nbr[i].cl = BELOW;
                               nbr[(i+nnbr-1)%nnbr].cl = BELOW;
                        }
                        else
                        {
                               nbr[i].cl = ABOVE;
                               nbr[(i+nnbr-1)%nnbr].cl = ABOVE;
                        }
                }
        }
}
