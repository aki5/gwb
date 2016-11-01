# include "gwb.h"

# define UNION 0
# define INTERSECT 1
# define DIFFERENCE 2

# define MAXVV  1000
# define MAXVF  1000
# define MAXNE  1000
# define MAXNF  20

struct
{
        Vertex  *va, *vb;
}              sonvv[MAXVV];
int     nvtx;
struct
{
        Vertex *v;
        Face   *f;
}              sonva[MAXVF], sonvb[MAXVF];
int     nvtxa, nvtxb;
Edge    *sonea[MAXNE], *soneb[MAXNE];
int     nedga, nedgb;
Face    *sonfa[MAXNF], *sonfb[MAXNF];
int     nfaca, nfacb;

void           addsovf();
void           addsovv();
void           process_edge();
