#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{

}

void BitMapManager::Init(HWND hWnd)
{
	char buf[256];
	BitMap bitmapTmp;
	HDC hdc = GetDC(hWnd);

	for (int i = TITLE::TITLE_START; i < TITLE::TITLE_END; i++)
	{
		sprintf_s(buf, "RES//Menu//0%d.bmp", i);
		bitmapTmp.Init(hdc, buf);
		m_TitleBitMap.push_back(new BitMap(bitmapTmp));
	}

	for (int i = BACKGROUND::BG_START; i < BACKGROUND::BG_END; i++)
	{
		sprintf_s(buf, "RES//Background//0%d.bmp", i);
		bitmapTmp.Init(hdc, buf);
		m_BackgroundBM.push_back(new BitMap(bitmapTmp));
	}

	for (int i = PLAYER::P_START; i < PLAYER::P_END; i++)
	{
		sprintf_s(buf, "RES//Player//0%d.bmp", i);
		bitmapTmp.Init(hdc, buf);
		m_PlayerBitMap.push_back(new BitMap(bitmapTmp));
	}

	for (int i = OBSTACLE::OB_START; i < OBSTACLE::OB_END; i++)
	{
		sprintf_s(buf, "RES//Obstacle//0%d.bmp", i);
		bitmapTmp.Init(hdc, buf);
		m_ObstacleBitMap.push_back(new BitMap(bitmapTmp));
	}

	for (int i = INTERFACE::INT_START; i < INTERFACE::INT_END; i++)
	{
		sprintf_s(buf, "RES//Interface//0%d.bmp", i);
		bitmapTmp.Init(hdc, buf);
		m_InterfaceBitMap.push_back(new BitMap(bitmapTmp));
	}

	ReleaseDC(hWnd, hdc);
}



BitMapManager::~BitMapManager()
{

}