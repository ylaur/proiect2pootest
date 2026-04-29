#include "ManagerJoc.h"
#include "Iteme.h"
#include <iostream>
#include <limits>
#include <random>
#include <ctime>

ManagerJoc::ManagerJoc() : puncteJucator(0), rundaCurenta(1), 
    numeInamici({"Demonul Umbrelor", "Regele Nimicirii", "Goblinul Furios", "Bestia de Piatra", "Spectrul Noptii", "Lupul Intunecat"}) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

ManagerJoc::~ManagerJoc() {
    for (auto e : echipaEroi) delete e;
    for (auto i : hoardaInamici) delete i;
}

int ManagerJoc::citesteInt() {
    int val;
    while (!(std::cin >> val)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << ">>> Eroare Input: Te rugam sa introduci un numar intreg: ";
    }
    return val;
}

void ManagerJoc::afisareSeparatoare() const { std::cout << "\n========================================================\n"; }
void ManagerJoc::afisareMiniSeparator() const { std::cout << "--------------------------------------------------------\n"; }
void ManagerJoc::curataEcran() const { for(int i=0; i<2; ++i) std::cout << "\n"; }

void ManagerJoc::fazaSelectieEroi() {
    afisareSeparatoare();
    std::cout << "          FAZA 1: SELECTIA EROILOR TAI\n";
    std::cout << "1. Cavaler | 2. Print | 3. Arcas | 4. Magician\n";

    for (int i = 1; i <= 2; ++i) {
        std::cout << "\n-> Alege clasa pentru eroul " << i << " (tasteaza 1-4): ";
        int clasaOpt = citesteInt();
        std::string numeAles;
        std::cout << "-> Introdu un nume legendar: ";
        std::cin >> numeAles;

        switch (clasaOpt) {
            case 1: echipaEroi.push_back(new Cavaler(numeAles)); break;
            case 2: echipaEroi.push_back(new Print(numeAles)); break;
            case 3: echipaEroi.push_back(new Arcas(numeAles)); break;
            case 4: echipaEroi.push_back(new Magician(numeAles)); break;
            default: 
                std::cout << ">>> Atribuit default: Cavaler.\n";
                echipaEroi.push_back(new Cavaler(numeAles));
                break;
        }
    }
}

void ManagerJoc::fazaGenerareInamici() {
    int bazaHP = 0;
    for(auto e : echipaEroi) bazaHP += e->getHPMax();
    bazaHP = bazaHP / 3;

    for (int i = 0; i < 3; ++i) {
        std::string numeRand = numeInamici[std::rand() % numeInamici.size()];
        int hp = bazaHP + (std::rand() % 40) + (rundaCurenta * 5);
        int dmg = 10 + (std::rand() % 10) + (rundaCurenta * 3);
        hoardaInamici.push_back(new Inamic(numeRand, hp, dmg));
    }
}

