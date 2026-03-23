#include "Paquete.h"
#include <iostream>

Paquete::Paquete(int id, const std::string& descripcion,
                 const std::string& destino, bool urgente)
    : id(id), descripcion(descripcion), destino(destino), urgente(urgente) {}

void Paquete::mostrar() const {
    std::cout << "  Paquete #" << id
              << " | Desc: " << descripcion
              << " | Destino: " << destino
              << " | Urgente: " << (urgente ? "Si" : "No") << "\n";
}
