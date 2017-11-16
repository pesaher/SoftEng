#include "stdafx.h"
#include "World.h"
#include <time.h>
#include <math.h>
#include <windows.h>

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

CWorld::CWorld()
{
	m_lives           = 2;
	m_size            = 100;
	m_rainChance      = 20;
	m_mushroom        = -1;
	m_score           = 0;
	m_charToString    = new char[2];
	m_charToString[1] = 0;

	m_character = new CCharacter(2, floor(m_size / 2));
	m_rain      = new CRainManager(m_size, m_rainChance);

	srand(static_cast<unsigned int>(time(0)));
	printf("\n");
}

CWorld::~CWorld()
{
	delete []m_character;
	m_character = nullptr;
	delete []m_rain;
	m_rain = nullptr;
}

CWorld::CWorld(unsigned char lives, unsigned int size, unsigned char rainChance)
{
	m_lives           = lives;
	m_size            = size;
	m_rainChance      = rainChance;
	m_mushroom        = -1;
	m_score           = 0;
	m_charToString    = new char[2];
	m_charToString[1] = 0;

	m_character = new CCharacter(lives, floor(size / 2));
	m_rain      = new CRainManager(size, rainChance);

	srand(static_cast<unsigned int>(time(0)));
	printf("\n");
}

void CWorld::MoveLeft()
{
	if(m_character->GetPosition() > 0)
		m_character->MoveLeft();
}

void CWorld::MoveRight()
{
	if(m_character->GetPosition() < m_size - 1)
		m_character->MoveRight();
}

void CWorld::ShootLeft()
{
	CBullet bullet(m_character->GetPosition(), -1);
	m_bullets.push_back(bullet);
	m_score -= m_score >= 10 ? 10 : 0;
}

void CWorld::ShootRight()
{
	CBullet bullet(m_character->GetPosition(), 1);
	m_bullets.push_back(bullet);
	m_score -= m_score >= 10 ? 10 : 0;
}

int CWorld::Update()
{
	//Make enemy possibly appear
	if(!(rand() % 50)){
		CEnemy enemy((rand() % 2) ? -1 : m_size);
		m_enemies.push_back(enemy);
	}
	//Make mushroom possibly appear if not present
	if((rand() % 2) && (m_mushroom < 0))
		m_mushroom = rand() % m_size;
	//Make enemies move
	for(auto enemy = m_enemies.begin(); enemy != m_enemies.end(); enemy++)
		(enemy->GetPosition() > m_character->GetPosition()) ? enemy->MoveLeft() : enemy->MoveRight();
	//Make bullets move
	for(auto bullet = m_bullets.begin(); bullet != m_bullets.end(); )
		if(bullet->GetPosition() >= 0 && bullet->GetPosition() < m_size){
			bullet->Move();
			bullet++;
		}
		else{
			bullet = m_bullets.erase(bullet);
		}
		//Kill enemies
		for(auto enemy = m_enemies.begin(); enemy != m_enemies.end(); ){
			bool killed = false;
			for(auto bullet = m_bullets.begin(); bullet != m_bullets.end(); )
				if(bullet->GetPosition() == enemy->GetPosition() || (bullet->GetPosition() - bullet->GetDirection()) == enemy->GetPosition()){
					bullet = m_bullets.erase(bullet);
					enemy = m_enemies.erase(enemy);
					killed = true;
					break;
				}
				else{
					bullet++;
				}
				if(!killed)
					enemy++;
		}
		//Let enemy kill you
		for(auto enemy = m_enemies.begin(); enemy != m_enemies.end(); )
			if(enemy->GetPosition() >= m_character->GetPosition() - 1 && enemy->GetPosition() <= m_character->GetPosition() + 1){
				if(m_character->GetLives() > 0){
					m_character->LoseLife();
					enemy = m_enemies.erase(enemy);
				}
				else{
					printf("\n\n  ________.__  __                      .___\n /  _____/|__|/  |_     ____  __ __  __| _/\n/   \\  ___|  \\   __\\   / ___\\|  |  \\/ __ | \n\\    \\_\\  \\  ||  |    / /_/  >  |  / /_/ | \n \\______  /__||__|    \\___  /|____/\\____ | \n        \\/           /_____/            \\/ \n\n");
					system("PAUSE");
					system("PAUSE");
					delete []m_charToString;
					return -1;
				}
			}
			else
				enemy++;
		//Eat mushroom
		if(m_character->GetPosition() == m_mushroom){
			m_mushroom = -1;
			m_score = static_cast<int>(ceil(m_score * 1.1f));
		}
		//Update rain
		m_rain->UpdateRain();
		//Increase score
		m_score++;
		Sleep(20);
}

void CWorld::Print()
{
	printf("\r");
	for (unsigned int i = 0; i < m_size; i++) {
		char found = FOUND_NOTHING;
		m_charToString[0] = m_rain->GetRain(i);
		for (auto bullet = m_bullets.begin(); bullet != m_bullets.end(); bullet++)
			if (bullet->GetPosition() == i) {
				found = bullet->GetDirection();
				break;
			}
		if (found == FOUND_NOTHING)
			for (auto enemy = m_enemies.begin(); enemy != m_enemies.end(); enemy++)
				if (enemy->GetPosition() == i) {
					found = FOUND_ENEMY;
					break;
				}
		printf(i == m_character->GetPosition()
			?
			CHARACTER
			:
			(found == FOUND_ENEMY)
			?
			ENEMY
			:
			((found == FOUND_NOTHING)
				?
				(i == m_mushroom
					?
					MUSHROOM
					:
					m_charToString)
				:
				((found == FOUND_BULLET_RIGHT)
					?
					BULLET_RIGHT
					:
					BULLET_LEFT)));
	}
	printf(" LIVES: %u SCORE: %u                   ", m_character->GetLives(), m_score);
}