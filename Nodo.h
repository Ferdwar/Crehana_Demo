#pragma once
#include <iostream>
using namespace std;

// Nodo genérico para ABB y AVL
template <typename T>
class Nodo {
public:
    T dato;                // El dato almacenado (puede ser un Curso, un int, etc.)
    Nodo<T>* izquierda;    // Hijo izquierdo
    Nodo<T>* derecha;      // Hijo derecho
    int altura;            // Usado por AVL (el ABB lo ignora sin problema)

    // Constructor principal
    Nodo(const T& valor)
        : dato(valor), izquierda(nullptr), derecha(nullptr), altura(1) {}

    // Constructor vacío opcional
    Nodo()
        : dato(T()), izquierda(nullptr), derecha(nullptr), altura(1) {}
};
