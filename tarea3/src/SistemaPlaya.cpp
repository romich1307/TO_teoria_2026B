#include "SistemaPlaya.h"

#include "Auto.h"
#include "Bus.h"
#include "Moto.h"
#include "Propietario.h"

#include <cctype>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

SistemaPlaya::SistemaPlaya() {
    capacidadTickets = 10;
    cantidadTickets = 0;
    siguienteNumero = 1;

    tickets = new Ticket*[capacidadTickets]{};
    vehiculos = new Vehiculo*[capacidadTickets]{};
    propietarios = new Propietario*[capacidadTickets]{};
    activos = new bool[capacidadTickets]{};
    espaciosEntrada = new int[capacidadTickets]{};
}

SistemaPlaya::~SistemaPlaya() {
    for (int i = 0; i < cantidadTickets; i++) {
        delete tickets[i];
        delete vehiculos[i];
        delete propietarios[i];
    }

    delete[] tickets;
    delete[] vehiculos;
    delete[] propietarios;
    delete[] activos;
    delete[] espaciosEntrada;
}

void SistemaPlaya::ampliarCapacidad() {
    int nuevaCapacidad = capacidadTickets * 2;

    Ticket** nuevosTickets =
        new Ticket*[nuevaCapacidad]{};

    Vehiculo** nuevosVehiculos =
        new Vehiculo*[nuevaCapacidad]{};

    Propietario** nuevosPropietarios =
        new Propietario*[nuevaCapacidad]{};

    bool* nuevosActivos =
        new bool[nuevaCapacidad]{};

    int* nuevosEspacios =
        new int[nuevaCapacidad]{};

    for (int i = 0; i < cantidadTickets; i++) {
        nuevosTickets[i] = tickets[i];
        nuevosVehiculos[i] = vehiculos[i];
        nuevosPropietarios[i] = propietarios[i];
        nuevosActivos[i] = activos[i];
        nuevosEspacios[i] = espaciosEntrada[i];
    }

    delete[] tickets;
    delete[] vehiculos;
    delete[] propietarios;
    delete[] activos;
    delete[] espaciosEntrada;

    tickets = nuevosTickets;
    vehiculos = nuevosVehiculos;
    propietarios = nuevosPropietarios;
    activos = nuevosActivos;
    espaciosEntrada = nuevosEspacios;

    capacidadTickets = nuevaCapacidad;
}

int SistemaPlaya::buscarTicketActivoPorPlaca(
    const string& placa
) const {
    for (int i = cantidadTickets - 1; i >= 0; i--) {
        if (
            activos[i] &&
            vehiculos[i] != nullptr &&
            vehiculos[i]->getPlaca() == placa
        ) {
            return i;
        }
    }

    return -1;
}

string SistemaPlaya::nombreTipo(char tipo) const {
    if (tipo == 'A') {
        return "Automovil";
    }

    if (tipo == 'M') {
        return "Motocicleta";
    }

    if (tipo == 'B') {
        return "Bus";
    }

    return "Desconocido";
}

void SistemaPlaya::mostrarFechaHora(int tiempo) const {
    if (tiempo == 0) {
        cout << "Pendiente";
        return;
    }

    time_t valor = static_cast<time_t>(tiempo);
    tm* fecha = localtime(&valor);

    if (fecha != nullptr) {
        cout << put_time(
            fecha,
            "%d/%m/%Y %I:%M %p"
        );
    }
}

void SistemaPlaya::configurarEstacionamiento() {
    int columnas;
    int autos;
    int motos;
    int buses;

    cout << "\nCONFIGURACION INICIAL\n";

    cout << "Numero de columnas: ";
    cin >> columnas;

    cout << "Espacios para automoviles: ";
    cin >> autos;

    cout << "Espacios para motocicletas: ";
    cin >> motos;

    cout << "Espacios para buses: ";
    cin >> buses;

    estacionamiento.configurar(
        columnas,
        autos,
        motos,
        buses
    );
}

