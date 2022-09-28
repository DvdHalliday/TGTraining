#pragma once

template<typename T>
class TSLList
{
private:
	struct FNode
	{
	public:
		T Value;
		FNode* Next;

		FNode(const T& NewValue, FNode* NewNext = nullptr) : Value(NewValue), Next(NewNext) {}
	};

	FNode* Head = nullptr;
	FNode* Tail = nullptr;
	int Size = 0;

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	FNode& GetNodeAt(const int Index) const
	{
		FNode* CurrentNode = Head;
		for (int i = 0; i < Index; i++)
		{
			CurrentNode = CurrentNode->Next;
		}

		return *CurrentNode;
	}

public:
	TSLList() {}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	TSLList(const T& Value) : Size(1)
	{
		Head = new FNode(Value);
		Tail = Head;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	TSLList(const TSLList<T>& Other)
	{
		FNode* CurrentNode = Other.Head;
		for (int i = 0; i < Other.GetSize(); i++)
		{
			AddTail(CurrentNode->Value);
			CurrentNode = CurrentNode->Next;
		}
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	~TSLList()
	{
		Clear();
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	TSLList& operator=(const TSLList<T>& Other)
	{
		Clear();

		for (T Item : Other)
		{
			AddTail(Item);
		}

		return *this;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	T& operator[](const int Index)
	{
		return GetNodeAt(Index).Value;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	const T& operator[](const int Index) const
	{
		return GetNodeAt(Index).Value;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	T& GetHead()
	{
		return Head->Value;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	const T& GetHead() const
	{
		return Head->Value;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	T& GetTail()
	{
		return Tail->Value;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	const T& GetTail() const
	{
		return Tail->Value;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	bool IsEmpty() const
	{
		return Size == 0;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	int GetSize() const
	{
		return Size;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void AddHead(const T& Value)
	{
		if (IsEmpty())
		{
			Head = new FNode(Value);
			Tail = Head;

			Size = 1;
			return;
		}

		Head = new FNode(Value, Head);
		Size++;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void AddTail(const T& Value)
	{
		if (IsEmpty())
		{
			AddHead(Value);
			return;
		}

		Tail->Next = new FNode(Value);
		Tail = Tail->Next;

		Size++;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void Insert(const T& Value, const int Index)
	{
		if (Index < 0 || Index > Size)
		{
			return;
		}

		if (Index == 0)
		{
			AddHead(Value);
			return;
		}
		else
		{
			FNode& PreviousNode = GetNodeAt(Index - 1);
			PreviousNode.Next = new FNode(Value, PreviousNode.Next);
			
			if (Index == Size)
			{
				Tail = Tail->Next;
			}

			Size++;
		}
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void Remove(const int Index)
	{
		if (Index < 0 || Index >= Size)
		{
			return;
		}

		if (Index == 0)
		{
			FNode* NodeToDeletePtr = Head;
			Head = NodeToDeletePtr->Next;

			delete NodeToDeletePtr;
			NodeToDeletePtr = nullptr;

			if (Size == 1)
			{
				Tail = nullptr;
			}
		}
		else
		{
			FNode& PreviousNode = GetNodeAt(Index - 1);
			FNode* NodeToDeletePtr = PreviousNode.Next;

			PreviousNode.Next = NodeToDeletePtr->Next;

			delete NodeToDeletePtr;
			NodeToDeletePtr = nullptr;

			if (Index == Size - 1)
			{
				Tail = &PreviousNode;
			}
		}

		Size--;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void Clear()
	{
		int OriginalSize = Size;
		for (int i = 0; i < OriginalSize; i++)
		{
			Remove(0);
		}
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	class FIterator
	{
	private:
		FNode* Current;

	public:
		FIterator(FNode* NewCurrent) : Current(NewCurrent) {}

		FIterator& operator++()
		{
			Current = Current->Next;
			return *this;
		}

		T& operator*()
		{
			return Current->Value;
		}

		bool operator!=(const FIterator& Other)
		{
			return Current != Other.Current;
		}
	};
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	FIterator begin() const
	{
		return FIterator(Head);
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	FIterator end() const
	{
		return FIterator(nullptr);
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<typename Pred>
	void ForEach(const Pred& Predicate)
	{
		for (T& Item : *this)
		{
			Predicate(Item);
		}
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<typename Pred>
	T* FindByPredicate(const Pred& Predicate) const
	{
		for (T& Item : *this)
		{
			if (Predicate(Item))
			{
				return &Item;
			}
		}

		return nullptr;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<typename Pred>
	TSLList<T> FilterByPredicate(const Pred& Predicate) const
	{
		TSLList<T> NewList;
		
		for (T& Item : *this)
		{
			if (Predicate(Item))
			{
				NewList.AddTail(Item);
			}
		}
		
		return NewList;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<typename Pred>
	void RemoveAllByPredicate(const Pred& Predicate)
	{
		FNode* CurrentNode = Head;
		for (int i = 0; i < Size; i++)
		{
			if (Predicate(CurrentNode->Value))
			{
				CurrentNode = CurrentNode->Next;
				Remove(i--);
			}
			else
			{
				CurrentNode = CurrentNode->Next;
			}
		}
	}
};