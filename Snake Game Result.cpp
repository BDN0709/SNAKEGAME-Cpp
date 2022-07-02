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
int Tick();

struct Snake
{
	int x;
	int y;

}s[100];

struct Apple
{
public:
	int x;
	int y;

	void New()
	{
		x = rand() % (N - 2) + 2;
		y = rand() % (M - 2) + 2;

		for (int i = 0; i < num; i++)
		{
			while (x == s[i].x && y == s[i].y)
			{
				x = rand() % (N - 2) + 2;
				y = rand() % (M - 2) + 2;
			}

		}

		Draw();
	}

	void Draw()
	{
		setcolor(10);

		rectangle(apple.x * Scale, apple.y * Scale, (apple.x + 1) * Scale, (apple.y + 1) * Scale);
	}

}apple;

int main()
{
	srand(time(NULL));

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

			if (button == Up && dir != 3)
				dir = 1;
			if (button == Right && dir != 4)
				dir = 2;
			if (button == Down && dir != 1)
				dir = 3;
			if (button == Left && dir != 2)
				dir = 4;
		}

		if (Tick() == -1)
			return 0;

		Sleep(70);

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
	apple.New();

	return;
}

int Tick()
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

	if (s[0].x == apple.x && s[0].y == apple.y)
	{
		num++;
		apple.New();
	}

	for (int i = 1; i < num; i++)
	{
		if (s[0].x == s[i].x && s[0].y == s[i].y)
		{
			closegraph();
			std::cout << "Вы наехали себе на хвост!" << std::endl;
			std::cout << "Ваш результат = " << num << std::endl;
			return -1;
		}
	}

	if (s[0].y == M)
	{
		s[0].y = 0;
	}
	else
	{
		if (s[0].y == 0)
			s[0].y = M - 1;
	}

	if (s[0].x == N)
	{
		s[0].x = 0;
	}
	else
	{
		if (s[0].x == 0)
			s[0].x = N - 1;
	}

	DrawSnake();

	return 0;

}

void DrawField()
{
	for (int i = 0; i < Height; i += Scale)
		for (int j = 0; j < Width; j += Scale)
			rectangle(i, i, j, j);

	return;
}

void PutSnake()
{
	for (int i = 0; i < num; i++)
	{
		s[i].x = N / 2;
		s[i].y = M / 2 + i;
	}

	return;
}

void DrawSnake()
{
	/*setcolor(3);

	rectangle(s[num].x * Scale, s[num].y * Scale, (s[num].x + 1) * Scale, (s[num].y + 1) * Scale);*/
	cleardevice();  // !!!
	setcolor(15);
	apple.Draw();   // !!!
	for (int i = 0; i < num; i++)
		rectangle(s[i].x * Scale, s[i].y * Scale, (s[i].x + 1) * Scale, (s[i].y + 1) * Scale);

	return;
}