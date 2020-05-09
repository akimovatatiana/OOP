#include "LineSegment.h"
#include "Header.h"

CLineSegment::CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t lineColor)
	: CShape("Line segment", lineColor)
	, m_startPoint(startPoint)
	, m_endPoint(endPoint)
{
}
double CLineSegment::GetArea() const
{
	return 0.0;
}
double CLineSegment::GetPerimeter() const
{
	return GetDistance(m_startPoint, m_endPoint);
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}
CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::AppendProperties(std::ostream& strm) const
{
	strm << "\tStart point = " << m_startPoint.ToString() << endl
		<< "\tEnd point = " << m_endPoint.ToString() << endl;
}

double GetDistance(CPoint startPoint, CPoint endPoint)
{
	return sqrt(pow(endPoint.x - startPoint.x, 2) + pow(endPoint.y - startPoint.y, 2));
}
