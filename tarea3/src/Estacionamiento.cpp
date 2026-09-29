#include "Estacionamiento.h"
#include <iostream>

using namespace std;

Estacionamiento::Estacionamiento() {
    filas = 0;
    columnas = 0;
    cantAutos = 0;
    cantMotos = 0;
    cantBuses = 0;
    totalEspacios = 0;
    espacios = nullptr;
    zonas = nullptr;
}

Estacionamiento::~Estacionamiento() {
    delete[] espacios;
    delete[] zonas;
}

void Estacionamiento::configurar(int columnas, int cantAutos, int cantMotos, int cantBuses) {
    if (columnas <= 0 || cantAutos < 0 || cantMotos < 0 || cantBuses < 0) {
        cout << "Configuracion invalida." << endl;
        return;
    }

    int total = cantAutos + cantMotos + cantBuses;

    for (int i = 0; i < totalEspacios; i++) {
        if (espacios[i] != nullptr) {
            cout << "Para reconfigurar, el estacionamiento debe estar vacio." << endl;
            return;
        }
    }

    Zona* nuevasZonas = new Zona[3];
    nuevasZonas[0] = Zona('A', cantAutos, 0);
    nuevasZonas[1] = Zona('M', cantMotos, cantAutos);
    nuevasZonas[2] = Zona('B', cantBuses, cantAutos + cantMotos);
    Vehiculo** nuevosEspacios = new Vehiculo*[total]{};

    delete[] espacios;
    delete[] zonas;
    espacios = nuevosEspacios;
    zonas = nuevasZonas;
    this->columnas = columnas;
    this->cantAutos = cantAutos;
    this->cantMotos = cantMotos;
    this->cantBuses = cantBuses;
    totalEspacios = total;
    filas = totalEspacios / columnas;
    if (totalEspacios % columnas != 0) {
        filas++;
    }
}

void Estacionamiento::mostrarEstacionamiento() {
    if (totalEspacios == 0) {
        cout << "No hay espacios configurados." << endl;
        return;
    }

    cout << "Espacios (numero:tipo, - libre)" << endl;
    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            int indice = fila * columnas + columna;
            if (indice >= totalEspacios) {
                break;
            }

            char estado = '-';
            if (espacios[indice] != nullptr) {
                estado = espacios[indice]->getTipo();
            }
            cout << "[" << indice + 1 << ":" << estado << "] ";
        }
        cout << endl;
    }
}

int Estacionamiento::buscarEspacio(char tipo) {
    if (zonas == nullptr) {
        return -1;
    }

    for (int i = 0; i < 3; i++) {
        if (zonas[i].getTipo() == tipo) {
            for (int j = zonas[i].getInicio(); j <= zonas[i].getFin(); j++) {
                if (espacios[j] == nullptr) {
                    return j;
                }
            }
        }
    }
    return -1;
}

int Estacionamiento::contarDisponibles(char tipo) {
    int disponibles = 0;
    if (zonas == nullptr) {
        return disponibles;
    }

    for (int i = 0; i < 3; i++) {
        if (zonas[i].getTipo() == tipo) {
            for (int j = zonas[i].getInicio(); j <= zonas[i].getFin(); j++) {
                if (espacios[j] == nullptr) {
                    disponibles++;
                }
            }
        }
    }
    return disponibles;
}

int Estacionamiento::asignarEspacio(Vehiculo* v) {
    if (v == nullptr || buscarVehiculo(v->getPlaca()) != nullptr) {
        return -1;
    }

    int indice = buscarEspacio(v->getTipo());
    if (indice != -1) {
        espacios[indice] = v;
        v->setEspacioAsignado(indice);
    }
    return indice;
}

void Estacionamiento::liberarEspacio(int indice) {
    if (indice < 0 || indice >= totalEspacios || espacios[indice] == nullptr) {
        return;
    }

    espacios[indice]->setEspacioAsignado(-1);
    espacios[indice] = nullptr;
}

bool Estacionamiento::esEspacioValido(int indice, char tipo) {
    if (zonas == nullptr || indice < 0 || indice >= totalEspacios) {
        return false;
    }

    for (int i = 0; i < 3; i++) {
        if (zonas[i].getTipo() == tipo) {
            return zonas[i].esIndiceValido(indice);
        }
    }
    return false;
}

bool Estacionamiento::editarCapacidad(char tipo, int nuevaCantidad) {
    if (zonas == nullptr || nuevaCantidad < 0) {
        return false;
    }

    int zonaElegida = -1;
    int cantidades[3] = {cantAutos, cantMotos, cantBuses};
    for (int i = 0; i < 3; i++) {
        if (zonas[i].getTipo() == tipo) {
            zonaElegida = i;
        }
    }
    if (zonaElegida == -1) {
        return false;
    }
    if (nuevaCantidad == cantidades[zonaElegida]) {
        return true;
    }

    if (nuevaCantidad < cantidades[zonaElegida]) {
        int primerEliminado = zonas[zonaElegida].getInicio() + nuevaCantidad;
        for (int i = primerEliminado; i <= zonas[zonaElegida].getFin(); i++) {
            if (espacios[i] != nullptr) {
                return false;
            }
        }
    }

    cantidades[zonaElegida] = nuevaCantidad;
    int nuevoTotal = cantidades[0] + cantidades[1] + cantidades[2];
    Vehiculo** nuevosEspacios = new Vehiculo*[nuevoTotal]{};

    int nuevoInicio = 0;
    for (int i = 0; i < 3; i++) {
        int anteriorInicio = zonas[i].getInicio();
        int anteriorCantidad = zonas[i].getCantidadEspacios();

        for (int j = 0; j < anteriorCantidad && j < cantidades[i]; j++) {
            nuevosEspacios[nuevoInicio + j] = espacios[anteriorInicio + j];
            if (nuevosEspacios[nuevoInicio + j] != nullptr) {
                nuevosEspacios[nuevoInicio + j]->setEspacioAsignado(nuevoInicio + j);
            }
        }

        zonas[i].actualizarRango(cantidades[i], nuevoInicio);
        nuevoInicio += cantidades[i];
    }

    delete[] espacios;
    espacios = nuevosEspacios;
    cantAutos = cantidades[0];
    cantMotos = cantidades[1];
    cantBuses = cantidades[2];
    totalEspacios = nuevoTotal;
    filas = totalEspacios / columnas;
    if (totalEspacios % columnas != 0) {
        filas++;
    }
    return true;
}

Vehiculo* Estacionamiento::buscarVehiculo(string placa) {
    for (int i = 0; i < totalEspacios; i++) {
        if (espacios[i] != nullptr && espacios[i]->getPlaca() == placa) {
            return espacios[i];
        }
    }
    return nullptr;
}

int Estacionamiento::getCapacidad(char tipo) const {
    if (zonas != nullptr) {
        for (int i = 0; i < 3; i++) {
            if (zonas[i].getTipo() == tipo) {
                return zonas[i].getCantidadEspacios();
            }
        }
    }
    return 0;
}
