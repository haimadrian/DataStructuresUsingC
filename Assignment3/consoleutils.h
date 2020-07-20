//
// Created by Haim Adrian on 27-Aug-19.
//

#ifndef ASSIGNMENT3_CONSOLEUTILS_H
#define ASSIGNMENT3_CONSOLEUTILS_H

#ifdef _WIN32
#define gotoxy Gotoxy

#include <Windows.h>

void Gotoxy(int x, int y);

COORD GetConsoleCursorPosition();

#endif //_WIN32

#endif //ASSIGNMENT3_CONSOLEUTILS_H
