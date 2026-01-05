#pragma once
#include <iostream>
#include <string>
#include "Nodo.h"
using namespace std;

// ===================================
// LISTA ENLAZADA PARA RESULTADOS
// ===================================
template <typename T>
struct NodoLista {
    T dato;
    NodoLista<T>* sig;
    NodoLista(const T& d) : dato(d), sig(nullptr) {}
};

// ===================================
// AVL GENÉRICO
// ===================================
template <typename T>
class AVL {
private:
    Nodo<T>* raiz;

    int altura(Nodo<T>* n) {
        return (n ? n->altura : 0);
    }

    int getBalance(Nodo<T>* n) {
        if (!n) return 0;
        return altura(n->izquierda) - altura(n->derecha);
    }

    Nodo<T>* rotacionDerecha(Nodo<T>* y) {
        Nodo<T>* x = y->izquierda;
        Nodo<T>* T2 = x->derecha;

        x->derecha = y;
        y->izquierda = T2;

        y->altura = 1 + max(altura(y->izquierda), altura(y->derecha));
        x->altura = 1 + max(altura(x->izquierda), altura(x->derecha));

        return x;
    }

    Nodo<T>* rotacionIzquierda(Nodo<T>* x) {
        Nodo<T>* y = x->derecha;
        Nodo<T>* T2 = y->izquierda;

        y->izquierda = x;
        x->derecha = T2;

        x->altura = 1 + max(altura(x->izquierda), altura(x->derecha));
        y->altura = 1 + max(altura(y->izquierda), altura(y->derecha));

        return y;
    }

    Nodo<T>* insertar(Nodo<T>* nodo, const T& valor) {
        if (!nodo)
            return new Nodo<T>(valor);

        if (valor < nodo->dato)
            nodo->izquierda = insertar(nodo->izquierda, valor);
        else if (valor > nodo->dato)
            nodo->derecha = insertar(nodo->derecha, valor);
        else
            return nodo;

        nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));
        int balance = getBalance(nodo);

        if (balance > 1 && valor < nodo->izquierda->dato)
            return rotacionDerecha(nodo);

        if (balance < -1 && valor > nodo->derecha->dato)
            return rotacionIzquierda(nodo);

        if (balance > 1 && valor > nodo->izquierda->dato) {
            nodo->izquierda = rotacionIzquierda(nodo->izquierda);
            return rotacionDerecha(nodo);
        }

        if (balance < -1 && valor < nodo->derecha->dato) {
            nodo->derecha = rotacionDerecha(nodo->derecha);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    }

    void postOrder(Nodo<T>* nodo) {
        if (!nodo) return;
        postOrder(nodo->izquierda);
        postOrder(nodo->derecha);
        cout << nodo->dato.getNombre() << " | ";
    }

    // ============================================
    // BÚSQUEDA POR PREFIJO (IN-ORDER)
    // ============================================
    void buscarPrefijoRec(Nodo<T>* nodo, const string& prefijo, NodoLista<T>*& lista) {
        if (!nodo) return;

        buscarPrefijoRec(nodo->izquierda, prefijo, lista);

        // Comparación usando getter
        if (nodo->dato.getNombre().rfind(prefijo, 0) == 0) {
            NodoLista<T>* nuevo = new NodoLista<T>(nodo->dato);
            nuevo->sig = lista;
            lista = nuevo;
        }

        buscarPrefijoRec(nodo->derecha, prefijo, lista);
    }

public:

    AVL() : raiz(nullptr) {}

    void insertar(const T& valor) {
        raiz = insertar(raiz, valor);
    }

    void mostrarPostOrder() {
        cout << "\n===== AVL (POST-ORDER) =====\n";
        postOrder(raiz);
        cout << "\n";
    }

    // ============================================
    // FUNCIÓN PÚBLICA PARA BUSCAR POR PREFIJO
    // ============================================
    NodoLista<T>* buscarPorPrefijo(const string& prefijo) {
        NodoLista<T>* resultados = nullptr;
        buscarPrefijoRec(raiz, prefijo, resultados);
        return resultados;
    }
};
