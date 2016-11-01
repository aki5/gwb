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

void    sortnulledges()
{
    register int        i, j;

    if(nedg < 5) return;
    for(i=0; i<nedg; i++)
            for(j=i+1; j<nedg; j++)
                  if(greater(i, j)) swap(i, j);
}
int    greater(i, j)
int    i, j;
{
    register Vertex        *v1, *v2;
    register int        com;

    v1 = sone[i]->he1->vtx;
    v2 = sone[j]->he1->vtx;
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
int    swap(i, j)
int    i, j;
{
    register Edge *temp;

    temp = sone[i];
    sone[i] = sone[j];
    sone[j] = temp;
}

Edge    *getnextnulledge()
{
        Edge *e;
    static int n = 0;

    if(n == nedg)
    {
           n = 0;
           return((Edge *) NIL);
    }
    e = sone[n++];
    return(e);
}
