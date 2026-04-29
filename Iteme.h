#pragma once
#include <iostream>
#include "Exceptii.h"

// Forward declaration: spunem compilatorului ca exista o clasa Erou care va fi definita in alt fisier
class Erou; 

// ================== IERARHIA ARMA ==================
class Arma {
protected:
    int bonusDaune;
    virtual void descriere_impl() const = 0;
public:
    explicit Arma(int bonus);
    virtual ~Arma() = default;
    virtual Arma* clone() const = 0;
    void afiseazaArma() const;
    int getBonusDaune() const;
    void adaugaBonus(int valoare);
    virtual int calculeazaDauneEfective() const;
};

class Sabie : public Arma {
protected:
    void descriere_impl() const override;
public:
    explicit Sabie(int b = 15);
    Arma* clone() const override;
    int calculeazaDauneEfective() const override;
};

class Lance : public Arma {
protected:
    void descriere_impl() const override;
public:
    explicit Lance(int b = 18);
    Arma* clone() const override;
    int calculeazaDauneEfective() const override;
};

class Toiag : public Arma {
protected:
    void descriere_impl() const override;
public:
    explicit Toiag(int b = 20);
    Arma* clone() const override;
    int calculeazaDauneEfective() const override;
};

class Arc : public Arma {
protected:
    void descriere_impl() const override;
public:
    explicit Arc(int b = 17);
    Arma* clone() const override;
    int calculeazaDauneEfective() const override;
};

// ================== IERARHIA POTIUNE ==================
class Potiune {
protected:
    int valoareEfect;
public:
    explicit Potiune(int v);
    virtual ~Potiune() = default;
    virtual Potiune* clone() const = 0;
    virtual void aplicaEfect(Erou* erouTarget) const = 0;
    int getValoare() const;
};

class PotiuneRegenerare : public Potiune {
public:
    explicit PotiuneRegenerare(int v = 40);
    Potiune* clone() const override;
    void aplicaEfect(Erou* erouTarget) const override;
};

class PotiuneScut : public Potiune {
public:
    explicit PotiuneScut(int v = 25);
    Potiune* clone() const override;
    void aplicaEfect(Erou* erouTarget) const override;
};
