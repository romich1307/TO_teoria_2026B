#ifndef MOTO_H
#define MOTO_H

#include "Vehiculo.h"

class Moto : public Vehiculo {
private:
    float tarifaPorHora;

public:
    Moto(string placa, Propietario* propietario);

    char getTipo() override;
    float calcularPago(int horas) override;
    void mostrarDatos() override;
};

#endif