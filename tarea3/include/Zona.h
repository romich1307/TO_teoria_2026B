#ifndef ZONA_H
#define ZONA_H

class Zona {
private:
    char tipo;
    int cantidadEspacios;
    int inicio;
    int fin;

public:
    Zona();
    Zona(char tipo, int cantidadEspacios, int inicio);

    char getTipo() const;
    int getCantidadEspacios() const;
    int getInicio() const;
    int getFin() const;
    bool esIndiceValido(int indice);
    void actualizarRango(int cantidad, int inicio);
};

#endif