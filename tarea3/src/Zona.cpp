#include "Zona.h"

Zona::Zona() {
    tipo = '\0';
    cantidadEspacios = 0;
    inicio = 0;
    fin = -1;
}

Zona::Zona(char tipo, int cantidadEspacios, int inicio) {
    this->tipo = tipo;
    this->cantidadEspacios = 0;
    this->inicio = 0;
    fin = -1;
    actualizarRango(cantidadEspacios, inicio);
}

char Zona::getTipo() const {
    return tipo;
}

int Zona::getCantidadEspacios() const {
    return cantidadEspacios;
}

int Zona::getInicio() const {
    return inicio;
}

int Zona::getFin() const {
    return fin;
}

bool Zona::esIndiceValido(int indice) {
    return cantidadEspacios > 0 && indice >= inicio && indice <= fin;
}

void Zona::actualizarRango(int cantidad, int inicio) {
    if (cantidad < 0 || inicio < 0) {
        return;
    }

    this->cantidadEspacios = cantidad;
    this->inicio = inicio;
    fin = inicio + (this->cantidadEspacios - 1);
}