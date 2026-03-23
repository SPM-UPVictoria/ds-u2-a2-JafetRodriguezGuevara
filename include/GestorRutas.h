#pragma once
#include <string>
#include <vector>
#include <map>

// Matriz dispersa con mapa de coordenadas
struct EntradaDispersa {
    int fila;
    int col;
    double valor;
};

class GestorRutas {
private:
    // Cola circular para puntos de control del camion
    std::vector<std::string> puntosControl;
    int frente;
    int capacidadCircular;
    int conteoCircular;

    // Matriz 1D: distancias entre puntos
    std::vector<double> distancias1D;
    std::vector<std::string> etiquetas1D;

    // Matriz 2D: tiempos entre ciudades
    std::vector<std::vector<double>> tiempos2D;
    std::vector<std::string> ciudades2D;

    // Matriz dispersa: rutas prioritarias
    std::vector<EntradaDispersa> matrizDispersa;
    int dimDispersa;

public:
    GestorRutas(int capacidadCircular = 8);

    // Cola circular
    void cargarPuntoControl(const std::string& punto);
    void avanzarCamion();
    void mostrarPosicionActual() const;
    void mostrarColaCircular() const;

    // Matriz 1D
    void agregarDistancia(const std::string& etiqueta, double dist);
    void mostrarDistancias1D() const;

    // Matriz 2D
    void inicializarMatriz2D(const std::vector<std::string>& ciudades);
    void setTiempo(int i, int j, double tiempo);
    void mostrarTiempos2D() const;

    // Matriz dispersa
    void inicializarDispersa(int dim);
    void agregarRutaPrioritaria(int fila, int col, double valor);
    void mostrarDispersa() const;
};
