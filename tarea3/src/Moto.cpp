#include "Moto.h"
#include <iostream>

using namespace std;

Moto::Moto(string placa, Propietario* propietario)
    : Vehiculo(placa, propietario) {
    tarifaPorHora = 3.0;
}

char Moto::getTipo() {
    return 'M';
}

float Moto::calcularPago(int horas) {
    return horas * tarifaPorHora;
}

void Moto::mostrarDatos() {
    cout << "Tipo: Moto" << endl;
    cout << "Placa: " << placa << endl;
    cout << "Propietario: " << getPropietario() << endl;
    cout << "Espacio asignado: " << espacioAsignado << endl;
    cout << "Tarifa por hora: S/ " << tarifaPorHora << endl;
}