#pragma once
#include "Modul.h"
#include "Colonist.h"
#include <vector>
#include <string>

//Singleton
class ApplicationMenu {
    private:
        std::vector <ModulSistem*> modul; // Stocare polimorfica module
        std::vector <Colonist*> personal; // Stocare polimorfica colonisti
        static ApplicationMenu* instance; // Unica instanta
        ApplicationMenu(); // Constructor privat specific Singleton-ului
    public:
        static ApplicationMenu* getInstance();
        
        // Operatiuni pentru Module
        void adaugaModul(ModulSistem *m);
        void afiseazaModul();   
        void modificaIntegritateModul(int idCautat, float integritate_noua);  
        void stergeModul(int idCautat);  
        void rulareDiagnostic(int idCautat); 

        // Operatiuni pentru Personal
        void adaugaPersonal(Colonist* c);
        void afiseazaPersonal();
        // Optimizat cu referinta constanta
        void rulareSarcina(const std::string& nume_cautat);
        void stergePersonal(const std::string& numeCautat);
        
        ~ApplicationMenu();
};