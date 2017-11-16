#pragma once

#include "Character.h"
#include "Bullet.h"
#include "Enemy.h"
#include "RainManager.h"
#include <list>

class CWorld
{
public:
	CWorld();
	CWorld(unsigned char lives, unsigned int size, unsigned char rainChance);
	~CWorld();

	void MoveLeft();
	void MoveRight();
	void ShootLeft();
	void ShootRight();
	int  Update();
	void Print();

private:
	unsigned char m_lives;
	unsigned int  m_size;
	unsigned char m_rainChance;

	char         m_mushroom;
	unsigned int m_score;
	char         *m_charToString;

	CCharacter        *m_character;
	CRainManager      *m_rain;
	std::list<CEnemy>  m_enemies;
	std::list<CBullet> m_bullets;
};
