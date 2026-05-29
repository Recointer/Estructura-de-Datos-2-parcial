#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

// Clase que representa la Red usando una Lista de Adyacencia
class RedInformatica {
private:
    // Lista de adyacencia
    map<string, vector<string>> listaAdyacencia;

public:
    // Método para agregar conexiones 
    void agregarConexion(string u, string v) {
        listaAdyacencia[u].push_back(v);
        listaAdyacencia[v].push_back(u);
    }

    // Mostrar la Topología de la Red
    void mostrarTopologia() {
        cout << "\n--- TOPOLOGÍA DE RED (Lista de Adyacencia) ---\n";
        for (const auto& par : listaAdyacencia) {
            cout << "[" << par.first << "] -> ";
            for (size_t i = 0; i < par.second.size(); ++i) {
                cout << par.second[i];
                if (i < par.second.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    }

    // Simular Infección Masiva usando BFS
    void simularInfeccionBFS(string inicio) {
        if (listaAdyacencia.find(inicio) == listaAdyacencia.end()) {
            cout << "El nodo inicial no existe en la red.\n";
            return;
        }

        cout << "\n--- SIMULACIÓN DE INFECCIÓN MASIVA (BFS) ---\n";
        cout << "Brecha detectada en: " << inicio << "\n\n";

        map<string, bool> visitado;
        queue<string> cola;

        // Inicializar el nodo raíz
        visitado[inicio] = true;
        cola.push(inicio);

        int paso = 1;

        while (!cola.empty()) {
            string actual = cola.front();
            cola.pop();

            cout << "Paso " << paso++ << ": " << actual << " ha sido INFECTADO.\n";

            // Visitar los vecinos del nodo actual
            for (const string& vecino : listaAdyacencia[actual]) {
                if (!visitado[vecino]) {
                    visitado[vecino] = true;
                    cola.push(vecino);
                }
            }
        }
        cout << "\n Alerta: Toda la red accesible ha sido comprometida.\n";
    }

    // Auditoría de Seguridad usando DFS (Exploración profunda)
    void auditoriaDFS(string inicio) {
        if (listaAdyacencia.find(inicio) == listaAdyacencia.end()) {
            cout << "El nodo inicial no existe en la red.\n";
            return;
        }

        cout << "\n--- AUDITORÍA DE SEGURIDAD (DFS) ---\n";
        cout << "Iniciando rastreo forense desde: " << inicio << "\n\n";

        map<string, bool> visitado;
        stack<string> pila;

        pila.push(inicio);

        while (!pila.empty()) {
            string actual = pila.top();
            pila.pop();

            if (visitado[actual]) continue;

            visitado[actual] = true;
            cout << "-> Auditando " << actual << ": Sistema analizado y parcheado.\n";

            // Agregar vecinos a la pila
            for (auto it = listaAdyacencia[actual].rbegin(); it != listaAdyacencia[actual].rend(); ++it) {
                if (!visitado[*it]) {
                    pila.push(*it);
                }
            }
        }
        cout << "\n Auditoria completada. Todos los nodos accesibles han sido asegurados.\n";
    }
};

int main() {
    RedInformatica red;

    // Construcción de la topología propuesta:
    // - Firewall conecta con Router
    // - Router conecta con Switch
    // - Switch conecta con Servidor, PC1 y PC2
    red.agregarConexion("Firewall", "Router");
    red.agregarConexion("Router", "Switch");
    red.agregarConexion("Switch", "Servidor");
    red.agregarConexion("Switch", "PC1");
    red.agregarConexion("Switch", "PC2");

    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "      SISTEMA DE GESTIÓN DE RED        " << endl;
        cout << "========================================" << endl;
        cout << "[1] Mostrar Topologia de Red" << endl;
        cout << "[2] Simular Infeccion Masiva (BFS)" << endl;
        cout << "[3] Auditoria de Seguridad (DFS)" << endl;
        cout << "[4] Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                red.mostrarTopologia();
                break;
            case 2:
             
                red.simularInfeccionBFS("PC1");
                break;
            case 3:
              
                red.auditoriaDFS("PC1");
                break;
            case 4:
                cout << "Saliendo del simulador de seguridad..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (opcion != 4);

    return 0;
}