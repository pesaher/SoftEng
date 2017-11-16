#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <list>
#include <iterator>
#include "Character.h"
#include "Bullet.h"
#include "Enemy.h"
#include "RainManager.h"

#define ESC                27
#define LEFT               'a'
#define RIGHT              'd'
#define SHOOT_LEFT         'j'
#define SHOOT_RIGHT        'l'
#define FLOOR              "_"
#define CHARACTER          "X"
#define ENEMY              "O"
#define BULLET_LEFT        "<"
#define BULLET_RIGHT       ">"
#define MUSHROOM           "M"
#define RAIN               "?"
#define FOUND_NOTHING      0
#define FOUND_BULLET_LEFT  -1
#define FOUND_BULLET_RIGHT 1
#define FOUND_ENEMY        2

const unsigned int size = 100;
const unsigned char rain = 20;

int main() {
	char mushroom = -1;
	unsigned int score = 0;

	CCharacter character(2, 40);
	//CRainManager rain(size);

	std::list<CEnemy> enemies;
	std::list<CBullet> bullets;

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
	srand(static_cast<unsigned int>(time(0)));
	printf("\n");

	while (true) {

		//INPUT
		if (_kbhit()) {
			char pressed = _getch();
			if (pressed == RIGHT && character.GetPosition() < size - 1)
				character.MoveRight();
			else if (pressed == LEFT && character.GetPosition() > 0)
				character.MoveLeft();
			else if (pressed == SHOOT_LEFT) {
				CBullet bullet(character.GetPosition(), -1);
				bullets.push_back(bullet);
				score -= score >= 10 ? 10 : 0;
			}
			else if (pressed == SHOOT_RIGHT) {
				CBullet bullet(character.GetPosition(), 1);
				bullets.push_back(bullet);
				score -= score >= 10 ? 10 : 0;
			}
			else if (pressed == ESC)
				return 0;
		}

		//LOGIC
		//Make enemy possibly appear
		if(!(rand() % 50)){
			CEnemy enemy((rand() % 2) ? -1 : size);
			enemies.push_back(enemy);
		}
		//Make mushroom possibly appear if not present
		if((rand() % 2) && (mushroom < 0))
			mushroom = rand() % size;
		//Make enemies move
		for(auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
			(enemy->GetPosition() > character.GetPosition()) ? enemy->MoveLeft() : enemy->MoveRight();
		//Make bullets move
		for(auto bullet = bullets.begin(); bullet != bullets.end(); )
			if(bullet->GetPosition() >= 0 && bullet->GetPosition() < size){
				bullet->Move();
				bullet++;
			}else{
				bullet = bullets.erase(bullet);
			}
		//Kill enemies
		for(auto enemy = enemies.begin(); enemy != enemies.end(); ){
			bool killed = false;
			for(auto bullet = bullets.begin(); bullet != bullets.end(); )
				if(bullet->GetPosition() == enemy->GetPosition() || (bullet->GetPosition() - bullet->GetDirection()) == enemy->GetPosition()){
					bullet = bullets.erase(bullet);
					enemy = enemies.erase(enemy);
					killed = true;
					break;
				}else{
					bullet++;
				}
			if(!killed)
				enemy++;
		}
		//Eat mushroom
		if(character.GetPosition() == mushroom){
			mushroom = -1;
			score = static_cast<int>(ceil(score * 1.1f));
		}
		//Let enemy kill you
		for(auto enemy = enemies.begin(); enemy != enemies.end(); )
			if(enemy->GetPosition() >= character.GetPosition() - 1 && enemy->GetPosition() <= character.GetPosition() + 1){
				if(character.GetLives() > 0){
					character.LoseLife();
					enemy = enemies.erase(enemy);
				}else{
					printf("\n\n  ________.__  __                      .___\n /  _____/|__|/  |_     ____  __ __  __| _/\n/   \\  ___|  \\   __\\   / ___\\|  |  \\/ __ | \n\\    \\_\\  \\  ||  |    / /_/  >  |  / /_/ | \n \\______  /__||__|    \\___  /|____/\\____ | \n        \\/           /_____/            \\/ \n\n");
					system("PAUSE");
					system("PAUSE");
					return -1;
				}
			}else
				enemy++;
		//Increase score
		score++;

		//PRINT
		printf("\r");
		for(unsigned int i = 0; i < size; i++){
			char found = FOUND_NOTHING;
			for(auto bullet = bullets.begin(); bullet != bullets.end(); bullet++)
				if(bullet->GetPosition() == i){
					found = bullet->GetDirection();
					break;
				}
			if(found == FOUND_NOTHING)
				for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
					if (enemy->GetPosition() == i) {
						found = FOUND_ENEMY;
						break;
					}
			printf(i == character.GetPosition()
				?
				CHARACTER
				:
				(found == FOUND_ENEMY)
					?
					ENEMY
					:
					((found == FOUND_NOTHING)
						?
						(i == mushroom
							?
							MUSHROOM
							:
							((rand() % rain)
								?
								FLOOR
								:
								RAIN))
						:
						((found == FOUND_BULLET_RIGHT)
							?
							BULLET_RIGHT
							:
							BULLET_LEFT)));
		}
		printf(" LIVES: %u SCORE: %u                   ", character.GetLives(), score);
		Sleep(20);
	}
	return 0;
}

