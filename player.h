#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class player {
	int X, Y;           // Polozenie pionka
	int ilosc_scian;    // Ilosc pozostalych scian
	char nick[50];
public:
	// settery
	void set_X(int XX);
	void set_Y(int YY);
	void set_sciany(int sciany);
	// gettery
	int get_X();
	int get_Y();
	int get_sciany();
	player(int startX, int startY); // konstruktor argumentowy
	void wczytaj_nick();
	void zaktualizuj_ranking();
	void dodaj_do_rankingu_jezeli_nie_istnieje();
};

#endif // PLAYER_H
