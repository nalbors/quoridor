#define _CRT_SECURE_NO_WARNINGS
#include "gra.h"
#include "kolory_kierunki.h"
#include <iostream>
#include <conio.h>

using namespace std;

gra::gra() : p1(8, 16), p2(8, 0), isGameOver(false), kogo_kolej(1) {}

void gra::play() {
	p1.wczytaj_nick();
	p2.wczytaj_nick();
	while (!isGameOver) {
		wyczysc();	//czyszczenie konsoli
		set_color(BIALY);
		wypisz();
		next_turn();
		sprawdz_wygrana();
	}
}

void gra::wypisz() {
	char i = 0;
	for (int Y = 0;Y < 17;Y++) {
		set_color(ZOLTY);
		if (i < 10)
			printf(" %d|", i);
		else printf("%d|", i);
		i++;

		set_color(BIALY);
		for (int X = 0;X < 17;X++) {
			set_color(BIALY);
			if (Y == p1.get_Y() && X == p1.get_X()) {
				set_color(CZERWONY);
				printf(" %c", 219);
			}
			else if (Y == p2.get_Y() && X == p2.get_X()) {
				set_color(ZIELONY);
				printf(" %c", 219);
			}
			else {
				if (board.board[Y][X] == 'X') set_color(BIALY);
				else if (board.board[Y][X] >= '0'&&board.board[Y][X] <= '9')set_color(NIEBIESKI);
				else set_color(ZOLTY);
				printf(" %c", board.board[Y][X]);
			}
		}
		if (Y == 0) {
			set_color(ZIELONY); 
			printf("\tScian: %d", p2.get_sciany());
			set_color(BIALY);
		}
		else if (Y == 16) {
			set_color(CZERWONY);
			printf("\tScian: %d", p1.get_sciany());
			set_color(BIALY);
		}
		printf("\n");
	}
}

