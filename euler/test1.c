# include "gwb.h"

main()
{
    Solid    *s;

    s = mvfs(1, 1, 0.0, 0.0, 0.0);
solidls(s, 3);
    mev(s, 1, 1, 2, 1.0, 0.0, 0.0);
solidls(s, 3);
    mev(s, 1, 2, 3, 1.0, 1.0, 0.0);
solidls(s, 3);
    listsolid(s);
}
