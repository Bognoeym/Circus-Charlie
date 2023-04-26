#pragma once
#include "BitMapManager.h"
#include "Player.h"
#include "Map.h"

#define BONUS 10000
#define SELETE_X 300
#define SELETE_Y 250

enum SCENE
{
	SCENE_TITLE,
	GAMMING,
	SCENE_END
};


class GameManager
{
private:
	static GameManager* m_hThis;
	int m_iScore;
	int m_iBonus;
	bool m_GetScore;
	bool m_GetRingScore;
	bool m_GetFireScore;
	bool m_GetItemScore;
	float m_fReTime;
	float m_fFinishTime;
	bool m_finish;
	bool m_stop;
	bool m_click;
	POINT m_cussor;
	POINT m_title;

	SCENE m_GameScene;
	HDC m_BackDC;
	RECT m_WindowRect;
	vector<BitMap*> m_arrTitle;
	vector<BitMap*> m_arrInterface;
	Player* m_player;
	Map m_map;
	Obstacle m_obstacle;

	PASS m_score;
	HWND m_hwnd;
public:
	static GameManager* GetInstance()
	{
		if (m_hThis == NULL)
		{
			m_hThis = new GameManager;
		}
		return m_hThis;
	}
	GameManager();
	~GameManager();

	void Init(HWND hWnd);
	void Update(float deltaTime);
	void Draw(HDC hdc);

private:
	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);
	void CheckFinish();
	void CalScore();
};

