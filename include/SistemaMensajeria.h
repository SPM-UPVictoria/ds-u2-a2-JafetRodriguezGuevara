#pragma once
#include "Ruta.h"
#include "GestorRutas.h"
#include "GestorPaquetes.h"

class SistemaMensajeria {
private:
    Ruta ruta;
    GestorRutas gestorRutas;
    GestorPaquetes gestorPaquetes;

    void menuRutas();
    void menuPaquetes();
    void menuCamion();
    void menuMatrices();
    void mostrarResumen() const;

    void inicializarDatosDemostracion();

    static void encabezado(const std::string& titulo);
    static void separador();
    static std::string leerLinea(const std::string& prompt);
    static int leerEntero(const std::string& prompt);
    static double leerDouble(const std::string& prompt);

public:
    SistemaMensajeria();
    void ejecutar();
};
