#pragma once
#include <iostream>

class Rover{
    private:
        float nivelBaterie;
        float distantaParcursa;
        bool echipaj;
    public:
        Rover(float n, float d, bool e);
        ~Rover() = default;
        //functie pt calcularea distantei posibile de parcurs
        void deplasare(float km);
        void afisare();
};