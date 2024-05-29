#pragma once
#ifndef PLANSZA_H
#define PLANSZA_H

#include "elementy_gry.h"
#include "kolory_kierunki.h"

#albo polski albo angielski we wszystkich plikach preferowany angielski a nie plansza_scianki_revers
class plansza : public elementy_gry {
public:
	unsigned char board[17][17]; // Plansza o wymiarach 9x9
	plansza();                   // konstruktor domyslny
	void ustaw_sciane(int X, int Y, int kierunek);
	void wypisz();
	bool mozliwosc_postawienia_scianki(int rzad, int kolumna, int kierunek);
	void plansza_scianki();
	void plansza_scianki_reverse();
};

#endif // PLANSZA_H
