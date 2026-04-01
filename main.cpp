#include "ApplicationMenu.h"
#include "Modul.h"
#include "Colonist.h"
#include "Resursa.h"
#include "Rover.h"
#include "Exceptii.h"

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main() {
    // Instantiem meniul Singleton (o singura instanta pe tot parcursul programului)
    ApplicationMenu *menu = ApplicationMenu::getInstance();
    
    // Declaram resursa si roverul in exteriorul buclei while 
    // pentru a le pastra starea si datele pe toata durata simularii
    Resursa oxigen("Oxigen", 100.0, 500.0);
    Rover curiosity(20.0, 100.0, false);
    
    int optiune; // Declarare mai restransa conform cppcheck
    
    // Bloc try-catch principal pentru a prinde erorile fatale
    try {
        // Protectie timeout: bucla se opreste daca inputul esueaza sau este 0
        while (std::cin >> optiune && optiune != 0) {
            std::cout << "1. Administreaza module\n2. Administreaza colonistii\n3. Manipuleaza resursele\n4. Calculare traseu rover\n5. Iesire\n";
            std::cout << "Alege: ";

            // Bloc try-catch secundar pentru a nu inchide meniul daca utilizatorul greseste o data
            try {
                while (optiune != 0) {
                    if (optiune == 1) {
                        std::cout << "1. Adauga modul\n2. Sterge modul\n3. Afiseaza toate modulele\n4. Ruleaza un diagnostic\n5. Modificati integritatea unui modul\n6. Inapoi\n Alege: ";
                        int optiune2;
                        std::cin >> optiune2;
                        if (optiune2 == 1) {
                            std::cout << "1. Modul de productie\n2. Modul de cercetare\n3. Laborator Biosustenabil\nAlege: ";
                            int optiune1;
                            std::cin >> optiune1;
                            // Crearea obiectelor
                            if (optiune1 == 1) {
                                int c; float r, i;
                                std::cout << "Consum energie(int > 0): "; std::cin >> c;
                                std::cout << "Integritate(float): "; std::cin >> i;
                                std::cout << "Rata productie oxigen(float > 0.0): "; std::cin >> r;
                                // Adaugam prin pointer
                                menu->adaugaModul(new ModulProductie(c, i, r, nullptr));
                            } else if (optiune1 == 2) {
                                int c; float i; std::string d;
                                std::cout << "Consum energie(int > 0): "; std::cin >> c;
                                std::cout << "Integritate(float): "; std::cin >> i;
                                std::cout << "Domeniu stiintific studiat(string): "; std::cin >> d;
                                menu->adaugaModul(new ModulCercetare(c, i, d, nullptr));
                            } else if (optiune1 == 3) {
                                int c; float i, r; std::string d;
                                std::cout << "Consum energie(int > 0): "; std::cin >> c;
                                std::cout << "Integritate(float): "; std::cin >> i;
                                std::cout << "Rata productie oxigen(float > 0.0): "; std::cin >> r;
                                std::cout << "Domeniu stiintific studiat(string): "; std::cin >> d;
                                // Modulul hibrid (Problema diamantului)
                                menu->adaugaModul(new LaboratorBioSustenabil(c, i, r, nullptr, nullptr, d));
                            }
                        }
                        // Stergerea obiectelor
                        if (optiune2 == 2) {
                            int id;
                            std::cout << "Introduceti ID-ul modului(int): ";
                            std::cin >> id;
                            menu->stergeModul(id);
                        }
                        // Afisarea obiectelor
                        if (optiune2 == 3) {
                            menu->afiseazaModul();
                        }
                        if (optiune2 == 4) {
                            int idCautat;
                            std::cout << "Introduceti ID-ul modulului(int): ";
                            std::cin >> idCautat;
                            menu->rulareDiagnostic(idCautat);
                        }
                        // Actualizarea obiectelor
                        if (optiune2 == 5) {
                            int idCautat; float integritate_noua;
                            std::cout << "Introduceti ID-ul modulului(int): "; std::cin >> idCautat;
                            std::cout << "Introduceti integritatea noua(float): "; std::cin >> integritate_noua;
                            menu->modificaIntegritateModul(idCautat, integritate_noua);
                        }
                        // Iesire din submeniu
                        if (optiune2 == 6) {
                            break; 
                        }
                    }
                    if (optiune == 2) {
                        std::cout << "1. Adauga colonist\n2. Sterge colonist\n3. Afiseaza toti colinistii\n4. Ruleaza o sarcina\n5. Inapoi\nAlege: ";
                        int optiune2;
                        std::cin >> optiune2;
                        
                        if (optiune2 == 1) {
                            std::cout << "1. Inginer\n2. Cercetator\n";
                            std::cout << "Alege: ";
                            int optiune1;
                            std::cin >> optiune1;
                            
                            if (optiune1 == 1) {
                                int v, a; std::string n;
                                char s[100]; 
                                std::cout << "Nume(string): "; std::cin >> n;
                                std::cout << "Varsta(int > 0): "; std::cin >> v;
                                std::cout << "Specializare(char): "; std::cin >> s;
                                std::cout << "Ani de experienta(int): "; std::cin >> a;
                                menu->adaugaPersonal(new Inginer(v, n, s, a));
                            } else if (optiune1 == 2) {
                                int v, pb; std::string n, p;
                                char s[100];
                                std::cout << "Nume(string): "; std::cin >> n;
                                std::cout << "Varsta(int > 0): "; std::cin >> v;
                                std::cout << "Specializare(char): "; std::cin >> s;
                                std::cout << "Publicatie Stiintifica(string): "; std::cin >> p;
                                std::cout << "Numar de publicatii stiintifica(int): "; std::cin >> pb;
                                menu->adaugaPersonal(new Cercetator(v, n, s, p, pb));
                            }
                        }
                        if (optiune2 == 2) {
                            std::string nume;
                            std::cout << "Introduceti numele colonistului(string): ";
                            std::cin >> nume;
                            menu->stergePersonal(nume);
                        }
                        if (optiune2 == 3) {
                            menu->afiseazaPersonal();
                        }
                        if (optiune2 == 4) {
                            std::string n;
                            std::cout << "Introduceti nume(string): ";
                            std::cin >> n;
                            menu->rulareSarcina(n);
                        }
                        if (optiune2 == 5) {
                            break;
                        }
                    }
                    if(optiune == 3){
                        oxigen.afisare();
                        std::cout << "1. Adaugati oxigen\n2. Consumati oxigen\n3. Inapoi\nAlege: ";
                        int optiune3;
                        std::cin >> optiune3;
                        if(optiune3 == 1){
                            float c;
                            std::cout << "Introduceti cantitatea de oxigen adaugata(float): "; std::cin >> c;
                            oxigen.produce(c);
                        }if(optiune3 == 2){
                            float c;
                            std::cout << "Introduceti cantitatea de oxigen consumata(float > cantitate_curenta): "; std::cin >> c;
                            oxigen.consuma(c);
                        }
                        if(optiune3 == 3)
                            break;
                    }
                    
                    if(optiune == 4){
                        curiosity.afisare();
                        float km;
                        std::cout << "1.Cati kilometri doriti sa parcurgeti?(float): ";
                        std::cin >> km;
                        curiosity.deplasare(km);
                        curiosity.afisare();
                        
                        std::cout << "1. Doriti sa repetati?\n2.Inapoi\nAlege: ";
                        int optiune4;
                        std::cin >> optiune4;
                        if(optiune4 == 1)
                            optiune = 4;
                        else if(optiune4 == 2)
                            break;
                    }
                    // Iesirea din program optimizata
                    if(optiune == 5){
                        optiune = 0; // Oprim si bucla while principala
                        break;
                    }
                }
            }catch (std::exception &e) {
                // Prinde exceptiile declansate la introducerea datelor gresite
                std::cout << e.what() << "\n";
            }
        }

    } catch (std::exception &e) {
        std::cout << e.what() << "\n";
    }
    
    // Apelam manual destructorul meniului pentru a preveni Memory Leaks la final
    delete menu;
    return 0;
}