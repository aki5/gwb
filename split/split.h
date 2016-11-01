# include "gwb.h"

# define ABOVE 1
# define BELOW -1
# define ON 0

# define MAXONVERTICES 100
# define MAXNULLEDGES 200
# define MAXNULLFACES 50
# define MAXEDGESFORVERTEX 20

Vertex  *soov[MAXONVERTICES];     /* naille paremmat nimet */
int     nvtx;
Edge    *sone[MAXNULLEDGES];
int     nedg;
Face    *sonf[MAXNULLFACES*2];
int     nfac;

struct
{
        HalfEdge        *sector;
        int             cl;
}       nbr[MAXEDGESFORVERTEX];
int     nnbr;
