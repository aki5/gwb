# include    <math.h>

# define    void        int
/*# define    fabs(x)        (((x) < 0.0) ? (-x) : (x))*/

void        addlist();
HalfEdge        *addhe();
Solid        *ball();
Solid        *block();    /* MAC: clash with mem.h */
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
double        dist();
