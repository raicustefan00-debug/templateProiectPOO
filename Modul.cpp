#include "Modul.h"
#include "Resursa.h"
#include "Colonist.h"
#include "Exceptii.h"

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