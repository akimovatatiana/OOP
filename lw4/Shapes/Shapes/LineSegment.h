#pragma once
#include "Shape.h"
#include "Point.h"
#include "Header.h"

class CLineSegment : public CShape
{
public:
	CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t lineColor);
	
	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
private:
	CPoint m_startPoint;
	CPoint m_endPoint;

	void AppendProperties(std::ostream& strm) const override;
};

double GetDistance(CPoint startPoint, CPoint endPoint);