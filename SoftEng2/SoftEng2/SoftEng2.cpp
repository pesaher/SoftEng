#include "stdafx.h"
#include <conio.h>
#include <windows.h>
#include "World.h"

#define ESC         27
#define LEFT        'a'
#define RIGHT       'd'
#define SHOOT_LEFT  'j'
#define SHOOT_RIGHT 'l'

const unsigned int  size       = 100;
const unsigned char rainChance = 20;

int main() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);

	CWorld world(2, size, rainChance);

	while(true){

		//Input
		if(_kbhit()) {
			char pressed = _getch();
			if(pressed == RIGHT)
				world.MoveRight();
			else if(pressed == LEFT)
				world.MoveLeft();
			else if(pressed == SHOOT_LEFT)
				world.ShootLeft();
			else if(pressed == SHOOT_RIGHT)
				world.ShootRight();
			else if(pressed == ESC)
				return 0;
		}

		//Logic
		if(world.Update() == -1)
			return -1;

		//Print
		world.Print();
	}
	return 0;
}

