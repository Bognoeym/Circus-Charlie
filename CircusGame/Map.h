#pragma once
#include "BitMapManager.h"
#include "Player.h"
#include "Obstacle.h"

class Map
{
private:
	int m_iHeight;
	float m_fWidth;
	float m_fCrowdWid;
	float m_fTrackWid;
	int m_iCrowdCount;
	int m_iTrackCount;
	float m_ixst;
	float m_ixnd;
	float m_fFinish_x;

	int m_imiterY;
	int m_imiter;
	float m_ifinish;
	float m_fBitMapTime;

	bool m_bIsFinish;
	BACKGROUND m_Crowd;

	HDC m_BackDC;
	vector<BitMap*> m_arrBack;
	Player* m_player;
public:
	Map();
	~Map();

	void Init(HDC hdc, float width, Player* player);
	void Update(int speed, float deltaTime);
	void Draw();
	void ChangeBitMap(float deltaTime);
	bool FinishCheck();
	
	float GetHeight();
	bool GetFinish();
};

