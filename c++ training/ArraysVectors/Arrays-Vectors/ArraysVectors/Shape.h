#pragma once
#include <iostream>

class FShape
{
private:
	const static std::string ShapeName;

public:
	virtual float GetArea() const;
	virtual float GetPerimeter() const;
	virtual const std::string& GetShapeName() const;
};