#include "Obstacle.h"

Obstacle::Obstacle()
{

}

void Obstacle::Init(HDC hdc, Player* player)
{
	m_ring.clear();
	m_fireRects.clear();
	m_miniRing.clear();

	m_BackDC = hdc;
	m_RingPoint.x = 700;
	m_RingPoint.y = 160;
	m_iSpeed = -300;
	m_iMiniSpeed = -400;

	m_ixst = -100;
	m_ixnd = m_ixst + (DISTANCE * 2);
	m_ifireHeight = 295;

	m_arrObstacle = BitMapManager::GetInstance()->GetObstacleArray();
	m_fireBitMap = OBSTACLE::FIRE1;

	m_fRingTime = 0;
	m_fMiniTime = 0;
	m_fBitMapTime = 0;

	m_ringCheck = false;
	m_fireCheck = false;

	m_player = player;

	Ring ringTmp;
	float width = m_arrObstacle[OBSTACLE::LEFTRING1]->GetSize().cx;
	float height = m_arrObstacle[OBSTACLE::LEFTRING1]->GetSize().cy;
	ringTmp.point = m_RingPoint;
	ringTmp.rect.left = m_RingPoint.x + width;
	ringTmp.rect.right = ringTmp.rect.left + 1;
	ringTmp.rect.top = m_RingPoint.y + (height - 1);
	ringTmp.rect.bottom = m_RingPoint.y + height;
	m_ring.push_back(ringTmp);

	RECT tmp;
	tmp.left = m_ixst + 10;
	tmp.right = tmp.left + m_arrObstacle[m_fireBitMap]->GetSize().cx - 10;
	tmp.top = m_ifireHeight + 3;
	tmp.bottom = tmp.top + m_arrObstacle[m_fireBitMap]->GetSize().cy;
	m_fireRects.push_back(new RECT(tmp));

	tmp.left = m_ixst + DISTANCE + 10;
	tmp.right = tmp.left + m_arrObstacle[m_fireBitMap]->GetSize().cx - 10;
	m_fireRects.push_back(new RECT(tmp));

	tmp.left = m_ixnd + 10;
	tmp.right = tmp.left + m_arrObstacle[m_fireBitMap]->GetSize().cx - 10;
	m_fireRects.push_back(new RECT(tmp));

	tmp.left = m_ixnd + DISTANCE + 10;
	tmp.right = tmp.left + m_arrObstacle[m_fireBitMap]->GetSize().cx - 10;
	m_fireRects.push_back(new RECT(tmp));
}

