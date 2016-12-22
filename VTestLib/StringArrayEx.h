#include "stdafx.h"

class CStringArrayEx : public CStringArray
{
public:
	int operator = (CStringArray& other)
	{
		RemoveAll();
		for (int i=0;i<other.GetSize();i++)
			Add(other[i]);
	}
};