void SistemaPlaya::ingresarVehiculo() {
    char tipo;
    string placa;
    string nombre;
    string dni;

    cout << "\nINGRESO DE VEHICULO\n";

    cout << "Tipo (A = Auto, M = Moto, B = Bus): ";
    cin >> tipo;

    tipo = static_cast<char>(
        toupper(
            static_cast<unsigned char>(tipo)
        )
    );

    if (
        tipo != 'A' &&
        tipo != 'M' &&
        tipo != 'B'
    ) {
        cout << "Tipo de vehiculo invalido.\n";
        return;
    }

    if (
        estacionamiento.contarDisponibles(tipo) <= 0
    ) {
        cout
            << "No hay espacios disponibles para "
            << nombreTipo(tipo)
            << ".\n";

        return;
    }

    cout << "Ingrese placa del vehiculo: ";
    cin >> placa;

    if (
        estacionamiento.buscarVehiculo(placa)
        != nullptr
    ) {
        cout
            << "Ya existe un vehiculo con esa placa.\n";

        return;
    }

    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );

    cout << "Ingrese nombre del propietario: ";
    getline(cin, nombre);

    cout << "Ingrese DNI: ";
    getline(cin, dni);

    Propietario* propietario =
        new Propietario(nombre, dni);

    Vehiculo* vehiculo = nullptr;

    if (tipo == 'A') {
        vehiculo = new Auto(
            placa,
            propietario
        );
    }
    else if (tipo == 'M') {
        vehiculo = new Moto(
            placa,
            propietario
        );
    }
    else {
        vehiculo = new Bus(
            placa,
            propietario
        );
    }

    int indiceEspacio =
        estacionamiento.asignarEspacio(
            vehiculo
        );

    if (indiceEspacio == -1) {
        cout
            << "No fue posible asignar un espacio.\n";

        delete vehiculo;
        delete propietario;

        return;
    }

    if (
        cantidadTickets ==
        capacidadTickets
    ) {
        ampliarCapacidad();
    }

    Ticket* ticket =
        new Ticket(
            siguienteNumero++
        );

    tickets[cantidadTickets] = ticket;
    vehiculos[cantidadTickets] = vehiculo;
    propietarios[cantidadTickets] = propietario;
    activos[cantidadTickets] = true;

    espaciosEntrada[cantidadTickets] =
        indiceEspacio;

    cout << "\nTICKET DE ENTRADA\n";

    cout
        << "Numero: "
        << ticket->getNumero()
        << '\n';

    cout
        << "Placa: "
        << vehiculo->getPlaca()
        << '\n';

    cout
        << "Tipo: "
        << nombreTipo(
            vehiculo->getTipo()
        )
        << '\n';

    cout
        << "Espacio: "
        << indiceEspacio + 1
        << '\n';

    cout << "Hora de entrada: ";

    mostrarFechaHora(
        ticket->getHoraEntrada()
    );

    cout << '\n';

    cantidadTickets++;
}

void SistemaPlaya::retirarVehiculo() {
    string placa;

    cout << "\nINGRESO DE SALIDA\n";

    cout << "Ingrese placa: ";
    cin >> placa;

    int indiceTicket =
        buscarTicketActivoPorPlaca(
            placa
        );

    if (indiceTicket == -1) {
        cout
            << "No se encontro un vehiculo activo "
            << "con esa placa.\n";

        return;
    }

    Vehiculo* vehiculo =
        vehiculos[indiceTicket];

    Ticket* ticket =
        tickets[indiceTicket];

    int espacio =
        vehiculo->getEspacioAsignado();

    ticket->calcularTotal(
        vehiculo
    );

    cout << "\nBOLETA DE VENTA\n";

    cout
        << "Numero de ticket: "
        << ticket->getNumero()
        << '\n';

    cout
        << "Placa: "
        << vehiculo->getPlaca()
        << '\n';

    cout
        << "Propietario: "
        << vehiculo->getPropietario()
        << '\n';

    cout
        << "Tipo: "
        << nombreTipo(
            vehiculo->getTipo()
        )
        << '\n';

    cout
        << "Espacio: "
        << espacio + 1
        << '\n';

    cout << "Entrada: ";

    mostrarFechaHora(
        ticket->getHoraEntrada()
    );

    cout << "\nSalida: ";

    mostrarFechaHora(
        ticket->getHoraSalida()
    );

    cout
        << "\nHoras: "
        << ticket->getHoras()
        << '\n';

    cout
        << fixed
        << setprecision(2);

    cout
        << "Total: S/ "
        << ticket->getTotalPago()
        << '\n';

    estacionamiento.liberarEspacio(
        espacio
    );

    activos[indiceTicket] = false;

    cout
        << "El espacio se ha liberado correctamente.\n";
}

void SistemaPlaya::mostrarEstacionamiento() {
    cout << "\nESTACIONAMIENTO\n";

    estacionamiento.mostrarEstacionamiento();
}

int SistemaPlaya::buscarTicket(
    int numero
) const {
    for (int i = 0; i < cantidadTickets; i++) {
        if (
            tickets[i] != nullptr &&
            tickets[i]->getNumero() == numero
        ) {
            return i;
        }
    }

    return -1;
}

