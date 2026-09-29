#ifndef BUS_H
#define BUS_H

#include "Vehiculo.h"

class Bus : public Vehiculo {
private:
    float tarifaPorHora;

public:
    Bus(string placa, Propietario* propietario);

    char getTipo() override;
    float calcularPago(int horas) override;
    void mostrarDatos() override;
};

#endif