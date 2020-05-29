#pragma once
#include "stdafx.h"

template < typename T, typename Less = std::less<T> >

bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less = Less())
{
	if (arr.empty())
	{
		return false;
	}
	auto max = arr.begin();
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		if (less(*max, *it))
		{
			max = it;
		}
	}
	maxValue = *max;
	return true;
}
