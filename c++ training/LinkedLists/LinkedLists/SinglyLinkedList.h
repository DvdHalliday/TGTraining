#pragma once

template<typename T>
class TSLList
{
private:
	FNode* Head = nullptr;
	FNode* Tail = nullptr;
	int Size = 0;

	struct FNode
	{
	public:
		T Value;
		FNode* Next;

		FNode(const T& NewValue, const FNode* NewNext = nullptr) : Value(NewValue), Next(NewNext) {}
	};

public:
	TSLList() {}
	TSLList(const T& Value) : Size(1)
	{
		Head = new FNode(Value);
		Tail = Head;
	}
};