#include <iostream>

using namespace std;

// Estructura del Nodo para el Árbol de Decisión
struct Nodo {
  int id;
  int valor; // Decisión (para hojas) o Etiqueta (para nodos internos)
  Nodo *izq, *der;
  bool esHoja;

  Nodo(int _id, int _val, bool _hoja)
      : id(_id), valor(_val), izq(nullptr), der(nullptr), esHoja(_hoja) {}
};

// --- FUNCIÓN AUXILIAR: Comparar si dos subárboles son idénticos (Isomorfismo)
// ---
bool sonIsomorfos(Nodo *a, Nodo *b) {
  if (!a && !b)
    return true;
  if (!a || !b)
    return false;
  if (a->esHoja && b->esHoja)
    return a->valor == b->valor;
  if (a->esHoja || b->esHoja)
    return false;
  return (a->valor == b->valor) && sonIsomorfos(a->izq, b->izq) &&
         sonIsomorfos(a->der, b->der);
}

// --- TRANSFORMACIÓN 1: Poda de Hojas Iguales ---
void aplicarPoda(Nodo *&raiz) {
  if (!raiz || raiz->esHoja)
    return;
  aplicarPoda(raiz->izq);
  aplicarPoda(raiz->der);

  if (raiz->izq && raiz->der && raiz->izq->esHoja && raiz->der->esHoja) {
    if (raiz->izq->valor == raiz->der->valor) {
      int nuevoValor = raiz->izq->valor;
      delete raiz->izq;
      delete raiz->der;
      raiz->izq = raiz->der = nullptr;
      raiz->esHoja = true;
      raiz->valor = nuevoValor;
      cout << ">> [T1: Poda] Nodo " << raiz->id
           << " simplificado a hoja con valor " << nuevoValor << endl;
    }
  }
}

// --- TRANSFORMACIÓN 2: Eliminación de Nodos Redundantes ---
void eliminarRedundantes(Nodo *&raiz) {
  if (!raiz || raiz->esHoja)
    return;
  eliminarRedundantes(raiz->izq);
  eliminarRedundantes(raiz->der);

  if (raiz->izq && raiz->der && sonIsomorfos(raiz->izq, raiz->der)) {
    cout << ">> [T2: Redundancia] Nodo " << raiz->id
         << " eliminado (ambas ramas son identicas)." << endl;
    Nodo *temp = raiz->izq;
    delete raiz->der;
    raiz->valor = temp->valor;
    raiz->esHoja = temp->esHoja;
    raiz->izq = temp->izq;
    raiz->der = temp->der;
    delete temp;
  }
}

// --- TRANSFORMACIÓN 3: Compresión de Ramas (Bypass) ---
void comprimirRamas(Nodo *&raiz) {
  if (!raiz || raiz->esHoja)
    return;
  comprimirRamas(raiz->izq);
  comprimirRamas(raiz->der);

  if (raiz->izq == nullptr || raiz->der == nullptr) {
    Nodo *hijoExistente = (raiz->izq != nullptr) ? raiz->izq : raiz->der;
    if (hijoExistente != nullptr) {
      cout << ">> [T3: Compresion] Nodo " << raiz->id
           << " colapsado hacia su unico hijo." << endl;
      Nodo *temp = hijoExistente;
      raiz->valor = temp->valor;
      raiz->esHoja = temp->esHoja;
      raiz->izq = temp->izq;
      raiz->der = temp->der;
      delete temp;
    }
  }
}

// --- VISUALIZACIÓN Y MENÚ ---
void mostrarArbol(Nodo *r, int nivel = 0) {
  if (!r)
    return;
  mostrarArbol(r->der, nivel + 1);
  for (int i = 0; i < nivel; i++)
    cout << "    ";
  if (r->esHoja)
    cout << "[H:" << r->valor << "]" << endl;
  else
    cout << "(N:" << r->id << ")" << endl;
  mostrarArbol(r->izq, nivel + 1);
}

Nodo *crearArbolPrueba() {
  Nodo *raiz = new Nodo(1, 0, false);
  raiz->izq = new Nodo(2, 0, false);
  raiz->izq->izq = new Nodo(4, 1, true);
  raiz->izq->der = new Nodo(5, 1, true);
  raiz->der = new Nodo(3, 0, false);
  raiz->der->izq = new Nodo(6, 2, true);
  raiz->der->der = new Nodo(7, 2, true);
  return raiz;
}

int main() {
  Nodo *miArbol = crearArbolPrueba();
  int opcion;
  do {
    cout << "\n--- MENU TRANSFORMACION ESTRUCTURAL ---" << endl;
    cout << "1. Mostrar Arbol\n2. T1: Poda\n3. T2: Redundancia\n4. T3: "
            "Compresion\n5. Reiniciar\n0. Salir\nOpcion: ";
    cin >> opcion;
    if (opcion == 1)
      mostrarArbol(miArbol);
    else if (opcion == 2)
      aplicarPoda(miArbol);
    else if (opcion == 3)
      eliminarRedundantes(miArbol);
    else if (opcion == 4)
      comprimirRamas(miArbol);
    else if (opcion == 5)
      miArbol = crearArbolPrueba();
  } while (opcion != 0);
  return 0;
}
