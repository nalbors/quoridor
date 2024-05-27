#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <windows.h> 
#include <conio.h>

enum Kolor {
	ZIELONY = 10,
	CZERWONY = 12,
	RESET_KOLORU = 15,
	KOLOR_SCIANKI = 9,
	ZOLTY = 14
};

using namespace std;

//funckja zmieniajaca kolor czcionki w konsoli
void set_color(Kolor color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void wyczysc() {
	system("cls");
}

//klasa abstrakcyjne wirtualna (useless?)
class elementy_gry {
public:
	virtual void wypisz() = 0;
};

class player {
	int X, Y;			//Polozenie pionka
	int ilosc_scian;	//Ilosc pozostalych scian
public:
	//settery
	void set_X(int XX) { X = XX; };
	void set_Y(int YY) { Y = YY; };
	void set_sciany(int sciany) { ilosc_scian = sciany; };
	//gettery
	int get_X() { return X; };
	int get_Y() { return Y; };
	int get_sciany() { return ilosc_scian; };
	player(int startX, int startY) : X(startX), Y(startY), ilosc_scian(10) {}; //konstruktor argumentowy
};


class plansza : public elementy_gry {
	unsigned char board[17][17];				//Plansza o wymiarach 9x9 (17x17, poniewaz pomiedzy polami jest znak ' ' liczony dodatkowo (jest ich 8)
	player p1, p2;		//Gracze (pionki)
public:
	plansza(); //konstruktor domyslny
	//settery
	void set_p1X(int X) { p1.set_X(X); }
	void set_p1Y(int Y) { p1.set_Y(Y); }
	void set_p2X(int X) { p2.set_X(X); }
	void set_p2Y(int Y) { p2.set_Y(Y); }
	//gettery
	int get_p1X() { return p1.get_X(); }
	int get_p1Y() { return p1.get_Y(); }
	int get_p2X() { return p2.get_X(); }
	int get_p2Y() { return p2.get_Y(); }
	void ustaw_sciane(int X, int Y, int kierunek);	//metoda stawiajaca scianke
	void wypisz();									//metoda wypisujaca
	//metody sprawdzajace czy mozna wykonac nastepny ruch (do zrobienia potem)
	bool p1_mozliwosc_w_gore();
	bool p1_mozliwosc_w_dol();
	bool p1_mozliwosc_w_lewo();
	bool p1_mozliwosc_w_prawo();
	bool p2_mozliwosc_w_gore();
	bool p2_mozliwosc_w_dol();
	bool p2_mozliwosc_w_lewo();
	bool p2_mozliwosc_w_prawo();
	bool mozliwosc_postawienia_scianki(int rzad, int kolumna, int kierunek); //metoda sprawdzajaca czy da sie postawic scianke w odpowiednim kierunku
	void plansza_scianki();			//metoda wypisujaca (i podmieniajaca plansze) mozliwoscie gdzie mozna postawic scianki
	void plansza_scianki_reverse(); //metoda cofa podmienienia planszy (zostawia postawiona scianke)
};
//Konstruktor domyslny tworzacy plansze z polami ' ' (pusta przestrzen w ktorej mozna postawic scianke) oraz 'X'
plansza::plansza() : p1(8, 0), p2(8, 16) {
	for (int Y = 0;Y < 17;Y++) {
		for (int X = 0;X < 17;X++) {
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

//metoda wypisujaca plansze w odpowiednich kolorach
void plansza::wypisz() {
	char i = 0;
	for (int Y = 0;Y < 17;Y++) {
		set_color(ZOLTY);
		if (i < 10)
			printf(" %d|", i);
		else printf("%d|", i);
		i++;

		set_color(RESET_KOLORU);
		for (int X = 0;X < 17;X++) {
			set_color(RESET_KOLORU);
			if (Y == p1.get_Y() && X == p1.get_X()) {
				set_color(CZERWONY);
				printf(" %c", 219);
			}
			else if (Y == p2.get_Y() && X == p2.get_X()) {
				set_color(ZIELONY);
				printf(" %c", 219);
			}
			else {
				if (board[Y][X] == 'X') set_color(RESET_KOLORU);
				else if (board[Y][X] >= '0'&&board[Y][X] <= '9')set_color(KOLOR_SCIANKI);
				else set_color(ZOLTY);
				printf(" %c", board[Y][X]);
			}
		}
		printf("\n");
	}
}

//metoda ustawiajaca scianke w polozeniu podanym przez gracza
void plansza::ustaw_sciane(int rzad, int kolumna, int kierunek) {
	/* Kierunki w ktore ma byc polozona scianka (poniewaz uzytkownik podaje punkt, a scianka ma dlugosc 2 pol):
		1.Gora
		2.Dol
		3.Lewo
		4.Prawo

		179 oznacza '│' w rozszerzonym zestawie znaków ASCII
		196 oznacza '─' w rozszerzonym zestawie znaków ASCII
	*/
	if (kierunek == 1) {
		board[rzad][kolumna * 2 - 1] = 179;
		board[rzad - 1][kolumna * 2 - 1] = 179;
		board[rzad - 2][kolumna * 2 - 1] = 179;
	}
	else if (kierunek == 2) {
		board[rzad][kolumna * 2 - 1] = 179;
		board[rzad + 1][kolumna * 2 - 1] = 179;
		board[rzad + 2][kolumna * 2 - 1] = 179;
	}
	else if (kierunek == 3) {
		board[rzad][kolumna * 2 - 2] = 196;
		board[rzad][kolumna * 2 - 3] = 196;
		board[rzad][kolumna * 2 - 4] = 196;
	}
	else if (kierunek == 4) {
		board[rzad][kolumna * 2 - 2] = 196;
		board[rzad][kolumna * 2 - 1] = 196;
		board[rzad][kolumna * 2] = 196;
	}
}
//metoda ustawiajaca mozliwosci (w ktorym miejscu mozna postawic scianke)
void plansza::plansza_scianki() {
	char i = '1';
	for (int Y = 0; Y < 17;Y++) {
		for (int X = 0; X < 17;X++) {
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
//metoda, ktora cofa podmienienie planszy poprzes metode plansza_scianki()
void plansza::plansza_scianki_reverse() {
	for (int Y = 0; Y < 17;Y++) {
		for (int X = 0; X < 17;X++) {
			if ((Y % 2 == 0 && X % 2 == 1) || (Y % 2 == 1 && X % 2 == 0)) {
				if (board[Y][X] >= '0'&&board[Y][X] <= '9') {
					board[Y][X] = ' ';
				}
			}
		}
	}
}

bool plansza::p1_mozliwosc_w_gore() {
	int Y = p1.get_Y();
	int X = p1.get_X();
	if (Y == 0 || board[Y - 1][X] == 196) {
		return false;
	}
	else return true;
}
bool plansza::p1_mozliwosc_w_dol() {
	int Y = p1.get_Y();
	int X = p1.get_X();
	if (Y == 16 || board[Y + 1][X] == 196) {
		return false;
	}
	else return true;
}
bool plansza::p1_mozliwosc_w_lewo() {
	int Y = p1.get_Y();
	int X = p1.get_X();
	if (X == 0 || board[Y][X - 1] == 179) {
		return false;
	}
	else return true;
}
bool plansza::p1_mozliwosc_w_prawo() {
	int Y = p1.get_Y();
	int X = p1.get_X();
	if (X == 16 || board[Y][X + 1] == 179) {
		return false;
	}
	else return true;
}
bool plansza::p2_mozliwosc_w_gore() {
	int Y = p2.get_Y();
	int X = p2.get_X();
	if (Y == 0 || board[Y - 1][X] == 196) {
		return false;
	}
	else return true;
}
bool plansza::p2_mozliwosc_w_dol() {
	int Y = p2.get_Y();
	int X = p2.get_X();
	if (Y == 16 || board[Y + 1][X] == 196) {
		return false;
	}
	else return true;
}
bool plansza::p2_mozliwosc_w_lewo() {
	int Y = p2.get_Y();
	int X = p2.get_X();
	if (X == 0 || board[Y][X - 1] == 179) {
		return false;
	}
	else return true;
}
bool plansza::p2_mozliwosc_w_prawo() {
	int Y = p2.get_Y();
	int X = p2.get_X();
	if (X == 16 || board[Y][X + 1] == 179) {
		return false;
	}
	else return true;
}

bool plansza::mozliwosc_postawienia_scianki(int rzad, int kolumna, int kierunek) {
	/* Kierunki w ktore ma byc polozona scianka (poniewaz uzytkownik podaje punkt, a scianka ma dlugosc 2 pol):
		1.Gora
		2.Dol
		3.Lewo
		4.Prawo

		179 oznacza '│' w rozszerzonym zestawie znaków ASCII
		196 oznacza '─' w rozszerzonym zestawie znaków ASCII
	*/
	if (kierunek == 1) {
		if (board[rzad - 1][kolumna * 2 - 1] == 179 || board[rzad - 1][kolumna * 2 - 1] == 196 || rzad == 0) {
			set_color(CZERWONY);
			return false;
		}
		else {
			set_color(ZIELONY);
			return true;
		}
	}
	else if (kierunek == 2) {
		if (board[rzad + 1][kolumna * 2 - 1] == 179 || board[rzad + 1][kolumna * 2 - 1] == 196 || rzad == 16) {
			set_color(CZERWONY);
			return false;
		}
		else {
			set_color(ZIELONY);
			return true;
		}
	}
	else if (kierunek == 3) {
		if (board[rzad][kolumna * 2 - 3] == 179 || board[rzad][kolumna * 2 - 3] == 196 || kolumna * 2 - 2 == 0) {
			set_color(CZERWONY);
			return false;
		}
		else {
			set_color(ZIELONY);
			return true;
		}
	}
	else if (kierunek == 4) {
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

class gra :public elementy_gry {
	plansza board;		//Plansza
	bool isGameOver;	//Zmienna, w ktorej zapisane jest czy gra jest zakonczona
	int kogo_kolej;		//Kogo kolej wykonac ruch
public:
	gra() : kogo_kolej(1), isGameOver(false) {};				//konstruktor domyslny
	void play();												//metoda rozpoczynajaca gre
	void wypisz() { board.wypisz(); };							//metoda wypisujaca plansze (?)
	void next_turn();											//metoda przechodzaca do kolejnej rundy
	void setGameOver(bool gameover) { isGameOver = gameover; };	//setter, metoda konczaca gre
};

void gra::play() {
	while (!isGameOver) {
		wyczysc();	//czyszczenie konsoli
		set_color(RESET_KOLORU);
		wypisz();
		next_turn();
	}
	printf("Koniec gry.");
}

void gra::next_turn() {
	//warunek, sprawdzajacy kogo tura, aby zmienic kolor w konsoli (zeby bylo przejrzysciej)
	if (kogo_kolej == 1) set_color(CZERWONY);
	else set_color(ZIELONY);
	printf("Tura gracza %d\n", kogo_kolej);
	set_color(RESET_KOLORU);
	printf("Jaki Ruch chcesz wykonac?\n");
	printf("1. Rusz sie\n");
	printf("2. Postaw sciane\n");
	int wybor; //zmienna, w ktorej przechowujemy wybor gracza
	scanf("%d", &wybor);
	if (wybor == 1) {
		if (kogo_kolej == 1) {
			printf("gdzie chcesz sie ruszyc?\n");
			bool w_gore = board.p1_mozliwosc_w_gore();
			bool w_dol = board.p1_mozliwosc_w_dol();
			bool w_lewo = board.p1_mozliwosc_w_lewo();
			bool w_prawo = board.p1_mozliwosc_w_prawo();
			if (w_gore) {
				set_color(ZIELONY);
				printf("1. W Gore\n");
			}
			else {
				set_color(CZERWONY);
				printf("1. W Gore\n");
			}

			if (w_dol) {
				set_color(ZIELONY);
				printf("2. W Dol\n");
			}
			else {
				set_color(CZERWONY);
				printf("2. W Dol\n");
			}

			if (w_lewo) {
				set_color(ZIELONY);
				printf("3. W Lewo\n");
			}
			else {
				set_color(CZERWONY);
				printf("3. W Lewo\n");
			}

			if (w_prawo) {
				set_color(ZIELONY);
				printf("4. W Prawo\n");
			}
			else {
				set_color(CZERWONY);
				printf("4. W Prawo\n");
			}
			set_color(RESET_KOLORU);
			while (scanf("%d", &wybor) != 1 || getchar() != '\n' ||
				(w_gore == false && wybor == 1) ||
				(w_dol == false && wybor == 2) ||
				(w_lewo == false && wybor == 3) ||
				(w_prawo == false && wybor == 4)) {
				printf("Nie mozesz ruszyc sie w tym kierunku. Sprobuj ponownie.\n");
				continue;
			}
			//warunki i metody uzywane, by zmienic polozenie pionka
			if (wybor == 1) {
				int Y1 = board.get_p1Y() - 2;
				board.set_p1Y(Y1);
			}
			else if (wybor == 2) {
				int Y2 = board.get_p1Y() + 2;
				board.set_p1Y(Y2);
			}
			else if (wybor == 3) {
				int X1 = board.get_p1X() - 2;
				board.set_p1X(X1);
			}
			else {
				int X2 = board.get_p1X() + 2;
				board.set_p1X(X2);
			}

		}
		else {
			printf("gdzie chcesz sie ruszyc?\n");
			bool w_gore = board.p2_mozliwosc_w_gore();
			bool w_dol = board.p2_mozliwosc_w_dol();
			bool w_lewo = board.p2_mozliwosc_w_lewo();
			bool w_prawo = board.p2_mozliwosc_w_prawo();
			if (w_gore) {
				set_color(ZIELONY);
				printf("1. W Gore\n");
			}
			else {
				set_color(CZERWONY);
				printf("1. W Gore\n");
			}

			if (w_dol) {
				set_color(ZIELONY);
				printf("2. W Dol\n");
			}
			else {
				set_color(CZERWONY);
				printf("2. W Dol\n");
			}

			if (w_lewo) {
				set_color(ZIELONY);
				printf("3. W Lewo\n");
			}
			else {
				set_color(CZERWONY);
				printf("3. W Lewo\n");
			}

			if (w_prawo) {
				set_color(ZIELONY);
				printf("4. W Prawo\n");
			}
			else {
				set_color(CZERWONY);
				printf("4. W Prawo\n");
			}
			set_color(RESET_KOLORU);
			while (scanf("%d", &wybor) != 1 || getchar() != '\n' ||
				(w_gore == false && wybor == 1) ||
				(w_dol == false && wybor == 2) ||
				(w_lewo == false && wybor == 3) ||
				(w_prawo == false && wybor == 4)) {
				printf("Nie mozesz ruszyc sie w tym kierunku. Sprobuj ponownie.\n");
				continue;
			}
			//warunki i metody uzywane, by zmienic polozenie pionka
			if (wybor == 1) {
				int Y1 = board.get_p2Y() - 2;
				board.set_p2Y(Y1);
			}
			else if (wybor == 2) {
				int Y2 = board.get_p2Y() + 2;
				board.set_p2Y(Y2);
			}
			else if (wybor == 3) {
				int X1 = board.get_p2X() - 2;
				board.set_p2X(X1);
			}
			else {
				int X2 = board.get_p2X() + 2;
				board.set_p2X(X2);
			}
		}

	}
	else if (wybor == 2) {
		//Ustawianie scianki
		wyczysc();
		board.plansza_scianki();
		wypisz();
		printf("W jakim miejscu chcesz postawic sciane? (Podaj rzad i liczbe w rzedzie)\n");
		int rzad, liczba, kierunek;

		scanf("%d %d", &rzad, &liczba);
		if (rzad % 2 == 0) {
			printf("Chcesz dac scianke w:\n");
			bool w_gore = board.mozliwosc_postawienia_scianki(rzad, liczba, 1);
			printf("1.Gora\n");
			bool w_dol = board.mozliwosc_postawienia_scianki(rzad, liczba, 2);
			printf("2.Dol\n");
			set_color(RESET_KOLORU);
			if (!w_gore && !w_dol) {
				printf("Brak mozliwosci postawienia scianki w tym kierunku.\nNacisnij dowolny klawisz aby kontynuowac.");
				_getch(); //funkcja z biblioteki <conio.h> dzieki ktorej nie trzeba naciskac entera przy uzyciu getchar()
						  //dzieki czemu mozna zrobic opcje "Nacisnij dowolny klawisz aby kontynuowac"
				return;
			}
			scanf("%d", &kierunek);
			board.ustaw_sciane(rzad, liczba, kierunek);
			board.plansza_scianki_reverse();
		}
		else {
			printf("Chcesz dac scianke w:\n");
			bool w_lewo = board.mozliwosc_postawienia_scianki(rzad, liczba, 3);
			printf("1.Lewo\n");
			bool w_prawo = board.mozliwosc_postawienia_scianki(rzad, liczba, 4);
			printf("2.Prawo\n");
			set_color(RESET_KOLORU);
			if (!w_lewo && !w_prawo) {
				printf("Brak mozliwosci postawienia scianki w tym kierunku.\nNacisnij dowolny klawisz aby kontynuowac.");
				_getch(); //funkcja z biblioteki <conio.h> dzieki ktorej nie trzeba naciskac entera przy uzyciu getchar()
						  //dzieki czemu mozna zrobic opcje "Nacisnij dowolny klawisz aby kontynuowac"
				return;
			}
			scanf("%d", &kierunek);
			if (kierunek == 1) kierunek = 3;
			else kierunek = 4;
			board.ustaw_sciane(rzad, liczba, kierunek);
			board.plansza_scianki_reverse();
		}
	}
	//zmienianie tury gracza
	if (kogo_kolej == 1) {
		kogo_kolej = 2;
	}
	else {
		kogo_kolej = 1;
	}
}


int main() {
	gra game;
	game.play();
	return 0;
}
