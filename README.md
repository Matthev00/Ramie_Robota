# 209.3 Ramie robota

## Skład zespołu
Mateusz Ostaszewski
Krzysztof Gólcz

## Cel projektu

Celem projektu jest zrealizowanie symulacji ramienia robota, które za zadanie ma osiągnąć punkt w trójwymiarowej przestrzeni (współrzędne xyz) lub oznajmienie, że cel jest poza zasięgiem.
Zrealizuje to poprzez ruchy trzema przegubami oraz ocinków łączących.

## Podział problemu na klasy

1. Klasa ramienia robota

2. Klasa przegłubu

3. Klasa odcinka łączącego

4. Klasa ramienia (dziedzicząca po klasie odcinka)

5. Klasa przedramienia (dziedzicząca po klasie odcinka)

6. Klasa przegłubu barkowego (dziedzicząca po klasie przegłubu)

7. Klasa przegłubu łokciowego (dziedzicząca po klasie przegłubu)

8. Klasa chwytaka (w tym miejscu, jeżeli to możliwe, ma się znaleść punkt docelowy)

## Wstępne założenia algorytmy dostawania się do punktu

Na początku ruszamy przegłubem barkowym do momentu aż przegłub łokciowy będzie najbliżej punktu docelowego.
Następnie ruszamy przegłubem łokciowym do momentu aż chwytak będzie najbliżej celu.
Następnie (jeżeli to potrzebne) modyfikujemy długość przedramienia.
Po osiągnięciu celu przez chwytak zaczynamy powrót do pozycji starowej
Aby powrócić odginamy staw łokciowy
"Odkręcamy" staw barkowy
Odginamy staw barkowy
Wydłużamy odpowiednio przedramię aż do momentu gdy będzie w miejscu początkowym

## Sterowanie kamerą w oknie aplikacji
Sterowanie kamerą realizowane jest za pomocą modułu glut
Będąc w aplikacji okienkowej dostępne są następujące kontrole:
-ARROW_UP - zmniejszenie koordynatów z kamery
-ARROW_DOWN - zwiększenie koordynatów z kamery
-ARROW_LEFT - zmniejszenie koordynatów x kamery
-ARROW_RIGHT - zwiększenie koordynatów x kamery
-F1 - zwiększenie koordynatów y kamery
-F2 - zmniejszenie koordynatów y kamery
-F6 - cofnięcie się do poprzedniego stanu ramienia
-F7 - przejście do kolejnego stanu ramienia

## Instalacja
Aby program funkcjonował poprawnie niezbędne jest skopiowanie pliku freeglut.dll i umieszczenie go w $(SolutionDir)Debug,
gdzie $(SolutionDir) oznacza miejsce pliku projektowego.

Program powinien być kompilowanhy w wersji x86.
Plikiem wyświetlającym o inicjującym ramię jest plik RamieRobota.cpp (tam znajduje się funkcja main).