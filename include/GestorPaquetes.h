#pragma once
#include "Paquete.h"
#include <queue>
#include <stack>
#include <vector>

class GestorPaquetes {
private:
    std::queue<Paquete> colaPendientes;   // FIFO
    std::stack<Paquete> pilaUrgentes;     // LIFO
    int contadorId;
    std::vector<Paquete> historialProcesados;

public:
    GestorPaquetes();

    // Cola (pendientes)
    void agregarPendiente(const std::string& desc, const std::string& destino);
    void procesarPendiente();
    void mostrarCola() const;

    // Pila (urgentes)
    void agregarUrgente(const std::string& desc, const std::string& destino);
    void procesarUrgente();
    void mostrarPila() const;

    // Historial
    void mostrarHistorial() const;
    int totalPendientes() const;
    int totalUrgentes() const;
};
