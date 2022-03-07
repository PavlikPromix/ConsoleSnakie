#include "Snake.h"

Snake::Snake(short size, bool* isalive)
	: Direction('u'),
	Map(new char[size * size]),
	MapSize(size),
	SParts({ Point((short)(size / 2), (short)(size / 2)) }),
	FoodCoords({}),
	Score(0),
	Speed(1),
	IterCount(1)
{
	ConsoleClear();
	ConsoleCursorVisible(false);
	for (short i = 0; i < MapSize - 1; i++)
	{
		ConsoleSetPos(0, i);
		ConsoleWrite('#');
		ConsoleSetPos(i, 0);
		ConsoleWrite('#');
		ConsoleSetPos(MapSize - 1, i);
		ConsoleWrite('#');
		ConsoleSetPos(i, MapSize - 1);
		ConsoleWrite('#');
	}
	ConsoleSetPos(MapSize - 1, MapSize - 1);
	ConsoleWrite('#');
	ConsoleSetPos(0, MapSize);
	ConsoleWrite("Score: ");
	ConsoleWrite(Score);
	IsAlive = isalive;
	*IsAlive = true;
}

void Snake::Draw()
{
	for (short y = 1; y < MapSize - 1; y++)
	{
		for (short x = 1; x < MapSize - 1; x++)
		{
			ConsoleSetPos(x, y);
			ConsoleWrite(Map[x + y * MapSize]);
		}
		ConsoleWrite('\n');
	}
	ConsoleSetPos(7, MapSize);
	ConsoleWrite(Score);
}

void Snake::Update()
{
	if (IsAlive)
	{
		Point lCoords = SParts[0];
		SParts.pop_back();
		std::reverse(SParts.begin(), SParts.end());
		switch (Direction)
		{
		case 'r':
			SParts.push_back({ lCoords.x + 1, lCoords.y });
			break;
		case 'd':
			SParts.push_back({ lCoords.x, lCoords.y + 1 });
			break;
		case 'l':
			SParts.push_back({ lCoords.x - 1, lCoords.y });
			break;
		case 'u':
			SParts.push_back({ lCoords.x, lCoords.y - 1 });
			break;
		default:
			break;
		}
		std::reverse(SParts.begin(), SParts.end());
		CollisionCheck();
		MapConstruct();
		IterCount++;
		if (IterCount % MapSize * Speed == 0 && Speed < 50)
		{
			Speed = round(Speed * 1.1 * 100) / 100;
		}
		GenFood();
		Draw();
	}
}

void Snake::GenFood()
{
	if (IterCount % MapSize == 0 || FoodCoords.size() == 0)
	{
		FoodCoords.push_back({ (short)(rand() % (MapSize - 2) + 1), (short)(rand() % (MapSize - 2) + 1) });
	}
}

void Snake::SnakeGrowth()
{
	SParts.push_back({ SParts[0].x, SParts[0].y });
	/*switch (Direction)
	{
	case 'r':
		SParts.push_back({ SParts[0].x + 1, SParts[0].y });
		break;
	case 'd':
		SParts.push_back({ SParts[0].x, SParts[0].y + 1 });
		break;
	case 'l':
		SParts.push_back({ SParts[0].x - 1, SParts[0].y });
		break;
	case 'u':
		SParts.push_back({ SParts[0].x, SParts[0].y - 1 });
		break;
	default:
		break;
	}*/
}

void Snake::GameOver()
{
	*IsAlive = false;
	ConsoleSetPos(0, MapSize + 1);
	ConsoleWrite("GameOver\nPress any button to exit...");
	ConsoleReset();
	quick_exit(0);
}

void Snake::CollisionCheck()
{
	Point forepart = SParts[0];
	std::vector<Point> temp{ SParts };
	temp.erase(temp.begin());
	for (auto part : temp)
	{
		if (part == forepart)
		{
			GameOver();
		}
	}
	if (SParts[0].x == MapSize - 1 || SParts[0].y == MapSize - 1 || SParts[0].x == 0 || SParts[0].y == 0)
	{
		GameOver();
	}
}

void Snake::MapConstruct()
{
	for (short y = 1; y < MapSize; y++)
	{
		for (short x = 1; x < MapSize; x++)
		{
			Map[x + y * MapSize] = ' ';
			for (auto part : SParts)
			{
				for (auto food : FoodCoords)
				{
					if (y == food.y && x == food.x)
					{
						Map[x + y * MapSize] = '+';
					}
					if (food.x == part.x && food.y == part.y)
					{
						FoodCoords.erase(std::find(FoodCoords.begin(), FoodCoords.end(), food));
						SnakeGrowth();
						Map[food.x + food.y * MapSize] = 'S';
						Score++;

					}
				}
				if (y == part.y && x == part.x)
				{
					Map[x + y * MapSize] = 'S';
				}
			}
		}
	}
}

Snake::~Snake()
{
	delete Map;
}