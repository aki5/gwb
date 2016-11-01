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

# include "setop.h"

void    ssortnulledges()
{
    register int        i, j;

    if(nedga < 5) return;
    for(i=0; i<nedga; i++)
            for(j=i+1; j<nedga; j++)
                  if(sgreater(i, j)) sswap(i, j);
}
int    sgreater(i, j)
int    i, j;
{
    register Vertex        *v1, *v2;
    register int        com;

    v1 = sonea[i]->he1->vtx;
    v2 = sonea[j]->he1->vtx;
    if((com = comp(v1->vcoord[0], v2->vcoord[0], BIGEPS)) == -1) return(0);
    else if(com == 0)
    {
        if((com = comp(v1->vcoord[1], v2->vcoord[1], BIGEPS)) == -1)
            return(0);
        else if(com == 0)
        {
            if((com = comp(v1->vcoord[2], v2->vcoord[2], BIGEPS))
                == -1) return(0);
        }
    }
    return(1);
}
int    sswap(i, j)
int    i, j;
{
    register Edge *temp;

    temp = sonea[i];
    sonea[i] = sonea[j];
    sonea[j] = temp;
    temp = soneb[i];
    soneb[i] = soneb[j];
    soneb[j] = temp;
}

int     sgetnextnulledge(ea, eb)
Edge    **ea, **eb;
{
    static int n = 0;

    if(n == nedga)
    {
           n = 0;
           return(0);
    }
    *ea = sonea[n];
    *eb = soneb[n++];
    return(1);
}
