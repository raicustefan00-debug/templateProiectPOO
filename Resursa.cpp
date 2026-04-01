#include "Resursa.h"
#include "Exceptii.h"

//constructor
Resursa::Resursa(const std::string& T, float c, float cm) : TipEnergie(T) {
    if(c < 0.0 || cm < 0.0)
        throw DateInvalideException();
    cantitate_curenta = c;
    cantitateMaxima = cm;
}

void Resursa::afisare(){
    std::cout << TipEnergie << " in cantitate de " << cantitate_curenta << " poate avea valoarea maxima de " << cantitateMaxima << "\n";
}
//initializare valoare static
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