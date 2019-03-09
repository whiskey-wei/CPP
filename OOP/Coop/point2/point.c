#include "point.h"
#include <stdio.h>

struct pointPrivate
{
    int x;

    int y;
};

int get_x(point *point_)
{
    return point_->pp->x;
}

int get_y(point *point_)
{
    return point_->pp->y;
}
