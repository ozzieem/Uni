#pragma once
#include "../Course/Console.h"
#include <thread>
#include <conio.h>
#include <mutex>

using namespace Course;

struct Position
{
	int x, y;

	Position() : x(0), y(0) {}
	Position(int x, int y) : x(x), y(y) {}
};

struct BoardSize
{
	int x_block, y_block;

	BoardSize() : x_block(0), y_block(0) {}
	BoardSize(int x, int y) : x_block(x), y_block(y) {}
};

std::mutex mu;
BoardSize maxBoard(20, 20);
