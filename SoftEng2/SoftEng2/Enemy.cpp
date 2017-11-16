#include "stdafx.h"
#include "Enemy.h"

CEnemy::CEnemy()
{
	m_position = -1;
}

CEnemy::~CEnemy()
{

}
CEnemy::CEnemy(int position)
{
	m_position = position;
}

int CEnemy::GetPosition()
{
	return m_position;
}

void CEnemy::MoveLeft()
{
	m_position--;
}

void CEnemy::MoveRight()
{
	m_position++;
}