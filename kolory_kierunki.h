#pragma once
#ifndef KOLORY_KIERUNKI_H
#define KOLORY_KIERUNKI_H

enum Kolor {
	ZIELONY = 10,
	CZERWONY = 12,
	BIALY = 15,
	NIEBIESKI = 9,
	ZOLTY = 14
};

enum Kierunek {
	GORA = 1,
	DOL = 2,
	LEWO = 3,
	PRAWO = 4
};

void set_color(Kolor color);
void wyczysc();

#endif // KOLORY_KIERUNKI_H
