#pragma once
#pragma comment(lib, "msimg32.lib")

#include "framework.h"

class BitMap
{
private:
	HDC MemDC;
	HBITMAP m_BitMap;
	HBITMAP m_OldBitMap;
	SIZE m_Size;
public:
	BitMap();
	~BitMap();

	void Init(HDC hdc, char* FileName);
	void Draw(HDC hdc, int x, int y);
	SIZE GetSize() const { return m_Size; }
};

// #pragma comment(lib, "msimg32.lib")