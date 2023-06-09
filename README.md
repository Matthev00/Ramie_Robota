# 209.3 Ramie robota

## Skład zespołu
Mateusz Ostaszewski
Krzysztof Gólcz

## Cel projektu

Celem projektu jest zrealizowanie symulacji ramienia robota, które za zadanie ma osiągnąć punkt w trójwymiarowej przestrzeni (współrzędne xyz) lub oznajmienie, że cel jest poza zasięgiem.
Zrealizuje to poprzez ruchy dwoma przegubami oraz ocinków łączących.

## Podział problemu na klasy

# Joints:
														connncetion(zwykle polaczenie)(do stworzenia)
																	|
										BendingJointDirection(zginajacy staw tylko w podanej plaszczyznie)(do stworzenia)
																	|
											Joint(zginanie w dowolnej plaszczyznie prostopadlej do xy)
											/														\
ElbowJoint(staw okciowy posaiada poprzedni JointConnector)							ShoulderJoint(dodany ruch obrotowy)
																									|
																			RestrictedShoulderJoint(ograniczny kat ruchu obrotowego)
# JointConnectors
                                                            BaseJointConnector
                                                                    |
                                                                JointConnector
                                                                    |
                                                        ExtandebleJointConnector

# Robot
                                                    RobotPart(do stworzenia w przyszłości)
                                                                    |
                                                            Arm(nasza klasa ramienia)
                                                                    |
                                        klasy rozbudowywyjące klase arm i jej metody(do stworzenia w przyszłości)

# Gripper
Klasa chwytaka (w tym miejscu, jeżeli to możliwe, ma się znaleść punkt docelowy) - Gripper

# klasy pomocnicze
-struct Coordinates(koordynaty)

-class Wektor(wektor kierunkowy)


## Sposób działania algorytmu dostawania się do punktu
Przypadek 1: Punkt znajduje się w odleglości bliższej niż odległości łokcia od barku.
Najpierw (jeżeli to potrzebne) modyfikujemy długość przedramienia.
Ruszamy przegłubem barkowym do momentu aż chwytak będzie w miejscu docelowym.

Przypadek 2:
Na początku ruszamy przegłubem barkowym do momentu aż przegłub łokciowy będzie najbliżej punktu docelowego.
Następnie (jeżeli to potrzebne) modyfikujemy długość przedramienia.
Następnie ruszamy przegłubem łokciowym do momentu aż chwytak będzie najbliżej celu.

Dotyczy obu przypadków:
Po osiągnięciu celu przez chwytak łapiemy obiekt.
Następnie zaczynamy powrót do pozycji starowej.
Aby powrócić odginamy staw łokciowy.
"Odkręcamy" staw barkowy.
Odginamy docelowo łokieć.
Odginamy staw barkowy.
Wydłużamy odpowiednio przedramię aż do momentu gdy będzie w miejscu początkowym.

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
Aby program funkcjonował poprawnie niezbędne jest skopiowanie pliku freeglut.dll (znajdującego się w folderze NecessaryFiles) i umieszczenie go w $(SolutionDir)Debug,
gdzie $(SolutionDir) oznacza miejsce pliku projektowego.

Program powinien być kompilowanhy w wersji x86.
Plikiem wyświetlającym i inicjującym ramię jest plik RamieRobota.cpp (tam znajduje się funkcja main).

## Oznaczenia kolorów wizualizacji
Białe linie - oznaczają części łączące stawamy

Linia czerwona - oś X

Linia zielona - oś Y

Linia niebieska - oś Z

Punkty limonkowe - miejsca w których znajdują się poszczególne stawy

Punkt niebieski - Punkt docelowy

Punkt czerwony - Punkt docelowy złapany przez chwytak

## Pomysły na usprawnienie, dalszą rozbudowe
- stworzenie klasy przechowującej kolejne ustawienia coordynatów ramienia
- Dodanie klasy bazowej RobotPart po ktorej dziedziczyłaby klasa Arm
- W klasie RobotPart dodanie "mniej mądrych algorytmów osiagania celu"
- Stworzenie bardziej rozbudowanego ramienia który dziedziczyłby po Arm
- Stworzenie alternatywnych form wizualizacji (nawet w terminalu)

