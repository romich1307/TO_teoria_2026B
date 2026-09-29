#include "Ticket.h"
#include "Vehiculo.h"

#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

Ticket::Ticket(int numero) {
    this->numero = numero;
    horaEntrada = static_cast<int>(time(nullptr));
    horaSalida = 0;
    horas = 0;
    totalPago = 0.0f;
}

int Ticket::calcularHoras() {
    if (horaSalida == 0) {
        horaSalida = static_cast<int>(time(nullptr));
    }

    int segundos = horaSalida - horaEntrada;

    if (segundos <= 0) {
        horas = 1;
        return horas;
    }

    horas = (segundos + 3599) / 3600;

    if (horas < 1) {
        horas = 1;
    }

    return horas;
}

void Ticket::calcularTotal(Vehiculo* v) {
    if (v == nullptr) {
        totalPago = 0.0f;
        return;
    }

    int horasCalculadas = calcularHoras();

    totalPago = v->calcularPago(horasCalculadas);
}

void Ticket::mostrarTicket() {
    cout << "\n========== TICKET ==========\n";
    cout << "Numero: " << numero << '\n';

    time_t entrada = static_cast<time_t>(horaEntrada);
    tm* tmEntrada = localtime(&entrada);

    if (tmEntrada != nullptr) {
        cout << "Entrada: "
             << put_time(tmEntrada, "%d/%m/%Y %I:%M %p")
             << '\n';
    }

    if (horaSalida != 0) {
        time_t salida = static_cast<time_t>(horaSalida);
        tm* tmSalida = localtime(&salida);

        if (tmSalida != nullptr) {
            cout << "Salida:  "
                 << put_time(tmSalida, "%d/%m/%Y %I:%M %p")
                 << '\n';
        }

        cout << "Horas: " << horas << '\n';

        cout << fixed << setprecision(2);
        cout << "Total: S/ " << totalPago << '\n';
    }
    else {
        cout << "Salida: pendiente\n";
    }

    cout << "============================\n";
}

int Ticket::getNumero() const {
    return numero;
}

int Ticket::getHoraEntrada() const {
    return horaEntrada;
}

int Ticket::getHoraSalida() const {
    return horaSalida;
}

int Ticket::getHoras() const {
    return horas;
}

float Ticket::getTotalPago() const {
    return totalPago;
}
