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

/*
**    Geometric WorkBench V 0.6
**
**    Copyright (c) 1984 TEKES-Project, Helsinki Univ. of Tech.
**
**    inside()
**    - version 0.1
**
**    Form a vector pointing at the inside of the face of halfedge he
**
**    History:
**    - written by MaM (Feb 19, 1984)
*/

void        inside(he, in)
HalfEdge    *he;
vector        in;
{
    vector        eq, dir;

    vecminus(dir, he->nxt->vtx->vcoord, he->vtx->vcoord);
    faceeq(he->wloop->lface->flout, eq);
    cross(in, eq, dir);

# ifdef TEST
printf("in   : %f %f %f\n", in[0], in[1], in[2]);
printf("norm : %f %f %f\n", eq[0], eq[1], eq[2]);
printf("dir  : %f %f %f\n", dir[0], dir[1], dir[2]);
# endif
}
