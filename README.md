# Systemy-Operacyjne-2

Opis problemu:
Przy stole siedzi N filozofów, którzy wykonują na zmianę dwie czynności - jedzą lub myślą. Aby filozof mógł jeść musi posiadać dwa widelce, po jednym z lewej i prawej strony. Każdy widelec może być trzymany tylko przez jednego filozofa.
Filozofowie muszą dzielić się sztućcami w taki sposób, by żaden z nich nie pozostał za długo bez jedzenia oraz by nie wystąpiła sytuacja w której żaden z filozofów nie ma dostępu do jedzenia.

Instrukcje uruchomienia:
Należy pobrać pliki z GitHub, następnie przejść do katalogu w którym się znajdują i wprowadzić w terminalu „make”. Powstanie wówczas plik „program”. Przy uruchamianiu go trzeba podać po spacji liczbę filozofów, np. ./program 5

Wątki i ich zadania:
Wątek główny main() inicjalizuje filozofów i przypisuje im osobne wątki, obsługuje ncurses oraz kontroluje warunek stopu (naciśnięcie spacji) i obsługuje zakończenie programu.
Wątek filozofa (Philosopher::eat) symuluje zachowanie filozofa, czyli czeka na dostęp do jedzenia, je i zmniejsza liczbę dostępnych zasobów, powiadamia innych filozofów, że mogą próbować jeść. 

Sekcje krytyczne i ich rozwiązania:
Dostęp do jedzenia (zmienna food) jest ograniczony za pomocą mutexu, który umożliwia tylko jednemu filozofowi na raz modyfikację wartości zmiennej. Dodatkowym ograniczeniem jest condition_variable, które koordynuje oczekiwanie i jedzenie filozofów (gdy filozof kończy jeść, informuje pozostałych, że mogą próbować jeść przez notify_all()). W celu uniknięcia monopolu na jedzenie dla jednego filozofa, po zakończeniu jedzenia ma on opóźnienie 100ms, co pozwala pozostałym filozofom zdobyć dostęp do zasobów przed nim. Każdy filozof przed rozpoczęciem jedzenia sprawdza czy jego bezpośredni sąsiedzi nie jedzą.




