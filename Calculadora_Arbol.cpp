#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <cctype>

using namespace std;

// Nodo del árbol
struct Nodo {
    string valor;
    Nodo *izq, *der;
    Nodo(string v) : valor(v), izq(nullptr), der(nullptr) {}
};

class CalculadoraMaestra {
public:
    int prioridad(string op) {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/") return 2;
        return 0;
    }

    void procesarOperador(stack<Nodo*>& valores, stack<string>& operadores) {
        if (valores.size() < 2) return;
        Nodo* nodoOp = new Nodo(operadores.top());
        operadores.pop();
        
        // El primero que sale es el hijo derecho (por estructura de pila)
        nodoOp->der = valores.top(); valores.pop();
        nodoOp->izq = valores.top(); valores.pop();
        valores.push(nodoOp);
    }

    Nodo* construirArbol(string expresion) {
        stack<Nodo*> valores;
        stack<string> operadores;

        for (int i = 0; i < expresion.length(); i++) {
            if (isspace(expresion[i])) continue;

            // Si es un número (soporta varios dígitos)
            if (isdigit(expresion[i])) {
                string num;
                while (i < expresion.length() && (isdigit(expresion[i]) || expresion[i] == '.')) {
                    num += expresion[i++];
                }
                i--;
                valores.push(new Nodo(num));
            } 
            // Si es apertura de paréntesis
            else if (expresion[i] == '(') {
                operadores.push("(");
            } 
            // Si es cierre de paréntesis
            else if (expresion[i] == ')') {
                while (!operadores.empty() && operadores.top() != "(") {
                    procesarOperador(valores, operadores);
                }
                if (!operadores.empty()) operadores.pop(); // Quita el "("
            } 
            // Si es un operador
            else {
                string op(1, expresion[i]);
                while (!operadores.empty() && prioridad(operadores.top()) >= prioridad(op)) {
                    procesarOperador(valores, operadores);
                }
                operadores.push(op);
            }
        }

        while (!operadores.empty()) {
            procesarOperador(valores, operadores);
        }

        return valores.empty() ? nullptr : valores.top();
    }

    double evaluar(Nodo* raiz) {
        if (!raiz) return 0;
        if (!raiz->izq && !raiz->der) return stod(raiz->valor);

        double izq = evaluar(raiz->izq);
        double der = evaluar(raiz->der);

        if (raiz->valor == "+") return izq + der;
        if (raiz->valor == "-") return izq - der;
        if (raiz->valor == "*") return izq * der;
        if (raiz->valor == "/") return (der != 0) ? izq / der : 0;
        return 0;
    }
};

int main() {
    CalculadoraMaestra calc;
    string expr;

    cout << "========================================" << endl;
    cout << "    CALCULADORA DE EXPRESIONES ( )      " << endl;
    cout << "========================================" << endl;
    cout << " Ejemplo: (10 + 5) * 2 / (3 - 1)" << endl;
    cout << "----------------------------------------" << endl;
    cout << " > Ingrese expresion: "; getline(cin, expr);

    Nodo* raiz = calc.construirArbol(expr);
    
    if (raiz) {
        cout << "\n----------------------------------------" << endl;
        cout << " RESULTADO: " << calc.evaluar(raiz) << endl;
        cout << "----------------------------------------" << endl;
    } else {
        cout << " Error: Expresion invalida." << endl;
    }

    return 0;
}