PASS Obstacle::Update(int speed, float deltaTime, float width)
{
	m_fireCheck = false;
	m_ringCheck = false;
	
	EraseRing(width);

	/*if (CollisionCheck())
		return PASS::COLLISION;*/

	m_ixst += speed * deltaTime;
	m_ixnd += speed * deltaTime;
	m_fRingTime += deltaTime;
	m_fMiniTime += deltaTime;
	m_fBitMapTime += deltaTime;

	if (m_fBitMapTime >= 0.1f)
	{
		m_fBitMapTime = 0;
		switch (m_fireBitMap)
		{
		case FIRE1:
			m_fireBitMap = OBSTACLE::FIRE2;
			break;
		case FIRE2:
			m_fireBitMap = OBSTACLE::FIRE1;
			break;
		}
	}

	if (-(DISTANCE * 2) >= m_ixst)
	{
		m_ixst = m_ixnd + (DISTANCE * 2);
	}
	if ((DISTANCE * 2) <= m_ixst)
	{
		m_ixst = m_ixnd - (DISTANCE * 2);
	}
	if (-(DISTANCE * 2) >= m_ixnd)
	{
		m_ixnd = m_ixst + (DISTANCE * 2);
	}
	if ((DISTANCE * 2) <= m_ixnd)
	{
		m_ixnd = m_ixst - (DISTANCE * 2);
	}

	for (auto iter = m_fireRects.begin(); iter != m_fireRects.end(); iter++)
	{
		(*iter)->left += speed * deltaTime;
		(*iter)->right += speed * deltaTime;
	}

	if (0.8f <= m_fRingTime)
	{
		m_fRingTime = 0;

		m_RingPoint.x = m_ring.back().point.x + (width * 0.7f);

		Ring ringTmp;
		float width = m_arrObstacle[OBSTACLE::LEFTRING1]->GetSize().cx;
		ringTmp.point = m_RingPoint;
		ringTmp.rect.left = m_RingPoint.x + (width / 2);
		ringTmp.rect.right = ringTmp.rect.left + width;
		ringTmp.rect.top = m_ring.back().rect.top;
		ringTmp.rect.bottom = m_ring.back().rect.bottom;
		m_ring.push_back(ringTmp);
	}

	for (auto iter = m_ring.begin(); iter != m_ring.end(); iter++)
	{
		iter->point.x += (m_iSpeed + speed) * deltaTime;
		iter->rect.left += (m_iSpeed + speed) * deltaTime;
		iter->rect.right += (m_iSpeed + speed) * deltaTime;
	}

	if (2.5f <= m_fMiniTime)
	{
		m_fMiniTime = 0;

		m_RingPoint.x = m_ring.back().point.x + (width * 0.7f);

		MiniRing tmp;
		float width = m_arrObstacle[OBSTACLE::MINIRING_LEFT]->GetSize().cx;
		float height = m_arrObstacle[OBSTACLE::MINIRING_LEFT]->GetSize().cy;

		float itemWidth = m_arrObstacle[OBSTACLE::CASH]->GetSize().cx;
		float itemHeight = m_arrObstacle[OBSTACLE::CASH]->GetSize().cy;
		tmp.point = m_RingPoint;
		tmp.rect.left = m_RingPoint.x + (width / 2);
		tmp.rect.right = tmp.rect.left + width;
		tmp.rect.top = m_RingPoint.y + (height - 1);
		tmp.rect.bottom = m_RingPoint.y + height;

		tmp.itemRect.left = m_RingPoint.x + (width - (itemWidth/2));
		tmp.itemRect.right = tmp.itemRect.left + itemWidth;
		tmp.itemRect.top = m_RingPoint.y + 25;
		tmp.itemRect.bottom = tmp.itemRect.top + itemHeight;
		tmp.passItem = ITEM_STATE::F;

		m_miniRing.push_back(tmp);
	}

	for (auto iter = m_miniRing.begin(); iter != m_miniRing.end(); iter++)
	{
		iter->point.x += (m_iMiniSpeed + speed) * deltaTime;
		iter->rect.left += (m_iMiniSpeed + speed) * deltaTime;
		iter->rect.right += (m_iMiniSpeed + speed) * deltaTime;

		iter->itemRect.left += (m_iMiniSpeed + speed) * deltaTime;
		iter->itemRect.right += (m_iMiniSpeed + speed) * deltaTime;
	}

	return PassCheck();
}

bool Obstacle::CollisionCheck()
{
	RECT playerRect = m_player->GetRect();
	RECT rectTmp;

	for (auto iter = m_ring.begin(); iter != m_ring.end(); iter++)
	{
		if (IntersectRect(&rectTmp, &(iter->rect), &playerRect))
		{
			return true;
		}
		else
		{
			if (iter->rect.left >= playerRect.left && iter->rect.top >= playerRect.bottom && 
				iter->rect.right <= playerRect.right)
			{
				m_ringCheck = true;
				break;
			}
		}
	}

	if (!m_miniRing.empty())
	{
		for (auto iter = m_miniRing.begin(); iter != m_miniRing.end(); iter++)
		{
			if (IntersectRect(&rectTmp, &(iter->rect), &playerRect))
			{
				return true;
			}
			else
			{
				if (iter->rect.left >= playerRect.left && iter->rect.top >= playerRect.bottom && 
					iter->rect.right <= playerRect.right)
				{
					iter->passItem = ITEM_STATE::T;
					break;
				}
			}
		}
	}

	for (auto iter = m_fireRects.begin(); iter != m_fireRects.end(); iter++)
	{
		float halfRect;

		if (IntersectRect(&rectTmp, (*iter), &playerRect))
		{
			return true;
		}
		else
		{
			if ((*iter)->left >= playerRect.left && (*iter)->right <= playerRect.right)
			{
				m_fireCheck = true;
				break;
			}
		}
	}

	return false;
}

