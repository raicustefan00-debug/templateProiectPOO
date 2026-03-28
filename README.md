Proiect POO - Gestiune Colonie pe Marte 

Acest folder conține proiectul meu pentru cursul de Programare Orientată pe Obiecte (POO). Este o aplicație C++ care simulează gestionarea unei baze de pe Marte, folosind un meniu interactiv în consolă.

Ce face aplicația?
Prin intermediul meniului, utilizatorul poate:
-sa adauge, șteargă sau să modifice module (de producție, de cercetare sau laboratoare hibride);
-sa gestioneze personalul (ingineri și cercetători) și să-i asigneze la diverse sarcini;
-sa manipuleze resursele bazei (oxigenul) și să trimită roverul în misiuni, simulând consumul acestora.

Concepte tehnice implementate
Pentru a rezolva cerințele tehnice ale proiectului, am folosit următoarele:
-14 clase distincte, separate corect în fișiere .h și .cpp;
-ierarhii separate pentru Module și Coloniști, folosind metode virtuale;
-clasa LaboratorBioSustenabil moștenește din două clase, problemă rezolvată prin moștenire;
-meniul folosește std::vector pentru a stoca pointeri către obiecte. Am implementat Regula celor 3 (constructor de copiere, operator de atribuire, destructor) la clasa Colonist pentru gestionarea corectă a alocărilor dinamice;
-am creat 4 excepții derivate din std::exception (ex: BaterieInsuficientaException sau ResursaEpuizataException), care sunt prinse cu blocuri try-catch pentru a preveni crash-urile la date greșite;
-clasa ApplicationMenu folosește design pattern-ul Singleton pentru a avea o singură instanță globală de control.


Codul poate fi compilat rulând împreună fișierele main.cpp și marte.cpp.Am adăugat fișierele sursă în CMakeLists.txt la linia 19, astfel încât proiectul să treacă automat testele de memory leaks pe GitHub Actions. Destructorul meniului se ocupă de eliberarea întregii memorii alocate dinamic la finalul execuției.
