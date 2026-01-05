#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Estudiante.h"
using namespace std;

// =======================
// Función de normalización
// =======================
static string normalizar(const string& s) {
    string r = s;
    while (!r.empty() && isspace(r.front())) r.erase(r.begin());
    while (!r.empty() && isspace(r.back())) r.pop_back();
    transform(r.begin(), r.end(), r.begin(), ::tolower);
    return r;
}

// =======================
// Nodo del AVL
// =======================
struct NodoAVL {
    Estudiante data;
    NodoAVL* left;
    NodoAVL* right;
    int altura;
    NodoAVL(const Estudiante& e) : data(e), left(nullptr), right(nullptr), altura(1) {}
};

// =======================
// Nodo para lista de resultados por prefijo
// =======================
struct NodoLista1 {
    Estudiante data;
    NodoLista1* sig;
    NodoLista1(const Estudiante& e) : data(e), sig(nullptr) {}
};

// =======================
// Árbol AVL de Estudiantes
// =======================
class AVLEstudiantes {
private:
    NodoAVL* raiz;

    // Altura
    int obtenerAltura(NodoAVL* nodo) { return nodo ? nodo->altura : 0; }

    // Balance
    int getBalance(NodoAVL* nodo) {
        return nodo ? obtenerAltura(nodo->left) - obtenerAltura(nodo->right) : 0;
    }

    // Rotación derecha
    NodoAVL* rotacionDerecha(NodoAVL* y) {
        NodoAVL* x = y->left;
        NodoAVL* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->altura = max(obtenerAltura(y->left), obtenerAltura(y->right)) + 1;
        x->altura = max(obtenerAltura(x->left), obtenerAltura(x->right)) + 1;

        return x;
    }

    // Rotación izquierda
    NodoAVL* rotacionIzquierda(NodoAVL* x) {
        NodoAVL* y = x->right;
        NodoAVL* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->altura = max(obtenerAltura(x->left), obtenerAltura(x->right)) + 1;
        y->altura = max(obtenerAltura(y->left), obtenerAltura(y->right)) + 1;

        return y;
    }

    // ============================
    // Inserción usando comparación normalizada
    // ============================
    NodoAVL* insertarRec(NodoAVL* nodo, const Estudiante& e) {
        if (!nodo) return new NodoAVL(e);

        string keyE = normalizar(e.getUsername());
        string keyN = normalizar(nodo->data.getUsername());

        if (keyE < keyN)
            nodo->left = insertarRec(nodo->left, e);
        else if (keyE > keyN)
            nodo->right = insertarRec(nodo->right, e);
        else
            return nodo; // duplicado

        nodo->altura = 1 + max(obtenerAltura(nodo->left), obtenerAltura(nodo->right));
        int balance = getBalance(nodo);

        // Rebalance
        if (balance > 1 && keyE < normalizar(nodo->left->data.getUsername()))
            return rotacionDerecha(nodo);
        if (balance < -1 && keyE > normalizar(nodo->right->data.getUsername()))
            return rotacionIzquierda(nodo);
        if (balance > 1 && keyE > normalizar(nodo->left->data.getUsername())) {
            nodo->left = rotacionIzquierda(nodo->left);
            return rotacionDerecha(nodo);
        }
        if (balance < -1 && keyE < normalizar(nodo->right->data.getUsername())) {
            nodo->right = rotacionDerecha(nodo->right);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    }

    // Búsqueda normalizada
    NodoAVL* buscarRecNorm(NodoAVL* nodo, const string& usernameNorm) {
        if (!nodo) return nullptr;

        string actualNorm = normalizar(nodo->data.getUsername());
        if (actualNorm == usernameNorm) return nodo;

        if (usernameNorm < actualNorm)
            return buscarRecNorm(nodo->left, usernameNorm);

        return buscarRecNorm(nodo->right, usernameNorm);
    }

    // InOrder
    void inOrderRec(NodoAVL* nodo) {
        if (!nodo) return;
        inOrderRec(nodo->left);
        cout << nodo->data.getUsername() << " | "
            << nodo->data.getEmail() << " | "
            << nodo->data.getRol() << endl;
        inOrderRec(nodo->right);
    }

    // Prefijos
    void buscarPrefijoRec(NodoAVL* nodo, const string& prefijo, NodoLista1*& lista) {
        if (!nodo) return;

        buscarPrefijoRec(nodo->left, prefijo, lista);

        string userNorm = normalizar(nodo->data.getUsername());
        string prefNorm = normalizar(prefijo);

        if (userNorm.rfind(prefNorm, 0) == 0) {
            NodoLista1* nuevo = new NodoLista1(nodo->data);
            nuevo->sig = lista;
            lista = nuevo;
        }

        buscarPrefijoRec(nodo->right, prefijo, lista);
    }

public:
    AVLEstudiantes() : raiz(nullptr) {}

    void insertar(const Estudiante& e) { raiz = insertarRec(raiz, e); }

    Estudiante* buscar(const string& username) {
        string norm = normalizar(username);
        NodoAVL* nodo = buscarRecNorm(raiz, norm);
        return nodo ? &nodo->data : nullptr;
    }

    void mostrarEnOrden() { inOrderRec(raiz); }

    NodoLista1* buscarPorPrefijo(const string& prefijo) {
        NodoLista1* resultados = nullptr;
        buscarPrefijoRec(raiz, prefijo, resultados);
        return resultados;
    }

    // ============================
    // Cargar estudiantes desde archivo (robusto)
    // ============================
    void cargarDesdeArchivo(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return;

        string linea;
        while (getline(file, linea)) {

            auto extractField = [&](const string& campo) -> string {
                size_t pos = linea.find(campo);
                if (pos == string::npos) return string();
                size_t start = pos + campo.length();
                size_t fin = linea.find('|', start);
                if (fin == string::npos) fin = linea.size();
                string s = linea.substr(start, fin - start);
                // trim
                while (!s.empty() && isspace((unsigned char)s.front())) s.erase(s.begin());
                while (!s.empty() && isspace((unsigned char)s.back())) s.pop_back();
                return s;
                };

            string username = extractField("Usuario: ");
            string email = extractField("Email: ");
            string rol = extractField("Rol: ");

            // Evitar cargar líneas vacías o inválidas
            if (username.empty()) continue;

            Estudiante est(username, email, rol);
            insertar(est);
        }

        file.close();
    }
};

