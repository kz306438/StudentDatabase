#include "window.h"

Window::Window(size_t windowWidth, size_t windowHeight, size_t windowPositionX, size_t windowPositionY) :
	windowWidth(windowWidth), windowHeight(windowHeight),
	windowPositionX(windowPositionX), windowPositionY(windowPositionY)
{
	windowFill();
}

Window::Window(size_t windowWidth, size_t windowHeight, size_t windowPositionX, size_t windowPositionY, std::string windowName, size_t windowNamePositionX, size_t windowNamePositionY) :
	windowWidth(windowWidth), windowHeight(windowHeight),
	windowPositionX(windowPositionX), windowPositionY(windowPositionY),
	windowName(windowName), windowNamePositionX(windowNamePositionX), windowNamePositionY(windowNamePositionY)
{
	windowFill();
}

void Window::windowFill()
{
	if (windowName.size() > windowWidth - 2)
	{
		windowName = "";
	}
	arr.resize(windowHeight);
	for (size_t i = 0; i < windowHeight; i++)
	{
		for (size_t j = 0; j < windowWidth; j++)
		{
			arr[i].push_back(' ');
		}
	}
	for (size_t i = 1; i < windowHeight - 1; i++)
	{
		for (size_t j = 1; j < windowWidth - 1; j++)
		{
			arr[i][j] = ' ';
		}
	}
	for (size_t i = 1; i < windowHeight - 1; i++)
	{
		arr[i][0] = leftVerticalLine;
		arr[i][windowWidth - 1] = rightVerticalLine;
	}
	for (size_t j = 0; j < windowWidth; j++)
	{
		arr[0][j] = topHorizontalLine;
		arr[windowHeight - 1][j] = bottomHorizontalLine;
	}

	arr[0][0] = topLeftCorner;
	arr[windowHeight - 1][0] = bottomLeftCorner;
	arr[0][windowWidth - 1] = topRightCorner;
	arr[windowHeight - 1][windowWidth - 1] = bottomRightCorner;
	for (size_t i = 0; i < windowName.size(); i++)
	{
		arr[windowNamePositionY][windowNamePositionX + i] = windowName[i];
	}
}

void Window::show()
{
	for (size_t i = 0; i < windowHeight; i++)
	{
		for (size_t j = 0; j < windowWidth; j++)
		{
			setcur(windowPositionX + j, windowPositionY + i);
			std::cout << arr[i][j];
		}
	}
}
void Window::addWindowName(std::string windowName, size_t windowNamePositionX, size_t windowNamePositionY)
{
	if (windowName.size() <= windowWidth - 2 && windowNamePositionX > 0 && windowNamePositionX < windowWidth && windowNamePositionY >= 0 && windowNamePositionY <= windowHeight)
	{
		if (windowNamePositionY == 0 || windowNamePositionY == windowHeight)windowName = wrapStringWithSymbols(windowName);
		this->windowName = windowName;
		this->windowNamePositionX = windowPositionX;
		this->windowNamePositionY = windowNamePositionY;
		for (size_t i = 0; i < windowName.size(); i++)
		{
			arr[windowNamePositionY][windowNamePositionX + i] = windowName[i];
		}
	}
}

void Window::setTexture(char topLeft, char topRight, char bottomLeft, char bottomRight, char topHorizontal, char bottomHorizontal, char leftVertical, char rightVertical) {
	topLeftCorner = topLeft;
	topRightCorner = topRight;
	bottomLeftCorner = bottomLeft;
	bottomRightCorner = bottomRight;
	topHorizontalLine = topHorizontal;
	bottomHorizontalLine = bottomHorizontal;
	leftVerticalLine = leftVertical;
	rightVerticalLine = rightVertical;
	windowFill();
	show();
}

std::string wrapStringWithSymbols(const std::string& input) {
	std::string leftSymbol = "";
	leftSymbol += char(185);
	leftSymbol += " ";
	std::string rightSymbol = "";
	rightSymbol += " ";
	rightSymbol += char(204);
	return leftSymbol + input + rightSymbol;
}

