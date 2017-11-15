#include "stdafx.h"
#include "Bullet.h"

CBullet::CBullet()
{
	m_position = -1;
	m_direction = 1;
}

CBullet::~CBullet()
{

}
CBullet::CBullet(int position, char direction)
{
	m_position = position;
	m_direction = direction;
}

unsigned char CBullet::GetPosition()
{
	return m_position;
}

void CBullet::Move()
{
	m_position += m_direction;
}