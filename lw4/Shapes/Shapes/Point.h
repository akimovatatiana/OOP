#pragma once

class CPoint
{
public:
	CPoint(double x, double y);

	double x = 0;
	double y = 0;

	std::string ToString() const;
};