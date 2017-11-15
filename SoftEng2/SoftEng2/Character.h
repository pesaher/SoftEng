#pragma once

class CCharacter
{
public:
	CCharacter();
	CCharacter(unsigned char lives, unsigned int position);
	~CCharacter();

	unsigned char GetLives();
	int GetPosition();
	void GainLife();
	void LoseLife();
	void MoveLeft();
	void MoveRight();

private:
	unsigned char m_lives;
	unsigned int m_position;
};