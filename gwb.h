# include <stdio.h>
# include <math.h>
# define VAX 1

typedef float                   vector[4];
typedef float                   matrix[4][4];
#ifdef VAX
typedef short                   Id;
#endif
#ifdef MAC
typedef int                     Id;
#endif
typedef struct solid            Solid;
typedef struct face             Face;
typedef struct loop             Loop;
typedef struct halfedge         HalfEdge;
typedef struct vertex           Vertex;
typedef struct edge             Edge;
typedef union nodes             Node;

struct solid
{
        Face            *sfaces;        /* pointer to list of faces */
        Edge            *sedges;        /* pointer to list of edges */
        Vertex          *sverts;        /* pointer to list of vertices */
};
struct face
{
        Id              faceno;         /* face identifier */
        Solid           *fsolid;        /* back pointer to solid */
        Loop            *flout;         /* pointer to outer loop */
        Loop            *floops;        /* pointer to list of loops */
        vector          feq;            /* face equation */
        Face            *nextf;         /* pointer to next face */
        Face            *prevf;         /* pointer to previous face */
};
struct loop
{
        HalfEdge        *ledg;          /* pointer to ring of halfedges */
        Face            *lface;         /* back pointer to face */
        Loop            *nextl;         /* pointer to next loop */
        Loop            *prevl;         /* pointer to previous loop */
};
struct edge
{
        HalfEdge        *he1;           /* pointer to right halfedge */
        HalfEdge        *he2;           /* pointer to left halfedge */
        Edge            *nexte;         /* pointer to next edge */
        Edge            *preve;         /* pointer to previous edge */
};
struct halfedge
{
        Edge            *edg;           /* pointer to parent edge */
        Vertex          *vtx;           /* pointer to starting vertex */
        Loop            *wloop;         /* back pointer to loop */
        HalfEdge        *nxt;           /* pointer to next halfedge */
        HalfEdge        *prv;           /* pointer to previous halfedge */
};
struct vertex
{
        Id              vertexno;       /* vertex identifier */
        HalfEdge        *vedge;         /* pointer to an adjacent halfedge */
        vector          vcoord;         /* vertex coordinates */
        Vertex          *nextv;         /* pointer to next vertex */
        Vertex          *prevv;         /* pointer to previous vertex */
};
union nodes
{
        Solid           s;
        Face            f;
        Loop            l;
        HalfEdge        h;
        Vertex          v;
        Edge            e;
};

# include "params.h"
