#include "../../../include/kmint/pigisland/rectangle.h"

kmint::pigisland::rectangle::rectangle(int x, int y, int w, int h) : x_{x}, y_{y}, w_{w}, h_{h}
{
}

bool kmint::pigisland::rectangle::overlaps(int x, int y, int w, int h) const
{
	return x < x_ + w_ && x + w > x_ && y < y_ + h_ && y + h > y_;
}
