#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include <string>
using namespace std;

class Propietario {
private:
    string nombre;
    string dni;

public:
    Propietario(string nombre, string dni);

    string getNombre();
    string getDni();
};

#endif