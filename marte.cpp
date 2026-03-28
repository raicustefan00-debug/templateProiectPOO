#include "marte.h"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <string>

// Validam datele in constructor; daca nu sunt ok aruncam exceptia creata de noi
ModulSistem::ModulSistem(int c, float i) : consumEnergie(c){
    if(c < 0)
        throw DateInvalideException();
    integritate = i;
    idModul = ++id; // Autoincrementare pe baza variabilei statice
}

int ModulSistem::id = 0; // Initializarea variabilei statice

void ModulSistem::afisare(){
    std::cout << "Modulul cu id-ul " << idModul << " are un consum de " << consumEnergie << " si este intr-o stare de " << integritate <<"%" << "\n";
}

float ModulSistem::integritateGetter(){
    return integritate;
}

void ModulSistem::integritateSetter(float i){
    integritate = i;
}

int ModulSistem::idGetter(){
    return idModul;
}

// Apelam constructorul de baza in lista de initializare
ModulProductie::ModulProductie(int c, float i, float r, Resursa *res) : ModulSistem(c, i){
    if(r < 0.0)
        throw DateInvalideException();
    rataProductieOxigen = r;
    rezervor_conectat = res;
}

ModulCercetare::ModulCercetare(int c, float i, const std::string& d, Cercetator *p) : ModulSistem(c, i), domeniuStiintific(d), publicatii(p) {}

// Datorita mostenirii virtuale, Laboratorul trebuie sa apeleze explicit constructorul ModulSistem
LaboratorBioSustenabil::LaboratorBioSustenabil(int c, float i, float r, Cercetator *p, Resursa *res, const std::string& d) : ModulSistem(c, i), ModulProductie(c, i, r, res), ModulCercetare(c, i, d, p) {}

void ModulProductie::ruleazaDiagnostic(){
    if(rezervor_conectat != nullptr)
        rezervor_conectat->produce(rataProductieOxigen);
    std::cout << "Rata de productie de oxigen este " << rataProductieOxigen << "\n";
}

void ModulCercetare::ruleazaDiagnostic(){
    if(publicatii != nullptr)
        publicatii->publicatiiIncr();
    std::cout << "Se ruleaza cercetari in " << domeniuStiintific << "\n";
}

// Demonstram rezolvarea problemei diamantului apeland metodele parintilor direct
void LaboratorBioSustenabil::ruleazaDiagnostic(){
    ModulCercetare::ruleazaDiagnostic();
    ModulProductie::ruleazaDiagnostic();
    std::cout << "Laboratorul ruleaza un diagnostic hibrid" << "\n";
}

Colonist::Colonist(int v, const std::string& n, const char *s){
    if(v < 0)
        throw DateInvalideException();
    varsta = v;
    nume = n;
    // Alocare dinamica a memoriei pentru pointer char
    specializare = new char[strlen(s) + 1]; 
    strcpy(specializare, s);
}

void Colonist::afisare(){
    std::cout << "Colonistul " << nume << " are " << varsta << " si este specializat in " << specializare << "\n";
}

std::string Colonist::numeGetter(){
    return nume;
}

// 1. Constructorul de copiere - Optimizat pt cppcheck
Colonist::Colonist(const Colonist &other) : varsta(other.varsta), nume(other.nume) {
    specializare = new char[strlen(other.specializare) + 1];
    strcpy(specializare, other.specializare);
}

// REGULA CELOR 3: 2. Operatorul de atribuire
Colonist& Colonist::operator=(const Colonist& other){
    if(this != &other){ // Ne asiguram ca nu copiem acelasi obiect
        delete[] specializare; // Curatam memoria veche
        varsta = other.varsta;
        nume = other.nume;
        specializare = new char[strlen(other.specializare) + 1]; // Alocam una noua
        strcpy(specializare, other.specializare);
    }
    return *this;
}

// REGULA CELOR 3: 3. Destructor
Colonist::~Colonist(){
    delete[] specializare; // Previne memory leak
}

Inginer::Inginer(int v, const std::string& n, const char *s, int e) : Colonist(v, n, s), ani_experienta(e) {}

Cercetator::Cercetator(int v, const std::string& n, const char *s, const std::string& p, int pb) : Colonist(v, n, s), publicatiiStiintifice(p), nrPublicatii(pb){}

void Cercetator::publicatiiIncr(){
    nrPublicatii++;
}

void Inginer::executaSarcina(ModulSistem *m){
    if(m == nullptr){
        std::cout << "Inginerul " << numeGetter() << " nu a primit un modul" << "\n";
        return;
    } 
    float integ = m->integritateGetter();
    integ += integ * (ani_experienta / 100.0);
    m->integritateSetter(integ);
    std::cout << "Inginerul a reparat " << ani_experienta << " la suta din modul" << "\n";
}

