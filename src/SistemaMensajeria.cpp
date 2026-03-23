#include "SistemaMensajeria.h"
#include <iostream>
#include <limits>
#include <string>

// ---- Helpers estáticos ----

void SistemaMensajeria::encabezado(const std::string& titulo) {
    std::cout << "\n============================================\n";
    std::cout << "  " << titulo << "\n";
    std::cout << "============================================\n";
}

void SistemaMensajeria::separador() {
    std::cout << "--------------------------------------------\n";
}

std::string SistemaMensajeria::leerLinea(const std::string& prompt) {
    std::cout << prompt;
    std::string val;
    std::getline(std::cin, val);
    return val;
}

int SistemaMensajeria::leerEntero(const std::string& prompt) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [!] Entrada invalida. Intente de nuevo.\n";
    }
}

double SistemaMensajeria::leerDouble(const std::string& prompt) {
    double val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [!] Entrada invalida. Intente de nuevo.\n";
    }
}

// ---- Constructor ----

SistemaMensajeria::SistemaMensajeria() : gestorRutas(8) {
    inicializarDatosDemostracion();
}

void SistemaMensajeria::inicializarDatosDemostracion() {
    // Ciudades predefinidas en ruta
    ruta.agregarCiudad("Ciudad Victoria");
    ruta.agregarCiudad("Monterrey");
    ruta.agregarCiudad("Saltillo");
    ruta.agregarCiudad("Reynosa");

    // Puntos de control
    gestorRutas.cargarPuntoControl("Bodega Central");
    gestorRutas.cargarPuntoControl("Distribuidor Norte");
    gestorRutas.cargarPuntoControl("Zona Industrial");
    gestorRutas.cargarPuntoControl("Terminal Sur");

    // Matriz 1D
    gestorRutas.agregarDistancia("Victoria-Monterrey", 220.5);
    gestorRutas.agregarDistancia("Monterrey-Saltillo", 86.0);
    gestorRutas.agregarDistancia("Saltillo-Reynosa", 310.0);
    gestorRutas.agregarDistancia("Victoria-Reynosa", 190.0);

    // Matriz 2D
    gestorRutas.inicializarMatriz2D({"Victoria", "Monterrey", "Saltillo", "Reynosa"});
    gestorRutas.setTiempo(0, 1, 2.5);
    gestorRutas.setTiempo(0, 2, 3.8);
    gestorRutas.setTiempo(0, 3, 2.0);
    gestorRutas.setTiempo(1, 2, 1.0);
    gestorRutas.setTiempo(1, 3, 3.5);
    gestorRutas.setTiempo(2, 3, 4.0);

    // Matriz dispersa
    gestorRutas.inicializarDispersa(5);
    gestorRutas.agregarRutaPrioritaria(0, 2, 9.5);
    gestorRutas.agregarRutaPrioritaria(1, 4, 7.0);
    gestorRutas.agregarRutaPrioritaria(3, 3, 8.2);

    // Paquetes de prueba
    gestorPaquetes.agregarPendiente("Electrodomestico grande", "Monterrey");
    gestorPaquetes.agregarPendiente("Ropa y textiles", "Saltillo");
    gestorPaquetes.agregarUrgente("Medicamentos refrigerados", "Reynosa");

    std::cout << "\n  [Sistema listo con datos de demostracion.]\n";
}

// ---- Menú Rutas ----

