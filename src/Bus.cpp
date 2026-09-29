#include "Bus.h"
#include <iostream>

using namespace std;

Bus::Bus(string placa, Propietario* propietario)
    : Vehiculo(placa, propietario) {
    tarifaPorHora = 10.0;
}

char Bus::getTipo() {
    return 'B';
}

float Bus::calcularPago(int horas) {
    return horas * tarifaPorHora;
}

void Bus::mostrarDatos() {
    cout << "Tipo: Bus" << endl;
    cout << "Placa: " << placa << endl;
    cout << "Propietario: " << getPropietario() << endl;
    cout << "Espacio asignado: " << espacioAsignado << endl;
    cout << "Tarifa por hora: S/ " << tarifaPorHora << endl;
}