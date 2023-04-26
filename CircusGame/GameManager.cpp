#include "GameManager.h"

GameManager* GameManager::m_hThis = NULL;

GameManager::GameManager()
{
	m_GameScene = SCENE_TITLE;
	m_player = new Player();
}

void GameManager::Init(HWND hWnd)
{
	BitMapManager::GetInstance()->Init(hWnd);

	HDC hdc = GetDC(hWnd);
	GetWindowRect(hWnd, &m_WindowRect);
	m_BackDC = CreateCompatibleDC(hdc);
	m_hwnd = hWnd;

	m_arrTitle = BitMapManager::GetInstance()->GetTitleArray();
	m_arrInterface = BitMapManager::GetInstance()->GetInterfaceArray();

	m_player->Init(m_BackDC);
	m_map.Init(m_BackDC, m_WindowRect.right - m_WindowRect.left, m_player);
	m_obstacle.Init(m_BackDC, m_player);

	m_iScore = 0;
	m_iBonus = BONUS;
	m_fReTime = 0;
	m_fFinishTime = 0;

	m_GetScore = true;
	m_GetFireScore = false;
	m_GetRingScore = false;
	m_GetItemScore = false;
	m_finish = false;
	m_stop = false;
	m_click = false;

	m_title.x = SELETE_X;
	m_title.y = SELETE_Y;
	m_cussor.x = m_title.x - m_arrTitle[TITLE::TITLE_POINT]->GetSize().cx - 10;
	m_cussor.y = m_title.y;
}

