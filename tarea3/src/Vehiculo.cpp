#include "Vehiculo.h"
#include "Propietario.h"

Vehiculo::Vehiculo(string placa, Propietario* propietario) {
    this->placa = placa;
    this->espacioAsignado = -1;
    this->propietario = propietario;
}

string Vehiculo::getPlaca() {
    return placa;
}

int Vehiculo::getEspacioAsignado() {
    return espacioAsignado;
}

void Vehiculo::setEspacioAsignado(int espacio) {
    espacioAsignado = espacio;
}

string Vehiculo::getPropietario() {
    return propietario->getNombre();
}

Vehiculo::~Vehiculo() {
}