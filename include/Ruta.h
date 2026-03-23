#pragma once
#include "Ciudad.h"
#include <string>

class Ruta {
private:
    Ciudad* cabeza;
    int tamano;
    int contadorId;

public:
    Ruta();
    ~Ruta();

    void agregarCiudad(const std::string& nombre);
    bool eliminarPorNombre(const std::string& nombre);
    bool eliminarPorPosicion(int pos);
    void mostrarRuta() const;
    int getTamano() const;
    Ciudad* getCabeza() const;
    bool estaVacia() const;
};