void ManagerJoc::fazaMagazin() {
    bool inMagazin = true;
    while (inMagazin) {
        curataEcran(); afisareSeparatoare();
        std::cout << "          MAGAZINUL TIMPULUI (Sfarsitul Rundei " << (rundaCurenta - 1) << ")\n";
        std::cout << "          Fonduri: " << puncteJucator << " Puncte Aur\n";
        afisareMiniSeparator();
        std::cout << "1. Ascute Arma (+10 Daune Baza) | Cost: 50\n";
        std::cout << "2. Bea Potiune Regen (+40 HP)   | Cost: 30\n";
        std::cout << "3. Baza Potiune Scut (+25 HP)   | Cost: 40\n";
        std::cout << "0. Iesire din magazin\n-> Alegere: ";

        int opt = citesteInt();
        if (opt == 0) { inMagazin = false; continue; }
        if (opt < 1 || opt > 3) continue;

        std::cout << "\nSelecteaza ID erou:\n";
        for (size_t i = 0; i < echipaEroi.size(); ++i) {
            std::cout << i << ". " << echipaEroi[i]->getNume() << "\n";
        }
        int eIdx = citesteInt();
        if (eIdx < 0 || eIdx >= (int)echipaEroi.size()) continue;

        Erou* erouSelectat = echipaEroi[eIdx];
        try {
            if (opt == 1) {
                if (puncteJucator < 50) throw ResurseInsuficiente("Upgrade Arma");
                puncteJucator -= 50;
                if (erouSelectat->getArma()) erouSelectat->getArma()->adaugaBonus(10);
            }
            else if (opt == 2) {
                if (puncteJucator < 30) throw ResurseInsuficiente("Regen");
                puncteJucator -= 30;
                PotiuneRegenerare p; p.aplicaEfect(erouSelectat);
            }
            else if (opt == 3) {
                if (puncteJucator < 40) throw ResurseInsuficiente("Scut");
                puncteJucator -= 40;
                PotiuneScut p; p.aplicaEfect(erouSelectat);
            }
        } catch (const JocError& e) {
            std::cout << e.what() << "\n";
        }
        std::cout << "[ENTER pentru a continua]";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}

void ManagerJoc::afiseazaStareCurentaLupta() const {
    std::cout << "\n[ FORMATIA TA ]\n";
    for (size_t i = 0; i < echipaEroi.size(); ++i) {
        std::cout << " ID: " << i << " | "; echipaEroi[i]->afisareCompleta();
    }
    std::cout << "\n[ INAMICI ]\n";
    for (size_t i = 0; i < hoardaInamici.size(); ++i) {
        if (hoardaInamici[i]->esteViu()) {
            std::cout << " ID: " << i << " | "; hoardaInamici[i]->afiseazaStatusCard();
            std::cout << " | Daune: " << hoardaInamici[i]->getDauneBaza() << "\n";
        }
    }
}

void ManagerJoc::proceseazaAbilitatiPasiveDeClasa() {
    std::cout << "\n--- Efecte Pasive ---\n";
    for (auto e : echipaEroi) {
        if (!e->esteViu()) continue;
        if (Magician* m = dynamic_cast<Magician*>(e)) {
            std::cout << " * Magicianul " << m->getNume() << " recupereaza 8 HP.\n";
            m->primesteVindecare(8);
        } else if (Print* p = dynamic_cast<Print*>(e)) {
            std::cout << " * Printul " << p->getNume() << " aduce 5 Puncte Aur.\n";
            puncteJucator += 5;
        }
    }
}

void ManagerJoc::executaTurulJucatorului() {
    std::cout << "\n>>> ATACUL TAU! <<<\nID Erou atacator: ";
    int atkIdx = citesteInt();
    std::cout << "ID Inamic tinta: ";
    int defIdx = citesteInt();

    if (atkIdx >= 0 && atkIdx < (int)echipaEroi.size() && defIdx >= 0 && defIdx < (int)hoardaInamici.size()) {
        Erou* erouAtacator = echipaEroi[atkIdx];
        Inamic* inamicTinta = hoardaInamici[defIdx];

        if (erouAtacator->esteViu() && inamicTinta->esteViu()) {
            int dmg = erouAtacator->calculeazaFortaTotala();
            std::cout << "!!! " << erouAtacator->getNume() << " loveste cu " << dmg << " daune!\n";
            inamicTinta->incaseazaDaune(dmg);

            if (!inamicTinta->esteViu()) {
                std::cout << ">>> INAMIC ELIMINAT! +45 Puncte.\n";
                puncteJucator += 45;
            }
        }
    }
}

void ManagerJoc::executaTurulInamicilor() {
    std::cout << "\n>>> INAMICII RETALIAZA... <<<\n";
    for (auto inamic : hoardaInamici) {
        if (inamic->esteViu()) {
            std::vector<Erou*> tinteDisponibile;
            for (auto e : echipaEroi) if (e->esteViu()) tinteDisponibile.push_back(e);

            if (!tinteDisponibile.empty()) {
                Erou* victima = tinteDisponibile[std::rand() % tinteDisponibile.size()];
                std::cout << " !!! " << inamic->getNume() << " ataca pe " << victima->getNume() << " cu " << inamic->getDauneBaza() << " daune!\n";
                victima->incaseazaDaune(inamic->getDauneBaza());
            }
        }
    }
}

void ManagerJoc::fazaLupta() {
    afisareSeparatoare();
    std::cout << "                 RUNDA DE COMBAT " << rundaCurenta << "\n";
    afiseazaStareCurentaLupta();
    executaTurulJucatorului();
    executaTurulInamicilor();
    proceseazaAbilitatiPasiveDeClasa();
    puncteJucator += 20;
    rundaCurenta++;
}

void ManagerJoc::ruleazaJocul() {
    fazaSelectieEroi();
    fazaGenerareInamici();

    bool luptaInDesfasurare = true;
    while (luptaInDesfasurare) {
        bool eroiInPicioare = false;
        for (auto e : echipaEroi) if (e->esteViu()) eroiInPicioare = true;
        if (!eroiInPicioare) {
            afisareSeparatoare(); std::cout << "          GAME OVER\n"; break;
        }

        bool inamiciRamas = false;
        for (auto i : hoardaInamici) if (i->esteViu()) inamiciRamas = true;
        if (!inamiciRamas) {
            afisareSeparatoare(); std::cout << "          VICTORIE EPICA!\n"; break;
        }

        if ((rundaCurenta - 1) > 0 && (rundaCurenta - 1) % 3 == 0) fazaMagazin();

        fazaLupta();
        std::cout << "\n[Apasati ENTER...]";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}