void SistemaMensajeria::menuRutas() {
    bool salir = false;
    while (!salir) {
        encabezado("GESTION DE RUTAS (Lista Enlazada)");
        std::cout << "  1. Agregar ciudad al final\n";
        std::cout << "  2. Eliminar ciudad por nombre\n";
        std::cout << "  3. Eliminar ciudad por posicion\n";
        std::cout << "  4. Mostrar ruta completa\n";
        std::cout << "  0. Regresar\n";
        separador();
        int op = leerEntero("  Opcion: ");
        switch (op) {
            case 1: {
                std::string nombre = leerLinea("  Nombre de ciudad: ");
                ruta.agregarCiudad(nombre);
                break;
            }
            case 2: {
                std::string nombre = leerLinea("  Nombre a eliminar: ");
                if (ruta.eliminarPorNombre(nombre))
                    std::cout << "  [OK] Ciudad '" << nombre << "' eliminada.\n";
                else
                    std::cout << "  [!] Ciudad no encontrada.\n";
                break;
            }
            case 3: {
                int pos = leerEntero("  Posicion a eliminar (1 = primero): ");
                if (ruta.eliminarPorPosicion(pos))
                    std::cout << "  [OK] Ciudad en posicion " << pos << " eliminada.\n";
                else
                    std::cout << "  [!] Posicion invalida.\n";
                break;
            }
            case 4:
                ruta.mostrarRuta();
                break;
            case 0:
                salir = true;
                break;
            default:
                std::cout << "  [!] Opcion invalida.\n";
        }
    }
}

// ---- Menú Paquetes ----

void SistemaMensajeria::menuPaquetes() {
    bool salir = false;
    while (!salir) {
        encabezado("GESTION DE PAQUETES");
        std::cout << "  --- Cola (Pendientes - FIFO) ---\n";
        std::cout << "  1. Agregar paquete pendiente\n";
        std::cout << "  2. Procesar paquete pendiente\n";
        std::cout << "  3. Ver cola de pendientes\n";
        std::cout << "  --- Pila (Urgentes - LIFO) ---\n";
        std::cout << "  4. Agregar paquete urgente\n";
        std::cout << "  5. Procesar paquete urgente\n";
        std::cout << "  6. Ver pila de urgentes\n";
        std::cout << "  7. Ver historial de procesados\n";
        std::cout << "  0. Regresar\n";
        separador();
        int op = leerEntero("  Opcion: ");
        switch (op) {
            case 1: {
                std::string desc = leerLinea("  Descripcion: ");
                std::string dest = leerLinea("  Destino: ");
                gestorPaquetes.agregarPendiente(desc, dest);
                break;
            }
            case 2: gestorPaquetes.procesarPendiente(); break;
            case 3: gestorPaquetes.mostrarCola(); break;
            case 4: {
                std::string desc = leerLinea("  Descripcion (urgente): ");
                std::string dest = leerLinea("  Destino: ");
                gestorPaquetes.agregarUrgente(desc, dest);
                break;
            }
            case 5: gestorPaquetes.procesarUrgente(); break;
            case 6: gestorPaquetes.mostrarPila(); break;
            case 7: gestorPaquetes.mostrarHistorial(); break;
            case 0: salir = true; break;
            default: std::cout << "  [!] Opcion invalida.\n";
        }
    }
}

// ---- Menú Camión ----

void SistemaMensajeria::menuCamion() {
    bool salir = false;
    while (!salir) {
        encabezado("SIMULACION CAMION (Cola Circular)");
        std::cout << "  1. Cargar punto de control\n";
        std::cout << "  2. Avanzar camion\n";
        std::cout << "  3. Mostrar posicion actual\n";
        std::cout << "  4. Mostrar toda la cola circular\n";
        std::cout << "  0. Regresar\n";
        separador();
        int op = leerEntero("  Opcion: ");
        switch (op) {
            case 1: {
                std::string p = leerLinea("  Nombre del punto: ");
                gestorRutas.cargarPuntoControl(p);
                break;
            }
            case 2: gestorRutas.avanzarCamion(); break;
            case 3: gestorRutas.mostrarPosicionActual(); break;
            case 4: gestorRutas.mostrarColaCircular(); break;
            case 0: salir = true; break;
            default: std::cout << "  [!] Opcion invalida.\n";
        }
    }
}

// ---- Menú Matrices ----

