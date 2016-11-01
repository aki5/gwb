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

# include    <math.h>

# define    void        int
/*# define    fabs(x)        (((x) < 0.0) ? (-x) : (x))*/

void        addlist();
HalfEdge        *addhe();
Solid        *ball();
/*Solid        *block();*/    /* clash with mem.h */
Solid        *circle();
Solid        *cyl();
HalfEdge        *delhe();
Face        *fface();
HalfEdge        *fhe1();
HalfEdge        *fhe2();
Face            *lmef();
Face            *lmfkrh();
void            lmev();
int         mev();
Solid       *mvfs();
Node        *new();
Solid        *torus();

double        dot();
double        normalize();
double        dot2();
double        edist();
double        dist();
