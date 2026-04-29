#pragma once
#include <vector>
#include <string>
#include "Personaje.h"

class ManagerJoc {
private:
    std::vector<Erou*> echipaEroi;
    std::vector<Inamic*> hoardaInamici;
    int puncteJucator;
    int rundaCurenta;
    const std::vector<std::string> numeInamici;

    int citesteInt();
    void afisareSeparatoare() const;
    void afisareMiniSeparator() const;
    void curataEcran() const;

    void fazaSelectieEroi();
    void fazaGenerareInamici();
    void fazaMagazin();
    void afiseazaStareCurentaLupta() const;
    void proceseazaAbilitatiPasiveDeClasa();
    void executaTurulJucatorului();
    void executaTurulInamicilor();
    void fazaLupta();

public:
    ManagerJoc();
    ~ManagerJoc();

    ManagerJoc(const ManagerJoc&) = delete;
    ManagerJoc& operator=(const ManagerJoc&) = delete;

    void ruleazaJocul();
};
