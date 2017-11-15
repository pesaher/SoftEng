#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <list>
#include <iterator>

#define ESC 27
#define LEFT 'a'
#define RIGHT 'd'
#define SHOOT_LEFT 'j'
#define SHOOT_RIGHT 'l'
#define FLOOR "_"
#define CHARACTER "X"
#define ENEMY "O"
#define BULLET_LEFT "<"
#define BULLET_RIGHT ">"
#define MUSHROOM "M"
#define RAIN "'"

const int size = 100;
const char rain = 20;

int main() {
	unsigned char position = 50;
	char mushroom          = -1;
	unsigned int score     = 0;
	char lives             = 3;
	std::list<char> enemies;
	std::list<char> bullets;
	std::list<char> directions;

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
	srand(time(0));
	printf("\n");

	while (true) {

		//INPUT
		if (_kbhit()) {
			char pressed = _getch();
			if (pressed == RIGHT && position < size - 1)
				position++;
			else if (pressed == LEFT && position > 0)
				position--;
			else if (pressed == SHOOT_LEFT) {
				bullets.push_back(position);
				directions.push_back(-1);
				score -= score >= 10 ? 10 : 0;
			}
			else if (pressed == SHOOT_RIGHT) {
				bullets.push_back(position);
				directions.push_back(1);
				score -= score >= 10 ? 10 : 0;
			}
			else if (pressed == ESC)
				return 0;
		}

		//LOGIC
		//Make enemy possibly appear
		if(!(rand() % 50))
			enemies.push_back((rand() % 2) ? -1 : size);
		//Make mushroom possibly appear if not present
		if((rand() % 2) && (mushroom < 0))
			mushroom = rand() % 50;
		//Make enemies move
		for(auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
			*enemy += (*enemy > position) ? -1 : 1;
		//Make bullets move
		for(auto bullet = bullets.begin(), direction = directions.begin(); bullet != bullets.end(); )
			if(*bullet >= 0 && *bullet < size){
				*bullet += *direction;
				bullet++;
				direction++;
			}else{
				bullet = bullets.erase(bullet);
				direction = directions.erase(direction);
			}
		//Kill enemies
		for(auto enemy = enemies.begin(); enemy != enemies.end(); ){
			bool killed = false;
			for(auto bullet = bullets.begin(), direction = directions.begin(); bullet != bullets.end(); )
				if(*bullet == *enemy || (*bullet - *direction) == *enemy){
					bullet = bullets.erase(bullet);
					direction = directions.erase(direction);
					enemy = enemies.erase(enemy);
					killed = true;
					break;
				}else{
					bullet++;
					direction++;
				}
			if(!killed)
				enemy++;
		}
		//Eat mushroom
		if(position == mushroom){
			mushroom = -1;
			score = static_cast<int>(ceil(score * 1.1f));
		}
		//Let enemy kill you
		for(auto enemy = enemies.begin(); enemy != enemies.end(); )
			if(*enemy >= position - 1 && *enemy <= position + 1){
				if(lives > 0){
					lives--;
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
		for(char i = 0; i < size; i++){
			auto iterator = directions.begin();
			auto bullet_iterator = std::find(bullets.begin(), bullets.end(), i);
			if(bullet_iterator != bullets.end())
				std::advance(iterator, (std::distance(bullets.begin(), std::find(bullets.begin(), bullets.end(), i))));
			printf(i == position
				?
				CHARACTER
				:
				((std::find(enemies.begin(), enemies.end(), i) != enemies.end())
					?
					ENEMY
					:
					(!(std::find(bullets.begin(), bullets.end(), i) != bullets.end())
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
						((*iterator) > 0)
							?
							BULLET_RIGHT
							:
							BULLET_LEFT)));
		}
		printf(" LIVES: %u SCORE: %u", lives, score);
		Sleep(20);
	}
	return 0;
}