void GameManager::Update(float deltaTime)
{
	switch (m_GameScene)
	{
	case SCENE_TITLE:
	{
		float height = m_arrTitle[TITLE::SELECT1]->GetSize().cy;
		if (GetAsyncKeyState(VK_UP))
		{
			if (!m_click)
			{
				m_click = true;
				if (m_cussor.y <= SELETE_Y)
				{
					m_cussor.y = SELETE_Y;
					return;
				}
				m_cussor.y -= height;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (!m_click)
			{
				m_click = true;
				if (m_cussor.y >= (SELETE_Y + (height * 3)))
				{
					m_cussor.y = (SELETE_Y + (height * 3));
					return;
				}
				m_cussor.y += height;
			}
		}
		else
		{
			m_click = false;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{
			m_GameScene = SCENE::GAMMING;
		}
	}
	break;
	case GAMMING:
	{
		m_player->Move(deltaTime);

		int speed = m_player->GetSpeed();
		if (m_player->EndMoving(m_map.GetFinish()))
			m_map.Update(speed, deltaTime);
		else
			speed = 0;
		m_score = m_obstacle.Update(speed, deltaTime, m_WindowRect.right - m_WindowRect.left);

		if (m_player->GetState())
		{
			m_fReTime += deltaTime;
			m_stop = true;

			if (m_fReTime >= 0.7f)
			{
				m_fReTime = 0;

				if (m_player->GetHeart() == 0)
				{
					m_GameScene = SCENE::SCENE_TITLE;
					Init(m_hwnd);
					return;
				}
				m_player->SetState();
				m_obstacle.Init(m_BackDC, m_player);
				m_iBonus = BONUS;
				m_stop = false;
			}
			return;
		}

		CalScore();

		if (!m_finish || !m_stop)
			m_iBonus -= 1;

		if (m_player->CheckGround())
		{
			m_GetFireScore = false;
			m_GetRingScore = false;
			m_GetItemScore = false;
			m_GetScore = true;
		}

		if (m_finish)
		{
			m_fFinishTime += deltaTime;
			m_stop = true;

			if (m_fFinishTime >= 2.0f)
			{
				m_fFinishTime = 0;
				m_GameScene = SCENE::SCENE_END;
			}

			m_player->Finish(m_map.GetHeight(), deltaTime);

			if (m_iBonus != 0)
			{
				m_iScore += m_iBonus;
				m_iBonus = 0;
			}

			m_map.ChangeBitMap(deltaTime);
		}
		else
		{
			CheckFinish();
		}
	}
	break;
	case SCENE_END:
	{
		// 끝났을 때 메세지 박스나 뭔가 뜨도록
		if (MessageBox(m_hwnd, L"Complete", L"창", MB_OK) == IDOK)
		{
			m_GameScene = SCENE::SCENE_TITLE;
			Init(m_hwnd);
		}
	}
	break;
	}
}

void GameManager::CalScore()
{
	switch (m_score)
	{
	case NONE:
		break;
	case COLLISION:
		m_player->SetState();
		m_player->Collision();
		return;
	case RING:
		if (!m_GetRingScore)
		{
			m_GetRingScore = true;
			m_GetScore = false;
		}
		break;
	case FIRE:
		if (!m_GetFireScore)
		{
			m_GetFireScore = true;
			m_GetScore = false;
		}
		break;
	case ITEM:
		if (!m_GetItemScore)
		{
			m_GetItemScore = true;
			m_GetScore = false;
		}
		break;
	}

	if (!m_GetScore)
	{
		m_iScore += (int)m_score;
		m_GetScore = true;
	}
}

void GameManager::CheckFinish()
{
	if (m_map.FinishCheck())
	{
		m_finish = true;
		return;
	}

	m_finish = false;
}

void GameManager::Draw(HDC hdc)
{
	HBITMAP backBitmap = CreateDIBSectionRe(hdc, m_WindowRect.right - m_WindowRect.left, m_WindowRect.bottom - m_WindowRect.top);
	HBITMAP oldBack = (HBITMAP)SelectObject(m_BackDC, backBitmap);

	switch (m_GameScene)
	{
	case SCENE_TITLE:
	{
		m_arrTitle[TITLE::TITLE_BM]->Draw(m_BackDC, m_title.x, 70);
		m_arrTitle[TITLE::MENU]->Draw(m_BackDC, m_title.x - 50, 170);

		int y = m_title.y;
		float height = m_arrTitle[TITLE::SELECT1]->GetSize().cy;
		for (int i = TITLE::SELECT1; i <= TITLE::SELECT4; i++)
		{
			m_arrTitle[i]->Draw(m_BackDC, m_title.x, y);
			y += height;
		}

		m_arrTitle[TITLE::TITLE_POINT]->Draw(m_BackDC, m_cussor.x, m_cussor.y);
	}
	break;
	case GAMMING:
	{
		m_map.Draw();
		m_obstacle.Draw();
		m_player->Draw();
		m_obstacle.RightRingDraw();

		///// 값 수정
		m_arrInterface[INTERFACE::INFOMATION]->Draw(m_BackDC, 60, 10);

		int count = m_player->GetHeart();
		int x = m_arrInterface[INTERFACE::INFOMATION]->GetSize().cx + 20;
		for (int i = 0; i < count; i++)
		{
			m_arrInterface[INTERFACE::LIFE]->Draw(m_BackDC, x, 45);
			x -= m_arrInterface[INTERFACE::LIFE]->GetSize().cx;
		}
		/////

		SetTextColor(m_BackDC, RGB(255, 255, 255));
		SetBkColor(m_BackDC, RGB(0, 0, 0));

		string str = "Score: " + to_string(m_iScore);
		TextOutA(m_BackDC, 200, 30, str.c_str(), str.length());
		str = "Bonus: " + to_string(m_iBonus);
		TextOutA(m_BackDC, 600, 30, str.c_str(), str.length());
	}
	break;
	case SCENE_END:
	{

	}
	break;
	}

	BitBlt(hdc, 0, 0, m_WindowRect.right - m_WindowRect.left, m_WindowRect.bottom - m_WindowRect.top, m_BackDC, 0, 0, SRCCOPY);
	SelectObject(m_BackDC, oldBack);
	DeleteObject(backBitmap);
}

HBITMAP GameManager::CreateDIBSectionRe(HDC hdc, int width, int height)
{
	BITMAPINFO bm_info;
	ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));
	bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bm_info.bmiHeader.biBitCount = 24; // 컬러 수(color bits) : 1, 4, 8, 16, 24, 31
	bm_info.bmiHeader.biWidth = width; // 너비.
	bm_info.bmiHeader.biHeight = height;// 높이.
	bm_info.bmiHeader.biPlanes = 1;

	LPVOID pBits;
	return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}

GameManager::~GameManager()
{
	delete m_player;
	ReleaseDC(m_hwnd, m_BackDC);
}