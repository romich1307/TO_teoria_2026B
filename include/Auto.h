#ifndef AUTO_H
#define AUTO_H

#include "Vehiculo.h"

class Auto : public Vehiculo {
private:
    float tarifaPorHora;

public:
    Auto(string placa, Propietario* propietario);

    char getTipo() override;
    float calcularPago(int horas) override;
    void mostrarDatos() override;
};

#endif