void Cercetator::executaSarcina(ModulSistem *m){
    if(m == nullptr){
        std::cout << "Cercetatorul " << numeGetter() << " nu a scris o publicatie" << "\n";
        return;
    } 
    std::cout << "Cercetatorul a scris o publicatie despre " << publicatiiStiintifice << " in modulul cu id-ul " << m->idGetter() << "\n";
}

Rover::Rover(float n, float d, bool e) : nivelBaterie(n), distantaParcursa(d), echipaj(e) {}

void Rover::deplasare(float km){
    // Logica consumului si aruncarea exceptiei custom
    float baterie_necesara = km * 0.1;
    if(baterie_necesara > nivelBaterie)
    {
        throw BaterieInsuficientaException();
    }
    else{
        nivelBaterie -= baterie_necesara;
        distantaParcursa += km;
    }
}

void Rover::afisare(){
    if(echipaj == false)
        std::cout << "Roverul are " << nivelBaterie << " baterie, fara echipaj si a parcurs " << distantaParcursa <<" km" << "\n";
    else
        std::cout << "Roverul are " << nivelBaterie << " baterie, cu echipaj si a parcurs " << distantaParcursa <<" km" << "\n";
    std::cout << std::endl;
}

Resursa::Resursa(const std::string& T, float c, float cm) : TipEnergie(T) {
    if(c < 0.0 || cm < 0.0)
        throw DateInvalideException();
    cantitate_curenta = c;
    cantitateMaxima = cm;
}

void Resursa::afisare(){
    std::cout << TipEnergie << " in cantitate de " << cantitate_curenta << " poate avea valoarea maxima de " << cantitateMaxima << "\n";
}

float Resursa::consumGlobalOxigen = 0.0; 

void Resursa::consuma(float cantitate){
    if(cantitate_curenta - cantitate < 0){
        throw ResursaEpuizataException(); // Arunca exceptie cand trecem sub 0
    }
    else
        cantitate_curenta -= cantitate;
}

void Resursa::produce(float cantitate){
    if(cantitate + cantitate_curenta > cantitateMaxima)
        cantitate_curenta = cantitateMaxima; // Nu depasim valoarea setata
    else
        cantitate_curenta += cantitate;
}

//Implementare meniu Singleton
ApplicationMenu* ApplicationMenu::instance = nullptr; 

ApplicationMenu::ApplicationMenu() {};

ApplicationMenu* ApplicationMenu::getInstance(){
    if(!instance)
        instance = new ApplicationMenu();
    return instance;
}

void ApplicationMenu::adaugaModul(ModulSistem *m){
    modul.push_back(m);
}

void ApplicationMenu::afiseazaModul(){
    //apeleaza functia corecta in functie de tipul obiectului
    for(auto m:modul){
        m->afisare();
        std::cout << std::endl;
    }
}

// Destructorul care rezolva potentialele scurgeri de memorie (Memory Leaks)
ApplicationMenu::~ApplicationMenu(){
    for(auto m : modul)
        delete m;
    modul.clear();
    for(auto p : personal)
        delete p;
    personal.clear();
}

void ApplicationMenu::modificaIntegritateModul(int idCautat, float integritate_noua){
    for(auto m:modul){
        if(m->idGetter() == idCautat){
            m->integritateSetter(integritate_noua);
            return;   
        } 
    }
    std::cout << "Modulul nu exista" << "\n";
}

void ApplicationMenu::stergeModul(int idCautat){
    // Folosim iterator pentru a putea sterge elemente dintr-un vector in siguranta
    for(auto it = modul.begin(); it != modul.end(); ++it){
        if((*it)->idGetter() == idCautat){
            delete *it; // Eliberam memoria reala de pe Marte
            modul.erase(it); // Scoatem referinta din vector
            return;
        }
    }
    std::cout << "Modulul nu a fost gasit\n";
}

void ApplicationMenu::rulareDiagnostic(int idCautat){
    for(auto m:modul){
        if(m->idGetter() == idCautat){
            m->ruleazaDiagnostic();
            return;
        }       
    }
    std::cout << "Modulul nu exista" << "\n";
}

void ApplicationMenu::adaugaPersonal(Colonist *c){
    personal.push_back(c);
}

void ApplicationMenu::afiseazaPersonal(){
    for(auto p:personal){
        p->afisare();
        std::cout << std::endl;
    }
}

void ApplicationMenu::rulareSarcina(const std::string& nume_cautat){
    for(auto p:personal){
        if(p->numeGetter() == nume_cautat){
            p->executaSarcina();
            return;
        }
    }
    std::cout << "Colonistul nu exista" << "\n";
}

void ApplicationMenu::stergePersonal(const std::string& numeCautat){
    for(auto it = personal.begin(); it != personal.end(); ++it){
        if((*it)->numeGetter() == numeCautat){
            delete *it;
            personal.erase(it);
            return;
        }
    }
    std::cout << "Colonistul nu a fost gasit\n";
}
