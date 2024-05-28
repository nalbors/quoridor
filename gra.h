#pragma once
#ifndef GRA_H
#define GRA_H

#include "elementy_gry.h"
#include "plansza.h"
#include "player.h"

class gra : public elementy_gry {
	plansza board;        // Plansza
	player p1, p2;        // Gracze (pionki)
	bool isGameOver;      // Zmienna, w ktorej zapisane jest czy gra jest zakonczona
	int kogo_kolej;       // Kogo kolej wykonac ruch
public:
	gra();                // konstruktor domyslny
	void play();          // metoda rozpoczynajaca gre
	void wypisz();        // metoda wypisujaca plansze
	void next_turn();     // metoda przechodzaca do kolejnej rundy
	void setGameOver(bool gameover); // setter, metoda konczaca gre
	//mozliwosci ruchu gracza
	bool p1_mozliwosc_w_gore();
	bool p1_mozliwosc_w_dol();
	bool p1_mozliwosc_w_lewo();
	bool p1_mozliwosc_w_prawo();
	bool p2_mozliwosc_w_gore();
	bool p2_mozliwosc_w_dol();
	bool p2_mozliwosc_w_lewo();
	bool p2_mozliwosc_w_prawo();
	//metoda sprawdzajaca czy ktos wygral
	void sprawdz_wygrana();
};

#endif // GRA_H
