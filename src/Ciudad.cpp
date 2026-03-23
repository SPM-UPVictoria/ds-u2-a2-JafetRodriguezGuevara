#include "Ciudad.h"

Ciudad::Ciudad(const std::string& nombre, int id)
    : nombre(nombre), id(id), siguiente(nullptr) {}
