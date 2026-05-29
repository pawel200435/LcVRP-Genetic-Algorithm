# LcVRP Genetic Algorithm

Competition project for the "Techniques of Effective Programming" course. A C++ Genetic Algorithm solver for LcVRP, built by an Applied Computer Science student at WUST<br>
---

[![C++](https://img.shields.io/badge/C++-17%2F20-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-Build-success)](#)




## O projekcie (About The Project)
Projekt ten to obiektowa implementacja **Algorytmu Genetycznego (Genetic Algorithm)** w języku C++, stworzona w celu rozwiązywania problemu **LcVRP (Limited Capacitated Vehicle Routing Problem)**.

LcVRP to zaawansowany, NP-trudny problem optymalizacji kombinatorycznej polegający na wyznaczeniu optymalnych tras dla floty pojazdów przy jednoczesnym uwzględnieniu ograniczeń ładowności i logistyki. Zamiast szukania rozwiązania metodą "brute-force", projekt wykorzystuje metaheurystykę, aby w krótkim czasie znaleźć rozwiązania bliskie optymalnym.

Projekt został zaprojektowany z naciskiem na **nowoczesne standardy C++, wysoką wydajność pamięciową oraz elastyczność architektoniczną**.

## Kluczowe cechy (Features)

* **Wzorce Projektowe (Design Patterns):**
    * **Strategy Pattern:** Algorytmy krzyżowania (np. *One-Point Crossover*) oraz mutacji (np. *Random Mutation*, *Reversed Gen Mutation*) są wstrzykiwane przez interfejsy. Pozwala to na łatwe testowanie nowych operatorów genetycznych bez ingerencji w główną pętlę algorytmu.
    * **Observer / Listener Pattern:** Monitorowanie postępów algorytmu (czas, najlepszy wynik w populacji, rekord globalny) jest odseparowane od logiki biznesowej za pomocą interfejsu `IAlgorithmListener`. Zapobiega to "zaśmiecaniu" klas algorytmicznych funkcjami wypisującymi na konsolę
* **Robust Error Handling (Result Pattern):** Zamiast standardowych wyjątków (`exceptions`), projekt wykorzystuje obiektowy wzorzec `CResult<T, E>`. Zapewnia to przewidywalny i bezpieczny przepływ sterowania (`control flow`) np. przy błędach wczytywania plików instancji lub niepoprawnych parametrach startowych, w pełni zapobiegając awariom programu na etapie inicjalizacji.
* **Zarządzanie Pamięcią i Wydajność (Move Semantics):** Intensywne wykorzystanie semantyki przenoszenia (`std::move`) do bezkopijnego przekazywania dużych genotypów między pokoleniami. Drastycznie skraca to czas wykonywania algorytmu i minimalizuje narzut alokacji pamięci.
* **Zarządzanie czasem wykonania:** Wbudowany mechanizm kontroli czasu (oparty na `std::chrono`) gwarantujący bezpieczne zakończenie obliczeń i zwrócenie najlepszego wyniku w ściśle określonym czasie (np. max 180 sekund).

## Technologie i Narzędzia (Built With)

* **Język:** C++ (Standard 17/20)
* **System budowania:** CMake
* **Środowisko:** CLion
* **Biblioteki Standardowe:** `<chrono>`, `<random>`, `<vector>`, `<algorithm>`, `<filesystem>`

## Struktura Projektu (Project Structure)

* `/Alhorithms` - Implementacje operatorów genetycznych. Zawiera podfoldery `/Crossing` (krzyżowanie) oraz `/Mutation` (mutacja) oparte na wzorcu Strategii.
* `/data` - Zbiór instancji testowych problemu LcVRP (np. Set-A, Set-P) wczytywanych przez algorytm.
* `/Evaluator` - Moduł odpowiedzialny za ewaluację (obliczanie *Fitness*) oraz logikę oceny poszczególnych tras.
* `/GeneticAlgorithm` - Główny silnik napędowy metaheurystyki, parametry konfiguracyjne (`ConstantsGeneticAlgorithm.h`) oraz mechanizmy kontroli czasu.
* `/Helpers Classes` - Narzędzia pomocnicze: moduły parsujące pliki (`CFileDataLoader`), struktury przechowujące wczytane dane oraz implementacja wzorca `CResult`.
* `/Individual` - Reprezentacja pojedynczego rozwiązania (genotyp) oraz struktura zamrażająca najlepszy wynik (`SBestIndividualSnapshot`).
* `/Main` - Punkt wejścia aplikacji (`main.cpp`), interfejs nasłuchujący (`IAlgorithmListener`) oraz klasy logujące postępy na konsolę.



## Jak uruchomić? (Getting Started)

### Wymagania wstępne
* Kompilator wspierający C++17 (np. GCC, MinGW, Clang).
* Zainstalowany system **CMake**.

### Uruchomienie w środowisku CLion (Zalecane)
1. Otwórz sklonowany folder z projektem w środowisku CLion.
2. Środowisko automatycznie wykryje plik `CMakeLists.txt` i zaindeksuje projekt (jeśli nie, kliknij prawym przyciskiem myszy na `CMakeLists.txt` i wybierz *Load CMake Project*).
3. Na górnym pasku zadań wybierz konfigurację `PROJEKT_LcVRP` i naciśnij zieloną strzałkę **Run** (lub skrót `Shift + F10`).
4. W pliku main.cpp jest możliwość dostosowania parametrów algorytmu i wyboru pliku z danymi.

## Konfiguracja Algorytmu

Algorytm pozwala na swobodną konfigurację parametrów eksperymentu z poziomu funkcji main:

- iIterations: Maksymalna liczba pokoleń (np. 1 000 000).

- dMaxSeconds: Ścisły limit czasowy wykonania w sekundach.

- iPopulationSize: Rozmiar populacji (np. 100 osobników).

- dCrossProb / dMutProb: Prawdopodobieństwo zajścia krzyżowania i mutacji.

- iTournamentSize: Wielkość turnieju (siła presji selekcyjnej).

## O autorze (Context & Author)

Projekt został zrealizowany jako projekt konkursowy w ramach przedmiotu Techniki Efektywnego Programowania (TEP).
<br>Uczelnia: Politechnika Wrocławska (Wrocław University of Science and Technology)
<br>Kierunek: Informatyka Stosowana (Applied Computer Science)<br>
Autor: Paweł Goliński