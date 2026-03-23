#pragma once
#include <string>

class Paquete {
public:
    int id;
    std::string descripcion;
    std::string destino;
    bool urgente;

    Paquete(int id, const std::string& descripcion,
            const std::string& destino, bool urgente = false);
    void mostrar() const;
};
