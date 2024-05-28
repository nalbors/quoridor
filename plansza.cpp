#include "plansza.h"
#include <iostream>
#include <windows.h>

plansza::plansza() {
	for (int Y = 0; Y < 17; Y++) {
		for (int X = 0; X < 17; X++) {
			if (Y % 2 == 1) {
				board[Y][X] = ' ';
			}
			else {
				if (X % 2 == 1) {
					board[Y][X] = ' ';
				}
				else {
					board[Y][X] = 'X';
				}
			}
		}
	}
}

void plansza::ustaw_sciane(int rzad, int kolumna, int kierunek) {
	if (kierunek == GORA) {
		board[rzad][kolumna * 2 - 1] = 179;
		board[rzad - 1][kolumna * 2 - 1] = 179;
		board[rzad - 2][kolumna * 2 - 1] = 179;
	}
	else if (kierunek == DOL) {
		board[rzad][kolumna * 2 - 1] = 179;
		board[rzad + 1][kolumna * 2 - 1] = 179;
		board[rzad + 2][kolumna * 2 - 1] = 179;
	}
	else if (kierunek == LEWO) {
		board[rzad][kolumna * 2 - 2] = 196;
		board[rzad][kolumna * 2 - 3] = 196;
		board[rzad][kolumna * 2 - 4] = 196;
	}
	else if (kierunek == PRAWO) {
		board[rzad][kolumna * 2 - 2] = 196;
		board[rzad][kolumna * 2 - 1] = 196;
		board[rzad][kolumna * 2] = 196;
	}
}

void plansza::wypisz() {}

void plansza::plansza_scianki() {
	char i = '1';
	for (int Y = 0; Y < 17; Y++) {
		for (int X = 0; X < 17; X++) {
			if ((Y % 2 == 0 && X % 2 == 1) || (Y % 2 == 1 && X % 2 == 0)) {
				if (board[Y][X] == ' ') {
					board[Y][X] = i;
				}
				i++;
			}
		}
		i = '1';
	}
}

void plansza::plansza_scianki_reverse() {
	for (int Y = 0; Y < 17; Y++) {
		for (int X = 0; X < 17; X++) {
			if ((Y % 2 == 0 && X % 2 == 1) || (Y % 2 == 1 && X % 2 == 0)) {
				if (board[Y][X] >= '0' && board[Y][X] <= '9') {
					board[Y][X] = ' ';
				}
			}
		}
	}
}

bool plansza::mozliwosc_postawienia_scianki(int rzad, int kolumna, int kierunek) {
	/*scianka ma dlugosc 2 pol, dlatego trzeba sprawdzic warunek, czy chce np. w lewo czy prawo postawic scianke):
		179 oznacza '│' w rozszerzonym zestawie znaków ASCII
		196 oznacza '─' w rozszerzonym zestawie znaków ASCII
	*/
	if (kierunek == GORA) {
		if (board[rzad - 1][kolumna * 2 - 1] == 179 || board[rzad - 1][kolumna * 2 - 1] == 196 || rzad == 0) {
			set_color(CZERWONY);
			return false;
		}
		else {
			set_color(ZIELONY);
			return true;
		}
	}
	else if (kierunek == DOL) {
		if (board[rzad + 1][kolumna * 2 - 1] == 179 || board[rzad + 1][kolumna * 2 - 1] == 196 || rzad == 16) {
			set_color(CZERWONY);
			return false;
		}
		else {
			set_color(ZIELONY);
			return true;
		}
	}
	else if (kierunek == LEWO) {
		if (board[rzad][kolumna * 2 - 3] == 179 || board[rzad][kolumna * 2 - 3] == 196 || kolumna * 2 - 2 == 0) {
			set_color(CZERWONY);
			return false;
		}
		else {
			set_color(ZIELONY);
			return true;
		}
	}
	else if (kierunek == PRAWO) {
		if (board[rzad][kolumna * 2 - 3] == 179 || board[rzad][kolumna * 2 - 3] == 196 || kolumna * 2 - 2 == 16) {
			set_color(CZERWONY);
			return false;
		}
		else {
			set_color(ZIELONY);
			return true;
		}
	}
	return false;
}
