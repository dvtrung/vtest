#include "Account.h"
#pragma once

class CAccArray
{
public:
	CAccArray(void);
public:
	~CAccArray(void);

public:
	CArray<CAccount*, CAccount*>m_Array;
	void SaveAccount();
	void LoadAccount();
	CAccount* AddAccount();
};
