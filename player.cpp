#define _CRT_SECURE_NO_WARNINGS
#include "player.h"
#include "kolory_kierunki.h"
#include <cstdlib>
#include <iostream>
#include <cstring>

void player::set_X(int XX) { X = XX; }
void player::set_Y(int YY) { Y = YY; }
void player::set_sciany(int sciany) { ilosc_scian = sciany; }
int player::get_X() { return X; }
int player::get_Y() { return Y; }
int player::get_sciany() { return ilosc_scian; }
player::player(int startX, int startY) : X(startX), Y(startY), ilosc_scian(10) {}

void player::wczytaj_nick() {
	printf("Podaj swoj nick: ");
	scanf("%s", nick); // Gracz, którego wynik chcemy zmodyfikowaæ
}

//klasa pomocnicza (struktura) rankingu (listy wynikow)
class lista_wynikow{
public:
	char Nick[30];
	int wynik;
	lista_wynikow* nast;
	lista_wynikow() : nast(NULL) {  };
};

//funkcja zmieniajaca elementy listy miedzy soba
void swap(lista_wynikow* a, lista_wynikow* b) {
	int temp_wynik = a->wynik;
	char temp_nick[20];
	strcpy(temp_nick, a->Nick);

	a->wynik = b->wynik;
	strcpy(a->Nick, b->Nick);

	b->wynik = temp_wynik;
	strcpy(b->Nick, temp_nick);
}

//fukcja pomocnicza sortujaca liste
void bubbleSort(lista_wynikow* head) {
	int swapped;
	lista_wynikow* ptr1;
	lista_wynikow* lptr = NULL;

	if (head == NULL)
		return;

	do {
		swapped = 0;
		ptr1 = head;

		while (ptr1->nast != lptr) {
			if (ptr1->wynik < ptr1->nast->wynik) { // Zmieniamy warunek na malej¹cy wzglêdem wyniku
				swap(ptr1, ptr1->nast);
				swapped = 1;
			}
			ptr1 = ptr1->nast;
		}
		lptr = ptr1;
	} while (swapped);
}

//motoda aktualizujaca wynik wygranego oraz ranking
void player::zaktualizuj_ranking() {

	FILE *file = fopen("ranking.txt", "a+");
	if (!file) {
		printf("Nie mo¿na otworzyæ pliku ranking.txt.\n");
		exit(0);
	}
	if (fgetc(file) == EOF) {
		rewind(file);
		fprintf(file, "%s %d\n", nick, 1);
		return;
	}
	rewind(file);
	lista_wynikow *glowa = new lista_wynikow();
	lista_wynikow *wsk = glowa;
	bool czy_gracz_istnieje_w_pliku = false;
	fscanf(file, "%s %d\n", glowa->Nick, &glowa->wynik);
	while (!feof(file)) {
		wsk->nast = new lista_wynikow();
		wsk = wsk->nast;
		fscanf(file, "%s %d\n", wsk->Nick, &wsk->wynik);
		if (strcmp(wsk->Nick, nick)==0) {
			wsk->wynik += 1;
			czy_gracz_istnieje_w_pliku = true;
		}
	}

	fclose(file);
	bubbleSort(glowa);

	file = fopen("ranking.txt", "w");
	if (!file) {
		printf("Nie mo¿na otworzyæ pliku ranking.txt.\n");
		exit(0);
	}
	int i = 1;
	set_color(BIALY);
	printf("\nRanking graczy (Top 5):\n");
	while (glowa!=NULL) {
		if(i<=5) printf("%d. %s %d\n",i, glowa->Nick, glowa->wynik);
		i++;
		fprintf(file, "%s %d\n", glowa->Nick, glowa->wynik);
		glowa = glowa->nast;
	}
	fclose(file);
}

//metoda sprawdzajaca czy gracz jest zapisany w pliku ranking.txt, jezeli nie - zostaje wpisamy z 0 pktami
void player::dodaj_do_rankingu_jezeli_nie_istnieje() {
	FILE *file = fopen("ranking.txt", "a+");
	if (!file) {
		printf("Nie mo¿na otworzyæ pliku ranking.txt.\n");
		exit(0);
	}

	lista_wynikow *glowa = new lista_wynikow();
	lista_wynikow *wsk = glowa;
	bool czy_gracz_istnieje_w_pliku = false;
	fscanf(file, "%s %d\n", glowa->Nick, &glowa->wynik);
	while (!feof(file)) {
		wsk->nast = new lista_wynikow();
		wsk = wsk->nast;
		fscanf(file, "%s %d\n", wsk->Nick, &wsk->wynik);
		if (!strcmp(wsk->Nick, nick)) czy_gracz_istnieje_w_pliku = true;
	}

	if (!czy_gracz_istnieje_w_pliku) {
		fprintf(file, "%s %d\n", nick, 0);
	}
	fclose(file);
}