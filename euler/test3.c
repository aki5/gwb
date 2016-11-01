# include "gwb.h"

main()
{
    Solid    *s;

    s = mvfs(1, 1, 0.0, 1.0, 0.0);
    mev(s, 1, 1, 2, 1.0, 2.0, 0.0);
    mev(s, 1, 2, 3, 2.0, 1.0, 0.0);
    rsweep(s, 3);
    solidls(s, 2);
}
