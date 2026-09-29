#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>
using namespace std;

class Propietario;

class Vehiculo {
protected:
    string placa;
    int espacioAsignado;
    Propietario* propietario;

public:
    Vehiculo(string placa, Propietario* propietario);

    string getPlaca();
    int getEspacioAsignado();
    void setEspacioAsignado(int espacio);

    string getPropietario();

    virtual char getTipo() = 0;
    virtual float calcularPago(int horas) = 0;
    virtual void mostrarDatos() = 0;

    virtual ~Vehiculo();
};

#endif