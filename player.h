#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class player {
	int X, Y;           // Polozenie pionka
	int ilosc_scian;    // Ilosc pozostalych scian
	char nick[50]; # czemu char? mamy 2024 uzyj string
public:
	// settery
	void set_X(int XX);
	void set_Y(int YY);
	void set_sciany(int sciany);
	// gettery
#do czego sluzy get_X i get_Y clasa player powinna miec obiekt pionek ktory jako property bedzie mial obecja pozycje
	int get_X();
	int get_Y();
	int get_sciany();
	player(int startX, int startY); // konstruktor argumentowy
	void wczytaj_nick();
	void zaktualizuj_ranking();
	void dodaj_do_rankingu_jezeli_nie_istnieje();
};

#endif // PLAYER_H
