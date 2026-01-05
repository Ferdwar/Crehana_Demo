#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include "Estudiante.h"
using namespace std;

// =======================
// Nodo del ABB
// =======================
struct NodoABB {
    Estudiante data;
    NodoABB* left;
    NodoABB* right;

    NodoABB(const Estudiante& e) : data(e), left(nullptr), right(nullptr) {}
};

// =======================
// Árbol Binario de Búsqueda
// =======================
class ABBEstudiantes {
private:
    NodoABB* raiz;

    // =======================
    // Función recursiva agregar
    // =======================
    NodoABB* agregarRec(NodoABB* nodo, const Estudiante& e) {
        if (!nodo) return new NodoABB(e);

        if (e < nodo->data)
            nodo->left = agregarRec(nodo->left, e);
        else if (e > nodo->data)
            nodo->right = agregarRec(nodo->right, e);
        else
            cout << "El estudiante ya existe: " << e.getUsername() << endl;

        return nodo;
    }

    // =======================
    // Función recursiva buscar por username
    // =======================
    NodoABB* buscarRec(NodoABB* nodo, const string& username) {
        if (!nodo) return nullptr;
        if (nodo->data.getUsername() == username) return nodo;
        if (username < nodo->data.getUsername())
            return buscarRec(nodo->left, username);
        else
            return buscarRec(nodo->right, username);
    }

    // =======================
    // Función recursiva eliminar
    // =======================
    NodoABB* eliminarRec(NodoABB* nodo, const string& username) {
        if (!nodo) return nullptr;

        if (username < nodo->data.getUsername())
            nodo->left = eliminarRec(nodo->left, username);
        else if (username > nodo->data.getUsername())
            nodo->right = eliminarRec(nodo->right, username);
        else {
            if (!nodo->left) {
                NodoABB* temp = nodo->right;
                delete nodo;
                return temp;
            }
            else if (!nodo->right) {
                NodoABB* temp = nodo->left;
                delete nodo;
                return temp;
            }
            else {
                NodoABB* temp = nodo->right;
                while (temp->left) temp = temp->left;
                nodo->data = temp->data;
                nodo->right = eliminarRec(nodo->right, temp->data.getUsername());
            }
        }
        return nodo;
    }

    // =======================
    // InOrder normal
    // =======================
    void inOrderRec(NodoABB* nodo) {
        if (!nodo) return;
        inOrderRec(nodo->left);
        cout << nodo->data.getUsername() << " | "
            << nodo->data.getEmail() << " | "
            << nodo->data.getRol() << endl;
        inOrderRec(nodo->right);
    }

    // ======================================
    // Recorrido con lambda  función rec.
    // ======================================
    void forEachRec(NodoABB* nodo, function<void(Estudiante&)> fn) {
        if (!nodo) return;
        forEachRec(nodo->left, fn);
        fn(nodo->data);   // <<< AQUÍ ejecuta el lambda
        forEachRec(nodo->right, fn);
    }

    // ======================================
    // Buscar con lambda  recursiva
    // ======================================
    Estudiante* buscarIfRec(NodoABB* nodo, function<bool(const Estudiante&)> criterio) {
        if (!nodo) return nullptr;

        if (criterio(nodo->data))
            return &nodo->data;

        Estudiante* izq = buscarIfRec(nodo->left, criterio);
        if (izq) return izq;

        return buscarIfRec(nodo->right, criterio);
    }

    // ======================================
    // Filtrar con lambda  recursiva
    // ======================================
    void filtrarRec(NodoABB* nodo, function<bool(const Estudiante&)> filtro, vector<Estudiante*>& r) {
        if (!nodo) return;
        filtrarRec(nodo->left, filtro, r);
        if (filtro(nodo->data)) r.push_back(&nodo->data);
        filtrarRec(nodo->right, filtro, r);
    }

public:
    ABBEstudiantes() : raiz(nullptr) {}

    // =======================
    // Agregar estudiante
    // =======================
    void agregar(const Estudiante& e) {
        raiz = agregarRec(raiz, e);
    }

    // =======================
    // Buscar por username
    // =======================
    Estudiante* buscar(const string& username) {
        NodoABB* nodo = buscarRec(raiz, username);
        if (nodo) return &nodo->data;
        return nullptr;
    }

    // =======================
    // Eliminar por username
    // =======================
    void eliminar(const string& username) {
        raiz = eliminarRec(raiz, username);
    }

    // =======================
    // Mostrar todos
    // =======================
    void mostrarEnOrden() {
        inOrderRec(raiz);
    }

    // ======================================
    // Recorrido en orden con lambda
    // ======================================
    void forEach(function<void(Estudiante&)> fn) {
        forEachRec(raiz, fn);
    }

    // ======================================
    // Búsqueda con lambda
    // ======================================
    Estudiante* buscarIf(function<bool(const Estudiante&)> criterio) {
        return buscarIfRec(raiz, criterio);
    }

    // ======================================
    // Filtrar con lambda
    // ======================================
    vector<Estudiante*> filtrar(function<bool(const Estudiante&)> filtro) {
        vector<Estudiante*> r;
        filtrarRec(raiz, filtro, r);
        return r;
    }
};