void gra::next_turn() {
	//warunek, sprawdzajacy kogo tura, aby zmienic kolor w konsoli (zeby bylo przejrzysciej)
	// tutaj mozesz  podnosic licznik ruchow
	// i jezeli jest parzysta to masz p2
	// a w przeciwnym przypdaku to masz p1
	// jeszcze lepiej jakbys obsługe tury przeniósł do nowege typu (klasy tura)
	// i tam tym zarzadzał
	if (kogo_kolej == 1) set_color(CZERWONY);
	else set_color(ZIELONY);
	printf("Tura gracza %d\n", kogo_kolej);
	set_color(BIALY);
	printf("Jaki Ruch chcesz wykonac?\n");
	printf("1. Rusz sie\n");
	printf("2. Postaw sciane\n");
	int wybor; //zmienna, w ktorej przechowujemy wybor gracza
	scanf("%d", &wybor);
	if (wybor == 1) {
		if (kogo_kolej == 1) {
			printf("gdzie chcesz sie ruszyc?\n");
			bool w_gore = p1_mozliwosc_w_gore();
			bool w_dol = p1_mozliwosc_w_dol();
			bool w_lewo = p1_mozliwosc_w_lewo();
			bool w_prawo = p1_mozliwosc_w_prawo();
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
			set_color(BIALY);

			// wyciagni scanf z while zrob obsługe zeby przyjmowac ograniczony wybor
			// i wyrzuca error jak uzytkownik wpisze niedowzwolony string
			// wrzuc ten długi warunek do methody i zwracaj boola
			// wtedy mozesz wołac while(jakas_methoda(paramaetry))
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
				int Y1 = p1.get_Y() - 2;
				p1.set_Y(Y1);
			}
			else if (wybor == 2) {
				int Y2 = p1.get_Y() + 2;
				p1.set_Y(Y2);
			}
			else if (wybor == 3) {
				int X1 = p1.get_X() - 2;
				p1.set_X(X1);
			}
			else {
				int X2 = p1.get_X() + 2;
				p1.set_X(X2);
			}

		}
		else {
			printf("gdzie chcesz sie ruszyc?\n");
			bool w_gore = p2_mozliwosc_w_gore();
			bool w_dol = p2_mozliwosc_w_dol();
			bool w_lewo = p2_mozliwosc_w_lewo();
			bool w_prawo = p2_mozliwosc_w_prawo();
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
			set_color(BIALY);
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
				int Y1 = p2.get_Y() - 2;
				p2.set_Y(Y1);
			}
			else if (wybor == 2) {
				int Y2 = p2.get_Y() + 2;
				p2.set_Y(Y2);
			}
			else if (wybor == 3) {
				int X1 = p2.get_X() - 2;
				p2.set_X(X1);
			}
			else {
				int X2 = p2.get_X() + 2;
				p2.set_X(X2);
			}
		}

	}
	else if (wybor == 2) {
		//Ustawianie scianki
		if (kogo_kolej == 1) {
			if (p1.get_sciany() == 0) {
				// przenies to co w print do zmiennej const string, teraz masz dokanie ten sama printke
				// w kilku miejscach, mozesz nazwac ja log_cos_tam
				/*
    					void log_cos_tam(){
	 					print("twoj zajebiscie długi string")
       						_getch();
	     				}
	     			*/
				// wtedy wołasz sobie tylko log_cos_tam()
				printf("Brak ilosci scian do postawienia.\nNacisnij dowolny klawisz aby kontynuowac.");
				_getch(); //funkcja z biblioteki <conio.h> dzieki ktorej nie trzeba naciskac entera przy uzyciu getchar()
						  //dzieki czemu mozna zrobic opcje "Nacisnij dowolny klawisz aby kontynuowac"
				return;
			}
		}
		else {
			if (p2.get_sciany() == 0) {
				printf("Brak ilosci scian do postawienia.\nNacisnij dowolny klawisz aby kontynuowac.");
				_getch(); //funkcja z biblioteki <conio.h> dzieki ktorej nie trzeba naciskac entera przy uzyciu getchar()
						  //dzieki czemu mozna zrobic opcje "Nacisnij dowolny klawisz aby kontynuowac"
				return;
			}
		}
		wyczysc();
		board.plansza_scianki();
		wypisz();
		printf("W jakim miejscu chcesz postawic sciane? (Podaj rzad i liczbe w rzedzie)\n");
		int rzad, liczba, kierunek;

		scanf("%d %d", &rzad, &liczba);
		if (rzad % 2 == 0) {
			printf("Chcesz dac scianke w:\n");
			bool w_gore = board.mozliwosc_postawienia_scianki(rzad, liczba, GORA);
			printf("1.Gora\n");
			bool w_dol = board.mozliwosc_postawienia_scianki(rzad, liczba, DOL);
			printf("2.Dol\n");
			set_color(BIALY);
			if (!w_gore && !w_dol) {
				printf("Brak mozliwosci postawienia scianki w tym miejscu.\nNacisnij dowolny klawisz aby kontynuowac.");
				_getch(); //funkcja z biblioteki <conio.h> dzieki ktorej nie trzeba naciskac entera przy uzyciu getchar()
						  //dzieki czemu mozna zrobic opcje "Nacisnij dowolny klawisz aby kontynuowac"
				return;
			}
			scanf("%d", &kierunek);
			if ((w_gore == false && kierunek == GORA) ||
				(w_dol == false && kierunek == DOL)) {
				printf("Nie mozesz postawic scianki w tym kierunku.\nNacisnij dowolny klawisz aby kontynuowac.");
				_getch(); //funkcja z biblioteki <conio.h> dzieki ktorej nie trzeba naciskac entera przy uzyciu getchar()
						  //dzieki czemu mozna zrobic opcje "Nacisnij dowolny klawisz aby kontynuowac"
				return;
			}
			board.ustaw_sciane(rzad, liczba, kierunek);
			board.plansza_scianki_reverse();
		}
		else {
			
			printf("Chcesz dac scianke w:\n");
			bool w_lewo = board.mozliwosc_postawienia_scianki(rzad, liczba, LEWO);
			printf("1.Lewo\n");
			bool w_prawo = board.mozliwosc_postawienia_scianki(rzad, liczba, PRAWO);
			printf("2.Prawo\n");
			set_color(BIALY);
			if (!w_lewo && !w_prawo) {
				printf("Brak mozliwosci postawienia scianki w tym kierunku.\nNacisnij dowolny klawisz aby kontynuowac.");
				_getch(); //funkcja z biblioteki <conio.h> dzieki ktorej nie trzeba naciskac entera przy uzyciu getchar()
						  //dzieki czemu mozna zrobic opcje "Nacisnij dowolny klawisz aby kontynuowac"
				return;
			}
			if ((w_lewo == false && kierunek == LEWO) ||
				(w_prawo == false && kierunek == PRAWO)) {
				printf("Nie mozesz postawic scianki w tym kierunku.\nNacisnij dowolny klawisz aby kontynuowac.");
				_getch(); //funkcja z biblioteki <conio.h> dzieki ktorej nie trzeba naciskac entera przy uzyciu getchar()
						  //dzieki czemu mozna zrobic opcje "Nacisnij dowolny klawisz aby kontynuowac"
				return;
			}
			scanf("%d", &kierunek);
			if (kierunek == 1) kierunek = LEWO;
			else kierunek = PRAWO;
			board.ustaw_sciane(rzad, liczba, kierunek);
			board.plansza_scianki_reverse();
			if (kogo_kolej == 1) {
				int scian = p1.get_sciany();
				p1.set_sciany(--scian);
			}
			else {
				int scian = p2.get_sciany();
				p2.set_sciany(--scian);
			}
		}
	}
	//zmienianie tury gracza
	kogo_kolej = (kogo_kolej == 1) ? 2 : 1;
}


