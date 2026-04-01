#pragma once
#include <string>
#include <iostream>

class Resursa; // Pre-declarari
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
        virtual void ruleazaDiagnostic() override; // Adaugat override
};

// Mostenire VIRTUALA
class ModulCercetare : virtual public ModulSistem {
    private:
        std::string domeniuStiintific;
        Cercetator *publicatii;
    public:
        // Optimizare performanta: referinta constanta
        ModulCercetare(int c, float i, const std::string& d, Cercetator *p);
        ~ModulCercetare() = default;
        virtual void ruleazaDiagnostic() override; // Adaugat override
};

// Clasa care finalizeaza structura de diamant
class LaboratorBioSustenabil : public ModulProductie, public ModulCercetare {
    public:
        // Optimizare performanta: referinta constanta
        LaboratorBioSustenabil(int c, float i, float r, Cercetator *p, Resursa *res, const std::string& d);
        ~LaboratorBioSustenabil() = default;
        virtual void ruleazaDiagnostic() override; // Adaugat override
};