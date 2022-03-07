#include "ConsoleManipulator.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void ConsoleClear() {
	COORD topLeft = { 0, 0 };

	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;
	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

void ConsoleSetPos(short y, short x)
{
	SetConsoleCursorPosition(console, { y, x });
}

void ConsoleWrite(const char* c)
{
	DWORD  dw = 32000u;
	const size_t cSize = strlen(c);
	WCHAR* ch = new wchar_t[cSize + 1];
	mbstowcs(ch, c, cSize + 1);
	WriteConsoleW(console, ch, cSize, &dw, NULL);
}

void ConsoleWrite(char c)
{
	DWORD  dw = 32000u;
	WCHAR ch = (WCHAR)c;
	WriteConsoleW(console, &ch, 1, &dw, NULL);
}

void ConsoleWrite(int c)
{
	DWORD  dw = 32000u;
	std::wstring itos = std::to_wstring(c);
	const size_t cSize = itos.length();
	WCHAR* ch = (wchar_t*)itos.c_str();
	WriteConsoleW(console, ch, cSize, &dw, NULL);
}

void ConsoleCursorVisible(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void ConsoleSetup()
{
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(console, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = 18;
	lpConsoleCurrentFontEx->dwFontSize.Y = 18;
	lpConsoleCurrentFontEx->FontFamily = FF_DONTCARE;
	lpConsoleCurrentFontEx->FontWeight = FW_NORMAL;
	std::wcscpy(lpConsoleCurrentFontEx->FaceName, L"Cascadia Mono");
	SetCurrentConsoleFontEx(console, 0, lpConsoleCurrentFontEx);
}

void ConsoleReset()
{
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(console, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = 10;
	lpConsoleCurrentFontEx->dwFontSize.Y = 18;
	lpConsoleCurrentFontEx->FontFamily = FF_DONTCARE;
	lpConsoleCurrentFontEx->FontWeight = FW_NORMAL;
	std::wcscpy(lpConsoleCurrentFontEx->FaceName, L"Cascadia Mono");
	SetCurrentConsoleFontEx(console, 0, lpConsoleCurrentFontEx);
}