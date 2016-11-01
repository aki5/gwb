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
