#pragma once
#include "SolidShape.h"
#include "Point.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(const CPoint& topLeft, double width, double height, uint32_t fillColor, uint32_t outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetTopLeft() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_topLeft;
	double m_width;
	double m_height;

	void AppendProperties(std::ostream& strm) const override;
};
