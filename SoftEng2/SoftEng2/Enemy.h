#pragma once

class CEnemy
{
public:
	CEnemy();
	CEnemy(int position);
	~CEnemy();

	int GetPosition();
	void MoveLeft();
	void MoveRight();

private:
	unsigned int m_position;
};
