#ifndef ESTACIONAMIENTO_H
#define ESTACIONAMIENTO_H

#include "Vehiculo.h"
#include "Zona.h"

class Estacionamiento {
private:
    int filas;
    int columnas;
    int cantAutos;
    int cantMotos;
    int cantBuses;
    int totalEspacios;
    Vehiculo** espacios;
    Zona* zonas;

public:
    Estacionamiento();
    ~Estacionamiento();

    Estacionamiento(const Estacionamiento&) = delete;
    Estacionamiento& operator=(const Estacionamiento&) = delete;

    void configurar(int columnas, int cantAutos, int cantMotos, int cantBuses);
    void mostrarEstacionamiento();
    int buscarEspacio(char tipo);
    int contarDisponibles(char tipo);
    int asignarEspacio(Vehiculo* v);
    void liberarEspacio(int indice);
    bool esEspacioValido(int indice, char tipo);
    bool editarCapacidad(char tipo, int nuevaCantidad);
    Vehiculo* buscarVehiculo(string placa);
    int getCapacidad(char tipo) const;
};

#endif
