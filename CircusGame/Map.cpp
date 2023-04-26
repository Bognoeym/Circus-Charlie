#include "Map.h"

Map::Map()
{

}

void Map::Init(HDC hdc, float width, Player* player)
{
	m_BackDC = hdc;
	m_ixst = 0;
	m_arrBack = BitMapManager::GetInstance()->GetBackArray();
	m_fWidth = width;
	m_iHeight = 100;

	m_fCrowdWid = m_arrBack[BACKGROUND::CROWD1]->GetSize().cx;
	m_iCrowdCount = m_fWidth / m_fCrowdWid;
	m_ixnd = m_ixst + (m_iCrowdCount * m_fCrowdWid);

	m_fTrackWid = m_arrBack[BACKGROUND::TRACK]->GetSize().cx;
	m_iTrackCount = m_fWidth / m_fTrackWid;

	m_imiterY = 360;
	m_imiter = 100;

	m_bIsFinish = false;
	m_Crowd = BACKGROUND::CROWD1;
	m_fBitMapTime = 0;
	m_fFinish_x = 0;
	m_player = player;
}

void Map::Update(int speed, float deltaTime)
{
	if (m_player->GetState())
		return;

	m_ixst += speed * deltaTime;
	m_ixnd += speed * deltaTime;

	if (m_fFinish_x != 0)
		m_fFinish_x += speed * deltaTime;

	if (-(m_iCrowdCount * m_fCrowdWid) >= m_ixst)
	{
		m_ixst = m_ixnd + (m_iCrowdCount * m_fCrowdWid);
		m_imiter -= 20;
	}
	if ((m_iCrowdCount * m_fCrowdWid) <= m_ixst)
	{
		m_ixst = m_ixnd - (m_iCrowdCount * m_fCrowdWid);
		m_imiter += 20;
	}
	if (-(m_iCrowdCount * m_fCrowdWid) >= m_ixnd)
	{
		m_ixnd = m_ixst + (m_iCrowdCount * m_fCrowdWid);
	}
	if ((m_iCrowdCount * m_fCrowdWid) <= m_ixnd)
	{
		m_ixnd = m_ixst - (m_iCrowdCount * m_fCrowdWid);
	}

	if (m_imiter <= 0)
	{
		if (m_fFinish_x == 0)
			m_fFinish_x = m_ixnd + (m_ixst - m_ixnd);
	}
}

void Map::ChangeBitMap(float deltaTime)
{
	m_fBitMapTime += deltaTime;
	if (m_fBitMapTime >= 0.05f)
	{
		m_fBitMapTime = 0;
		switch (m_Crowd)
		{
		case CROWD1:
			m_Crowd = BACKGROUND::CROWD2;
				break;
		case CROWD2:
			m_Crowd = BACKGROUND::CROWD1;
			break;
		}
	}
}

bool Map::FinishCheck()
{
	if (m_fFinish_x != 0)
	{
		if ((m_player->GetRightX() - 10) >= m_fFinish_x)
			return true;
	}
	return false;
}

void Map::Draw()
{
	float height = m_arrBack[BACKGROUND::CROWD2]->GetSize().cy;

	for (int i = 0; i < m_iCrowdCount; i++)
	{
		m_arrBack[m_Crowd]->Draw(m_BackDC, m_ixst + (i * m_fCrowdWid), m_iHeight);
		m_arrBack[m_Crowd]->Draw(m_BackDC, m_ixnd + (i * m_fCrowdWid), m_iHeight);
	}

	for (int i = 0; i <= m_iTrackCount; i++)
	{
		m_arrBack[BACKGROUND::TRACK]->Draw(m_BackDC, m_ixst + (i * m_fTrackWid), m_iHeight + height);
		m_arrBack[BACKGROUND::TRACK]->Draw(m_BackDC, m_ixnd + (i * m_fTrackWid), m_iHeight + height);
	}

	m_arrBack[BACKGROUND::MITER]->Draw(m_BackDC, m_ixst + 10, m_imiterY);
	m_arrBack[BACKGROUND::MITER]->Draw(m_BackDC, m_ixst + (m_ixnd - m_ixst), m_imiterY);


	SetTextColor(m_BackDC, RGB(255, 255, 255));
	SetBkColor(m_BackDC, RGB(0, 0, 0));

	string str = to_string(m_imiter);
	TextOutA(m_BackDC, m_ixst + 30, m_imiterY + 5, str.c_str(), str.length());
	str = to_string(m_imiter - 10);
	TextOutA(m_BackDC, m_ixst + (m_ixnd - m_ixst) + 30, m_imiterY + 5, str.c_str(), str.length());

	if (m_fFinish_x != 0)
	{
		float height2 = m_arrBack[BACKGROUND::TRACK]->GetSize().cy - m_arrBack[BACKGROUND::FINISH]->GetSize().cy;

		m_fFinish_x = (m_fFinish_x <= LENGTH::FINISH_LINE) ? LENGTH::FINISH_LINE : m_fFinish_x;
		m_arrBack[BACKGROUND::FINISH]->Draw(m_BackDC, m_fFinish_x, m_iHeight + height + height2);
	}
}

float Map::GetHeight()
{
	float height = m_arrBack[BACKGROUND::CROWD1]->GetSize().cy;
	float height2 = m_arrBack[BACKGROUND::TRACK]->GetSize().cy - m_arrBack[BACKGROUND::FINISH]->GetSize().cy;

	return (m_iHeight + height + height2);
}

bool Map::GetFinish()
{
	if (m_fFinish_x != 0)
	{
		if (m_fFinish_x <= LENGTH::FINISH_LINE)
			return true;
	}

	return false;
}

Map::~Map()
{

}