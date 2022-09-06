#pragma once

template<typename T, int N>
class TStaticArray
{
private:
	T Data[N];

public:
	int GetSize() const
	{
		return N;
	}
};