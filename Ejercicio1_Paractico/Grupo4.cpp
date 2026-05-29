#include <iostream>

using namespace std;

// Estructura base en C++
struct Nodo {
  int decision;
  Nodo *izq, *der;
  bool esHoja;

  void aplicarPoda(Nodo *&raiz) {
    if (raiz == nullptr || raiz->esHoja)
      return;

    // 1. Recursión para llegar a las ramas finales
    aplicarPoda(raiz->izq);
    aplicarPoda(raiz->der);

    // 2. Lógica de Poda: Si ambos hijos son hojas y tienen la misma decisión
    if (raiz->izq != nullptr && raiz->der != nullptr) {
      if (raiz->izq->esHoja && raiz->der->esHoja &&
          raiz->izq->decision == raiz->der->decision) {

        int valorFinal = raiz->izq->decision;

        delete raiz->izq;
        delete raiz->der;

        raiz->izq = nullptr;
        raiz->der = nullptr;
        raiz->esHoja = true;
        raiz->decision = valorFinal;

        cout << "Nodo podado y simplificado." << endl;
      }
    }
  }
};

int main() {
    // Caso de prueba: Un nodo con dos hijos hojas que tienen el mismo valor (1)
    Nodo* hoja1 = new Nodo{1, nullptr, nullptr, true};
    Nodo* hoja2 = new Nodo{1, nullptr, nullptr, true};
    Nodo* raiz = new Nodo{0, hoja1, hoja2, false};

    cout << "--- Prueba de Poda ---" << endl;
    cout << "Estado inicial: El nodo raiz tiene dos hijos (hojas) con valor 1." << endl;
    cout << "Raiz esHoja: " << (raiz->esHoja ? "Si" : "No") << endl;

    // Aplicar la poda
    raiz->aplicarPoda(raiz);

    cout << "Estado final: Despues de aplicarPoda..." << endl;
    cout << "Raiz esHoja: " << (raiz->esHoja ? "Si" : "No") << endl;
    cout << "Nuevo valor de la Raiz: " << raiz->decision << endl;

    // Limpieza (si no se podó, aunque en este caso sí)
    if (!raiz->esHoja) {
        delete raiz->izq;
        delete raiz->der;
    }
    delete raiz;

    return 0;
}