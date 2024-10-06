#include "cursor.h"

void invisibleCursor()
{
	CONSOLE_CURSOR_INFO curs = { 0 };
	curs.dwSize = sizeof(curs);
	curs.bVisible = FALSE;
	::SetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &curs);
}

void setcur(int x, int y) 
{
	COORD coord{};
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};
namespace {
	static HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
	static INPUT_RECORD InputRecord;
	static DWORD Events;
	static COORD coord;
	static DWORD prev_mode;
	void setupInputHandling() {
		GetConsoleMode(hin, &prev_mode);
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
		SetConsoleMode(hin, ENABLE_MOUSE_INPUT);
	}
}
COORD GetCursorPosition()
{
	setupInputHandling();
	INPUT_RECORD InputRecord;
	DWORD Events = 0;
	PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &InputRecord, 1, &Events);
	MOUSE_EVENT_RECORD mouseEvent = InputRecord.Event.MouseEvent;
	COORD mousePos = mouseEvent.dwMousePosition;
	return mousePos;
}