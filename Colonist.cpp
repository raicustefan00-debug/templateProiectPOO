#include "Colonist.h"
#include "Modul.h"
#include "Exceptii.h"
#include <cstring>

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