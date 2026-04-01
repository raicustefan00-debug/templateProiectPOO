#include "ApplicationMenu.h"
#include <iostream>
#include <algorithm> // IMPORTANT pt cppcheck

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
    auto it = std::find_if(modul.begin(), modul.end(), [idCautat](ModulSistem* m) { return m->idGetter() == idCautat; });
    if(it != modul.end()) {
        (*it)->integritateSetter(integritate_noua);
    } else {
        std::cout << "Modulul nu exista\n";
    }
}

void ApplicationMenu::stergeModul(int idCautat){
    auto it = std::find_if(modul.begin(), modul.end(), [idCautat](ModulSistem* m) { return m->idGetter() == idCautat; });
    if(it != modul.end()) {
        delete *it; // Eliberam memoria reala de pe Marte
        modul.erase(it); // Scoatem referinta din vector
    } else {
        std::cout << "Modulul nu a fost gasit\n";
    }
}

void ApplicationMenu::rulareDiagnostic(int idCautat){
    auto it = std::find_if(modul.begin(), modul.end(), [idCautat](ModulSistem* m) { return m->idGetter() == idCautat; });
    if(it != modul.end()) {
        (*it)->ruleazaDiagnostic();
    } else {
        std::cout << "Modulul nu exista\n";
    }
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
    auto it = std::find_if(personal.begin(), personal.end(), [&nume_cautat](Colonist* p) { return p->numeGetter() == nume_cautat; });
    if(it != personal.end()) {
        (*it)->executaSarcina();
    } else {
        std::cout << "Colonistul nu exista\n";
    }
}

void ApplicationMenu::stergePersonal(const std::string& numeCautat){
    auto it = std::find_if(personal.begin(), personal.end(), [&numeCautat](Colonist* p) { return p->numeGetter() == numeCautat; });
    if(it != personal.end()) {
        delete *it;
        personal.erase(it);
    } else {
        std::cout << "Colonistul nu a fost gasit\n";
    }
}
