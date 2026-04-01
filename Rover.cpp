#include "Rover.h"
#include "Exceptii.h"

Rover::Rover(float n, float d, bool e) : nivelBaterie(n), distantaParcursa(d), echipaj(e) {}

void Rover::deplasare(float km){
    // Logica consumului si aruncarea exceptiei custom
    float baterie_necesara = km * 0.1;
    if(baterie_necesara > nivelBaterie)
    {
        throw BaterieInsuficientaException();
    }
    else{
        nivelBaterie -= baterie_necesara;
        distantaParcursa += km;
    }
}

void Rover::afisare(){
    if(echipaj == false)
        std::cout << "Roverul are " << nivelBaterie << " baterie, fara echipaj si a parcurs " << distantaParcursa <<" km" << "\n";
    else
        std::cout << "Roverul are " << nivelBaterie << " baterie, cu echipaj si a parcurs " << distantaParcursa <<" km" << "\n";
    std::cout << std::endl;
}