#ifndef TICKET_H
#define TICKET_H

class Vehiculo;

class Ticket {
private:
    int numero;
    int horaEntrada;
    int horaSalida;
    int horas;
    float totalPago;

public:
    Ticket(int numero);

    int calcularHoras();
    void calcularTotal(Vehiculo* v);
    void mostrarTicket();

    int getNumero() const;
    int getHoraEntrada() const;
    int getHoraSalida() const;
    int getHoras() const;
    float getTotalPago() const;
};

#endif
