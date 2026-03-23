#include "GestorRutas.h"
#include <iostream>
#include <iomanip>

GestorRutas::GestorRutas(int cap)
    : frente(0), capacidadCircular(cap), conteoCircular(0), dimDispersa(0) {
    puntosControl.resize(cap, "");
}

// ---- Cola Circular ----

void GestorRutas::cargarPuntoControl(const std::string& punto) {
    if (conteoCircular >= capacidadCircular) {
        std::cout << "  [!] Cola circular llena. Capacidad: " << capacidadCircular << "\n";
        return;
    }
    int pos = (frente + conteoCircular) % capacidadCircular;
    puntosControl[pos] = punto;
    conteoCircular++;
    std::cout << "  [+] Punto de control '" << punto << "' cargado.\n";
}

void GestorRutas::avanzarCamion() {
    if (conteoCircular == 0) {
        std::cout << "  [!] No hay puntos de control cargados.\n";
        return;
    }
    std::string actual = puntosControl[frente];
    std::cout << "  [>>] Camion avanza desde: " << actual << "\n";
    frente = (frente + 1) % capacidadCircular;
    // Re-encolar al final (circular continuo)
    int pos = (frente + conteoCircular - 1) % capacidadCircular;
    puntosControl[pos] = actual;
    std::cout << "  [>>] Camion ahora en: " << puntosControl[frente] << "\n";
}

void GestorRutas::mostrarPosicionActual() const {
    if (conteoCircular == 0) {
        std::cout << "  Sin puntos de control.\n";
        return;
    }
    std::cout << "  Posicion actual del camion: " << puntosControl[frente] << "\n";
}

void GestorRutas::mostrarColaCircular() const {
    if (conteoCircular == 0) {
        std::cout << "  Cola circular vacia.\n";
        return;
    }
    std::cout << "  Puntos de control (orden circular):\n  ";
    for (int i = 0; i < conteoCircular; i++) {
        int idx = (frente + i) % capacidadCircular;
        std::cout << "[" << puntosControl[idx] << "]";
        if (i < conteoCircular - 1) std::cout << " -> ";
    }
    std::cout << " (circular)\n";
}

// ---- Matriz 1D ----

void GestorRutas::agregarDistancia(const std::string& etiqueta, double dist) {
    etiquetas1D.push_back(etiqueta);
    distancias1D.push_back(dist);
    std::cout << "  [+] Distancia '" << etiqueta << "': " << dist << " km\n";
}

void GestorRutas::mostrarDistancias1D() const {
    if (distancias1D.empty()) { std::cout << "  Sin datos en matriz 1D.\n"; return; }
    std::cout << "  Matriz 1D - Distancias:\n";
    for (size_t i = 0; i < distancias1D.size(); i++) {
        std::cout << "  [" << i << "] " << etiquetas1D[i]
                  << ": " << distancias1D[i] << " km\n";
    }
}

// ---- Matriz 2D ----

void GestorRutas::inicializarMatriz2D(const std::vector<std::string>& ciudades) {
    ciudades2D = ciudades;
    int n = ciudades.size();
    tiempos2D.assign(n, std::vector<double>(n, 0.0));
    std::cout << "  [+] Matriz 2D inicializada para " << n << " ciudades.\n";
}

void GestorRutas::setTiempo(int i, int j, double tiempo) {
    if (i < 0 || j < 0 || i >= (int)ciudades2D.size() || j >= (int)ciudades2D.size()) {
        std::cout << "  [!] Indices fuera de rango.\n"; return;
    }
    tiempos2D[i][j] = tiempo;
    tiempos2D[j][i] = tiempo;
}

void GestorRutas::mostrarTiempos2D() const {
    if (ciudades2D.empty()) { std::cout << "  Sin datos en matriz 2D.\n"; return; }
    int n = ciudades2D.size();
    std::cout << "  Matriz 2D - Tiempos (horas):\n";
    std::cout << std::setw(14) << " ";
    for (auto& c : ciudades2D) std::cout << std::setw(12) << c;
    std::cout << "\n";
    for (int i = 0; i < n; i++) {
        std::cout << std::setw(14) << ciudades2D[i];
        for (int j = 0; j < n; j++)
            std::cout << std::setw(12) << tiempos2D[i][j];
        std::cout << "\n";
    }
}

// ---- Matriz Dispersa ----

void GestorRutas::inicializarDispersa(int dim) {
    dimDispersa = dim;
    matrizDispersa.clear();
    std::cout << "  [+] Matriz dispersa " << dim << "x" << dim << " inicializada.\n";
}

void GestorRutas::agregarRutaPrioritaria(int fila, int col, double valor) {
    if (fila < 0 || col < 0 || fila >= dimDispersa || col >= dimDispersa) {
        std::cout << "  [!] Indices fuera de rango de la matriz dispersa.\n"; return;
    }
    for (auto& e : matrizDispersa) {
        if (e.fila == fila && e.col == col) { e.valor = valor; return; }
    }
    matrizDispersa.push_back({fila, col, valor});
    std::cout << "  [+] Ruta prioritaria [" << fila << "][" << col << "] = " << valor << "\n";
}

void GestorRutas::mostrarDispersa() const {
    if (matrizDispersa.empty()) { std::cout << "  Sin entradas en matriz dispersa.\n"; return; }
    std::cout << "  Matriz Dispersa (rutas prioritarias, dim " << dimDispersa << "x" << dimDispersa << "):\n";
    std::cout << "  Entradas no nulas:\n";
    for (auto& e : matrizDispersa)
        std::cout << "    [" << e.fila << "][" << e.col << "] = " << e.valor << "\n";
    std::cout << "  Total entradas: " << matrizDispersa.size()
              << " de " << dimDispersa * dimDispersa << " posibles.\n";
}
