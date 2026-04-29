#include <iostream>
#include "ManagerJoc.h"
#include "Personaje.h" // Pentru a vedea Entitate::obtineNumarEntitati()

int main() {
    try {
        std::cout << "========================================================\n";
        std::cout << "          BINE ATI VENIT LA RPG-ENGINE v3.0\n";
        std::cout << "========================================================\n";

        ManagerJoc rpgEngine;
        rpgEngine.ruleazaJocul();

        std::cout << "\n[MONITOR MEMORIE STATICA] Entitati active ramase in sistem: "
                  << Entitate::obtineNumarEntitati() << "\n";

    } catch (const std::exception& e) {
        std::cerr << "\n>>> FATAL CRASH: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "\n>>> FATAL CRASH: Tip de exceptie neidentificat!\n";
    }

    return 0;
}
