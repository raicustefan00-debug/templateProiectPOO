#pragma once // Previne includerea multipla a header-ului
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Pre-declarari
class Resursa;
class Cercetator;

// Clasa de baza abstracta (contine cel putin o functie virtuala pura = 0)
class ModulSistem {
    private:
        int idModul;
        int consumEnergie;
        float integritate;
        static int id; // Variabila statica pentru generarea automata a ID-urilor unice

    public:
        ModulSistem(int c, float i);
        virtual ~ModulSistem() = default; // Destructor virtual obligatoriu in clase de baza polimorfice
        virtual void ruleazaDiagnostic() = 0; // Functie virtuala pura
        virtual void afisare();
        float integritateGetter();
        void integritateSetter(float i);
        int idGetter();
};

// Mostenire VIRTUALA pentru a rezolva "Problema Diamantului"
class ModulProductie : virtual public ModulSistem {
    private:
        float rataProductieOxigen;
        Resursa *rezervor_conectat;
    public:
        ModulProductie(int c, float i, float r, Resursa *res);
        ~ModulProductie() = default;
        virtual void ruleazaDiagnostic();
};

// Mostenire VIRTUALA
class ModulCercetare : virtual public ModulSistem {
    private:
        std::string domeniuStiintific;
        Cercetator *publicatii;
    public:
        ModulCercetare(int c, float i, std::string d, Cercetator *p);
        ~ModulCercetare() = default;
        virtual void ruleazaDiagnostic();

};

// Clasa care finalizeaza structura de diamant
class LaboratorBioSustenabil : public ModulProductie, public ModulCercetare {
    public:
        LaboratorBioSustenabil(int c, float i, float r, Cercetator *p, Resursa *res, std::string d);
        ~LaboratorBioSustenabil() = default;
        virtual void ruleazaDiagnostic();
};

class Colonist{
    private:
        int varsta;
        std::string nume;
        char *specializare; // Pointer alocat dinamic
    public:
        // Regula celor 3 implementata aici datorita pointerului de mai sus
        Colonist(int v, std::string n, const char *s); // Constructor
        Colonist(const Colonist& other); // 1. Constructor de copiere
        Colonist& operator=(const Colonist& other); // 2. Operator de atribuire
        virtual ~Colonist(); // 3. Destructor virtual

        virtual void executaSarcina(ModulSistem *m = nullptr) = 0; // Polimorfism
        std::string numeGetter();
        virtual void afisare();
};

class Inginer : public Colonist {
    private:
        int ani_experienta;
    public:
        Inginer(int v, std::string n, const char *s, int a);
        ~Inginer() = default;
        virtual void executaSarcina(ModulSistem *m = nullptr);
};

class Cercetator :  public Colonist {
    private:
        std::string publicatiiStiintifice;
        int nrPublicatii;
    public:
        Cercetator(int v, std::string n, const char *s, std::string p, int pb);
        ~Cercetator() = default;
        virtual void executaSarcina(ModulSistem *m = nullptr);
        int publicatiiGetter();
        void publicatiiIncr();
};

class Rover{
    private:
        float nivelBaterie;
        float distantaParcursa;
        bool echipaj;
    public:
        Rover(float n, float d, bool e);
        ~Rover() = default;
        void deplasare(float km);
        void afisare();
};

class Resursa{
    private:
        std::string TipEnergie;
        float cantitate_curenta;
        float cantitateMaxima;
        static float consumGlobalOxigen;
    public:
        Resursa(std::string T, float c, float cm);
        ~Resursa() = default;
        void consuma(float cantitate);
        void produce(float cantitate);
        void afisare();
};

// --- EXCEPTII CUSTOM (Derivate din std::exception) ---
class AlertaSistem : public std::exception{
    public:
        const char* what() const throw() override
        {return "Alerta: Sistem critic!";}
};

class BaterieInsuficientaException : public std::exception {
    public:
        const char* what() const throw() override
        {return "Eroare Rover:nivelul bateriei este prea mic pt aceasta distanta";}
};

class ResursaEpuizataException: public std::exception {
    public:
        const char* what() const throw() override
        {return "Alerta critica: resurse insuficiente pt a finaliza actiunea!";}
};

class DateInvalideException : public std::exception {
    public:
        const char* what() const throw() override
            {return "Eroare initializare: Datele introduse sunt invalide";}
};

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
        void punePersonalLaMunca(std::string nume_cautat);
        void rulareSarcina(std::string nume_cautat);
        void stergePersonal(std::string nume_cautat);
        
        ~ApplicationMenu();
};