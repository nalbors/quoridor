#include "kolory_kierunki.h"
#include <windows.h>
#include <iostream>

void set_color(Kolor color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void wyczysc() {
	system("cls");
}