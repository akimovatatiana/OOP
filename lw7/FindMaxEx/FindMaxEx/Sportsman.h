#pragma once
#include "stdafx.h"

struct Sportsman
{
	std::string name;
	int height;
	double weight;
};

bool IsHeightLess(Sportsman const& left, Sportsman const& right)
{
	return left.height < right.height;
}

bool IsNameLess(Sportsman const& left, Sportsman const& right)
{
	return left.name < right.name;
}

bool IsWeightLess(Sportsman const& left, Sportsman const& right)
{
	return fabs(left.weight - right.weight) < DBL_EPSILON;
}