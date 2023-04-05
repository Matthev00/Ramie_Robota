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