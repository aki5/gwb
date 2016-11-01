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

unsigned nodesize[] =
{
        sizeof(Solid), sizeof(Face), sizeof(Loop),
        sizeof(HalfEdge), sizeof(Edge), sizeof(Vertex), 0,
};

Node    *new(what, where)
int     what;
Node    *where;
{
        Node    *node;
        char    *malloc();

        node = (Node *) malloc(nodesize[what]);
    if(node == NULL)
        printf("new: malloc() failed!\n");

        switch(what)
        {
                case SOLID:
                        node->s.sfaces = (Face *) NIL;
                        node->s.sedges = (Edge *) NIL;
                        node->s.sverts = (Vertex *) NIL;
                        break;
                case FACE:
                        addlist(FACE, node, where);
                        node->f.floops = (Loop *) NIL;
                        node->f.flout = (Loop *) NIL;
                        break;
                case LOOP:
                        addlist(LOOP, node, where);
                        break;
                case EDGE:
                        addlist(EDGE, node, where);
                        break;
                case VERTEX:
                        addlist(VERTEX, node, where);
                        node->v.vedge = (HalfEdge *) NIL;
                        break;
                default:
                        break;
        }
        return(node);
}
