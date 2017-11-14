#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define ESC 27
#define LEFT 'a'
#define RIGHT 'd'
#define SHOOT_LEFT 'z'
#define SHOOT_RIGHT 'c'

const int size = 100;

int main(){
	char position  = 50;
	char bullet    = -1;
	char enemy     = -1;
	char direction = 0;

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);

	while(true){

		//INPUT
		if(_kbhit()){
			char pressed = _getch();
			if(pressed == RIGHT && position < size - 1)
				position++;
			else if(pressed == LEFT && position > 0)
				position--;
			else if(pressed == SHOOT_LEFT && (bullet < 0 || bullet >= size)){
				bullet = position;
				direction = -1;
			}
			else if(pressed == SHOOT_RIGHT && (bullet < 0 || bullet >= size)){
				bullet = position;
				direction = 1;
			}
			else if(pressed == ESC)
				return 0;
		}

		//LOGIC
		//Make enemy possibly appear if not present
		if((rand() % 2) && (enemy < 0 || enemy >= size))
			enemy = (rand() % 2) ? 0 : size - 1;
		//Make enemy move if he hasn't just appeared
		else if(enemy >= 0 || enemy < size)
			enemy += (enemy > position) ? -1 : 1;
		//Make bullet move
		if(bullet >= 0 && bullet < size)
			bullet += direction;
		else
			direction = 0;
		//Kill enemy
		if(bullet == enemy || (bullet - direction) == enemy){
			bullet = -1;
			direction = 0;
			enemy = -1;
		}
		//Let enemy kill you
		if(enemy >= position - 1 && enemy <= position + 1){
			printf("\n\n  ________.__  __                      .___\n /  _____/|__|/  |_     ____  __ __  __| _/\n/   \\  ___|  \\   __\\   / ___\\|  |  \\/ __ | \n\\    \\_\\  \\  ||  |    / /_/  >  |  / /_/ | \n \\______  /__||__|    \\___  /|____/\\____ | \n        \\/           /_____/            \\/ \n\n");
			system("PAUSE");
			return -1;
		}

		//PRINT
		printf("\r");
		for(char i = 0; i < size; i++)
			printf(i == position ? "X" : (i == enemy ? "O" : (i != bullet ? "_" : (direction > 0) ? ">" : "<")));
		Sleep(20);
	}
    return 0;
}