void SistemaPlaya::emitirTicket() {
    int numero;

    cout << "Ingrese numero de ticket: ";
    cin >> numero;

    int indice =
        buscarTicket(numero);

    if (indice == -1) {
        cout << "Ticket no encontrado.\n";
        return;
    }

    cout
        << "Placa: "
        << vehiculos[indice]->getPlaca()
        << '\n';

    cout
        << "Tipo: "
        << nombreTipo(
            vehiculos[indice]->getTipo()
        )
        << '\n';

    cout
        << "Espacio asignado al ingresar: "
        << espaciosEntrada[indice] + 1
        << '\n';

    tickets[indice]->mostrarTicket();
}

void SistemaPlaya::mostrarHistorial() {
    cout << "\nHISTORIAL DE ENTRADAS Y SALIDAS\n";

    if (cantidadTickets == 0) {
        cout << "No hay tickets registrados.\n";
        return;
    }

    for (int i = 0; i < cantidadTickets; i++) {
        cout
            << "Ticket: "
            << tickets[i]->getNumero()

            << " | Placa: "
            << vehiculos[i]->getPlaca()

            << " | Tipo: "
            << vehiculos[i]->getTipo()

            << " | Espacio: "
            << espaciosEntrada[i] + 1

            << " | Estado: "
            << (
                activos[i]
                ? "DENTRO"
                : "SALIO"
            )
            << '\n';

        cout << "Entrada: ";

        mostrarFechaHora(
            tickets[i]->getHoraEntrada()
        );

        cout << " | Salida: ";

        mostrarFechaHora(
            tickets[i]->getHoraSalida()
        );

        if (!activos[i]) {
            cout
                << " | Horas: "
                << tickets[i]->getHoras()

                << " | Total: S/ "
                << fixed
                << setprecision(2)
                << tickets[i]->getTotalPago();
        }

        cout << '\n';
    }
}

void SistemaPlaya::configurarCapacidad() {
    char tipo;
    int nuevaCantidad;

    cout << "\nEDICION DE ESPACIOS\n";

    cout
        << "A: AUTOMOVILES | "
        << "M: MOTOCICLETAS | "
        << "B: BUSES\n";

    cout << "Ingrese el tipo: ";
    cin >> tipo;

    tipo = static_cast<char>(
        toupper(
            static_cast<unsigned char>(tipo)
        )
    );

    if (
        tipo != 'A' &&
        tipo != 'M' &&
        tipo != 'B'
    ) {
        cout << "Tipo invalido.\n";
        return;
    }

    cout
        << "Cantidad actual: "
        << estacionamiento.getCapacidad(tipo)
        << '\n';

    cout << "Ingrese la nueva cantidad: ";
    cin >> nuevaCantidad;

    if (
        estacionamiento.editarCapacidad(
            tipo,
            nuevaCantidad
        )
    ) {
        cout
            << "Capacidad actualizada correctamente.\n";
    }
    else {
        cout
            << "No se pudo actualizar la capacidad.\n";
    }
}

void SistemaPlaya::menu() {
    if (
        estacionamiento.getCapacidad('A') == 0 &&
        estacionamiento.getCapacidad('M') == 0 &&
        estacionamiento.getCapacidad('B') == 0
    ) {
        configurarEstacionamiento();
    }

    int opcion = 0;

    do {
        cout << "\nMENU DEL SISTEMA\n";

        cout
            << "DISPONIBILIDAD | AUTOMOVILES: "
            << estacionamiento.contarDisponibles('A')

            << " | MOTOCICLETAS: "
            << estacionamiento.contarDisponibles('M')

            << " | BUSES: "
            << estacionamiento.contarDisponibles('B')

            << '\n';

        cout << "1. Ingresar vehiculo\n";
        cout << "2. Ingresar salida\n";
        cout << "3. Visualizar historial\n";
        cout << "4. Mostrar estacionamiento\n";
        cout << "5. Editar espacios\n";
        cout << "6. Consultar ticket\n";
        cout << "7. Salir\n";

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                ingresarVehiculo();
                break;

            case 2:
                retirarVehiculo();
                break;

            case 3:
                mostrarHistorial();
                break;

            case 4:
                mostrarEstacionamiento();
                break;

            case 5:
                configurarCapacidad();
                break;

            case 6:
                emitirTicket();
                break;

            case 7:
                cout << "Saliendo del sistema...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 7);
}
