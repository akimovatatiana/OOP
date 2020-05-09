#include "Shape.h"
#include "Header.h"

CShape::CShape(const std::string& type, uint32_t outlineColor)
	: m_type(type)
	, m_outlineColor(outlineColor)
{
}

uint32_t CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CShape::ToString() const
{
	ostringstream strm;
	strm << m_type << ":" << endl 
		<< fixed << setprecision(4)
		<< "\tArea = " << GetArea() << endl
		<< "\tPerimeter = " << GetPerimeter() << endl
		<< "\tOutline color = #" << setfill('0') << setw(6) << hex << GetOutlineColor() << endl;
	AppendProperties(strm);
	return strm.str();
}