#include "Square.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const std::string FSquare::ShapeName = "Square";
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
	return 4 * SideLength;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const std::string& FSquare::GetShapeName() const
{
	return ShapeName;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FSquare::operator==(const FSquare& Other) const
{
	return SideLength == Other.SideLength;
}