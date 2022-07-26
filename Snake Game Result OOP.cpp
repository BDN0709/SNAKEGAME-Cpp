#include "graphics.h"
#pragma comment(lib,"graphics.lib")
#include <Windows.h>
#include <ctime>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int M = 30, N = 30, Scale = 20;
int Width = N * Scale, Height = M * Scale;

class Snake;

class Apple
{
private:

	int x;
	int y;
public:
	void Draw()
	{
		setcolor(LIGHTGREEN);

		rectangle(x * Scale, y * Scale, (x + 1) * Scale, (y + 1) * Scale);

		setcolor(WHITE);
	}

public:

	void New(Snake& snake);

	int GetX()
	{
		return x;
	}

	int GetY()
	{
		return y;
	}

}apple;

enum SnakeDirection
{
	UP, RIGHT, DOWN, LEFT
};

class Snake
{
private:

	static int length;
	static SnakeDirection dir;

	struct Part
	{
		int x;
		int y;

	}s[100];

public:

	void SetDirection(const SnakeDirection& dir)
	{
		this->dir = dir;
	}

	SnakeDirection GetDirection()
	{
		return dir;
	}

	int GetLength()
	{
		return length;
	}

	Part operator [] (const int& which)
	{
		return s[which];
	}

	void Put()
	{
		for (int i = 0; i < length; i++)
		{
			s[i].x = N / 2;
			s[i].y = M / 2 + i - 1;
		}
	}

	void Move()
	{
		for (int i = length; i > 0; i--)
		{
			s[i].x = s[i - 1].x;
			s[i].y = s[i - 1].y;
		}

		if (s[0].x == 0)
			s[0].x = N;
		else
			if (s[0].x == N)
				s[0].x = 0;


		if (s[0].y == 0)
			s[0].y = M;
		else
			if (s[0].y == M)
				s[0].y = 0;

		if (dir == UP)
			s[0].y -= 1;
		if (dir == RIGHT)
			s[0].x += 1;
		if (dir == DOWN)
			s[0].y += 1;
		if (dir == LEFT)
			s[0].x -= 1;

	}

	bool Bump()
	{
		for (int i = 1; i < length; i++)
			if (s[0].x == s[i].x && s[0].y == s[i].y)
				return true;

		return false;
	}

	bool Eat(Apple& apple)
	{
		if (s[0].x == apple.GetX() && s[0].y == apple.GetY())
		{
			length++;
			return true;
		}
		else
			return false;
	}

	void Draw()
	{
		/*setcolor(CYAN);
		rectangle(s[length].x * Scale, s[length].y * Scale, (s[length].x + 1) * Scale, (s[length].y + 1) * Scale);
		setcolor(WHITE);*/
		
		for (int i = 0; i < length; i++)
			rectangle(s[i].x * Scale, s[i].y * Scale, (s[i].x + 1) * Scale, (s[i].y + 1) * Scale);
	}

}snake;

int Snake::length = 3;
SnakeDirection Snake::dir = UP;

void Apple::New(Snake& snake)
{
	x = rand() % (N - 3) + 1;
	y = rand() % (M - 3) + 1;

	for (int i = 0; i < snake.GetLength(); i++)
		while (x == snake[i].x && y == snake[i].y)
			New(snake);

	Draw();
}

void DrawField()
{
	setcolor(CYAN);
	for (int i = 0; i < Height; i += Scale)
		for (int j = 0; j < Width; j += Scale)
			rectangle(i, i, j, j);
	setcolor(WHITE);
}

int main()
{
	srand(time(NULL));

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	SetConsoleTitle(L"SNAKE GAME!!!");

	initwindow(Width, Height, "SNAKE GAME!!!");

	//DrawField();
	snake.Put();
	apple.New(snake);

	int button = NULL;
	
	while (true)
	{
		cleardevice();  // !!
		if (kbhit())
		{
			button = getch();

			if (button == KEY_UP && snake.GetDirection() != DOWN)
				snake.SetDirection(UP);

			if (button == KEY_RIGHT && snake.GetDirection() != LEFT)
				snake.SetDirection(RIGHT);

			if (button == KEY_DOWN && snake.GetDirection() != UP)
				snake.SetDirection(DOWN);

			if (button == KEY_LEFT && snake.GetDirection() != RIGHT)
				snake.SetDirection(LEFT);
		}

		snake.Move();

		if (snake.Eat(apple))
			apple.New(snake);

		snake.Draw();
		apple.Draw();   // !!
		if (snake.GetLength() > 8 && snake.Bump())
		{
			closegraph();
			std::cout << "Вы наехали себе на хвост!" << std::endl;
			std::cout << "Ваш результат = " << snake.GetLength() << std::endl;
			return 0;
		}
		
		Sleep(69);
	}

	closegraph();

	return 0;
}