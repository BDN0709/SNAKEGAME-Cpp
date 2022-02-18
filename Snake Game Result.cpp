#include "graphics.h"
#pragma comment(lib,"graphics.lib")
#include <Windows.h>
#include <ctime>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define Left 75
#define Right 77
#define Up 72
#define Down 80

int M = 30, N = 30, Scale = 20;
int Width = N * Scale, Height = M * Scale;
int dir = 1, num = 3;

void IniGr();
void DrawField();
void PutSnake();
void DrawSnake();
void Tick();

struct Snake
{
	int x;
	int y;

}s[100];

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	SetConsoleTitle(L"Snake Game!");

	IniGr();

	int button = NULL;

	while (1)
	{
		if (kbhit())
		{
			button = getch();

			if (button == Up)
				dir = 1;
			if (button == Right)
				dir = 2;
			if (button == Down)
				dir = 3;
			if (button == Left)
				dir = 4;
		}

		Tick();
		Sleep(150);

	}

	closegraph();

	return 0;
}

void IniGr()
{
	initwindow(Width, Height, "Snake Game!");

	setcolor(3);
	DrawField();

	PutSnake();

	return;
}

void Tick()
{
	for (int i = num; i > 0; i--)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	if (dir == 1)
		s[0].y -= 1;
	if (dir == 2)
		s[0].x += 1;
	if (dir == 3)
		s[0].y += 1;
	if (dir == 4)
		s[0].x -= 1;


	DrawSnake();

}

void DrawField()
{
	for (int i = 0; i < Height; i += Scale)
		for (int j = 0; j < Width; j += Scale)
			rectangle(i, i, j, j);
}

void PutSnake()
{
	for (int i = 0; i < num; i++)
	{
		s[i].x = N / 2;
		s[i].y = M / 2 + i;
	}
}

void DrawSnake()
{
	setcolor(5);

	rectangle(s[num].x * Scale, s[num].y * Scale, (s[num].x + 1) * Scale, (s[num].y + 1) * Scale);

	setcolor(15);

	for (int i = 0; i < num; i++)
		rectangle(s[i].x * Scale, s[i].y * Scale, (s[i].x + 1) * Scale, (s[i].y + 1) * Scale);

}