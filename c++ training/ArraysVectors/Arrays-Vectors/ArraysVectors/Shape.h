#pragma once
#include <iostream>

class FShape
{
public:
	virtual float GetArea() const = 0;
	virtual float GetPerimeter() const = 0;
	virtual const std::string GetShapeName() const = 0;
};
