#pragma once
#include <Windows.h>
#include <cwchar>
#include <string>

void ConsoleClear();

void ConsoleSetPos(short y, short x);

void ConsoleWrite(const char* c);
void ConsoleWrite(char c);
void ConsoleWrite(int c);

void ConsoleCursorVisible(bool showFlag);
void ConsoleSetup();
void ConsoleReset();