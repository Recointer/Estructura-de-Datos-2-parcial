#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

// Representación del grafo mediante Lista de Adyacencia
map<char, vector<char>> grafo;

// Función para inicializar el grafo tal como viene en la imagen
void inicializarGrafo() {
    grafo['A'] = {'B', 'C'};
    grafo['B'] = {'A', 'D', 'E'};
    grafo['C'] = {'A', 'F'};
    grafo['D'] = {'B'};
    grafo['E'] = {'B', 'F'};
    grafo['F'] = {'C', 'E'};
}

// Opción 1: Ver todos los nodos
void verTodosLosNodos() {
    cout << "\n--- [1] Nodos del Grafo ---\n";
    for (auto const& par : grafo) {
        cout << par.first << " ";
    }
    cout << "\n";
}

// Opción 2: Lista de adyacencia (nodos y vecinos)
void mostrarListaAdyacencia() {
    cout << "\n--- [2] Lista de Adyacencia ---\n";
    for (auto const& par : grafo) {
        cout << par.first << " -> [";
        for (size_t i = 0; i < par.second.size(); ++i) {
            cout << par.second[i];
            if (i < par.second.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
}

// Función auxiliar recursiva para el DFS
void dfsRecursivo(char nodoActual, set<char>& visitados) {
    // Marcar el nodo actual como visitado e imprimirlo
    visitados.insert(nodoActual);
    cout << nodoActual << " ";

    // Recorrer todos los vecinos del nodo actual
    for (char vecino : grafo[nodoActual]) {
        // Si el vecino no ha sido visitado, profundizar en él
        if (visitados.find(vecino) == visitados.end()) {
            dfsRecursivo(vecino, visitados);
        }
    }
}

// Opción 3: Recorrido DFS desde A
void ejecutarDFS() {
    cout << "\n--- [3] Recorrido DFS desde A ---\n";
    set<char> visitados;
    
    // Iniciamos la búsqueda en profundidad desde el nodo 'A'
    dfsRecursivo('A', visitados);
    cout << "\n";
}

int main() {
    // Se carga la estructura del grafo de la imagen
    inicializarGrafo();
    
    int opcion;
    do {
        cout << "\n======================================\n";
        cout << "           MENU EJERCICIO DFS         \n";
        cout << "======================================\n";
        cout << "[1] Ver todos los nodos\n";
        cout << "[2] Lista de adyacencia (nodos y vecinos)\n";
        cout << "[3] Recorrido DFS desde A\n";
        cout << "[4] Salir del programa\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                verTodosLosNodos();
                break;
            case 2:
                mostrarListaAdyacencia();
                break;
            case 3:
                ejecutarDFS();
                break;
            case 4:
                cout << "\nSaliendo del programa. ¡Hasta luego!\n";
                break;
            default:
                cout << "\n[!] Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}