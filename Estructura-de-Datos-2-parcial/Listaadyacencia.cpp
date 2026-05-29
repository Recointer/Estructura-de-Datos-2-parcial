#include <iostream>
#include <vector>

using namespace std;

// Definición de la red de metro
const int NUM_ESTACIONES = 5;
vector<vector<int>> listaAdyacencia(NUM_ESTACIONES);
bool redCargada = false;

// Opción 1: Inicializar y Cargar la Red de Metro
void cargarRed() {
    // Limpiar por si se vuelve a cargar
    for (int i = 0; i < NUM_ESTACIONES; i++) {
        listaAdyacencia[i].clear();
    }

    // Definición de las conexiones bidireccionales: 0-1, 0-2, 1-3, 2-3, 3-4
    int conexiones[][2] = {
        {0, 1},
        {0, 2},
        {1, 3},
        {2, 3},
        {3, 4}
    };
    int totalConexiones = 5;

    for (int i = 0; i < totalConexiones; i++) {
        int u = conexiones[i][0];
        int v = conexiones[i][1];
        
        // Al ser un metro (no dirigido), la conexión va en ambos sentidos
        listaAdyacencia[u].push_back(v);
        listaAdyacencia[v].push_back(u);
    }

    redCargada = true;
    cout << "\n[+] Red de metro cargada con exito.\n";
}

// Opción 2: Mostrar Estaciones y sus Vecinos
void mostrarRed() {
    if (!redCargada) {
        cout << "\n[!] Primero debes cargar la red (Opcion 1).\n";
        return;
    }

    cout << "\n--- ESTACIONES Y SUS VECINOS ---\n";
    for (int i = 0; i < NUM_ESTACIONES; i++) {
        cout << "Estacion " << i << ": ";
        if (listaAdyacencia[i].empty()) {
            cout << "Sin vecinos";
        } else {
            for (int vecino : listaAdyacencia[i]) {
                cout << vecino << " ";
            }
        }
        cout << "\n";
    }
}

// Opción 3: Calcular Total de Valores Guardados
void calcularTotalValores() {
    if (!redCargada) {
        cout << "\n[!] Primero debes cargar la red (Opcion 1).\n";
        return;
    }

    int totalValores = 0;
    for (int i = 0; i < NUM_ESTACIONES; i++) {
        totalValores += listaAdyacencia[i].size();
    }

    cout << "\n--- TOTAL DE VALORES GUARDADOS ---\n";
    cout << "La lista de adyacencia guarda un total de " << totalValores << " valores (elementos).\n";
    cout << "(Nota: Son 5 conexiones no dirigidas, por lo que se guardan 2 valores por cada enlace).\n";
}

int main() {
    int opcion;

    do {
        cout << "\n==================================\n";
        cout << "          MENU ESPERADO           \n";
        cout << "==================================\n";
        cout << "1: Inicializar y Cargar la Red de Metro\n";
        cout << "2: Mostrar Estaciones y sus Vecinos\n";
        cout << "3: Calcular Total de Valores Guardados\n";
        cout << "4: Salir del Programa\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cargarRed();
                break;
            case 2:
                mostrarRed();
                break;
            case 3:
                calcularTotalValores();
                break;
            case 4:
                cout << "\nSaliendo del programa. Hasta luego\n";
                break;
            default:
                cout << "\n Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}