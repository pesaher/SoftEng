#pragma once

#include "Character.h"
#include "Bullet.h"
#include "Enemy.h"
#include "RainManager.h"
#include <list>

#define CHARACTER          "X"
#define ENEMY              "O"
#define BULLET_LEFT        "<"
#define BULLET_RIGHT       ">"
#define MUSHROOM           "M"
#define RAIN               "'"
#define FOUND_NOTHING      0
#define FOUND_BULLET_LEFT  -1
#define FOUND_BULLET_RIGHT 1
#define FOUND_ENEMY        2

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
