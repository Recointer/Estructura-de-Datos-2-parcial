#include<iostream>
#include <ostream>
using namespace std;
class TreeNode{
    public:
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(){
        value=0;
        left=nullptr;
        right=nullptr;
    }
    TreeNode(int v){
        value=v;
        left=nullptr;
        right=nullptr;
    }
    
};
class BST{
    public:
    TreeNode* root;
    BST(){
        root=nullptr;
    }
    bool isEmpty(){
        if (root==nullptr){
            return true;
        } else {
            return false;
        }
    }

    void insertNode(TreeNode* newNode){
        if (root == nullptr){
            root=newNode;
            cout <<"Valor insertado como Root"<<endl;

        }else {
        TreeNode*temp=root;
        while (temp!=nullptr){
            if(newNode->value == temp->value){
                cout <<"el valor ingresado ya existe, ingrese otro valor"<<endl;
                break;
            }else if((newNode->value < temp->value) && (temp->left == nullptr)){
                temp->left = newNode;
                cout<<"Valor insertado a la izquierda de "<< temp->value <<endl;
                break;
            }else if((newNode->value > temp->value) && (temp->right == nullptr)){
                temp->right = newNode;
                cout<<"Valor insertado a la derecha de "<< temp->value <<endl;
                break;
            }else if(newNode->value < temp->value){
                temp=temp->left;
            }else{
                temp=temp->right;
            }

        }
    }
    }

    // Metodo para imprimir el arbol de forma visual (ver posiciones)
    void imprimirArbol(TreeNode* nodo, int espacio) {
        if (nodo == nullptr) {
            return;
        }
        espacio += 5;
        // Imprime primero la rama derecha
        imprimirArbol(nodo->right, espacio);
        cout << endl;
        for (int i = 5; i < espacio; i++) {
            cout << " ";
        }
        cout << nodo->value << "\n";
        // Luego imprime la rama izquierda
        imprimirArbol(nodo->left, espacio);
    }
    
};

int main(){
    BST arbol;
    int opcion, valor;

    do {
        cout << "\n--- MENU ARBOL BINARIO DE BUSQUEDA ---" << endl;
        cout << "1. Insertar Nodo" << endl;
        cout << "2. Imprimir Arbol (Ver posiciones)" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Ingrese el valor a insertar: ";
                cin >> valor;
                arbol.insertNode(new TreeNode(valor));
                break;
            case 2:
                cout << "\n--- ESTRUCTURA DEL ARBOL ---" << endl;
                if (arbol.isEmpty()) {
                    cout << "El arbol esta vacio." << endl;
                } else {
                    arbol.imprimirArbol(arbol.root, 0);
                    cout << endl;
                }
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