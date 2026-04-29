#pragma once
#include <string>
#include <iostream>
#include <utility>
#include "Exceptii.h"
#include "Iteme.h"

// ================== CLASA ENTITATE ==================
class Entitate {
protected:
    std::string nume;
    int hpCurent;
    int hpMaxim;
    int dauneBaza;
    static int contorEntitati;
    virtual void afisare_identitate() const = 0;

public:
    Entitate(std::string n, int h, int d);
    virtual ~Entitate();

    bool esteViu() const;
    std::string getNume() const;
    int getHP() const;
    int getHPMax() const;
    int getDauneBaza() const;

    virtual void incaseazaDaune(int daune);
    void primesteVindecare(int vindecare);
    void afiseazaStatusCard() const;

    static int obtineNumarEntitati();
};

// ================== CLASA EROU ==================
class Erou : public Entitate {
protected:
    Arma* armaEchipata;

public:
    Erou(std::string n, int h, int d);
    virtual ~Erou();
    Erou(const Erou& other);
    Erou& operator=(const Erou& other);

    void atribuieArma(const Arma& nouaArma);
    Arma* getArma() const;
    int calculeazaFortaTotala() const;
    void afisareCompleta() const;
};

// ================== EROI PARTICULARI ==================
class Cavaler : public Erou {
protected:
    void afisare_identitate() const override;
public:
    explicit Cavaler(std::string n);
};

class Print : public Erou {
protected:
    void afisare_identitate() const override;
public:
    explicit Print(std::string n);
};

class Arcas : public Erou {
protected:
    void afisare_identitate() const override;
public:
    explicit Arcas(std::string n);
};

class Magician : public Erou {
protected:
    void afisare_identitate() const override;
public:
    explicit Magician(std::string n);
};

// ================== CLASA INAMIC ==================
class Inamic : public Entitate {
protected:
    void afisare_identitate() const override;
public:
    Inamic(std::string n, int h, int d);
};
