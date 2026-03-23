#include "GestorPaquetes.h"
#include <iostream>

GestorPaquetes::GestorPaquetes() : contadorId(100) {}

// ---- Cola Pendientes ----

void GestorPaquetes::agregarPendiente(const std::string& desc, const std::string& destino) {
    Paquete p(contadorId++, desc, destino, false);
    colaPendientes.push(p);
    std::cout << "  [+] Paquete pendiente agregado:\n";
    p.mostrar();
}

void GestorPaquetes::procesarPendiente() {
    if (colaPendientes.empty()) {
        std::cout << "  [!] No hay paquetes pendientes en la cola.\n";
        return;
    }
    Paquete p = colaPendientes.front();
    colaPendientes.pop();
    historialProcesados.push_back(p);
    std::cout << "  [>>] Paquete pendiente procesado (FIFO):\n";
    p.mostrar();
}

void GestorPaquetes::mostrarCola() const {
    if (colaPendientes.empty()) {
        std::cout << "  Cola de pendientes vacia.\n"; return;
    }
    std::cout << "  Cola de paquetes pendientes (" << colaPendientes.size() << "):\n";
    std::queue<Paquete> tmp = colaPendientes;
    int pos = 1;
    while (!tmp.empty()) {
        std::cout << "  [" << pos++ << "] ";
        tmp.front().mostrar();
        tmp.pop();
    }
}

// ---- Pila Urgentes ----

void GestorPaquetes::agregarUrgente(const std::string& desc, const std::string& destino) {
    Paquete p(contadorId++, desc, destino, true);
    pilaUrgentes.push(p);
    std::cout << "  [+] Paquete urgente agregado:\n";
    p.mostrar();
}

void GestorPaquetes::procesarUrgente() {
    if (pilaUrgentes.empty()) {
        std::cout << "  [!] No hay paquetes urgentes en la pila.\n";
        return;
    }
    Paquete p = pilaUrgentes.top();
    pilaUrgentes.pop();
    historialProcesados.push_back(p);
    std::cout << "  [>>] Paquete urgente procesado (LIFO):\n";
    p.mostrar();
}

void GestorPaquetes::mostrarPila() const {
    if (pilaUrgentes.empty()) {
        std::cout << "  Pila de urgentes vacia.\n"; return;
    }
    std::cout << "  Pila de paquetes urgentes (" << pilaUrgentes.size() << "):\n";
    std::stack<Paquete> tmp = pilaUrgentes;
    int pos = 1;
    while (!tmp.empty()) {
        std::cout << "  [" << pos++ << "] ";
        tmp.top().mostrar();
        tmp.pop();
    }
}

// ---- Historial ----

void GestorPaquetes::mostrarHistorial() const {
    if (historialProcesados.empty()) {
        std::cout << "  Sin paquetes procesados aun.\n"; return;
    }
    std::cout << "  Historial de paquetes procesados (" << historialProcesados.size() << "):\n";
    for (size_t i = 0; i < historialProcesados.size(); i++) {
        std::cout << "  [" << (i+1) << "] ";
        historialProcesados[i].mostrar();
    }
}

int GestorPaquetes::totalPendientes() const { return colaPendientes.size(); }
int GestorPaquetes::totalUrgentes()   const { return pilaUrgentes.size(); }
