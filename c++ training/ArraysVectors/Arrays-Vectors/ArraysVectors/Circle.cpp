#include "Circle.h"

FCircle::FCircle(const int NewRadius) : Radius(NewRadius)
{
}

float FCircle::GetArea() const
{
	return Radius * Radius * 3.141592653589793238462643383279502884f;
}

float FCircle::GetPerimeter() const
{
	return 2 * Radius * 3.141592653589793238462643383279502884f;
}
