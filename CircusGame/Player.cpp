#include "Player.h"

Player::Player() : m_iJumpSpeed(50)
{
	m_currentBM = PLAYER::WALK1;
}

void Player::Init(HDC hdc)
{
	m_BackDC = hdc;
	m_fx = PLAYERX;
	m_fy = GROUND;
	m_iSpeed = 0;
	m_iJump = JUMPPOWER;
	m_JumpCheck = false;
	m_arrPlayer = BitMapManager::GetInstance()->GetPlayerArray();
	m_Die = false;
	m_playerMove = false;
	m_finish = false;
	m_Moving = false;
	m_fDistance = LENGTH::START;
	m_fFinishTime = 0;
	m_fBitMapTime = 0;

	m_iHeart = HEART;

	rect.left = m_fx + 5;
	rect.top = m_fy + 2;
	rect.right = rect.left + m_arrPlayer[m_currentBM]->GetSize().cx - 5;
	rect.bottom = rect.top + m_arrPlayer[m_currentBM]->GetSize().cy - 2;
}

void Player::Move(float deltaTime)
{
	m_Moving = false;

	if (m_Die || m_finish)
	{
		m_JumpCheck = false;
	}
	else
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			m_fDistance -= 1;
			m_iSpeed = SPEED;
			m_Moving = true;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			m_iSpeed = -SPEED;
			m_fDistance += 1;
			m_Moving = true;
		}
		else
		{
			m_iSpeed = 0;
		}

		if (GetAsyncKeyState(VK_SPACE))
		{
			if (m_JumpCheck != true)
			{
				m_JumpCheck = true;
			}
		}

		if (m_Moving)
		{
			m_fBitMapTime += deltaTime;
			if (m_fBitMapTime >= 0.05f)
			{
				m_fBitMapTime = 0;
				switch (m_currentBM)
				{
				case PLAYER::WALK1:
					m_currentBM = PLAYER::WALK2;
					break;
				default:
					m_currentBM = PLAYER::WALK1;
					break;
				}
			}
		}
		else
			m_currentBM = PLAYER::WALK1;

		if (m_playerMove)
		{
			if (m_fx < PLAYERX)
				m_fx = PLAYERX;
			else
				m_fx -= m_iSpeed * deltaTime;
		}
	}

	if (m_JumpCheck)
	{
		m_currentBM = PLAYER::JUMP;
		Jump(deltaTime);
	}
}

bool Player::EndMoving(bool check)
{
	if (m_fDistance < LENGTH::START)
	{
		m_fDistance = 0;
		return false;
	}
	else if (m_iSpeed > 0 && m_fx < PLAYERX)
	{
		m_fx = PLAYERX;
		return true;
	}
	else if (check)
	{
		m_playerMove = true;
		return false;
	}
	else
	{
		m_playerMove = false;
	}

	return true;
}

void Player::Jump(float deltaTime)
{
	m_iJump += m_iJumpSpeed * deltaTime;
	m_fy += m_iJump;

	if (m_fy <= MAX)
	{
		m_iJump = 0;
	}

	if (GROUND <= m_fy)
	{
		m_iJump = JUMPPOWER;
		m_fy = GROUND;
		m_JumpCheck = false;
	}

	rect.top = m_fy;
	rect.bottom = rect.top + m_arrPlayer[m_currentBM]->GetSize().cy;
}

void Player::Collision()
{
	m_currentBM = PLAYER::DIE;
	m_Die = true;
	m_iHeart -= 1;
}

bool Player::CheckGround()
{
	if (m_fy >= GROUND)
		return true;
	
	return false;
}

void Player::Finish(float height, float deltaTime)
{
	m_finish = true;
	float pHeight = m_arrPlayer[m_currentBM]->GetSize().cy;
	m_fFinishTime += deltaTime;
	m_fy = (height - pHeight);
	m_fx = LENGTH::FINISH_LINE;

	if (m_fy >= (height - pHeight))
	{
		m_fy = (height - pHeight);
		m_iJump = JUMPPOWER;

		switch (m_currentBM)
		{
		case END1:
			break;
		case END2:
			break;
		default:
			m_currentBM = PLAYER::END1;
			break;
		}

		if (m_fFinishTime >= 0.1f)
		{
			m_fFinishTime = 0;

			switch (m_currentBM)
			{
			case END1:
				m_currentBM = PLAYER::END2;
				break;
			case END2:
				m_currentBM = PLAYER::END1;
				break;
			}
		}
	}
}

void Player::SetState()
{
	if (m_Die)
	{
		m_Die = false;
		m_fy = GROUND;
	}
	else
		m_Die = true;

	m_currentBM = PLAYER::WALK1;
}

float Player::GetRightX()
{
	float width = m_arrPlayer[PLAYER::WALK1]->GetSize().cx;

	return m_fx + width;
}

void Player::Draw()
{
	m_arrPlayer[m_currentBM]->Draw(m_BackDC, m_fx, m_fy);
}

Player::~Player()
{

}