#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Estructura del Nodo
struct Nodo {
    string cargo;
    vector<Nodo*> hijos;

    Nodo(string _cargo) : cargo(_cargo) {}
};

/**
 * Función para imprimir el árbol usando ASCII estándar
 */
void imprimirGraficoASCII(Nodo* nodo, string prefijo = "", bool esUltimo = true) {
    if (nodo == nullptr) return;

    // Imprimir el prefijo y el conector
    cout << prefijo;
    if (prefijo == "") {
        cout << "[RAIZ] "; // Para el nodo principal
    } else {
        // Usa \-- para el último hijo y |-- para los intermedios
        cout << (esUltimo ? "\\-- " : "|-- ");
    }
    
    cout << nodo->cargo << endl;

    // Calcular el prefijo para la siguiente generación (los hijos)
    string nuevoPrefijo = prefijo + (esUltimo ? "    " : "|   ");

    // Recorrer todos los hijos del nodo actual
    for (size_t i = 0; i < nodo->hijos.size(); ++i) {
        bool ultimoHijo = (i == nodo->hijos.size() - 1);
        imprimirGraficoASCII(nodo->hijos[i], nuevoPrefijo, ultimoHijo);
    }
}

int main() {
    // 1. RAIZ
    Nodo* empresa = new Nodo("ZETAVOX 3D (EMPRESA)");

    // 2. NODO INTERMEDIO
    Nodo* gerenteGral = new Nodo("Gerente General");
    empresa->hijos.push_back(gerenteGral);

    // 3. NODOS INTERMEDIOS
    Nodo* gProduccion = new Nodo("Gerente de Produccion (Damaris)");
    Nodo* gVentas = new Nodo("Gerente de Ventas");
    
    gerenteGral->hijos.push_back(gProduccion);
    gerenteGral->hijos.push_back(gVentas);

    // 4. HOJAS
    gProduccion->hijos.push_back(new Nodo("Operador Bambu Lab A1"));
    gProduccion->hijos.push_back(new Nodo("Post-procesado"));
    
    gVentas->hijos.push_back(new Nodo("Vendedor Local"));

    cout << "REPRESENTACION DEL ARBOL ORGANIZACIONAL:" << endl;
    cout << "=========================================" << endl;
    
    imprimirGraficoASCII(empresa);

    return 0;
}