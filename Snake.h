#pragma once
#include <vector>
#include <algorithm>
#include "Point.h"
#include "ConsoleManipulator.h"

class Snake
{
public:
	unsigned char Direction; 
	std::vector<Point> SParts;
	char* Map;
	std::vector<Point> FoodCoords;
	double_t Speed;
	const short MapSize;
	unsigned short int Score;
	unsigned int IterCount;
	bool* IsAlive;
	Snake(short size, bool *IsAlive);
	~Snake();
	void Draw();
	void Update();
	void GameOver();

private:
	void GenFood();
	void MapConstruct();
	void SnakeGrowth();
	void CollisionCheck();
};