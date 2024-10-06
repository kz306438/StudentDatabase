#include "colors.h"
#include <windows.h>

WORD savedAttributes = 0;
CONSOLE_SCREEN_BUFFER_INFO savedConsoleInfo;

void setColorForeground(ConsoleColor color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD attributes = consoleInfo.wAttributes;
    attributes &= 0xF0;
    attributes |= (WORD)color;
    SetConsoleTextAttribute(hConsole, attributes);
}

void setColorBackground(ConsoleColor color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD attributes = consoleInfo.wAttributes;
    attributes &= 0x0F;
    attributes |= ((WORD)color << 4);
    SetConsoleTextAttribute(hConsole, attributes);
}

void saveConsoleAttributes() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &savedConsoleInfo);
    savedAttributes = savedConsoleInfo.wAttributes;
}

void restoreConsoleAttributes() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, savedAttributes);
}