#pragma once
#include "SolidShape.h"
#include "Point.h"

class CCircle : public CSolidShape
{
public:
	CCircle(const CPoint& center, double radius, uint32_t fillColor, uint32_t outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetCenter() const;
	double GetRadius() const;
private:
	CPoint m_center;
	double m_radius;

	void AppendProperties(std::ostream& strm) const override;
};



