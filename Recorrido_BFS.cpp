#include <iostream>
#include <queue>

using namespace std;

// Definición de la estructura del nodo
struct Nodo {
    int dato;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(int valor) {
        dato = valor;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

// Función para el recorrido BFS usando una Cola (Queue)
void recorridoBFS(Nodo* raiz) {
    if (raiz == nullptr) return;

    // Crear una cola de punteros a nodos
    queue<Nodo*> cola;

    // Encolar la raíz para empezar
    cola.push(raiz);

    cout << "Recorrido BFS: ";

    while (!cola.empty()) {
        // Obtener el nodo al frente de la cola
        Nodo* actual = cola.front();
        cout << actual->dato << " ";
        cola.pop();

        // Encolar hijo izquierdo si existe
        if (actual->izquierdo != nullptr) {
            cola.push(actual->izquierdo);
        }

        // Encolar hijo derecho si existe
        if (actual->derecho != nullptr) {
            cola.push(actual->derecho);
        }
    }
    cout << endl;
}

// Metodo para imprimir el arbol de forma visual (ver posiciones)
void imprimirArbol(Nodo* nodo, int espacio) {
    if (nodo == nullptr) {
        return;
    }
    espacio += 5;
    imprimirArbol(nodo->derecho, espacio);
    cout << endl;
    for (int i = 5; i < espacio; i++) {
        cout << " ";
    }
    cout << nodo->dato << "\n";
    imprimirArbol(nodo->izquierdo, espacio);
}

int main() {
    // Construcción del árbol de la imagen
    Nodo* raiz = new Nodo(50);
    raiz->izquierdo = new Nodo(30);
    raiz->derecho = new Nodo(70);
    raiz->izquierdo->izquierdo = new Nodo(20);
    raiz->izquierdo->derecho = new Nodo(40);
    raiz->derecho->izquierdo = new Nodo(60);
    raiz->derecho->derecho = new Nodo(80);

    int opcion;

    do {
        cout << "\n--- MENU RECORRIDO BFS ---" << endl;
        cout << "1. Mostrar Arbol" << endl;
        cout << "2. Imprimir BFS" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "\n--- ESTRUCTURA DEL ARBOL ---" << endl;
                imprimirArbol(raiz, 0);
                cout << endl;
                break;
            case 2:
                recorridoBFS(raiz);
                break;
            case 3:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 3);

    return 0;
}