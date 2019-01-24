/*
#########################################################################################
#																					                                            	#
#										                    Wykonał:										                    #
#									                    Marek Żubrycki									                  #
#		          Student 1 roku Wyższej Szkoły Informatyki i Zarządzania "Copernicus"      #
#									                    we Wrocławiu									                    #
#																						                                            #
#########################################################################################
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <windows.h>

using namespace std;

char figura(int szachownica[8][8], int i, int j) { //funkcja potrzebna do wyświetlania (zamienia numery figury na ich symboliczne oznaczenia)
	if (szachownica[i][j] == 1 || szachownica[i][j] == 7) return 'P';
	else {
		if (szachownica[i][j] == 2 || szachownica[i][j] == 8) return 'W';
		else {
			if (szachownica[i][j] == 3 || szachownica[i][j] == 9) return 'R';
			else {
				if (szachownica[i][j] == 4 || szachownica[i][j] == 10) return 'L';
				else {
					if (szachownica[i][j] == 5 || szachownica[i][j] == 11) return 'K';
					else {
						if (szachownica[i][j] == 6 || szachownica[i][j] == 12) return 'Q';
						else return 0;
					}
				}
			}
		}
	}

}

void wprowadzone_dane(char Sprawdzana_tablica[2]) { //poprawia wprowadzone dane w przypadku odwrotnej kolejności lub użycia wielkich liter
	if (Sprawdzana_tablica[0] > 48 && Sprawdzana_tablica[0] < 57) swap(Sprawdzana_tablica[0], Sprawdzana_tablica[1]); //zamienia miejscami w przypadku użycia na początku liczby
	if (Sprawdzana_tablica[0] > 64 && Sprawdzana_tablica[0] < 73) Sprawdzana_tablica[0] += 32; //zamienia wielkie litery na małe
}

void ulozenie_przed_ruchem(int szachownica[8][8], int poprzednie_ulozenie[8][8]) {//przepisuje wartości z jednej tablicy do drugiej
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			poprzednie_ulozenie[i][j] = szachownica[i][j];
		}
	}
}

int przeksztalcanie(char miejsce[2]) { //przekształca wpisaną literę na liczbę (potrzebne przy tablicach)
	if (miejsce[0] > 96 && miejsce[0] < 105) return miejsce[0] - 97;
	else return 9; //jako że tablica zawierająca cały układ figur jest od 0 do 7, to liczba 9 będąca poza zakresem, będzie zawsze błędna
}

//Globalne tablice
int ruszad[6] = { 2, 5, 2, 8, 11, 8 }; //podana globalna tablicy potrzebna jest do ruszady, aby sprawdzić czy w przeszłości zrobiliśmy jakiś ruch daną wieżą (kolejność w tablicy jest ważna) lub królem (2 5 2 są po stronie białej, a 8 11 8 są po stronie czarnej)
char poprzedni_ruch_przeciwnika[2] = { 0, 0 }; //podana globalna tablica przechowuje miejsce na planszy do którego poruszył się przeciwnik (potrzebne przy wyświetlaniu)
int zbite_figury[32]; //przechwouje wszystkie zbite figury

void nowe_logi_ruszada() {//przywraca pierwotne wartości globalnej tablicy ruszad
	ruszad[0] = 2;
	ruszad[1] = 5;
	ruszad[2] = 2;
	ruszad[3] = 8;
	ruszad[4] = 11;
	ruszad[5] = 8;
}

int jaka_to_figura(char miejsce[2], int szachownica[8][8]) { //Podaje numer figury (każda figura ma swój przypisany numer)
	return szachownica[miejsce[1] - 49][przeksztalcanie(miejsce)];
}
bool czyRuchDozwolony(int szachownica[8][8], char Figura_ktora[2], char Figura_gdzie[2]); //deklarujemy, że w kodzie będzie jakaś funkcja "czyRuchDozwolony", ale będzie zdefiniowana potem (potrzebne po to, aby użyć "czyRuchDozwolony" w funkcji "ruszada" po której dopiero jest opisana funkcja "czyRuchDozwolony")

bool ruszada(int ruszada[6], char Figura_ktora[2], char Figura_gdzie[2], int strona, int szachownica[8][8]) { //sprawdza czy można wykonać ruszadę
	char miejsce[2];
	char miejsce2[2];
	bool flaga = true;
	if (jaka_to_figura(Figura_ktora, szachownica) == 5 || jaka_to_figura(Figura_ktora, szachownica) == 11) {
		if (strona == 0) { //dla białej strony
			if (przeksztalcanie(Figura_gdzie) == 2 && ruszada[0] != 0 && ruszada[1] != 0) { //dla lewej wieży (w kolumnie A)
				for (int a = 0; a < 5; a++) {
					miejsce[0] = a + 97;
					miejsce[1] = 49;
					for (int x = 0; x < 8; x++) {
						for (int y = 0; y < 8; y++) {
							miejsce2[0] = y + 97;
							miejsce2[1] = x + 49;
							if (szachownica[x][y] > 6 && czyRuchDozwolony(szachownica, miejsce2, miejsce) == true) flaga = false;
						}
					}
				}
			}
			else {
				if (przeksztalcanie(Figura_gdzie) == 6 && ruszada[2] != 0 && ruszada[1] != 0) { //dla prawej wieży (w kolumnie H)
					for (int a = 0; a < 4; a++) {
						miejsce[0] = 97 + (7 - a);
						miejsce[1] = 49;
						for (int x = 0; x < 8; x++) {
							for (int y = 0; y < 8; y++) {
								miejsce2[0] = y + 97;
								miejsce2[1] = x + 49;
								if (szachownica[x][y] > 6 && czyRuchDozwolony(szachownica, miejsce2, miejsce) == true) flaga = false;
							}
						}
					}
				}
				else flaga = false;
			}
		}
		else { //dla czarnej strony
			if (przeksztalcanie(Figura_gdzie) == 2 && ruszada[3] != 0 && ruszada[4] != 0) { //dla prawej wieży z perspektywy czarnej strony (w kolumnie A)
				for (int a = 0; a < 5; a++) {
					miejsce[0] = a + 97;
					miejsce[1] = 49 + 7;
					for (int x = 0; x < 8; x++) {
						for (int y = 0; y < 8; y++) {
							miejsce2[0] = y + 97;
							miejsce2[1] = x + 49;
							if (szachownica[x][y] != 0 && szachownica[x][y] < 7 && czyRuchDozwolony(szachownica, miejsce2, miejsce) == true) flaga = false;
						}
					}
				}
			}
			else {
				if (przeksztalcanie(Figura_gdzie) == 6 && ruszada[5] != 0 && ruszada[4] != 0) { //dla lewej wieży z perspektywy czarnej strony (w kolumnie H)
					for (int a = 0; a < 4; a++) {
						miejsce[0] = 97 + (7 - a);
						miejsce[1] = 49 + 7;
						for (int x = 0; x < 8; x++) {
							for (int y = 0; y < 8; y++) {
								miejsce2[0] = y + 97;
								miejsce2[1] = x + 49;
								if (szachownica[x][y] != 0 && szachownica[x][y] < 7 && czyRuchDozwolony(szachownica, miejsce2, miejsce) == true) flaga = false;
							}
						}
					}
				}
				else flaga = false;
			}
		}
	}
	else flaga = false;
	if (flaga == true) return true;
	else return false;
}

bool czyRuchDozwolony(int szachownica[8][8], char Figura_ktora[2], char Figura_gdzie[2]) { //sprawdza czy ruch jest prawidłowy według zasad szachów
	int NumerFiguryPoruszanej = jaka_to_figura(Figura_ktora, szachownica);
	int NumerFiguryDocelowej = jaka_to_figura(Figura_gdzie, szachownica); //zmienna potrzebna do pionka
	bool flaga = false; //sprawdza czy zaszała jakaś zmiana/coś się nie zgadza

	switch (NumerFiguryPoruszanej) {
	case 1: //biały pionek
		if (Figura_ktora[1] == 2 + 48 && NumerFiguryDocelowej == 0 && szachownica[Figura_gdzie[1] - 1 - 49][przeksztalcanie(Figura_gdzie)] == 0 && Figura_ktora[1] + 2 == Figura_gdzie[1] && przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie)) return true;
		else {
			if (jaka_to_figura(Figura_gdzie, szachownica) == 0 && Figura_ktora[1] + 1 == Figura_gdzie[1] && przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie)) return true;
			else {
				if (jaka_to_figura(Figura_gdzie, szachownica) != 0 && Figura_ktora[1] + 1 == Figura_gdzie[1] && (przeksztalcanie(Figura_ktora) - 1 == przeksztalcanie(Figura_gdzie) || przeksztalcanie(Figura_ktora) + 1 == przeksztalcanie(Figura_gdzie))) return true;
				else return false;
			}
		}
		break;
	case 2: //biała wieża
		if (Figura_ktora[1] == Figura_gdzie[1]) {
			if (przeksztalcanie(Figura_ktora) < przeksztalcanie(Figura_gdzie)) {
				for (int i = przeksztalcanie(Figura_ktora) + 1; i < przeksztalcanie(Figura_gdzie); i++) {
					if (szachownica[Figura_ktora[1] - 49][i] != 0) flaga = true;
				}
			}
			if (przeksztalcanie(Figura_ktora) > przeksztalcanie(Figura_gdzie)) {
				for (int i = przeksztalcanie(Figura_ktora) - 1; i > przeksztalcanie(Figura_gdzie); i--) {
					if (szachownica[Figura_ktora[1] - 49][i] != 0) flaga = true;
				}
			}
		}
		else {
			if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie)) {
				if (Figura_ktora[1] < Figura_gdzie[1]) {
					for (int i = Figura_ktora[1] + 1; i < Figura_gdzie[1]; i++) {
						if (szachownica[i - 49][przeksztalcanie(Figura_ktora)] != 0) flaga = true;
					}
				}
				if (Figura_ktora[1] > Figura_gdzie[1]) {
					for (int i = Figura_ktora[1] - 1; i > Figura_gdzie[1]; i--) {
						if (szachownica[i - 49][przeksztalcanie(Figura_ktora)] != 0) flaga = true;
					}
				}
			}
			else flaga = true;
		}
		if (flaga == true) return false;
		else return true;
		break;
	case 3: //biały koń/rycerz
		if (Figura_ktora[1] < Figura_gdzie[1]) {
			if (Figura_gdzie[1] == Figura_ktora[1] + 2) {
				if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) + 1 || przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) - 1) return true;
				else return false;
			}
			else {
				if (Figura_gdzie[1] == Figura_ktora[1] + 1) {
					if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) + 2 || przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) - 2) return true;
					else return false;
				}
				else return false;
			}
		}
		else {
			if (Figura_ktora[1] > Figura_gdzie[1]) {
				if (Figura_gdzie[1] + 2 == Figura_ktora[1]) {
					if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) + 1 || przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) - 1) return true;
					else return false;
				}
				else {
					if (Figura_gdzie[1] + 1 == Figura_ktora[1]) {
						if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) + 2 || przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) - 2) return true;
						else return false;
					}
					else return false;
				}
			}
			else {
				return false;
			}
		}
		break;
	case 4: //biały laufer

		if (Figura_ktora[1] < Figura_gdzie[1]) {
			if (przeksztalcanie(Figura_ktora) < przeksztalcanie(Figura_gdzie)) {
				if (przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora) == Figura_gdzie[1] - Figura_ktora[1]) {
					for (int i = 1; i < przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora); i++) {
						if (szachownica[Figura_ktora[1] - 49 + i][przeksztalcanie(Figura_ktora) + i] != 0) flaga = true;
					}
				}
				else flaga = true;
			}
			else {
				if (przeksztalcanie(Figura_ktora) > przeksztalcanie(Figura_gdzie)) {
					if (przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie) == Figura_gdzie[1] - Figura_ktora[1]) {
						for (int i = 1; i < przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie); i++) {
							if (szachownica[Figura_ktora[1] - 49 + i][przeksztalcanie(Figura_ktora) - i] != 0) flaga = true;
						}
					}
					else flaga = true;
				}
				else flaga = true;
			}
		}
		else {
			if (Figura_ktora[1] > Figura_gdzie[1]) {
				if (przeksztalcanie(Figura_ktora) < przeksztalcanie(Figura_gdzie)) {
					if (przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora) == Figura_ktora[1] - Figura_gdzie[1]) {
						for (int i = 1; i < przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora); i++) {
							if (szachownica[Figura_ktora[1] - 49 - i][przeksztalcanie(Figura_ktora) + i] != 0) flaga = true;
						}
					}
					else flaga = true;
				}
				else {
					if (przeksztalcanie(Figura_ktora) > przeksztalcanie(Figura_gdzie)) {
						if (przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie) == Figura_ktora[1] - Figura_gdzie[1]) {
							for (int i = 1; i < przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie); i++) {
								if (szachownica[Figura_ktora[1] - 49 - i][przeksztalcanie(Figura_ktora) - i] != 0) flaga = true;
							}
						}
						else flaga = true;
					}
					else flaga = true;
				}
			}
			else flaga = true;
		}
		if (flaga == true) return false;
		else return true;
		break;
	case 5: //biały król
		if (Figura_ktora[1] == Figura_gdzie[1]) {
			if (przeksztalcanie(Figura_ktora) + 1 == przeksztalcanie(Figura_gdzie) || przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) + 1) return true;
			else {
				if (Figura_ktora[1] == 49 && przeksztalcanie(Figura_gdzie) == 2 && ruszada(ruszad, Figura_ktora, Figura_gdzie, 0, szachownica) == true) return true;
				else {
					if (Figura_ktora[1] == 49 && przeksztalcanie(Figura_gdzie) == 6 && ruszada(ruszad, Figura_ktora, Figura_gdzie, 0, szachownica) == true) return true;
					else return false;
				}
			}
		}
		else {
			if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie)) {
				if (Figura_ktora[1] + 1 == Figura_gdzie[1] || Figura_ktora[1] == Figura_gdzie[1] + 1) return true;
				else return false;
			}
			else {
				if ((przeksztalcanie(Figura_ktora) + 1 == przeksztalcanie(Figura_gdzie) || przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) + 1) && (Figura_ktora[1] + 1 == Figura_gdzie[1] || Figura_ktora[1] == Figura_gdzie[1] + 1)) return true;
				else return false;
			}
		}
		break;
	case 6: //biała królowa
		if (Figura_ktora[1] == Figura_gdzie[1]) {
			if (przeksztalcanie(Figura_ktora) < przeksztalcanie(Figura_gdzie)) {
				for (int i = przeksztalcanie(Figura_ktora) + 1; i < przeksztalcanie(Figura_gdzie); i++) {
					if (szachownica[Figura_ktora[1] - 49][i] != 0) flaga = true;
				}
			}
			if (przeksztalcanie(Figura_ktora) > przeksztalcanie(Figura_gdzie)) {
				for (int i = przeksztalcanie(Figura_ktora) - 1; i > przeksztalcanie(Figura_gdzie); i--) {
					if (szachownica[Figura_ktora[1] - 49][i] != 0) flaga = true;
				}
			}
		}
		else {
			if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie)) {
				if (Figura_ktora[1] < Figura_gdzie[1]) {
					for (int i = Figura_ktora[1] + 1; i < Figura_gdzie[1]; i++) {
						if (szachownica[i - 49][przeksztalcanie(Figura_ktora)] != 0) flaga = true;
					}
				}
				if (Figura_ktora[1] > Figura_gdzie[1]) {
					for (int i = Figura_ktora[1] - 1; i > Figura_gdzie[1]; i--) {
						if (szachownica[i - 49][przeksztalcanie(Figura_ktora)] != 0) flaga = true;
					}
				}
			}
			else {
				if (Figura_ktora[1] < Figura_gdzie[1]) {
					if (przeksztalcanie(Figura_ktora) < przeksztalcanie(Figura_gdzie)) {
						if (przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora) == Figura_gdzie[1] - Figura_ktora[1]) {
							for (int i = 1; i < przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora); i++) {
								if (szachownica[Figura_ktora[1] - 49 + i][przeksztalcanie(Figura_ktora) + i] != 0) flaga = true;
							}
						}
						else flaga = true;
					}
					if (przeksztalcanie(Figura_ktora) > przeksztalcanie(Figura_gdzie)) {
						if (przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie) == Figura_gdzie[1] - Figura_ktora[1]) {
							for (int i = 1; i < przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie); i++) {
								if (szachownica[Figura_ktora[1] - 49 + i][przeksztalcanie(Figura_ktora) - i] != 0) flaga = true;
							}
						}
						else flaga = true;
					}
				}
				else {
					if (Figura_ktora[1] > Figura_gdzie[1]) {
						if (przeksztalcanie(Figura_ktora) < przeksztalcanie(Figura_gdzie)) {
							if (przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora) == Figura_ktora[1] - Figura_gdzie[1]) {
								for (int i = 1; i < przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora); i++) {
									if (szachownica[Figura_ktora[1] - 49 - i][przeksztalcanie(Figura_ktora) + i] != 0) flaga = true;
								}
							}
							else flaga = true;
						}
						if (przeksztalcanie(Figura_ktora) > przeksztalcanie(Figura_gdzie)) {
							if (przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie) == Figura_ktora[1] - Figura_gdzie[1]) {
								for (int i = 1; i < przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie); i++) {
									if (szachownica[Figura_ktora[1] - 49 - i][przeksztalcanie(Figura_ktora) - i] != 0) flaga = true;
								}
							}
							else flaga = true;
						}
					}
					else flaga = true;
				}
			}
		}
		if (flaga == true) return false;
		else return true;
		break;
	case 7: //czarny pionek
		if (Figura_ktora[1] == 6 + 49 && NumerFiguryDocelowej == 0 && szachownica[Figura_gdzie[1] + 1 - 49][przeksztalcanie(Figura_gdzie)] == 0 && Figura_ktora[1] - 2 == Figura_gdzie[1] && przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie)) return true;
		else {
			if (jaka_to_figura(Figura_gdzie, szachownica) == 0 && Figura_ktora[1] - 1 == Figura_gdzie[1] && przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie)) return true;
			else {
				if (jaka_to_figura(Figura_gdzie, szachownica) != 0 && Figura_ktora[1] - 1 == Figura_gdzie[1] && (przeksztalcanie(Figura_ktora) - 1 == przeksztalcanie(Figura_gdzie) || przeksztalcanie(Figura_ktora) + 1 == przeksztalcanie(Figura_gdzie))) return true;
				else return false;
			}
		}
		break;
	case 8: //czarna wieża

		if (Figura_ktora[1] == Figura_gdzie[1]) {
			if (przeksztalcanie(Figura_ktora) < przeksztalcanie(Figura_gdzie)) {
				for (int i = przeksztalcanie(Figura_ktora) + 1; i < przeksztalcanie(Figura_gdzie); i++) {
					if (szachownica[Figura_ktora[1] - 49][i] != 0) flaga = true;
				}
			}
			if (przeksztalcanie(Figura_ktora) > przeksztalcanie(Figura_gdzie)) {
				for (int i = przeksztalcanie(Figura_ktora) - 1; i > przeksztalcanie(Figura_gdzie); i--) {
					if (szachownica[Figura_ktora[1] - 49][i] != 0) flaga = true;
				}
			}
		}
		else {
			if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie)) {
				if (Figura_ktora[1] < Figura_gdzie[1]) {
					for (int i = Figura_ktora[1] + 1; i < Figura_gdzie[1]; i++) {
						if (szachownica[i - 49][przeksztalcanie(Figura_ktora)] != 0) flaga = true;
					}
				}
				if (Figura_ktora[1] > Figura_gdzie[1]) {
					for (int i = Figura_ktora[1] - 1; i > Figura_gdzie[1]; i--) {
						if (szachownica[i - 49][przeksztalcanie(Figura_ktora)] != 0) flaga = true;
					}
				}
			}
			else flaga = true;
		}
		if (flaga == true) return false;
		else return true;
		break;
	case 9: //czarny koń/rycerz
		if (Figura_ktora[1] < Figura_gdzie[1]) {
			if (Figura_gdzie[1] == Figura_ktora[1] + 2) {
				if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) + 1 || przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) - 1) return true;
				else return false;
			}
			else {
				if (Figura_gdzie[1] == Figura_ktora[1] + 1) {
					if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) + 2 || przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) - 2) return true;
					else return false;
				}
				else return false;
			}
		}
		else {
			if (Figura_ktora[1] > Figura_gdzie[1]) {
				if (Figura_gdzie[1] + 2 == Figura_ktora[1]) {
					if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) + 1 || przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) - 1) return true;
					else return false;
				}
				else {
					if (Figura_gdzie[1] + 1 == Figura_ktora[1]) {
						if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) + 2 || przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) - 2) return true;
						else return false;
					}
					else return false;
				}
			}
			else return false;
		}
		break;
	case 10: //czarny laufer

		if (Figura_ktora[1] < Figura_gdzie[1]) {
			if (przeksztalcanie(Figura_ktora) < przeksztalcanie(Figura_gdzie)) {
				if (przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora) == Figura_gdzie[1] - Figura_ktora[1]) {
					for (int i = 1; i < przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora); i++) {
						if (szachownica[Figura_ktora[1] - 49 + i][przeksztalcanie(Figura_ktora) + i] != 0) flaga = true;
					}
				}
				else flaga = true;
			}
			else {
				if (przeksztalcanie(Figura_ktora) > przeksztalcanie(Figura_gdzie)) {
					if (przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie) == Figura_gdzie[1] - Figura_ktora[1]) {
						for (int i = 1; i < przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie); i++) {
							if (szachownica[Figura_ktora[1] - 49 + i][przeksztalcanie(Figura_ktora) - i] != 0) flaga = true;
						}
					}
					else flaga = true;
				}
				else flaga = true;
			}
		}
		else {
			if (Figura_ktora[1] > Figura_gdzie[1]) {
				if (przeksztalcanie(Figura_ktora) < przeksztalcanie(Figura_gdzie)) {
					if (przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora) == Figura_ktora[1] - Figura_gdzie[1]) {
						for (int i = 1; i < przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora); i++) {
							if (szachownica[Figura_ktora[1] - 49 - i][przeksztalcanie(Figura_ktora) + i] != 0) flaga = true;
						}
					}
					else flaga = true;
				}
				else {
					if (przeksztalcanie(Figura_ktora) > przeksztalcanie(Figura_gdzie)) {
						if (przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie) == Figura_ktora[1] - Figura_gdzie[1]) {
							for (int i = 1; i < przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie); i++) {
								if (szachownica[Figura_ktora[1] - 49 - i][przeksztalcanie(Figura_ktora) - i] != 0) flaga = true;
							}
						}
						else flaga = true;
					}
					else flaga = true;
				}
			}
			else flaga = true;
		}
		if (flaga == true) return false;
		else return true;
		break;
	case 11: //czarny król
		if (Figura_ktora[1] == Figura_gdzie[1]) {
			if (przeksztalcanie(Figura_ktora) + 1 == przeksztalcanie(Figura_gdzie) || przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) + 1) return true;
			else {
				if (Figura_ktora[1] == 7 + 49 && przeksztalcanie(Figura_gdzie) == 2 && ruszada(ruszad, Figura_ktora, Figura_gdzie, 1, szachownica) == true) return true;
				else {
					if (Figura_ktora[1] == 7 + 49 && przeksztalcanie(Figura_gdzie) == 6 && ruszada(ruszad, Figura_ktora, Figura_gdzie, 1, szachownica) == true) return true;
					else return false;
				}
			}
		}
		else {
			if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie)) {
				if (Figura_ktora[1] + 1 == Figura_gdzie[1] || Figura_ktora[1] == Figura_gdzie[1] + 1) return true;
				else return false;
			}
			else {
				if ((przeksztalcanie(Figura_ktora) + 1 == przeksztalcanie(Figura_gdzie) || przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie) + 1) && (Figura_ktora[1] + 1 == Figura_gdzie[1] || Figura_ktora[1] == Figura_gdzie[1] + 1)) return true;
				else return false;
			}
		}
		break;
	case 12: //czarna królowa
		if (Figura_ktora[1] == Figura_gdzie[1]) {
			if (przeksztalcanie(Figura_ktora) < przeksztalcanie(Figura_gdzie)) {
				for (int i = przeksztalcanie(Figura_ktora) + 1; i < przeksztalcanie(Figura_gdzie); i++) {
					if (szachownica[Figura_ktora[1] - 49][i] != 0) flaga = true;
				}
			}
			if (przeksztalcanie(Figura_ktora) > przeksztalcanie(Figura_gdzie)) {
				for (int i = przeksztalcanie(Figura_ktora) - 1; i > przeksztalcanie(Figura_gdzie); i--) {
					if (szachownica[Figura_ktora[1] - 49][i] != 0) flaga = true;
				}
			}
		}
		else {
			if (przeksztalcanie(Figura_ktora) == przeksztalcanie(Figura_gdzie)) {
				if (Figura_ktora[1] < Figura_gdzie[1]) {
					for (int i = Figura_ktora[1] + 1; i < Figura_gdzie[1]; i++) {
						if (szachownica[i - 49][przeksztalcanie(Figura_ktora)] != 0) flaga = true;
					}
				}
				if (Figura_ktora[1] > Figura_gdzie[1]) {
					for (int i = Figura_ktora[1] - 1; i > Figura_gdzie[1]; i--) {
						if (szachownica[i - 49][przeksztalcanie(Figura_ktora)] != 0) flaga = true;
					}
				}
			}
			else {
				if (Figura_ktora[1] < Figura_gdzie[1]) {
					if (przeksztalcanie(Figura_ktora) < przeksztalcanie(Figura_gdzie)) {
						if (przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora) == Figura_gdzie[1] - Figura_ktora[1]) {
							for (int i = 1; i < przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora); i++) {
								if (szachownica[Figura_ktora[1] - 49 + i][przeksztalcanie(Figura_ktora) + i] != 0) flaga = true;
							}
						}
						else flaga = true;
					}
					if (przeksztalcanie(Figura_ktora) > przeksztalcanie(Figura_gdzie)) {
						if (przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie) == Figura_gdzie[1] - Figura_ktora[1]) {
							for (int i = 1; i < przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie); i++) {
								if (szachownica[Figura_ktora[1] - 49 + i][przeksztalcanie(Figura_ktora) - i] != 0) flaga = true;
							}
						}
						else flaga = true;
					}
				}
				else {
					if (Figura_ktora[1] > Figura_gdzie[1]) {
						if (przeksztalcanie(Figura_ktora) < przeksztalcanie(Figura_gdzie)) {
							if (przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora) == Figura_ktora[1] - Figura_gdzie[1]) {
								for (int i = 1; i < przeksztalcanie(Figura_gdzie) - przeksztalcanie(Figura_ktora); i++) {
									if (szachownica[Figura_ktora[1] - 49 - i][przeksztalcanie(Figura_ktora) + i] != 0) flaga = true;
								}
							}
							else flaga = true;
						}
						if (przeksztalcanie(Figura_ktora) > przeksztalcanie(Figura_gdzie)) {
							if (przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie) == Figura_ktora[1] - Figura_gdzie[1]) {
								for (int i = 1; i < przeksztalcanie(Figura_ktora) - przeksztalcanie(Figura_gdzie); i++) {
									if (szachownica[Figura_ktora[1] - 49 - i][przeksztalcanie(Figura_ktora) - i] != 0) flaga = true;
								}
							}
							else flaga = true;
						}
					}
					else flaga = true;
				}
			}
		}
		if (flaga == true) return false;
		else return true;
		break;
	default:
		return false;
		break;
	}
}

int figura_na_numer(string figura, int strona) { //zwraca numer figury po podaniu literki (potrzebne do przypadku, w którym biały pionek dochodzi do 8 wiersza lub czarny pionek do pierwszego wiersza)
	int numer;
	if (figura == "P" || figura == "p") numer = 1;
	else {
		if (figura == "W" || figura == "w") numer = 2;
		else {
			if (figura == "R" || figura == "r") numer = 3;
			else {
				if (figura == "L" || figura == "l") numer = 4;
				else {
					if (figura == "K" || figura == "k") numer = 5;
					else {
						if (figura == "Q" || figura == "q") numer = 6;
						else {
							numer = 0;
						}
					}
				}
			}
		}
	}
	if (strona == 0) return numer;
	else return numer + 6;
}

bool szach(int szachownica[8][8], int strona, char krol[2]) { //sprawdza czy nie ma "Szacha" (król pod biciem wrogiej figury)
	bool flaga = false;
	char figura_sprawdzana[2];

	if (strona == 0) { //dla białych 
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (szachownica[i][j] == 5) {
					krol[0] = j + 97;
					krol[1] = i + 49;
					break;
				}
			}
		}
		for (int c = 0; c < 8; c++) {
			for (int d = 0; d < 8; d++) {
				figura_sprawdzana[0] = d + 97;
				figura_sprawdzana[1] = c + 49;
				if (szachownica[c][d] > 6 && czyRuchDozwolony(szachownica, figura_sprawdzana, krol) == true) flaga = true;
			}
		}
	}
	else { //dla czarnych
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (szachownica[i][j] == 11) {
					krol[0] = j + 97;
					krol[1] = i + 49;
					break;
				}
			}
		}
		for (int c = 0; c < 8; c++) {
			for (int d = 0; d < 8; d++) {
				figura_sprawdzana[0] = d + 97;
				figura_sprawdzana[1] = c + 49;
				if (szachownica[c][d] < 7 && czyRuchDozwolony(szachownica, figura_sprawdzana, krol) == true) flaga = true;
			}
		}
	}
	if (flaga == true) return true;
	else return false;
}

bool szachMat(int szachownica[8][8], int poprzednie_ulozenie[8][8], int strona, char krolo[2]) { //sprawdza czy nie ma "Szach Mat" (ostateczny "Szach")
	if (szach(szachownica, strona, krolo) == true) {
		char miejsce[2];
		bool brakszachu = false;
		//robię kopię pozycjy króla, ponieważ nie chce, aby funkcja nadpisała rzeczywiste położenie króla przy rozpatrywaniu przypadków
		char krolk[2];
		krolk[0] = krolo[0];
		krolk[1] = krolo[1];
		if (strona == 0) { //dla białych
			for (int c = 0; c < 8; c++) {
				for (int d = 0; d < 8; d++) {
					miejsce[0] = d + 97;
					miejsce[1] = c + 49;
					if ((szachownica[c][d] > 6 || szachownica[c][d] == 0) && czyRuchDozwolony(szachownica, krolk, miejsce) == true) {
						if (szachownica[c][d] != 0) poprzednie_ulozenie[c][d] = 0;
						swap(poprzednie_ulozenie[c][d], poprzednie_ulozenie[krolk[1] - 49][krolk[0] - 97]);
						if (szach(poprzednie_ulozenie, strona, krolk) == false) brakszachu = true;
						krolk[0] = krolo[0];
						krolk[1] = krolo[1];
						ulozenie_przed_ruchem(szachownica, poprzednie_ulozenie);
					}
				}
			}
			if (brakszachu == true) return false;
			else {
				char miejsce2[2];
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if (szachownica[a][b] > 0 && szachownica[a][b] < 7) {
							miejsce[0] = b + 97;
							miejsce[1] = a + 49;
							for (int c = 0; c < 8; c++) {
								for (int d = 0; d < 8; d++) {
									miejsce2[0] = d + 97;
									miejsce2[1] = c + 49;
									if ((szachownica[c][d] > 6 || szachownica[c][d] == 0) && czyRuchDozwolony(szachownica, miejsce, miejsce2) == true) {
										if (szachownica[c][d] != 0) poprzednie_ulozenie[c][d] = 0;
										swap(poprzednie_ulozenie[c][d], poprzednie_ulozenie[a][b]);
										if (szach(poprzednie_ulozenie, strona, krolk) == false) brakszachu = true;
										ulozenie_przed_ruchem(szachownica, poprzednie_ulozenie);
									}
								}
							}
						}
					}
				}
				if (brakszachu == true) return false;
				else return true;
			}
		}
		else { //dla czarnych
			for (int c = 0; c < 8; c++) {
				for (int d = 0; d < 8; d++) {
					miejsce[0] = d + 97;
					miejsce[1] = c + 49;
					if ((szachownica[c][d] < 7 || szachownica[c][d] == 0) && czyRuchDozwolony(szachownica, krolk, miejsce) == true) {
						if (szachownica[c][d] != 0) poprzednie_ulozenie[c][d] = 0;
						swap(poprzednie_ulozenie[c][d], poprzednie_ulozenie[krolk[1] - 49][krolk[0] - 97]);
						if (szach(szachownica, strona, krolk) == false) brakszachu = true;
						krolk[0] = krolo[0];
						krolk[1] = krolo[1];
						ulozenie_przed_ruchem(szachownica, poprzednie_ulozenie);
					}
				}
			}
			if (brakszachu == true) return false;
			else {
				char miejsce2[2];
				for (int a = 0; a < 8; a++) {
					for (int b = 0; b < 8; b++) {
						if (szachownica[a][b] == 0 || szachownica[a][b] > 6) {
							miejsce[0] = b + 97;
							miejsce[1] = a + 49;
							for (int c = 0; c < 8; c++) {
								for (int d = 0; d < 8; d++) {
									miejsce2[0] = d + 97;
									miejsce2[1] = c + 49;
									if (szachownica[c][d] < 7 && czyRuchDozwolony(szachownica, miejsce, miejsce2) == true) {
										if (szachownica[c][d] != 0) poprzednie_ulozenie[c][d] = 0;
										swap(poprzednie_ulozenie[c][d], poprzednie_ulozenie[a][b]);
										if (szach(poprzednie_ulozenie, strona, krolk) == false) brakszachu = true;
										ulozenie_przed_ruchem(szachownica, poprzednie_ulozenie);
									}
								}
							}
						}
					}
				}
				if (brakszachu == true) return false;
				else return true;
			}
		}
	}
	else return false;
}

void zbite_figury_wyswietlanie(int strona) { //wyświetla wszystkie zbite figury, przez daną stronę
	int tablica[8][8]; //wymyślona plansza, potrzebna do funkcji "figura", aby zamieniała numery figur na ich symbole, do której w miejscu [0][0] będziemy zawsze przypisywać numer figury którą chcemy wyświetlić
	cout << " Zbite\nwrogie	";
	for (int i = 0; i < 16; i++) {
		if (strona == 1) { //zbite czarne figury
			if (zbite_figury[i] > 6) {
				tablica[0][0] = zbite_figury[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6 << 4 | 0);
				cout << figura(tablica, 0, 0);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
				cout << " ";
			}
		}
		else { //zbite białe figury
			if (zbite_figury[i] < 7 && zbite_figury[i] != 0) {
				tablica[0][0] = zbite_figury[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6 << 4 | 15);
				cout << figura(tablica, 0, 0);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
				cout << " ";
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	cout << "\nfigury\n\n";
}

bool warunki(int strona, int szachownica[8][8], char Figura_ktora[2], char Figura_gdzie[2], char krol[2]) { //warunki do funkcji "Pat" i "plansza"
	bool bezpiecznik = true;
	int poprzednie_ulo[8][8];
	ulozenie_przed_ruchem(szachownica, poprzednie_ulo);
	if (strona == 0) { //dla białych
		if (przeksztalcanie(Figura_ktora) > 7 || przeksztalcanie(Figura_gdzie) > 7 || Figura_ktora[1] == '9' || Figura_gdzie[1] == '9' || (jaka_to_figura(Figura_gdzie, szachownica) < 7 && jaka_to_figura(Figura_gdzie, szachownica) != 0)) bezpiecznik = false;
		else {
			swap(poprzednie_ulo[Figura_ktora[1] - 49][przeksztalcanie(Figura_ktora)], poprzednie_ulo[Figura_gdzie[1] - 49][przeksztalcanie(Figura_gdzie)]); //pracujemy na kopi tablicy zawierającej rzeczywiste ułożenie figur
			if (poprzednie_ulo[Figura_ktora[1] - 49][przeksztalcanie(Figura_ktora)] != 0) poprzednie_ulo[Figura_ktora[1] - 49][przeksztalcanie(Figura_ktora)] = 0;
			if (czyRuchDozwolony(szachownica, Figura_ktora, Figura_gdzie) == false || jaka_to_figura(Figura_ktora, szachownica) > 6 || szach(poprzednie_ulo, 0, krol) == true) bezpiecznik = false;
		}
	}
	else { //dla czarnych
		if (przeksztalcanie(Figura_ktora) > 7 || przeksztalcanie(Figura_gdzie) > 7 || Figura_ktora[1] == '9' || Figura_gdzie[1] == '9' || jaka_to_figura(Figura_gdzie, szachownica) > 6) bezpiecznik = false;
		else {
			swap(poprzednie_ulo[Figura_ktora[1] - 49][przeksztalcanie(Figura_ktora)], poprzednie_ulo[Figura_gdzie[1] - 49][przeksztalcanie(Figura_gdzie)]); //pracujemy na kopi tablicy zawierającej rzeczywiste ułożenie figur
			if (poprzednie_ulo[Figura_ktora[1] - 49][przeksztalcanie(Figura_ktora)] != 0) poprzednie_ulo[Figura_ktora[1] - 49][przeksztalcanie(Figura_ktora)] = 0;
			if (czyRuchDozwolony(szachownica, Figura_ktora, Figura_gdzie) == false || jaka_to_figura(Figura_ktora, szachownica) < 7 || szach(poprzednie_ulo, 1, krol) == true) bezpiecznik = false;
		}
	}
	if (bezpiecznik == true) return true;
	else return false;
}

bool pat(int strona, int szachownica[8][8], char krol[2]) { //sprawdza czy nie ma "PAT" (dana strona nie może wykonać żadnego ruchu, przy czym nie ma "Szacha")
	char figura_sprawdzana[2];
	char gdzie[2];
	bool flaga = false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			figura_sprawdzana[0] = j + 97;
			figura_sprawdzana[1] = i + 49;
			if (strona == 0) { //dla białych
				if (jaka_to_figura(figura_sprawdzana, szachownica) < 7 && jaka_to_figura(figura_sprawdzana, szachownica) != 0) {
					for (int a = 0; a < 8; a++) {
						for (int b = 0; b < 8; b++) {
							gdzie[0] = b + 97;
							gdzie[1] = a + 49;
							if (warunki(0, szachownica, figura_sprawdzana, gdzie, krol) == true) flaga = true;
						}
					}
				}
			}
			else { //dla czarnych
				if (jaka_to_figura(figura_sprawdzana, szachownica) > 6) {
					for (int a = 0; a < 8; a++) {
						for (int b = 0; b < 8; b++) {
							gdzie[0] = b + 97;
							gdzie[1] = a + 49;
							if (warunki(1, szachownica, figura_sprawdzana, gdzie, krol) == true) flaga = true;
						}
					}
				}
			}
			if (flaga == true) break; //w przypadku znalezienia figury, która może wykonać jakiś ruch, wychodzi z pętli
		}
		if (flaga == true) break; //w przypadku znalezienia figury, która może wykonać jakiś ruch, wychodzi z pętli
	}
	if (flaga == true) return false;
	else return true;
}

void plansza(int szachownica[8][8], int strona, bool poziom_ez, char ktora[2], char krol[2]) { //wyświetla całą szachownice 
	char sprawdzane_miejsce[2];
	bool mozliwy_ruch;
	char x = 0;
	cout << "==================SZACHY================== \n";
	zbite_figury_wyswietlanie(strona); //wyświetla zbite figury
	if (strona == 0) {//dla białej strony
		cout << "   - 	  A    B    C    D    E    F    G    H \n";
		for (int i = 7; i > 0 - 1; i--) {
			cout << x << "	";
			for (int j = 0; j < 8; j++) {
				mozliwy_ruch = false;
				if (poziom_ez == true) { //w przypadku, gdy wybraliśmy poziom umiejętności "podstawowy", funkcja będzie sprawdzać możliwe ruchy wybranej figury
					sprawdzane_miejsce[0] = j + 97;
					sprawdzane_miejsce[1] = i + 49;
					if (warunki(0, szachownica, ktora, sprawdzane_miejsce, krol) == true) mozliwy_ruch = true;
				}
				if ((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0)) {
					if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 0);
					else {
						if (przeksztalcanie(poprzedni_ruch_przeciwnika) == j && poprzedni_ruch_przeciwnika[1] == i + 49) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 << 4 | 0);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 << 4 | 15);
					}
				}
				else {
					if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 0);
					else {
						if (przeksztalcanie(poprzedni_ruch_przeciwnika) == j && poprzedni_ruch_przeciwnika[1] == i + 49) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 << 4 | 0);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 << 4 | 0);
					}
				}
				cout << x << x << x << x << x;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
			}
			cout << "\n   " << i + 1 << "	";
			for (int j = 0; j < 8; j++) {
				mozliwy_ruch = false;
				if (poziom_ez == true) { //w przypadku, gdy wybraliśmy poziom umiejętności "podstawowy", funkcja będzie sprawdzać możliwe ruchy wybranej figury
					sprawdzane_miejsce[0] = j + 97;
					sprawdzane_miejsce[1] = i + 49;
					if (warunki(0, szachownica, ktora, sprawdzane_miejsce, krol) == true) mozliwy_ruch = true;
				}
				if ((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0)) {
					if (szachownica[i][j] < 7) {
						if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 0);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 << 4 | 15);
					}
					else {
						if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 0);
						else {
							if (przeksztalcanie(poprzedni_ruch_przeciwnika) == j && poprzedni_ruch_przeciwnika[1] == i + 49) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 << 4 | 0);
							else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 << 4 | 0);
						}
					}
				}
				else {
					if (szachownica[i][j] < 7) {
						if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 0);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 << 4 | 15);
					}
					else {
						if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 0);
						else {
							if (przeksztalcanie(poprzedni_ruch_przeciwnika) == j && poprzedni_ruch_przeciwnika[1] == i + 49) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 << 4 | 0);
							else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 << 4 | 0);
						}
					}
				}
				cout << x << x << figura(szachownica, i, j) << x << x;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);

			}
			cout << "\n" << x << "	";
			for (int j = 0; j < 8; j++) {
				mozliwy_ruch = false;
				if (poziom_ez == true) { //w przypadku, gdy wybraliśmy poziom umiejętności "podstawowy", funkcja będzie sprawdzać możliwe ruchy wybranej figury
					sprawdzane_miejsce[0] = j + 97;
					sprawdzane_miejsce[1] = i + 49;
					if (warunki(0, szachownica, ktora, sprawdzane_miejsce, krol) == true) mozliwy_ruch = true;
				}
				if ((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0)) {
					if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 0);
					else {
						if (przeksztalcanie(poprzedni_ruch_przeciwnika) == j && poprzedni_ruch_przeciwnika[1] == i + 49) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 << 4 | 0);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 << 4 | 15);
					}
				}
				else {
					if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 0);
					else {
						if (przeksztalcanie(poprzedni_ruch_przeciwnika) == j && poprzedni_ruch_przeciwnika[1] == i + 49) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 << 4 | 0);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 << 4 | 0);
					}
				}
				cout << x << x << x << x << x;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);

			}
			cout << "\n";
		}
		zbite_figury_wyswietlanie(1); //wyświetla zbite figury
	}
	else {//dla czarnej strony
		cout << "   - 	  H    G    F    E    D    C    B    A \n";
		for (int i = 0; i < 8; i++) {
			cout << x << "	";
			for (int j = 7; j > 0 - 1; j--) {
				mozliwy_ruch = false;
				if (poziom_ez == true) { //w przypadku, gdy wybraliśmy poziom umiejętności "podstawowy", funkcja będzie sprawdzać możliwe ruchy wybranej figury
					sprawdzane_miejsce[0] = j + 97;
					sprawdzane_miejsce[1] = i + 49;
					if (warunki(1, szachownica, ktora, sprawdzane_miejsce, krol) == true) mozliwy_ruch = true;
				}
				if ((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0)) {
					if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 15);
					else {
						if (przeksztalcanie(poprzedni_ruch_przeciwnika) == j && poprzedni_ruch_przeciwnika[1] == i + 49) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 << 4 | 15);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 << 4 | 15);
					}
				}
				else {
					if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 15);
					else {
						if (przeksztalcanie(poprzedni_ruch_przeciwnika) == j && poprzedni_ruch_przeciwnika[1] == i + 49) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 << 4 | 15);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 << 4 | 0);
					}
				}
				cout << x << x << x << x << x;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
			}
			cout << "\n   " << i + 1 << "	";
			for (int j = 7; j > 0 - 1; j--) {
				mozliwy_ruch = false;
				if (poziom_ez == true) { //w przypadku, gdy wybraliśmy poziom umiejętności "podstawowy", funkcja będzie sprawdzać możliwe ruchy wybranej figury
					sprawdzane_miejsce[0] = j + 97;
					sprawdzane_miejsce[1] = i + 49;
					if (warunki(1, szachownica, ktora, sprawdzane_miejsce, krol) == true) mozliwy_ruch = true;
				}
				if ((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0)) {
					if (szachownica[i][j] < 7) {
						if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 15);
						else {
							if (przeksztalcanie(poprzedni_ruch_przeciwnika) == j && poprzedni_ruch_przeciwnika[1] == i + 49) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 << 4 | 15);
							else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 << 4 | 15);
						}
					}
					else {
						if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 15);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 << 4 | 0);
					}
				}
				else {
					if (szachownica[i][j] < 7) {
						if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 15);
						else {
							if (przeksztalcanie(poprzedni_ruch_przeciwnika) == j && poprzedni_ruch_przeciwnika[1] == i + 49) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 << 4 | 15);
							else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 << 4 | 15);
						}
					}
					else {
						if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 15);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 << 4 | 0);
					}
				}
				cout << x << x << figura(szachownica, i, j) << x << x;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);

			}
			cout << "\n" << x << "	";
			for (int j = 7; j > 0 - 1; j--) {
				mozliwy_ruch = false;
				if (poziom_ez == true) { //w przypadku, gdy wybraliśmy poziom umiejętności "podstawowy", funkcja będzie sprawdzać możliwe ruchy wybranej figury
					sprawdzane_miejsce[0] = j + 97;
					sprawdzane_miejsce[1] = i + 49;
					if (warunki(1, szachownica, ktora, sprawdzane_miejsce, krol) == true) mozliwy_ruch = true;
				}
				if ((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0)) {
					if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 15);
					else {
						if (przeksztalcanie(poprzedni_ruch_przeciwnika) == j && poprzedni_ruch_przeciwnika[1] == i + 49) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 << 4 | 15);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 << 4 | 15);
					}
				}
				else {
					if (mozliwy_ruch == true) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 15);
					else {
						if (przeksztalcanie(poprzedni_ruch_przeciwnika) == j && poprzedni_ruch_przeciwnika[1] == i + 49) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 << 4 | 15);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 << 4 | 0);
					}
				}
				cout << x << x << x << x << x;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);

			}
			cout << "\n";
		}
		zbite_figury_wyswietlanie(0); //wyświetla zbite figury
	}
}

void zerowanie_ruszada(char ktora[2], int szachownica[8][8]) { //jeśli został wykonany jakiś ruch królem lub wieżą dla danej strony, zeruje w danym miejscu tablice globalną "ruszad"
	switch (jaka_to_figura(ktora, szachownica)) {
	case 2:
		if (przeksztalcanie(ktora) == 0) ruszad[0] = 0;
		else ruszad[2] = 0;
		break;
	case 5:
		ruszad[1] = 0;
		break;
	case 8:
		if (przeksztalcanie(ktora) == 0) ruszad[3] = 0;
		else ruszad[5] = 0;
		break;
	case 11:
		ruszad[4] = 0;
		break;
	default:
		break;
	}
}

void napis() {//wyświetla napis "Szachy"
	cout << "	..######..########....###.....######..##.....##.##....##\n	.##....##......##....##.##...##....##.##.....##..##..##.\n	.##...........##....##...##..##.......##.....##...####..\n	..######.....##....##.....##.##.......#########....##...\n	.......##...##.....#########.##.......##.....##....##...\n	.##....##..##......##.....##.##....##.##.....##....##...\n	..######..########.##.....##..######..##.....##....##... \n\n";
}

int main(int argc, char *argv[])
{
	//pobiera rozmiar ekranu
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	//ustawia domyślny rozmiar okna cmd
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) { MoveWindow(hwnd, desktop.right / 4, desktop.bottom / 4, 680, 680, TRUE); } //początkowy punkt okna cmd znajduje się w 1/4 długości i szerokości całego ekranu

	setlocale(LC_ALL, "polish"); //umożliwa pokazywanie polskich znaków w cmd
	int restart; //po zakończeniu parti szachów, przechowuje wybór gracza w sprawie ponownej gry
	do {
		char poziomgracza1, poziomgracza2; //zmienne przechowujące poziom umiejętności danego gracza
		char Ruchy_z_pliku1[1000]; //przechowuje ruchy białej strony
		char Ruchy_z_pliku2[1000]; //przechowuje ruchy czarnej strony
		int numer_tury_bialych = 0;
		int numer_tury_czarnych = 0;
		int numer_zbitej_figury = 0;
		napis(); //wyświetla napis "Szachy"
		do {
			cout << "Poziom umiejetności pierwszego gracza:\n'p'-początkujący\n'n'-normalny\n\n'h'-ruchy znajdują się w gotowym pliku\n\n";
			cin >> poziomgracza1;
			if (poziomgracza1 == 'h') { //ruchy znajdują się w pliku
				string nazwa_pliku;
				cout << "Podaj źródło/nazwę pliku zawierającego ruchy: ";
				cin >> nazwa_pliku;
				ifstream plik(nazwa_pliku);
				if (plik.good() == true)
				{
					cout << "\nPlik z ruchami został znaleziony!\n";
					int i = 0;
					char znak;
					while (plik >> znak) { //wpisywanie danych znajdujących się w pliku do tablicy
						Ruchy_z_pliku1[i] = znak;
						i++;
					}
					plik.close();
				}
				else {
					cout << "\nPodane źródło nie istnieje!\n\n";
					poziomgracza1 = ' ';
				}
			}
		} while (poziomgracza1 != 'p'&&poziomgracza1 != 'n'&&poziomgracza1 != 'h');
		do {
			cout << "\nPoziom umiejetności drugiego gracza:\n'p'-początkujący\n'n'-normalny\n\n'h'-ruchy znajdują się w gotowym pliku\n\n";
			cin >> poziomgracza2;
			if (poziomgracza2 == 'h') { //ruchy znajdują się w pliku
				string decyzja;
				if (poziomgracza1 == 'h') { //w przypadku gdy dla białej strony wybraliśmy ruchy z pliku, pyta czy ruchy dla czarnej strony również się tam znajdują 
					cout << "Czy ruchy czarnej strony, również znajdują się w tym samym pliku co białej?\n't'-TAK\n'n'-NIE\nDecyzja: ";
					cin >> decyzja;
				}
				if (decyzja == "t") { //ruchy czarnej strony znajdują się w tym samym miejscu co białej
					int ruchy_bialej_strony = 0; //numer miejsca w tablicy, od którego zaczynają się ruchy białej strony
					int numer_miejsca = 0; //numer miejsca w tablicy przechowującej ruchy białej strony
					int numer_miejsca1 = 0; //numer miejsca w tablicy przechowującej ruchy czarnej strony
					char kopia[1000]; //kopia tablicy, w której przechowywane są wszystkie ruchy
					for (int k = 0; k < 1000; k++) {
						kopia[k] = Ruchy_z_pliku1[k];
						Ruchy_z_pliku1[k] = '\0'; //zeruje tablice, w której będa zawarte ruchy białej strony
					}
					for (int j = 0; j < 1000; j++) {
						if (kopia[j] == '\0') break; //wychodzi z pętli w przypadku gdy dochodzi do końca tablicy, przechowującej ruchy obydwu stron
						else {
							if (j == ruchy_bialej_strony) { //ruchy białej strony
								for (int k = 0; k < 4; k++) {
									Ruchy_z_pliku1[numer_miejsca + k] = kopia[j + k];
								}
								ruchy_bialej_strony += 8; //numer miejsca w tablicy od którego zaczynają się kolejne ruchy białej strony
								numer_miejsca += 4;
								j += 3;
							}
							else { //ruchy czarnej strony
								for (int k = 0; k < 4; k++) {
									Ruchy_z_pliku2[numer_miejsca1 + k] = kopia[j + k];
								}
								numer_miejsca1 += 4;
								j += 3;
							}

						}
					}
				}
				else { //ruchy czarnej strony znajdują się w innym pliku
					string nazwa_pliku2;
					cout << "Podaj źródło/nazwę pliku zawierającego ruchy: ";
					cin >> nazwa_pliku2;
					ifstream plik2(nazwa_pliku2);
					if (plik2.good() == true)
					{
						cout << "\nPlik z ruchami został znaleziony!\n";
						int i = 0;
						char znak;
						while (plik2 >> znak) { //wpisywanie danych znajdujących się w pliku do tablicy
							Ruchy_z_pliku2[i] = znak;
							i++;
						}
						plik2.close();
					}
					else {
						cout << "\nPodane źródło nie istnieje\n\n";
						poziomgracza2 = ' ';
					}
				}
			}
		} while (poziomgracza2 != 'p' && poziomgracza2 != 'n'&&poziomgracza2 != 'h');
		system("CLS");
		int szachownica[8][8] = { { 2, 3, 4, 6, 5, 4, 3, 2 },{ 1, 1, 1, 1, 1, 1, 1, 1 },{ 0, 0, 0, 0, 0, 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },{ 7, 7, 7, 7, 7, 7, 7, 7 },{ 8, 9, 10, 12, 11, 10, 9, 8 } };
		int poprzednie_ulozenie[8][8] = { { 2, 3, 4, 6, 5, 4, 3, 2 },{ 1, 1, 1, 1, 1, 1, 1, 1 },{ 0, 0, 0, 0, 0, 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },{ 7, 7, 7, 7, 7, 7, 7, 7 },{ 8, 9, 10, 12, 11, 10, 9, 8 } };
		char Figura_ktora[2];
		char Figura_gdzie[2];
		bool bezpiecznik, mat;
		int zamiana; //przechowuje numer figury na którą zamienimy pionek
		char krolb[2]; //aktualna pozycja białego króla
		char krolc[2]; //aktualna pozycja czarnego króla
		numer_tury_bialych = 0;
		numer_tury_czarnych = 0;
		bool czy_zbita_figura;
		do {
			mat = false;
			if (szachMat(szachownica, poprzednie_ulozenie, 0, krolb) == false && pat(0, szachownica, krolb) == false) { //sprawdza czy nie ma "Szach Mat" lub "Pat"
				plansza(szachownica, 0, false, Figura_ktora, krolb); //wyświetla szachownicę z perspektywy białej strony
				do {
					bezpiecznik = true;
					czy_zbita_figura = false;
					ulozenie_przed_ruchem(szachownica, poprzednie_ulozenie);
					if (poziomgracza1 == 'h') { //w przypadku, gdy program ma pobierać ruchy z pliku, przypisuje zmiennym wartości tablicy, do której wcześniej zostały wpisane ruchy z pliku
						Sleep(2000); //odczekanie 2 sec
						Figura_ktora[0] = Ruchy_z_pliku1[numer_tury_bialych];
						Figura_ktora[1] = Ruchy_z_pliku1[numer_tury_bialych + 1];
						Figura_gdzie[0] = Ruchy_z_pliku1[numer_tury_bialych + 2];
						Figura_gdzie[1] = Ruchy_z_pliku1[numer_tury_bialych + 3];
						wprowadzone_dane(Figura_ktora); //poprawia wprowadzone dane w przypadku odwrotnej kolejności lub użycia wielkich liter
						wprowadzone_dane(Figura_gdzie); //poprawia wprowadzone dane w przypadku odwrotnej kolejności lub użycia wielkich liter
					}
					else {
						//pytamy gracza o dane ruchu jaki chce wykonać
						cout << "\n [Ruch białych] Którą figurą chcesz się poruszyć: ";
						cin >> Figura_ktora[0];
						cin >> Figura_ktora[1];
						wprowadzone_dane(Figura_ktora); //poprawia wprowadzone dane w przypadku odwrotnej kolejności lub użycia wielkich liter
						if (poziomgracza1 == 'p') { //w przypadku wyboru podstawowego poziomu umiejętności pokazuje możliwe ruchy podanej figury
							system("CLS");
							plansza(szachownica, 0, true, Figura_ktora, krolb);
						}
						cout << "\n [Ruch białych] Gdzie chcesz się poruszyć: ";
						cin >> Figura_gdzie[0];
						cin >> Figura_gdzie[1];
						wprowadzone_dane(Figura_gdzie); //poprawia wprowadzone dane w przypadku odwrotnej kolejności lub użycia wielkich liter
					}
					//sprawdzamy poprawność wpisanych danych przez gracza oraz ich zgodność według zasad
					if (przeksztalcanie(Figura_ktora) > 7 || przeksztalcanie(Figura_gdzie) > 7 || Figura_ktora[1] == '9' || Figura_gdzie[1] == '9' || (jaka_to_figura(Figura_gdzie, szachownica) < 7 && jaka_to_figura(Figura_gdzie, szachownica) != 0)) {
						cout << "\nBłąd!\n";
						if (przeksztalcanie(Figura_ktora) > 7 || przeksztalcanie(Figura_gdzie) > 7 || Figura_ktora[1] == '9' || Figura_gdzie[1] == '9') cout << "Wybrane pola nie znajdują się na szachownicy!\n";
						else cout << "Bicie swojej figury jest niedozwolone!\n";
						bezpiecznik = false;
					}
					else {
						swap(poprzednie_ulozenie[Figura_ktora[1] - 49][przeksztalcanie(Figura_ktora)], poprzednie_ulozenie[Figura_gdzie[1] - 49][przeksztalcanie(Figura_gdzie)]); //pracujemy na kopi tablicy zawierającej rzeczywiste ułożenie figur
						if (poprzednie_ulozenie[Figura_ktora[1] - 49][przeksztalcanie(Figura_ktora)] != 0) {
							czy_zbita_figura = true; //informuje, że figura przeciwnika została zbita
							poprzednie_ulozenie[Figura_ktora[1] - 49][przeksztalcanie(Figura_ktora)] = 0;
						}
						if (czyRuchDozwolony(szachownica, Figura_ktora, Figura_gdzie) == false || jaka_to_figura(Figura_ktora, szachownica) > 6 || jaka_to_figura(Figura_ktora, szachownica) == 0 || szach(poprzednie_ulozenie, 0, krolb) == true) {
							//w przypadku błędnego ruchu pokazuje, czy ruch był dozwolony według zasad, jaką figurą chciał gracz się poruszyć oraz czy nie ma "Szachu"
							cout << "\nBłąd!\n";
							if (jaka_to_figura(Figura_ktora, szachownica) > 6 || jaka_to_figura(Figura_ktora, szachownica) == 0) cout << "To nie jest twoja figura!\n";
							else {
								if (czyRuchDozwolony(szachownica, Figura_ktora, Figura_gdzie) == false) cout << "Ruch niezgodny z zasadami!\n";
								if (szach(poprzednie_ulozenie, 0, krolb) == true) cout << "Twój król jest pod biciem!\n";
							}
							bezpiecznik = false;
						}
						else {
							if (jaka_to_figura(Figura_ktora, szachownica) == 1 && Figura_gdzie[1] == '8') {//wybór figury na która zamienimy pionek jak dojdzie do końca (do 8 wiersza)
								do {
									string pionek_zamiana;
									cout << "\nNa jaką figurę chcesz wymienić pionka? (jeśli chcesz zostawić pionka wpisz symbol pionka) Twój wybór: ";
									cin >> pionek_zamiana;
									zamiana = figura_na_numer(pionek_zamiana, 0);
								} while (zamiana > 6 || zamiana == 5 || zamiana < 1);
								poprzednie_ulozenie[Figura_gdzie[1] - 49][przeksztalcanie(Figura_gdzie)] = zamiana;
							}
							if (Figura_ktora[1] == 49 && przeksztalcanie(Figura_gdzie) == 2 && ruszada(ruszad, Figura_ktora, Figura_gdzie, 0, szachownica) == true) swap(poprzednie_ulozenie[0][0], poprzednie_ulozenie[0][3]); //w przypadku ruszady zmienia pozycję wieży z kolumny A
							else {
								if (Figura_ktora[1] == 49 && przeksztalcanie(Figura_gdzie) == 6 && ruszada(ruszad, Figura_ktora, Figura_gdzie, 0, szachownica) == true) swap(poprzednie_ulozenie[0][7], poprzednie_ulozenie[0][5]); //w przypadku ruszady zmienia pozycję wieży z kolumny H
							}
						}
					}
					if (poziomgracza1 == 'h'&&bezpiecznik == false) {//w przypadku, gdy ruch znajdujący się w pliku jest niepoprawny, program przestaje korzystać z ruchów zawartych w pliku i przełącza się na "początkujący poziom umiejętności"(gracz wprowadza ręcznie ruchy i dostaje podpowiedzi możliwych ruchów)
						cout << "\nRuch znajdujący się w pliku nie jest możliwy do wykonania! Aby gra mogła toczyć się dalej zmieniam tryb na 'początkujący'.\n\n";
						poziomgracza1 = 'p';
					}
					if (czy_zbita_figura == true && bezpiecznik == true) { //w przypadku zbitej figury, dodaje ją do tablicy "zbite_figury"
						zbite_figury[numer_zbitej_figury] = jaka_to_figura(Figura_gdzie, szachownica);
						numer_zbitej_figury++;
					}
				} while (bezpiecznik == false);
				zerowanie_ruszada(Figura_ktora, szachownica); //jeśli został wykonany jakis ruch królem lub wieżą, zeruje w danym miejscu tablice globalną "ruszad"
				ulozenie_przed_ruchem(poprzednie_ulozenie, szachownica); //przepisuje wartości kopi na której pracowaliśmy do oryginału 
				poprzedni_ruch_przeciwnika[0] = Figura_gdzie[0]; //przypisujemy tablicy globalnej wartości tablicy przechowującej pole gdzie poruszyła się figura
				poprzedni_ruch_przeciwnika[1] = Figura_gdzie[1]; //przypisujemy tablicy globalnej wartości tablicy przechowującej pole gdzie poruszyła się figura
				numer_tury_bialych += 4;
				system("CLS"); //czyści cmd
			}
			else { //w przypadku jak był "Szach Mat" lub "Pat"
				if (pat(0, szachownica, krolb) == true && szachMat(szachownica, poprzednie_ulozenie, 0, krolb) == false) cout << "\nRemis (PAT)";
				else cout << "\nCzarne wygrały";
				mat = true;
			}
			if (mat == false && szachMat(szachownica, poprzednie_ulozenie, 1, krolc) == false && pat(1, szachownica, krolc) == false) {//sprawdza czy nie ma "Szach Mat" lub "Pat"
				plansza(szachownica, 1, false, Figura_ktora, krolc); //wyświetla szachownicę z perspektywy czarnej strony

				do {
					bezpiecznik = true;
					czy_zbita_figura = false;
					ulozenie_przed_ruchem(szachownica, poprzednie_ulozenie);
					if (poziomgracza2 == 'h') { //w przypadku, gdy program ma pobierać ruchy z pliku, przypisuje zmiennym wartości tablicy, do której wcześniej zostały wpisane ruchy z pliku
						Sleep(2000); //odczekanie 2 sec
						Figura_ktora[0] = Ruchy_z_pliku2[numer_tury_czarnych];
						Figura_ktora[1] = Ruchy_z_pliku2[numer_tury_czarnych + 1];
						Figura_gdzie[0] = Ruchy_z_pliku2[numer_tury_czarnych + 2];
						Figura_gdzie[1] = Ruchy_z_pliku2[numer_tury_czarnych + 3];
						wprowadzone_dane(Figura_ktora); //poprawia wprowadzone dane w przypadku odwrotnej kolejności lub użycia wielkich liter
						wprowadzone_dane(Figura_gdzie); //poprawia wprowadzone dane w przypadku odwrotnej kolejności lub użycia wielkich liter
					}
					else {
						//pytamy gracza o dane ruchu jaki chce wykonać
						cout << "\n [Ruch czarnych] Którą figurą chcesz się poruszyć: ";
						cin >> Figura_ktora[0];
						cin >> Figura_ktora[1];
						wprowadzone_dane(Figura_ktora); //poprawia wprowadzone dane w przypadku odwrotnej kolejności lub użycia wielkich liter
						if (poziomgracza2 == 'p') { //w przypadku wyboru podstawowego poziomu umiejętności pokazuje możliwe ruchy podanej figury
							system("CLS");
							plansza(szachownica, 1, true, Figura_ktora, krolc);
						}
						cout << "\n [Ruch czarnych] Gdzie chcesz się poruszyć: ";
						cin >> Figura_gdzie[0];
						cin >> Figura_gdzie[1];
						wprowadzone_dane(Figura_gdzie); //poprawia wprowadzone dane w przypadku odwrotnej kolejności lub użycia wielkich liter
					}
					//sprawdzamy poprawność wpisanych danych przez gracza oraz ich zgodność według zasad
					if (przeksztalcanie(Figura_ktora) > 7 || przeksztalcanie(Figura_gdzie) > 7 || Figura_ktora[1] == '9' || Figura_gdzie[1] == '9' || jaka_to_figura(Figura_gdzie, szachownica) > 6) {
						cout << "\nBłąd!\n";
						if (przeksztalcanie(Figura_ktora) > 7 || przeksztalcanie(Figura_gdzie) > 7 || Figura_ktora[1] == '9' || Figura_gdzie[1] == '9') cout << "Wybrane pola nie znajdują się na szachownicy!\n";
						else cout << "Bicie swojej figury jest niedozwolone!\n";
						bezpiecznik = false;
					}
					else {
						swap(poprzednie_ulozenie[Figura_ktora[1] - 49][przeksztalcanie(Figura_ktora)], poprzednie_ulozenie[Figura_gdzie[1] - 49][przeksztalcanie(Figura_gdzie)]); //pracujemy na kopi tablicy zawierającej rzeczywiste ułożenie figur
						if (poprzednie_ulozenie[Figura_ktora[1] - 49][przeksztalcanie(Figura_ktora)] != 0) {
							czy_zbita_figura = true; //informuje, że figura przeciwnika została zbita
							poprzednie_ulozenie[Figura_ktora[1] - 49][przeksztalcanie(Figura_ktora)] = 0;
						}
						if (czyRuchDozwolony(szachownica, Figura_ktora, Figura_gdzie) == false || jaka_to_figura(Figura_ktora, szachownica) < 7 || szach(poprzednie_ulozenie, 1, krolc) == true) {
							//w przypadku błędnego ruchu pokazuje, czy ruch był dozwolony według zasad, jaką figurą chciał gracz się poruszyć oraz czy nie ma "Szachu"
							cout << "\nBłąd!\n";
							if (jaka_to_figura(Figura_ktora, szachownica) < 7) cout << "To nie jest twoja figura!\n";
							else {
								if (czyRuchDozwolony(szachownica, Figura_ktora, Figura_gdzie) == false) cout << "Ruch niezgodny z zasadami!\n";
								if (szach(poprzednie_ulozenie, 1, krolc) == true) cout << "Twój król jest pod biciem!\n";
							}
							bezpiecznik = false;
						}
						else {
							if (jaka_to_figura(Figura_ktora, szachownica) == 7 && Figura_gdzie[1] == '1') {//wybór figury na która zamienimy pionek jak dojdzie do końca (do 1 wiersza)
								do {
									string pionek_zamiana;
									cout << "\nNa jaką figurę chcesz wymienić pionka? (jeśli chcesz zostawić pionka wpisz symbol pionka) Twój wybór: ";
									cin >> pionek_zamiana;
									zamiana = figura_na_numer(pionek_zamiana, 1);
								} while (zamiana < 7 || zamiana == 11 || zamiana < 1);
								poprzednie_ulozenie[Figura_gdzie[1] - 49][przeksztalcanie(Figura_gdzie)] = zamiana;
							}
							if (Figura_ktora[1] == 7 + 49 && przeksztalcanie(Figura_gdzie) == 2 && ruszada(ruszad, Figura_ktora, Figura_gdzie, 1, szachownica) == true) swap(poprzednie_ulozenie[7][0], poprzednie_ulozenie[7][3]); //w przypadku ruszady zmienia pozycję wieży z kolumny A
							else {
								if (Figura_ktora[1] == 7 + 49 && przeksztalcanie(Figura_gdzie) == 6 && ruszada(ruszad, Figura_ktora, Figura_gdzie, 1, szachownica) == true) swap(poprzednie_ulozenie[7][7], poprzednie_ulozenie[7][5]); //w przypadku ruszady zmienia pozycję wieży z kolumny H
							}
						}
					}
					if (poziomgracza2 == 'h'&&bezpiecznik == false) {//w przypadku, gdy ruch znajdujący się w pliku jest niepoprawny, program przestaje korzystać z ruchów zawartych w pliku i przełącza się na "początkujący poziom umiejętności"(gracz wprowadza ręcznie ruchy i dostaje podpowiedzi możliwych ruchów)
						cout << "\nRuch znajdujący się w pliku nie jest możliwy do wykonania! Aby gra mogła toczyć się dalej zmieniam tryb na 'początkujący'.\n\n";
						poziomgracza2 = 'p';
					}
					if (czy_zbita_figura == true && bezpiecznik == true) { //w przypadku zbitej figury, dodaje ją do tablicy "zbite_figury"
						zbite_figury[numer_zbitej_figury] = jaka_to_figura(Figura_gdzie, szachownica);
						numer_zbitej_figury++;
					}
				} while (bezpiecznik == false);
				zerowanie_ruszada(Figura_ktora, szachownica); //jeśli został wykonany jakis ruch królem lub wieżą, zeruje w danym miejscu tablice globalną "ruszad"
				ulozenie_przed_ruchem(poprzednie_ulozenie, szachownica); //przepisuje wartości kopi na której pracowaliśmy do oryginału 
				poprzedni_ruch_przeciwnika[0] = Figura_gdzie[0]; //przypisujemy tablicy globalnej wartości tablicy przechowującej pole gdzie poruszyła się figura
				poprzedni_ruch_przeciwnika[1] = Figura_gdzie[1]; //przypisujemy tablicy globalnej wartości tablicy przechowującej pole gdzie poruszyła się figura
				numer_tury_czarnych += 4;
				system("CLS"); //czyści cmd
			}
			else { //w przypadku jak był "Szach Mat" lub "Pat"
				if (pat(1, szachownica, krolb) == true && mat == false && szachMat(szachownica, poprzednie_ulozenie, 1, krolc) == false) cout << "\nRemis (PAT)";
				else {
					if (mat != true)
						cout << "\nBiałe wygrały";
				}
				mat = true;
			}
		} while (mat == false);
		nowe_logi_ruszada(); //przywraca pierwotne wartości globalnej tablicy ruszad
		cout << "\n \n CZY URUCHOMIĆ GRĘ PONOWNIE? \n 't'-Tak \n Inny klawisz- Nie\n";
		for (int i = 0; i < numer_zbitej_figury + 1; i++) { //zeruje globlaną tablicę przechowującą zbite figury
			zbite_figury[i] = 0;
		}
		restart = _getwch();
		poprzedni_ruch_przeciwnika[0] = 0; //czyścimy tablicę globalną, aby można było z niej korzystać w przypadku restartu
		poprzedni_ruch_przeciwnika[1] = 0; //czyścimy tablicę globalną, aby można było z niej korzystać w przypadku restartu
		if (restart == 't') system("CLS"); //czyści cmd;
	} while (restart == 't');
	system("PAUSE");
	return EXIT_SUCCESS;
}
