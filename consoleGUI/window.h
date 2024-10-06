
#pragma once
#include <vector>
#include <iostream>
#include <Windows.h>
#include "object.h"
#include "cursor.h"

class Window : public Object
{
public:
    Window(size_t windowWidth, size_t windowHeight, size_t windowPositionX, size_t windowPositionY);
    Window(size_t windowWidth, size_t windowHeight, size_t windowPositionX, size_t windoePositionY, std::string windowName, size_t windowNamePositionX, size_t windowNamePositionY);
    void windowFill();
    void show() override;
    void addWindowName(std::string windowName, size_t windoeNamePositionX, size_t windowNamePositionY);
    void setTexture(char topLeft, char topRight, char bottomLeft, char bottomRight, char topHorizontal, char bottomHorizontal, char leftVertical, char rightVertical);
private:
    std::vector<std::vector<char>> arr;
    size_t windowWidth;
    size_t windowHeight;
    size_t windowPositionX;
    size_t windowPositionY; 
    std::string windowName = "";
    size_t windowNamePositionX;
    size_t windowNamePositionY;
    char topLeftCorner = char(201);
    char topRightCorner = char(187);
    char bottomLeftCorner = char(200);
    char bottomRightCorner = char(188);
    char topHorizontalLine = char(205);
    char bottomHorizontalLine = char(205);
    char leftVerticalLine = char(186);
    char rightVerticalLine = char(186);
};

std::string wrapStringWithSymbols(const std::string& input);


