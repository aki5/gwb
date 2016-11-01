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

/* return codes and misc constants */
# define        ERROR           -1
# define        SUCCESS         -2
# define        NIL             0
# define        PI              3.141592653589793

/* parameters for memory allocation routines */
# define        SOLID           0
# define        FACE            1
# define        LOOP            2
# define        HALFEDGE        3
# define        EDGE            4
# define        VERTEX          5

/* coordinate plane names */
# define        X               0
# define        Y               1
# define        Z               2

/* orientations */
# define        PLUS            0
# define        MINUS           1

/* macros */
# define        mate(he)        (((he) == (he)->edg->he1) ? \
                                (he)->edg->he2 : (he)->edg->he1)
# define        max(x,y)        (((x) > (y)) ? (x) : (y))
# define        abs(x)          (((x) > 0.0) ? (x) : -(x))

/* global variables */
extern Id       maxf;           /* largest face no. given so far */
extern Id       maxv;           /* largest vertex no. given so far */

/* epsilons for geometric tests */
extern double   EPS;
extern double   BIGEPS;

# include "funcs.h"
