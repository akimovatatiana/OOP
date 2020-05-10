#include "stdafx.h"
#include "Point.h"

CPoint::CPoint(double x, double y)
	: x(x)
	, y(y)
{
}

string CPoint::ToString() const
{
	ostringstream strm;
	strm << "(" << x << ", " << y << ")";

	return strm.str();
}