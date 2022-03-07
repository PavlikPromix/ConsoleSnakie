#pragma once

struct Point
{
	short x, y;
	Point(short x, short y) : x(x), y(y) {}
	bool operator==(const Point& lhs) const
	{
		return (x == lhs.x) && (y == lhs.y);
	}
};