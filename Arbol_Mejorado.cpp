#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Estructura del Nodo
struct Nodo {
    string cargo;
    vector<Nodo*> hijos;

    Nodo(string _cargo) : cargo(_cargo) {}
};

// --- FUNCIONES DE GESTIÓN ---

/**
 * Busca un nodo por su nombre de cargo (DFS)
 */
Nodo* buscarNodo(Nodo* raiz, string nombre) {
    if (raiz == nullptr) return nullptr;
    if (raiz->cargo == nombre) return raiz;

    for (Nodo* hijo : raiz->hijos) {
        Nodo* resultado = buscarNodo(hijo, nombre);
        if (resultado != nullptr) return resultado;
    }
    return nullptr;
}

/**
 * Inserta un nuevo nodo como hijo de un padre existente
 */
bool insertarNodo(Nodo* raiz, string nombrePadre, string nuevoCargo) {
    Nodo* padre = buscarNodo(raiz, nombrePadre);
    if (padre != nullptr) {
        padre->hijos.push_back(new Nodo(nuevoCargo));
        return true;
    }
    return false;
}

/**
 * Función auxiliar para liberar memoria recursivamente
 */
void liberarMemoria(Nodo* nodo) {
    if (nodo == nullptr) return;
    for (Nodo* hijo : nodo->hijos) {
        liberarMemoria(hijo);
    }
    delete nodo;
}

/**
 * Elimina un nodo y toda su descendencia
 */
bool eliminarNodo(Nodo* &raiz, string nombre) {
    if (raiz == nullptr) return false;

    // Caso especial: El nodo a eliminar es la raíz
    if (raiz->cargo == nombre) {
        liberarMemoria(raiz);
        raiz = nullptr;
        return true;
    }

    // Buscar en los hijos del nodo actual
    for (auto it = raiz->hijos.begin(); it != raiz->hijos.end(); ++it) {
        if ((*it)->cargo == nombre) {
            liberarMemoria(*it);
            raiz->hijos.erase(it);
            return true;
        }
        // Llamada recursiva para buscar en niveles inferiores
        if (eliminarNodo(*it, nombre)) return true;
    }
    return false;
}


void imprimirGraficoASCII(Nodo* nodo, string prefijo = "", bool esUltimo = true) {
    if (nodo == nullptr) return;

    cout << prefijo;
    if (prefijo == "") {
        cout << "[RAIZ] ";
    } else {
        cout << (esUltimo ? "\\-- " : "|-- ");
    }
    
    cout << nodo->cargo << endl;

    string nuevoPrefijo = prefijo + (esUltimo ? "    " : "|   ");

    for (size_t i = 0; i < nodo->hijos.size(); ++i) {
        bool ultimoHijo = (i == nodo->hijos.size() - 1);
        imprimirGraficoASCII(nodo->hijos[i], nuevoPrefijo, ultimoHijo);
    }
}


int main() {
    //CARGA INICIAL (4 Nodos precargados)
    Nodo* empresa = new Nodo("ZETAVOX 3D");
    insertarNodo(empresa, "ZETAVOX 3D", "Gerente General");
    insertarNodo(empresa, "Gerente General", "Gerente de Ventas");
    insertarNodo(empresa, "Gerente de Ventas", "Vendedor Local");

    int opcion;
    string nombrePadre, nombreNodo;

    do {
        cout << "\n--- MENU ESTRUCTURA ORGANIZACIONAL ---" << endl;
        if (empresa != nullptr) {
            imprimirGraficoASCII(empresa);
        } else {
            cout << "(Arbol vacio)" << endl;
        }
        
        cout << "\n1. Insertar Nodo" << endl;
        cout << "2. Eliminar Nodo" << endl;
        cout << "3. Buscar Nodo" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpiar buffer

        switch (opcion) {
            case 1:
                cout << "Nombre del cargo PADRE donde insertar: ";
                getline(cin, nombrePadre);
                cout << "Nombre del NUEVO cargo: ";
                getline(cin, nombreNodo);
                if (insertarNodo(empresa, nombrePadre, nombreNodo))
                    cout << ">> Insertado con exito." << endl;
                else
                    cout << ">> Error: No se encontro el padre." << endl;
                break;

            case 2:
                cout << "Nombre del cargo a ELIMINAR (y sus hijos): ";
                getline(cin, nombreNodo);
                if (eliminarNodo(empresa, nombreNodo))
                    cout << ">> Nodo eliminado." << endl;
                else
                    cout << ">> Error: Nodo no encontrado." << endl;
                break;

            case 3:
                cout << "Nombre del cargo a BUSCAR: ";
                getline(cin, nombreNodo);
                if (buscarNodo(empresa, nombreNodo))
                    cout << ">> El cargo '" << nombreNodo << "' EXISTE en el arbol." << endl;
                else
                    cout << ">> El cargo no existe." << endl;
                break;
        }
    } while (opcion != 4);

    // Limpieza final de memoria
    liberarMemoria(empresa);

    return 0;
}