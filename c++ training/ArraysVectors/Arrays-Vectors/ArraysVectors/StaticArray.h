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

	T& operator[](int Index)
	{
		return Data[Index];
	}

	const T& operator[](int Index) const
	{
		return Data[Index];
	}

	T& Front()
	{
		return Data[0];
	}
	
	const T& Front() const
	{
		return Data[0];
	}

	T& Back()
	{
		return Data[N-1];
	}

	const T& Back() const
	{
		return Data[N-1];
	}

	T* GetData()
	{
		return &Data[0];
	}

	const T* GetData() const
	{
		return &Data[0];
	}
};