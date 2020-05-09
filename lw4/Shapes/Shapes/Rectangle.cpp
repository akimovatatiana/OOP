#include "Rectangle.h"
#include "LineSegment.h"

CRectangle::CRectangle(const CPoint& topLeft, double width, double height, uint32_t fillColor, uint32_t outlineColor)
	: CSolidShape("Rectangle", outlineColor, fillColor)
	, m_topLeft(topLeft)
	, m_width(width)
	, m_height(height)
{
}

double CRectangle::GetArea() const
{
	return (m_width * m_height);
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

CPoint CRectangle::GetTopLeft() const
{
	return m_topLeft;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::AppendProperties(std::ostream& strm) const
{
	strm << "\tFill color = #" << setfill('0') << setw(6) << hex << GetFillColor() << endl
		<< "\tTop left = " << m_topLeft.ToString() << endl
		<< "\tWidth = " << GetWidth() << endl
		<< "\tHeight = " << GetHeight() << endl;
}

