#ifndef SISTEMAPLAYA_H
#define SISTEMAPLAYA_H

#include "Estacionamiento.h"
#include "Ticket.h"
#include <string>

using namespace std;

class Propietario;

class SistemaPlaya {
private:
    Estacionamiento estacionamiento;

    Ticket** tickets;
    Vehiculo** vehiculos;
    Propietario** propietarios;

    bool* activos;
    int* espaciosEntrada;

    int cantidadTickets;
    int capacidadTickets;
    int siguienteNumero;

    void ampliarCapacidad();

    int buscarTicketActivoPorPlaca(
        const string& placa
    ) const;

    string nombreTipo(char tipo) const;

    void mostrarFechaHora(int tiempo) const;

public:
    SistemaPlaya();
    ~SistemaPlaya();

    SistemaPlaya(const SistemaPlaya&) = delete;

    SistemaPlaya& operator=(
        const SistemaPlaya&
    ) = delete;

    void configurarEstacionamiento();

    void ingresarVehiculo();

    void retirarVehiculo();

    void mostrarEstacionamiento();

    void emitirTicket();

    int buscarTicket(int numero) const;

    void mostrarHistorial();
	
    void configurarCapacidad();

    void menu();
};

#endif
