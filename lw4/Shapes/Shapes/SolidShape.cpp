#include "stdafx.h"
#include "SolidShape.h"

CSolidShape::CSolidShape(const std::string& type, uint32_t outlineColor, uint32_t fillColor)
	: CShape::CShape(type, outlineColor)
	, m_fillColor(fillColor)
{
}

uint32_t CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}

uint32_t CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string CSolidShape::ToString() const
{
	return CShape::ToString();
}