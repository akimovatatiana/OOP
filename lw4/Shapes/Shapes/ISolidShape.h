#pragma once
#include "IShape.h"
#include "Header.h"

class ISolidShape : public virtual IShape
{
public:
	virtual ~ISolidShape() = default;

	virtual uint32_t GetFillColor() const = 0;
};

