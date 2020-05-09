#pragma once
#include "ISolidShape.h"
#include "Shape.h"

class CSolidShape : public ISolidShape,
	public CShape
{
public:
	CSolidShape(const std::string& type, uint32_t outlineColor, uint32_t fillColor);
	uint32_t GetOutlineColor() const final;
	uint32_t GetFillColor() const override;

	std::string ToString() const;
private:
	uint32_t m_fillColor;
};

