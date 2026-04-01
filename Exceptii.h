#pragma once
#include <exception>

// --- EXCEPTII CUSTOM (Derivate din std::exception) ---
class AlertaSistem : public std::exception{
    public:
        const char* what() const throw() override
        {return "Alerta: Sistem critic!";}
};
//eroare pt clasa rover
class BaterieInsuficientaException : public std::exception {
    public:
        const char* what() const throw() override
        {return "Eroare Rover:nivelul bateriei este prea mic pt aceasta distanta";}
};
//eraore pt clase resurse
class ResursaEpuizataException: public std::exception {
    public:
        const char* what() const throw() override
        {return "Alerta critica: resurse insuficiente pt a finaliza actiunea!";}
};
//eroare pt date invalide
class DateInvalideException : public std::exception {
    public:
        const char* what() const throw() override
            {return "Eroare initializare: Datele introduse sunt invalide";}
};