void Obstacle::EraseRing(float width)
{
	if (!m_ring.empty())
	{
		for (auto iter = m_ring.begin(); iter != m_ring.end(); iter++)
		{
			if (iter->point.x < -(width * 2))
			{
				m_ring.erase(iter);
				break;
			}
		}
	}

	if (!m_miniRing.empty())
	{
		for (auto iter = m_miniRing.begin(); iter != m_miniRing.end(); iter++)
		{
			if (iter->point.x < -(width * 2))
			{
				m_miniRing.erase(iter);
				break;
			}
		}
	}
}

PASS Obstacle::PassCheck()
{
	for (auto iter = m_miniRing.begin(); iter != m_miniRing.end(); iter++)
	{
		if (iter->passItem == ITEM_STATE::T)
		{
			iter->passItem = ITEM_STATE::GET;
			return PASS::ITEM;
		}
	}

	if (m_ringCheck)
	{
		return PASS::RING;
	}
	if (m_fireCheck)
	{
		return PASS::FIRE;
	}

	return PASS::NONE;
}

void Obstacle::Draw()
{
	m_arrObstacle[m_fireBitMap]->Draw(m_BackDC, m_ixst, m_ifireHeight);
	m_arrObstacle[m_fireBitMap]->Draw(m_BackDC, m_ixst + DISTANCE, m_ifireHeight);
	m_arrObstacle[m_fireBitMap]->Draw(m_BackDC, m_ixnd, m_ifireHeight);
	m_arrObstacle[m_fireBitMap]->Draw(m_BackDC, m_ixnd + DISTANCE, m_ifireHeight);

	float size = m_arrObstacle[OBSTACLE::LEFTRING1]->GetSize().cx;
	for (auto iter = m_ring.begin(); iter != m_ring.end(); iter++)
	{
		m_arrObstacle[OBSTACLE::LEFTRING1]->Draw(m_BackDC, iter->point.x, iter->point.y);
	}

	if (!m_miniRing.empty())
	{
		for (auto iter = m_miniRing.begin(); iter != m_miniRing.end(); iter++)
		{
			m_arrObstacle[OBSTACLE::MINIRING_LEFT]->Draw(m_BackDC, iter->point.x, iter->point.y);

			if (iter->passItem == ITEM_STATE::F)
			{
				m_arrObstacle[OBSTACLE::CASH]->Draw(m_BackDC, iter->itemRect.left, iter->itemRect.top);
			}
		}
	}
}

void Obstacle::RightRingDraw()
{
	float size = m_arrObstacle[OBSTACLE::LEFTRING1]->GetSize().cx;
	for (auto iter = m_ring.begin(); iter != m_ring.end(); iter++)
	{
		m_arrObstacle[OBSTACLE::RIGHTRING1]->Draw(m_BackDC, iter->point.x + size, iter->point.y);
	}

	if (!m_miniRing.empty())
	{
		float minisize = m_arrObstacle[OBSTACLE::MINIRING_LEFT]->GetSize().cx;
		for (auto iter = m_miniRing.begin(); iter != m_miniRing.end(); iter++)
		{
			m_arrObstacle[OBSTACLE::MINIRING_RIGHT]->Draw(m_BackDC, iter->point.x + minisize, iter->point.y);
		}
	}
}

Obstacle::~Obstacle()
{

}