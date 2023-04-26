#pragma once
#include "BitMap.h"
#include "Mecro.h"
#include <vector>
#include <string>

using namespace std;

class BitMapManager
{
private:
	static BitMapManager* m_hThis;
	vector<BitMap*> m_TitleBitMap;
	vector<BitMap*> m_BackgroundBM;
	vector<BitMap*> m_PlayerBitMap;
	vector<BitMap*> m_ObstacleBitMap;
	vector<BitMap*> m_InterfaceBitMap;
public:
	static BitMapManager* GetInstance()
	{
		if (m_hThis == NULL)
		{
			m_hThis = new BitMapManager;
		}
		return m_hThis;
	}
	vector<BitMap*> GetTitleArray() { return m_TitleBitMap; }
	vector<BitMap*> GetBackArray() { return m_BackgroundBM; }
	vector<BitMap*> GetPlayerArray() { return m_PlayerBitMap; }
	vector<BitMap*> GetObstacleArray() { return m_ObstacleBitMap; }
	vector<BitMap*> GetInterfaceArray() { return m_InterfaceBitMap; }
	
	BitMapManager();
	~BitMapManager();
	void Init(HWND hWnd);
};

