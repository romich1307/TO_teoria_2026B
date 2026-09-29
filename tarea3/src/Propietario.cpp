#include "Propietario.h"

Propietario::Propietario(string nombre, string dni) {
    this->nombre = nombre;
    this->dni = dni;
}

string Propietario::getNombre() {
    return nombre;
}

string Propietario::getDni() {
    return dni;
}