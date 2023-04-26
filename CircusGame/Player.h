#pragma once
#include "BitMapManager.h"

#define PLAYERX 40
#define SPEED 500

#define MAX 190
#define GROUND 280
#define JUMPPOWER -12

#define HEART 4

enum LENGTH
{
	START = 0,
	END = 1330,
	FINISH_LINE = 800
};

class Player
{
private:
	float m_fDistance;

	float m_fx;
	float m_fy;
	float m_iSpeed;
	float m_iJump;
	float m_fFinishTime;
	float m_fBitMapTime;
	const float m_iJumpSpeed;
	bool m_JumpCheck;
	bool m_Die;
	bool m_playerMove;
	bool m_finish;
	bool m_Moving;
	int m_iHeart;
	HDC m_BackDC;
	vector<BitMap*> m_arrPlayer;
	PLAYER m_currentBM;
	RECT rect;
public:
	Player();
	~Player();
	void Init(HDC hdc);
	void Move(float deltaTime);
	void Jump(float deltaTime);
	void Draw();
	void Collision();
	bool CheckGround();
	bool EndMoving(bool check);
	void Finish(float height, float deltaTime);

	void SetState();
	inline int GetSpeed() { return m_iSpeed; }
	RECT GetRect() { return rect; }
	bool GetState() { return m_Die; }
	int GetHeart() { return m_iHeart; }
	float GetDistance() { return m_fDistance; }
	float GetRightX();

private:
};

