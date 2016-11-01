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

# define MAXSECTORS 100

/*
# define OUT 1
# define IN -1
# define ON 0
*/
# define OUT -1
# define IN 1
# define ON 0

extern struct nb
{
    HalfEdge      *he;
    vector        ref1;
    vector        ref2;
    vector        ref12;
}                 nba[MAXSECTORS], nbb[MAXSECTORS];
extern int        nnba, nnbb;

extern struct
{
    int           secta, sectb;
    int           s1a, s2a;
    int           s1b, s2b;
    int           intersect;
}                 sectors[MAXSECTORS];
extern int        nsectors;

void    srecledges(op)
int     op;
{
    int         i, j, newsa, newsb;
    int         secta, prevsecta;
    int         sectb, prevsectb;

    /* search for doubly coplanar edges */
    for(i=0; i<nsectors; i++)
    {
        /* double "on"-edge ? */
        if(sectors[i].intersect &&
           sectors[i].s1a == ON && sectors[i].s1b == ON)
        {
            /* figure out the new classifications
               for the "on"-edges */
            newsa = (op == UNION) ? OUT : IN;
            newsb = (op == UNION) ? IN : OUT;

            secta = sectors[i].secta;
            sectb = sectors[i].sectb;
            prevsecta = (secta == 0) ? nnba-1 : secta-1;
            prevsectb = (sectb == 0) ? nnbb-1 : sectb-1;

            /* reclassify all instances of the situation */
            for(j=0; j<nsectors; j++)
            {
                if(sectors[j].intersect)
                {
                    if((sectors[j].secta == secta) &&
                       (sectors[j].sectb == sectb))
                    {
                        sectors[j].s1a = newsa;
                        sectors[j].s1b = newsb;
                    }

                    if((sectors[j].secta == prevsecta) &&
                       (sectors[j].sectb == sectb))
                    {
                        sectors[j].s2a = newsa;
                        sectors[j].s1b = newsb;
                    }

                    if((sectors[j].secta == secta) &&
                       (sectors[j].sectb == prevsectb))
                    {
                        sectors[j].s1a = newsa;
                        sectors[j].s2b = newsb;
                    }

                    if((sectors[j].secta == prevsecta) &&
                       (sectors[j].sectb == prevsectb))
                    {
                        sectors[j].s2a = newsa;
                        sectors[j].s2b = newsb;
                    }

                    if(sectors[j].s1a == sectors[j].s2a &&
                       (sectors[j].s1a == IN ||
                        sectors[j].s1a == OUT))
                        sectors[j].intersect = 0;
                    if(sectors[j].s1b == sectors[j].s2b &&
                       (sectors[j].s1b == IN ||
                        sectors[j].s1b == OUT))
                        sectors[j].intersect = 0;
                }
            }
        }
    }

    /* search for singly coplanar edges */
    for(i=0; i<nsectors; i++)
    {
        if(sectors[i].intersect && sectors[i].s1a == ON)
        {
            secta = sectors[i].secta;
            sectb = sectors[i].sectb;
            prevsecta = (secta == 0) ? nnba-1 : secta-1;
            prevsectb = (sectb == 0) ? nnbb-1 : sectb-1;
            newsa = (op == UNION) ? OUT : IN;

            for(j=0; j<nsectors; j++)
            {
                if(sectors[j].intersect)
                {
                    if((sectors[j].secta == secta) &&
                       (sectors[j].sectb == sectb))
                        sectors[j].s1a = newsa;

                    if((sectors[j].secta == prevsecta) &&
                       (sectors[j].sectb == sectb))
                        sectors[j].s2a = newsa;

                    if(sectors[j].s1a == sectors[j].s2a &&
                       (sectors[j].s1a == IN ||
                        sectors[j].s1a == OUT))
                        sectors[j].intersect = 0;
                }
            }
        }
        else if(sectors[i].intersect && sectors[i].s1b == ON)
        {
            secta = sectors[i].secta;
            sectb = sectors[i].sectb;
            prevsecta = (secta == 0) ? nnba-1 : secta-1;
            prevsectb = (sectb == 0) ? nnbb-1 : sectb-1;
            newsb = (op == UNION) ? OUT : IN;

            for(j=0; j<nsectors; j++)
            {
                if(sectors[j].intersect)
                {
                    if((sectors[j].secta == secta) &&
                       (sectors[j].sectb == sectb))
                        sectors[j].s1b = newsb;

                    if((sectors[j].secta == secta) &&
                       (sectors[j].sectb == prevsectb))
                        sectors[j].s2b = newsb;

                    if(sectors[j].s1b == sectors[j].s2b &&
                       (sectors[j].s1b == IN ||
                        sectors[j].s1b == OUT))
                        sectors[j].intersect = 0;
                }
            }
        }
    }
}
