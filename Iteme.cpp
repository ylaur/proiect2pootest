#include "Iteme.h"
#include "Personaje.h" // Pentru a stii ce sa faca cu Eroul
#include <cstdlib>

// --- Implementari Arma ---
Arma::Arma(int bonus) : bonusDaune(bonus) {
    if (bonus < 0) throw ConfigurareInvalida("O arma nu poate avea bonus de daune negativ!");
}
void Arma::afiseazaArma() const { descriere_impl(); std::cout << " (+ " << bonusDaune << " Daune)"; }
int Arma::getBonusDaune() const { return bonusDaune; }
void Arma::adaugaBonus(int valoare) { bonusDaune += valoare; }
int Arma::calculeazaDauneEfective() const { return bonusDaune; }

Sabie::Sabie(int b) : Arma(b) {}
void Sabie::descriere_impl() const { std::cout << "Sabie Greoaie"; }
Arma* Sabie::clone() const { return new Sabie(*this); }
int Sabie::calculeazaDauneEfective() const {
    int dmg = bonusDaune;
    if (rand() % 100 < 20) { std::cout << " [CRITICAL HIT CU SABIA!] "; dmg += 5; }
    return dmg;
}

Lance::Lance(int b) : Arma(b) {}
void Lance::descriere_impl() const { std::cout << "Lance Lunga de Penetrare"; }
Arma* Lance::clone() const { return new Lance(*this); }
int Lance::calculeazaDauneEfective() const { return bonusDaune; }

Toiag::Toiag(int b) : Arma(b) {}
void Toiag::descriere_impl() const { std::cout << "Toiag Magic Arcanic"; }
Arma* Toiag::clone() const { return new Toiag(*this); }
int Toiag::calculeazaDauneEfective() const {
    int fluctuatie = (rand() % 7) - 3;
    int dmg = bonusDaune + fluctuatie;
    return (dmg > 0) ? dmg : 1;
}

Arc::Arc(int b) : Arma(b) {}
void Arc::descriere_impl() const { std::cout << "Arc de Precizie Elfesc"; }
Arma* Arc::clone() const { return new Arc(*this); }
int Arc::calculeazaDauneEfective() const {
    int dmg = bonusDaune;
    if (rand() % 100 < 10) { std::cout << " [HEADSHOT!] "; dmg += 10; }
    return dmg;
}

// --- Implementari Potiune ---
Potiune::Potiune(int v) : valoareEfect(v) {
    if (v <= 0) throw ConfigurareInvalida("Potiunea trebuie sa aiba un efect strict pozitiv.");
}
int Potiune::getValoare() const { return valoareEfect; }

PotiuneRegenerare::PotiuneRegenerare(int v) : Potiune(v) {}
Potiune* PotiuneRegenerare::clone() const { return new PotiuneRegenerare(*this); }
void PotiuneRegenerare::aplicaEfect(Erou* erouTarget) const {
    std::cout << " * Potiunea de regenerare vindeca " << valoareEfect << " puncte de viata!\n";
    erouTarget->primesteVindecare(valoareEfect);
}

PotiuneScut::PotiuneScut(int v) : Potiune(v) {}
Potiune* PotiuneScut::clone() const { return new PotiuneScut(*this); }
void PotiuneScut::aplicaEfect(Erou* erouTarget) const {
    std::cout << " * Potiunea ofera " << valoareEfect << " viata bonus deasupra limitelor normale!\n";
    int hpVechi = erouTarget->getHP();
    erouTarget->primesteVindecare(valoareEfect);
    if(erouTarget->getHP() == hpVechi) { erouTarget->incaseazaDaune(-valoareEfect); }
}
