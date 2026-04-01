#pragma once
#include <string>
#include <iostream>

class Resursa{
    private:
        std::string TipEnergie;
        float cantitate_curenta;
        float cantitateMaxima;
        static float consumGlobalOxigen;
    public:
        // Optimizat cu referinta
        Resursa(const std::string& T, float c, float cm);
        ~Resursa() = default;
        // functii pt manipularea resurselor
        void consuma(float cantitate);
        void produce(float cantitate);
        
        void afisare();
};