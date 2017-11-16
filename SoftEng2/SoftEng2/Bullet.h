#pragma once

class CBullet
{
public:
	CBullet();
	CBullet(int position, char direction);
	~CBullet();

	unsigned char GetPosition();
	char GetDirection();
	void Move();

private:
	unsigned int m_position;
	unsigned char m_direction;
};