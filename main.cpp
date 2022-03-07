#include "Snake.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include <cwchar>

bool* IsAlive = new bool(false);
Snake* s = nullptr;

void KeyCheckThread()
{
	while (true)
	{
		if (*IsAlive && s != NULL)
		{
			if (GetKeyState(VK_UP) & 0x8000 && s->Direction != 'd')
			{
				s->Direction = 'u';
				std::this_thread::sleep_for((std::chrono::milliseconds)50);
			}
			if (GetKeyState(VK_DOWN) & 0x8000 && s->Direction != 'u')
			{
				s->Direction = 'd';
				std::this_thread::sleep_for((std::chrono::milliseconds)50);
			}
			if (GetKeyState(VK_LEFT) & 0x8000 && s->Direction != 'r')
			{
				s->Direction = 'l';
				std::this_thread::sleep_for((std::chrono::milliseconds)50);
			}
			if (GetKeyState(VK_RIGHT) & 0x8000 && s->Direction != 'l')
			{
				s->Direction = 'r';
				std::this_thread::sleep_for((std::chrono::milliseconds)50);
			}
			if (GetKeyState('Q') & 0x8000)
			{
				ConsoleReset();
				quick_exit(0);
			}
		}
	}
}

void UpdateThread()
{
	while (true)
	{
		if (*IsAlive && s != NULL)
		{
			std::this_thread::sleep_for((std::chrono::milliseconds)(int)(500 / s->Speed));
			s->Update();
		}
	}
}

int main(int argc, char** argv)
{
	std::thread kch(KeyCheckThread);
	std::thread upd(UpdateThread);
	int a;
	if (argc > 1)
	{
		std::stringstream str;
		str << argv[1]; str >> a;
	}
	else
	{
		std::cout << "Enter map size: ";
		std::cin >> a;
	}
	ConsoleSetup();
	s = new Snake(a, IsAlive);
	kch.join();
	upd.join();
	ConsoleReset();
	return 0;
}