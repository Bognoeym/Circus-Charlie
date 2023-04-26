#pragma once
#include "BitMapManager.h"
#include "Player.h"
#include <list>

#define DISTANCE 600

enum PASS
{
	NONE,
	COLLISION,
	RING = 100,
	FIRE = 200,
	ITEM = 500
};

enum ITEM_STATE
{
	F,
	T,
	GET
};

struct Ring
{
	POINT point;
	RECT rect;
};

struct MiniRing
{
	POINT point;
	RECT rect;
	RECT itemRect;
	ITEM_STATE passItem;
};

class Obstacle
{
private:
	float m_ixst;
	float m_ixnd;
	int m_ifireHeight;

	POINT m_RingPoint;
	int m_iSpeed;
	int m_iMiniSpeed;
	float m_fRingTime;
	float m_fMiniTime;
	float m_fBitMapTime;

	bool m_ringCheck;
	bool m_fireCheck;

	HDC m_BackDC;
	vector<BitMap*> m_arrObstacle;
	list<Ring> m_ring;
	list<MiniRing> m_miniRing;
	list<RECT*> m_fireRects;
	OBSTACLE m_fireBitMap;
	Player* m_player;
public:
	Obstacle();
	~Obstacle();

	void Init(HDC hdc, Player* player);
	PASS Update(int speed, float deltaTime, float width);
	void Draw();
	void RightRingDraw();
	void EraseRing(float width);

	bool CollisionCheck();
	PASS PassCheck();
};

