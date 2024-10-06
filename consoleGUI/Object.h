
#pragma once
#include <Windows.h>
#include <vector>
#include "objectInteraction.h"
class Object
{
public:
	virtual void show() = 0;
	virtual void handleMouseEvent(COORD mousePos);
	virtual void handleKeyboardEvent(int key);
};




