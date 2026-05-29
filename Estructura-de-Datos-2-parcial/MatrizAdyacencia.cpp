#include <iostream>
#include <vector>

using namespace std;

const int NUM_ESTACIONES = 5;
// Inicializamos una matriz de 5x5 llena de ceros (0 significa sin conexión)
vector<vector<int>> matrizAdyacencia(NUM_ESTACIONES, vector<int>(NUM_ESTACIONES, 0));
bool matrizCargada = false;

// Opción 1: Inicializar y Cargar la Matriz de Metro
void cargarMatriz() {
    // Reiniciar matriz a 0
    for (int i = 0; i < NUM_ESTACIONES; i++) {
        for (int j = 0; j < NUM_ESTACIONES; j++) {
            matrizAdyacencia[i][j] = 0;
        }
    }

    // Conexiones de la red: 0-1, 0-2, 1-3, 2-3, 3-4
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
        
        // Al ser un metro (no dirigido), marcamos con '1' ambas celdas
        matrizAdyacencia[u][v] = 1;
        matrizAdyacencia[v][u] = 1;
    }

    matrizCargada = true;
    cout << "\n[+] Matriz de metro inicializada y cargada con exito.\n";
}

// Opción 2: Mostrar Matriz de Adyacencia
void mostrarMatriz() {
    if (!matrizCargada) {
        cout << "\n[!] Primero debes cargar la matriz (Opcion 1).\n";
        return;
    }

    cout << "\n--- MATRIZ DE ADYACENCIA ---\n";
    cout << "    0 1 2 3 4\n";
    cout << "   ----------\n";
    for (int i = 0; i < NUM_ESTACIONES; i++) {
        cout << i << " | ";
        for (int j = 0; j < NUM_ESTACIONES; j++) {
            cout << matrizAdyacencia[i][j] << " ";
        }
        cout << "\n";
    }
}

// Opción 3: Identificar Propiedades del Grafo
void identificarPropiedades() {
    if (!matrizCargada) {
        cout << "\n[!] Primero debes cargar la matriz (Opcion 1).\n";
        return;
    }

    cout << "\n--- PROPIEDADES DEL GRAFO ---\n";
    cout << "* Es un Grafo NO Dirigido: Las conexiones son bidireccionales.\n";
    cout << "* Matriz Simetrica: Refleja la propiedad no dirigida (si A conecta con B, B conecta con A).\n";
    cout << "* Diagonal Principal en Cero: No existen bucles (ninguna estacion se conecta consigo misma).\n";
    cout << "* Densidad: Es un grafo esparcido o disperso (pocas conexiones comparadas con el total posible).\n";
}

// Opción 4: Análisis de Memoria Comparativo
void analisisMemoria() {
    if (!matrizCargada) {
        cout << "\n[!] Primero debes cargar la matriz (Opcion 1).\n";
        return;
    }

    // Un entero típico 'int' ocupa 4 bytes
    int bytesPorEntero = sizeof(int); 
    
    // Matriz: Guarda obligatoriamente V x V elementos
    int elementosMatriz = NUM_ESTACIONES * NUM_ESTACIONES;
    int memoriaMatriz = elementosMatriz * bytesPorEntero;

    // Lista (del ejercicio anterior): Guarda 10 elementos (2 por cada una de las 5 aristas)
    int elementosLista = 10; 
    int memoriaLista = elementosLista * bytesPorEntero;

    cout << "\n--- ANALISIS DE MEMORIA COMPARATIVO ---\n";
    cout << "* MATRIZ DE ADYACENCIA:\n";
    cout << "  - Elementos guardados: " << elementosMatriz << " enteros (5x5 celdas fijas).\n";
    cout << "  - Espacio aproximado:  " << memoriaMatriz << " bytes.\n\n";

    cout << "* LISTA DE ADYACENCIA (Ejercicio previo):\n";
    cout << "  - Elementos guardados: " << elementosLista << " enteros (solo vecinos reales).\n";
    cout << "  - Espacio aproximado:  " << memoriaLista << " bytes.\n\n";

    cout << ">> CONCLUSION: Para esta red pequena, la lista ahorra " 
         << (memoriaMatriz - memoriaLista) << " bytes frente a la matriz.\n";
    cout << "   La matriz siempre ocupa un espacio fijo de O(V^2), contenga o no conexiones.\n";
}

int main() {
    int opcion;

    do {
        cout << "\n==================================\n";
        cout << "          MENU ESPERADO           \n";
        cout << "==================================\n";
        cout << "1: Inicializar y Cargar la Matriz de Metro\n";
        cout << "2: Mostrar Matriz de Adyacencia\n";
        cout << "3: Identificar Propiedades del Grafo\n";
        cout << "4: Analisis de Memoria Comparativo\n";
        cout << "5: Salir del Programa\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cargarMatriz();
                break;
            case 2:
                mostrarMatriz();
                break;
            case 3:
                identificarPropiedades();
                break;
            case 4:
                analisisMemoria();
                break;
            case 5:
                cout << "\nSaliendo del programa. ¡Hasta luego!\n";
                break;
            default:
                cout << "\n[!] Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}