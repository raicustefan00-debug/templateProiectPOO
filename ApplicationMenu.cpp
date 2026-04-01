#include "ApplicationMenu.h"
#include <iostream>

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