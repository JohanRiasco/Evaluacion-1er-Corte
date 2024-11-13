#include <iostream>
using namespace std;

struct nodo {
    int edad;
    int NIUP;
    nodo *izq;
    nodo *der;
};

struct nodo *raiz = NULL;
struct nodo *aux = NULL;
struct nodo *aux2 = NULL;

void mostrarPacientesDescendente(nodo *actual) {
    if(actual != NULL) {
        mostrarPacientesDescendente(actual->der);
        cout << "Edad: " << actual->edad << " | NIUP: " << actual->NIUP << endl;
        mostrarPacientesDescendente(actual->izq);
    }
}

void mostrarPacientes() {
    if(raiz == NULL) {
        cout << "No hay pacientes registrados en el sistema\n";
        return;
    }
    cout << "\nLista de Pacientes en orden de mayor a menor:\n";
    cout << "\n";
    mostrarPacientesDescendente(raiz);
    cout << "\n";
}

void posicionar() {
    if(aux->edad > aux2->edad) {
        if(aux2->der == NULL) {
            aux2->der = aux;
        } else {
            aux2 = aux2->der;
            posicionar();
        }
    } else {
        if(aux2->izq == NULL) {
            aux2->izq = aux;
        } else {
            aux2 = aux2->izq;
            posicionar();
        }
    }
}

void registrar() {
    aux = new nodo;
   
    cout << "Ingrese la edad del paciente: ";
    cin >> aux->edad;
    cout << "Ingrese el NIUP del paciente: ";
    cin >> aux->NIUP;
   
    aux->izq = NULL;
    aux->der = NULL;
   
    if(raiz == NULL) {
        raiz = aux;
    } else {
        aux2 = raiz;
        posicionar();
    }
   
    cout << "Paciente registrado de forma correcta\n";
}

void buscarPacientePorNIUP(nodo *actual, int NIUP) {
    if (actual == NULL) {
        cout << "Paciente no encontrado.\n";
        return;
    }

    if (actual->NIUP == NIUP) {
        cout << "Paciente encontrado. Edad: " << actual->edad << endl;
        return;
    }

    if (NIUP > actual->NIUP) {
        buscarPacientePorNIUP(actual->der, NIUP);
    } else {
        buscarPacientePorNIUP(actual->izq, NIUP);
    }
}

nodo* encontrarMinimo(nodo* actual) {
    while (actual && actual->izq != NULL) {
        actual = actual->izq;
    }
    return actual;
}

nodo* eliminarPacientePorNIUP(nodo* actual, int NIUP) {
    if (actual == NULL) {
        cout << "Paciente no encontrado.\n";
        return actual;
    }

    if (NIUP < actual->NIUP) {
        actual->izq = eliminarPacientePorNIUP(actual->izq, NIUP);
    } else if (NIUP > actual->NIUP) {
        actual->der = eliminarPacientePorNIUP(actual->der, NIUP);
    } else {
        if (actual->izq == NULL && actual->der == NULL) {
            delete actual;
            return NULL;
        }
        else if (actual->izq == NULL) {
            nodo* temp = actual->der;
            delete actual;
            return temp;
        } else if (actual->der == NULL) {
            nodo* temp = actual->izq;
            delete actual;
            return temp;
        } else {
            nodo* temp = encontrarMinimo(actual->der);
            actual->edad = temp->edad;
            actual->NIUP = temp->NIUP;
            actual->der = eliminarPacientePorNIUP(actual->der, temp->NIUP);
        }
    }
    return actual;
}

int main() {
    int opcion;
    int NIUPBusqueda;

    do {
        cout << "\n Sistema de Registro de Pacientes \n Johan Steinert Riascos Panameño \n";
        cout << "1. Registrar nuevo paciente\n";
        cout << "2. Mostrar lista de pacientes\n";
        cout << "3. Buscar paciente por NIUP\n";
        cout << "4. Eliminar paciente por NIUP\n";
        cout << "5. Salir\n";
        cout << "\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
       
        switch(opcion) {
            case 1:
                registrar();
                break;
            case 2:
                mostrarPacientes();
                break;
            case 3:
                cout << "Ingrese el NIUP del paciente a buscar: ";
                cin >> NIUPBusqueda;
                buscarPacientePorNIUP(raiz, NIUPBusqueda);
                break;
            case 4:
                cout << "Ingrese el NIUP del paciente a eliminar: ";
                cin >> NIUPBusqueda;
                raiz = eliminarPacientePorNIUP(raiz, NIUPBusqueda);
                break;
            case 5:
                cout << "Abandonando Sistema...\n";
                break;
            default:
                cout << "Opcion invalida\n";
        }
    } while(opcion != 5);
   
    return 0;
}