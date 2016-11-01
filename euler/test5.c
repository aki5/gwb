# include "gwb.h"

Solid *cursolid;

main()
{
    cursolid = torus(10.0, 3.0, 16, 8);
    solidls(cursolid, 3);
}
