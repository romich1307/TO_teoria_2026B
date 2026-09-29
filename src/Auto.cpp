#include "Auto.h"
#include <iostream>

using namespace std;

Auto::Auto(string placa, Propietario* propietario)
    : Vehiculo(placa, propietario) {
    tarifaPorHora = 5.0;
}

char Auto::getTipo() {
    return 'A';
}

float Auto::calcularPago(int horas) {
    return horas * tarifaPorHora;
}

void Auto::mostrarDatos() {
    cout << "Tipo: Auto" << endl;
    cout << "Placa: " << placa << endl;
    cout << "Propietario: " << getPropietario() << endl;
    cout << "Espacio asignado: " << espacioAsignado << endl;
    cout << "Tarifa por hora: S/ " << tarifaPorHora << endl;
}