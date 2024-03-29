#include "Square.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FSquare::FSquare(const float NewSideLength) : SideLength(NewSideLength)
{
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FSquare::FSquare(const FSquare& Other) : SideLength(Other.SideLength)
{
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float FSquare::GetArea() const
{
	return SideLength * SideLength;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float FSquare::GetPerimeter() const
{
	return 4.f * SideLength;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::string FSquare::GetShapeName() const
{
	return "Square";
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FSquare::operator==(const FSquare& Other) const
{
	return SideLength == Other.SideLength;
}