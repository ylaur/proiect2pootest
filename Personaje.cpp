#include "Personaje.h"

int Entitate::contorEntitati = 0;

Entitate::Entitate(std::string n, int h, int d) : nume(n), hpCurent(h), hpMaxim(h), dauneBaza(d) {
    if (h <= 0 || d < 0) throw ConfigurareInvalida("Statusuri invalide la crearea entitatii " + n + ".");
    contorEntitati++;
}
Entitate::~Entitate() { contorEntitati--; }
bool Entitate::esteViu() const { return hpCurent > 0; }
std::string Entitate::getNume() const { return nume; }
int Entitate::getHP() const { return hpCurent; }
int Entitate::getHPMax() const { return hpMaxim; }
int Entitate::getDauneBaza() const { return dauneBaza; }
void Entitate::incaseazaDaune(int daune) { hpCurent -= daune; if (hpCurent < 0) hpCurent = 0; }
void Entitate::primesteVindecare(int vindecare) {
    if (!esteViu()) return;
    hpCurent += vindecare;
    if (hpCurent > hpMaxim) hpCurent = hpMaxim;
}
void Entitate::afiseazaStatusCard() const {
    std::cout << "["; afisare_identitate(); std::cout << "] " << nume << " - HP: " << hpCurent << "/" << hpMaxim;
}
int Entitate::obtineNumarEntitati() { return contorEntitati; }

// --- Implementari Erou ---
Erou::Erou(std::string n, int h, int d) : Entitate(std::move(n), h, d), armaEchipata(nullptr) {}
Erou::~Erou() { delete armaEchipata; }
Erou::Erou(const Erou& other) : Entitate(other) {
    this->armaEchipata = other.armaEchipata != nullptr ? other.armaEchipata->clone() : nullptr;
}
Erou& Erou::operator=(const Erou& other) {
    if (this != &other) {
        this->nume = other.nume;
        this->hpCurent = other.hpCurent;
        this->hpMaxim = other.hpMaxim;
        this->dauneBaza = other.dauneBaza;
        delete this->armaEchipata;
        this->armaEchipata = other.armaEchipata ? other.armaEchipata->clone() : nullptr;
    }
    return *this;
}
void Erou::atribuieArma(const Arma& nouaArma) {
    delete armaEchipata;
    armaEchipata = nouaArma.clone();
}
Arma* Erou::getArma() const { return armaEchipata; }
int Erou::calculeazaFortaTotala() const {
    return dauneBaza + (armaEchipata != nullptr ? armaEchipata->calculeazaDauneEfective() : 0);
}
void Erou::afisareCompleta() const {
    afiseazaStatusCard();
    std::cout << " | ";
    if (armaEchipata != nullptr) armaEchipata->afiseazaArma(); else std::cout << "FARA ARMA";
    std::cout << " | Daune potentiale: " << calculeazaFortaTotala() << "\n";
}

// --- Eroi Particulari ---
Cavaler::Cavaler(std::string n) : Erou(std::move(n), 150, 15) { atribuieArma(Sabie(10)); }
void Cavaler::afisare_identitate() const { std::cout << "Cavaler"; }

Print::Print(std::string n) : Erou(std::move(n), 120, 20) { atribuieArma(Lance(15)); }
void Print::afisare_identitate() const { std::cout << "Print"; }

Arcas::Arcas(std::string n) : Erou(std::move(n), 100, 25) { atribuieArma(Arc(18)); }
void Arcas::afisare_identitate() const { std::cout << "Arcas"; }

Magician::Magician(std::string n) : Erou(std::move(n), 80, 30) { atribuieArma(Toiag(22)); }
void Magician::afisare_identitate() const { std::cout << "Magician"; }

// --- Inamic ---
Inamic::Inamic(std::string n, int h, int d) : Entitate(std::move(n), h, d) {}
void Inamic::afisare_identitate() const { std::cout << "Inamic"; }
