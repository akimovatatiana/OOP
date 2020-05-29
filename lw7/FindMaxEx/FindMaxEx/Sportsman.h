#pragma once
#include "stdafx.h"

struct Sportsman
{
	std::string name;
	int height;
	double weight;
};

bool IsHeightLess(const Sportsman& left, const Sportsman& right)
{
	return left.height < right.height;
}

bool IsNameLess(const Sportsman& left, const Sportsman& right)
{
	return left.name < right.name;
}

bool IsWeightLess(const Sportsman& left, const Sportsman& right)
{
	return fabs(left.weight - right.weight) < DBL_EPSILON;
}