// czemu uzywa metody to ustawiana pola w tej samej klasie
// ta zmienna jest dostepna w kalse gra (ona jest prywatna ale po za nia)
void gra::setGameOver(bool gameover) {
	isGameOver = gameover;
}

bool gra::p1_mozliwosc_w_gore() {
	int Y = p1.get_Y();
	int X = p1.get_X();
	if (Y == 0 || board.board[Y - 1][X] == 196) {
		return false;
	}
	else return true;
}
bool gra::p1_mozliwosc_w_dol() {
	int Y = p1.get_Y();
	int X = p1.get_X();
	if (Y == 16 || board.board[Y + 1][X] == 196) {
		return false;
	}
	else return true;
}
bool gra::p1_mozliwosc_w_lewo() {
	int Y = p1.get_Y();
	int X = p1.get_X();
	if (X == 0 || board.board[Y][X - 1] == 179) {
		return false;
	}
	else return true;
}

// wszykie meteody powinny przejomowac obietk typ pione 
// i wyciagajac jego propertisy okresic czy moze wykonac dany ruch
/*
#include pionek.costam

bool gra::mozliwosc_w_prawo(Pionek pionek) {
	if (pionek.get_y() == 16 || board.board[Y][X + 1] == 179)
		return false;
	else return true;
}
*/
bool gra::p1_mozliwosc_w_prawo() {
	int Y = pionek.get_Y();
	int X = p1.get_X();
	if (X == 16 || board.board[Y][X + 1] == 179) {
		return false;
	}
	else return true;
}
bool gra::p2_mozliwosc_w_gore() {
	int Y = p2.get_Y();
	int X = p2.get_X();
	if (Y == 0 || board.board[Y - 1][X] == 196) {
		return false;
	}
	else return true;
}
bool gra::p2_mozliwosc_w_dol() {
	int Y = p2.get_Y();
	int X = p2.get_X();
	if (Y == 16 || board.board[Y + 1][X] == 196) {
		return false;
	}
	else return true;
}
bool gra::p2_mozliwosc_w_lewo() {
	int Y = p2.get_Y();
	int X = p2.get_X();
	if (X == 0 || board.board[Y][X - 1] == 179) {
		return false;
	}
	else return true;
}
bool gra::p2_mozliwosc_w_prawo() {
	int Y = p2.get_Y();
	int X = p2.get_X();
	if (X == 16 || board.board[Y][X + 1] == 179) {
		return false;
	}
	else return true;
}

void gra::sprawdz_wygrana() {
	if (p1.get_Y() == 0) {
		set_color(CZERWONY);
		printf("\nKONIEC GRY, WYGRYWA GRACZ CZERWONY");
		setGameOver(true); // ustawainie wyniku mozesz wyciagnac z ifa
		// dodatkow setGameOver moglo by przyjowac obiekt player i w zalenosci od jego 
		// pola color prinotwac ta linie
		
		// te 3 metody powinny przyjmowac obiekt typu pionek (p) i byc wrzucone do klasy gry
		// wtedy te 3 metody wołasz raz za if-em 
		// dodatkowo sama metoda zakutalizuj_ranking (a własciwie update_scoarboard)
		// powinna sprawdzac czy gracz (player) istnieje w rankingu
		p1.dodaj_do_rankingu_jezeli_nie_istnieje();
		p2.dodaj_do_rankingu_jezeli_nie_istnieje();
		p1.zaktualizuj_ranking();
	}
	else if (p2.get_Y()==16) {
		set_color(ZIELONY);
		printf("\nKONIEC GRY, WYGRYWA GRACZ ZIELONY");
		setGameOver(true);
		p1.dodaj_do_rankingu_jezeli_nie_istnieje();
		p2.dodaj_do_rankingu_jezeli_nie_istnieje();
		p2.zaktualizuj_ranking();
	}
}
