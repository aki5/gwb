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
    HalfEdge    *he;
    vector        ref1;
    vector        ref2;
    vector        ref12;
} nba[MAXSECTORS], nbb[MAXSECTORS];
extern int    nnba, nnbb;

extern struct
{
        int        secta, sectb;
    int             s1a, s2a;
    int             s1b, s2b;
    int             intersect;
}       sectors[MAXSECTORS];
extern int    nsectors;

void    sreclsectors(op)
int     op;
{
        HalfEdge        *ha, *hb;
    int             i, j, nonopposite, newsa, newsb;
        int             secta, prevsecta, nextsecta;
        int             sectb, prevsectb, nextsectb;

        /* search for coplanar sectors */
        for(i=0; i<nsectors; i++)
        {
                if(sectors[i].s1a == ON && sectors[i].s2a == ON &&
                   sectors[i].s1b == ON && sectors[i].s2b == ON)
                {
                        secta = sectors[i].secta;
                    sectb = sectors[i].sectb;
                prevsecta = (secta == 0) ? nnba-1 : secta-1;
                prevsectb = (sectb == 0) ? nnbb-1 : sectb-1;
                nextsecta = (secta == nnba-1) ? 0 : secta+1;
                nextsectb = (sectb == nnbb-1) ? 0 : sectb+1;

                        /* apply reclassification rules (Table 15.1) */
                        ha = nba[secta].he;
                        hb = nbb[sectb].he;
                        nonopposite = vecequal(ha->wloop->lface->feq,
                                               hb->wloop->lface->feq, EPS);
                        if(nonopposite)
                        {
                                newsa = (op == UNION) ? OUT : IN;
                                newsb = (op == UNION) ? IN : OUT;
                        }
                        else
                        {
                                newsa = (op == UNION) ? IN : OUT;
                                newsb = (op == UNION) ? IN : OUT;
                        }
                        /* reclassify intersecting neighbors */
                        for(j=0; j<nsectors; j++)
                        {
                            if((sectors[j].secta == prevsecta) &&
                          (sectors[j].sectb == sectb))
                    if(sectors[j].s1a != ON)
                                            sectors[j].s2a = newsa;

                            if((sectors[j].secta == nextsecta) &&
                          (sectors[j].sectb == sectb))
                    if(sectors[j].s2a != ON)
                                            sectors[j].s1a = newsa;

                            if((sectors[j].secta == secta) &&
                          (sectors[j].sectb == prevsectb))
                    if(sectors[j].s1b != ON)
                                            sectors[j].s2b = newsb;

                            if((sectors[j].secta == secta) &&
                          (sectors[j].sectb == nextsectb))
                    if(sectors[j].s2b != ON)
                                            sectors[j].s1b = newsb;

                                if(sectors[j].s1a == sectors[j].s2a &&
                                   (sectors[j].s1a == IN ||
                                    sectors[j].s1a == OUT))
                                        sectors[j].intersect = 0;

                                if(sectors[j].s1b == sectors[j].s2b &&
                                   (sectors[j].s1b == IN ||
                                    sectors[j].s1b == OUT))
                                        sectors[j].intersect = 0;
                        }
                        /* reclassify coplanar sectors themselves */
                        sectors[i].s1a = sectors[i].s2a = newsa;
                        sectors[i].s1b = sectors[i].s2b = newsb;
                        sectors[i].intersect = 0;
                }
        }
}
