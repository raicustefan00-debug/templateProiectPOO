#pragma once
#include <string>
#include <iostream>

class ModulSistem; // Pre-declarare pt a evita dependintele circulare

class Colonist{
    private:
        int varsta;
        std::string nume;
        char *specializare; // Pointer alocat dinamic
    public:
        // Regula celor 3 implementata aici datorita pointerului de mai sus
        Colonist(int v, const std::string& n, const char *s); // Optimizat
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
        // Optimizat cu referinta
        Inginer(int v, const std::string& n, const char *s, int a);
        ~Inginer() = default;
        virtual void executaSarcina(ModulSistem *m = nullptr) override; // Adaugat override
};

class Cercetator :  public Colonist {
    private:
        std::string publicatiiStiintifice;
        int nrPublicatii;
    public:
        // Optimizat cu referinta
        Cercetator(int v, const std::string& n, const char *s, const std::string& p, int pb);
        ~Cercetator() = default;
        virtual void executaSarcina(ModulSistem *m = nullptr) override; // Adaugat override
        void publicatiiIncr();
};