void SistemaMensajeria::menuMatrices() {
    bool salir = false;
    while (!salir) {
        encabezado("MANEJO DE MATRICES");
        std::cout << "  1. Ver matriz 1D (distancias)\n";
        std::cout << "  2. Agregar distancia a matriz 1D\n";
        std::cout << "  3. Ver matriz 2D (tiempos)\n";
        std::cout << "  4. Agregar tiempo a matriz 2D\n";
        std::cout << "  5. Ver matriz dispersa (rutas prioritarias)\n";
        std::cout << "  6. Agregar ruta prioritaria\n";
        std::cout << "  0. Regresar\n";
        separador();
        int op = leerEntero("  Opcion: ");
        switch (op) {
            case 1: gestorRutas.mostrarDistancias1D(); break;
            case 2: {
                std::string etq = leerLinea("  Etiqueta (ej. 'CiudadA-CiudadB'): ");
                double dist = leerDouble("  Distancia (km): ");
                gestorRutas.agregarDistancia(etq, dist);
                break;
            }
            case 3: gestorRutas.mostrarTiempos2D(); break;
            case 4: {
                int i = leerEntero("  Fila (indice ciudad origen): ");
                int j = leerEntero("  Col (indice ciudad destino): ");
                double t = leerDouble("  Tiempo (horas): ");
                gestorRutas.setTiempo(i, j, t);
                break;
            }
            case 5: gestorRutas.mostrarDispersa(); break;
            case 6: {
                int f = leerEntero("  Fila: ");
                int c = leerEntero("  Columna: ");
                double v = leerDouble("  Valor de prioridad: ");
                gestorRutas.agregarRutaPrioritaria(f, c, v);
                break;
            }
            case 0: salir = true; break;
            default: std::cout << "  [!] Opcion invalida.\n";
        }
    }
}

// ---- Resumen General ----

void SistemaMensajeria::mostrarResumen() const {
    encabezado("RESUMEN GENERAL DEL SISTEMA");
    std::cout << "\n--- RUTA ACTUAL ---\n";
    ruta.mostrarRuta();
    std::cout << "  Total ciudades: " << ruta.getTamano() << "\n";

    std::cout << "\n--- PAQUETES ---\n";
    std::cout << "  Pendientes en cola: " << gestorPaquetes.totalPendientes() << "\n";
    std::cout << "  Urgentes en pila:   " << gestorPaquetes.totalUrgentes() << "\n";
    gestorPaquetes.mostrarCola();
    gestorPaquetes.mostrarPila();

    std::cout << "\n--- CAMION ---\n";
    gestorRutas.mostrarPosicionActual();
    gestorRutas.mostrarColaCircular();

    std::cout << "\n--- MATRICES ---\n";
    gestorRutas.mostrarDistancias1D();
    gestorRutas.mostrarTiempos2D();
    gestorRutas.mostrarDispersa();
}

// ---- Menú Principal ----

void SistemaMensajeria::ejecutar() {
    encabezado("SISTEMA DE MENSAJERIA v1.0");
    std::cout << "  Empresa de Mensajeria Regional\n";
    std::cout << "  Gestion de Rutas y Paquetes\n";

    bool salir = false;
    while (!salir) {
        encabezado("MENU PRINCIPAL");
        std::cout << "  1. Gestion de Rutas (Lista Enlazada)\n";
        std::cout << "  2. Gestion de Paquetes (Cola / Pila)\n";
        std::cout << "  3. Simulacion del Camion (Cola Circular)\n";
        std::cout << "  4. Manejo de Matrices\n";
        std::cout << "  5. Resumen General\n";
        std::cout << "  0. Salir\n";
        separador();
        int op = leerEntero("  Opcion: ");
        switch (op) {
            case 1: menuRutas(); break;
            case 2: menuPaquetes(); break;
            case 3: menuCamion(); break;
            case 4: menuMatrices(); break;
            case 5: mostrarResumen(); break;
            case 0:
                std::cout << "\n  Hasta luego. Sistema cerrado.\n\n";
                salir = true;
                break;
            default:
                std::cout << "  [!] Opcion invalida.\n";
        }
    }
}
