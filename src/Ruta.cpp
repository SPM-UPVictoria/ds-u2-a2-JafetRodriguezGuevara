#include "Ruta.h"
#include <iostream>

Ruta::Ruta() : cabeza(nullptr), tamano(0), contadorId(1) {}

Ruta::~Ruta() {
    Ciudad* actual = cabeza;
    while (actual != nullptr) {
        Ciudad* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void Ruta::agregarCiudad(const std::string& nombre) {
    Ciudad* nueva = new Ciudad(nombre, contadorId++);
    if (cabeza == nullptr) {
        cabeza = nueva;
    } else {
        Ciudad* actual = cabeza;
        while (actual->siguiente != nullptr)
            actual = actual->siguiente;
        actual->siguiente = nueva;
    }
    tamano++;
    std::cout << "  [+] Ciudad '" << nombre << "' agregada a la ruta.\n";
}

bool Ruta::eliminarPorNombre(const std::string& nombre) {
    if (!cabeza) return false;
    if (cabeza->nombre == nombre) {
        Ciudad* tmp = cabeza;
        cabeza = cabeza->siguiente;
        delete tmp;
        tamano--;
        return true;
    }
    Ciudad* actual = cabeza;
    while (actual->siguiente && actual->siguiente->nombre != nombre)
        actual = actual->siguiente;
    if (!actual->siguiente) return false;
    Ciudad* tmp = actual->siguiente;
    actual->siguiente = tmp->siguiente;
    delete tmp;
    tamano--;
    return true;
}

bool Ruta::eliminarPorPosicion(int pos) {
    if (pos < 1 || pos > tamano) return false;
    if (pos == 1) {
        Ciudad* tmp = cabeza;
        cabeza = cabeza->siguiente;
        delete tmp;
        tamano--;
        return true;
    }
    Ciudad* actual = cabeza;
    for (int i = 1; i < pos - 1; i++)
        actual = actual->siguiente;
    Ciudad* tmp = actual->siguiente;
    actual->siguiente = tmp->siguiente;
    delete tmp;
    tamano--;
    return true;
}

void Ruta::mostrarRuta() const {
    if (!cabeza) {
        std::cout << "  La ruta esta vacia.\n";
        return;
    }
    Ciudad* actual = cabeza;
    int pos = 1;
    while (actual) {
        std::cout << "  [" << pos++ << "] ID:" << actual->id
                  << " - " << actual->nombre;
        if (actual->siguiente) std::cout << " --> ";
        actual = actual->siguiente;
    }
    std::cout << "\n";
}

int Ruta::getTamano() const { return tamano; }
Ciudad* Ruta::getCabeza() const { return cabeza; }
bool Ruta::estaVacia() const { return cabeza == nullptr; }
