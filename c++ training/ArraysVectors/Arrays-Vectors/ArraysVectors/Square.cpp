#include "Square.h"

FSquare::FSquare(const int NewSideLength) : SideLength(NewSideLength)
{
}

float FSquare::GetArea() const
{
	return SideLength * SideLength;
}

float FSquare::GetPerimeter() const
{
	return 4 * SideLength;
}
