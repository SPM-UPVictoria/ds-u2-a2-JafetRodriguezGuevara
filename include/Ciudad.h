#pragma once
#include <string>

class Ciudad {
public:
    std::string nombre;
    int id;
    Ciudad* siguiente;

    Ciudad(const std::string& nombre, int id);
};
