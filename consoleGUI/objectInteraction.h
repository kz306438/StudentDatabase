	#pragma once
#include <Windows.h>

template<typename... Args>
void mouseButtonInteraction(Args*... objects) {
	INPUT_RECORD InputRecord;
	DWORD Events = 0;

	if (PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &InputRecord, 1, &Events))
	{
		if (Events > 0 && ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &InputRecord, 1, &Events))
		{
			if (InputRecord.EventType == MOUSE_EVENT)
			{
				MOUSE_EVENT_RECORD mouseEvent = InputRecord.Event.MouseEvent;
				COORD mousePos = mouseEvent.dwMousePosition;

				(objects->handleMouseEvent(mousePos), ...);

				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			}
		}
	}

	(objects->show(), ...);
}