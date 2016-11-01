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

void    rsweep(s, nfaces)
Solid   *s;
int     nfaces;
{
        HalfEdge        *first, *cfirst, *last, *scan;
    matrix        m;
    vector        v;

    HalfEdge        *h;
    Face            *headf, *tailf;
    int             closed_figure;

    if(s->sfaces->nextf)        /* does the solid have > 1 faces ? */
    {
        printf("closed figure...\n");
        solidls(s, 2);
            /* assume it's a lamina */
        closed_figure = 1;
            h = s->sfaces->floops->ledg;
             lmev(h, mate(h)->nxt, ++maxv,
                    h->vtx->vcoord[0],
                    h->vtx->vcoord[1],
                    h->vtx->vcoord[2]);
            lkef(h->prv, mate(h->prv));
               headf = s->sfaces;
        printf("... opened\n");
        solidls(s, 1);
    }
    else    closed_figure = 0;                  /* no, it's a wire */

        getmaxnames(s);
        first = s->sfaces->floops->ledg;
        while(first->edg != first->nxt->edg) first = first->nxt;
        last = first->nxt;
        while(last->edg != last->nxt->edg) last = last->nxt;
        cfirst = first;
    matident(m);
    matrotat(m, (360.0 / nfaces), 0.0, 0.0);
        while(--nfaces)
        {
        vecmult(v, cfirst->nxt->vtx->vcoord, m);
                lmev(cfirst->nxt, cfirst->nxt, ++maxv,
                        v[0], v[1], v[2]);
                scan = cfirst->nxt;
                while(scan != last->nxt)
                {
            vecmult(v, scan->prv->vtx->vcoord, m);
                    lmev(scan->prv, scan->prv, ++maxv,
                            v[0], v[1], v[2]);
                        lmef(scan->prv->prv, scan->nxt, ++maxf);
                        scan = mate(scan->nxt->nxt);
                }
                last = scan;
                cfirst = mate(cfirst->nxt->nxt);
        }
        tailf = lmef(cfirst->nxt, mate(first), ++maxf);
        while(cfirst != scan)
        {
                lmef(cfirst, cfirst->nxt->nxt->nxt, ++maxf);
                cfirst = mate(cfirst->prv)->prv;
        }

    if(closed_figure == 1)
    {
            lkfmrh(headf, tailf);
        printf("lkfmrh done\n");
            loopglue(headf);
        printf("loopglue done\n");
    }
}
