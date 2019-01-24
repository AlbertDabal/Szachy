# Szachy
Projekt zaliczeniowy "Programowania w C++"  pierwszego semestru na pierwszym roku studiów na kierunku Informatyka.

## Opis funkcji dla poszczególnych trybów gry:
### „normalny”
* zawiera podstawowe ruchy figur
* wyświetla ręcznie zrobioną szachownice oraz poprawnie wyświetla kolory figur w zależności od ich położenia
* podświetla na różowo miejsce gdzie przeciwnik zrobił ostatni swój ruch 
* pokazuje zbite wcześniej figury przez każdą ze stron
* program pobiera rozmiar ekranu i ustawia początkowy punkt okna (punkt znajdujący się w lewym górnym rogu) w 1 / 4 szerokości i 1 / 4 wysokości ekranu
* sprawdza czy aktualnie jest szach (jakaś wroga figura jest wstanie dostać się na pole gdzie jest król) oraz czy po podanym przez nas ruchu będzie szach (w przypadku kiedy będzie, zwraca błąd)
* Szach Mat (Szach ostateczny) Sprawdza po każdym ruchu czy szach który się pojawił jest ostateczny (król nie jest wstanie się zasłonić/uciec)
* sprawdza po każdym ruchu czy nie ma patu (dana strona nie ma możliwości wykonania żadnego ruchu nie ważne jaką figurą, ale szachu nie ma)
* ruszada (sprawdza czy nie zrobiliśmy wcześniej jakiegoś ruchu królem lub wybraną wieżą, oraz czy żadne z pól przez które ruszada będzie wykonywana nie jest pod biciem jakieś wrogiej figury)
* wymiana pionka na inną figurę w przypadku dojścia do końca planszy
* w przypadku ruchu niezgodnego z zasadami szachów, zwraca konkretnie jaki jest błąd
* poprawia wprowadzone przez nas dane w przypadku lekkiego błędu (w odwrotnej kolejności lub użycie dużych liter zamiast małych)
* liczne zabezpieczenia w przypadku błędnych ruchów/danych
* możliwość zagrania kolejnej tury z nowymi ustawieniami bez potrzeby restartu programu 

### „początkujący”
* wszystko co zawiera tryb normalny
* po wybraniu figury podświetla na czerwono wszystkie miejsca gdzie może dana figura się poruszyć (sprawdzając czy zgodnie z zasadami, czy nie ma szachu oraz czy po tym ruchu nie będzie szachu)

### „ruchy znajdują się w pliku”
* wszystko co zawiera tryb normalny
* możliwość pobierania ruchów z plików osobno dla białej strony osobno dla czarnej (z 2 różnych plików)
* w przypadku gdy ruchy obydwu stron znajdują się w 1 wspólnym pliku wystarczy wpisać źródło w przypadku pierwszego gracza, a w przypadku drugiego pojawi się wtedy pytanie czy jego ruchy również znajdują się w tym samym pliku
* w przypadku gdy jakiś ruch znajdujący się w pliku będzie niezgodny z zasadami, program zmieni tryb danego gracza na „początkujący” (druga strona nadal będzie mogła korzystać z ruchów zawartych w pliku o ile są zgodne z zasadami) dzięki czemu dalsza gra będzie możliwa z tym samym ułożeniem jaki do tej pory był
* po każdym ruchu pobranym z pliku i wykonanym program odczekuje 2 sec

W folderze "PRZYKLADOWE_RUCHY" umieściłem pliki z ruchami do najszybszego PATA oraz z ruchami na najszybszego SZACH MATA, które można wykorzystać do trybu „ruchy znajdują się w pliku”.
