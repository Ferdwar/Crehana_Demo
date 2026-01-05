#pragma once
#include <iostream>
#include <vector>
#include "UtilidadesConsola.h"
using namespace std;

#include "Nodo.h"  // Usa tu Nodo<T> genérico

template <typename T>
class ABB {
private:
    Nodo<T>* raiz;

    // ===============================
    // RECORRIDO IN-ORDER (recolecta en vector)
    // ===============================
    void inOrderCollect(Nodo<T>* nodo, vector<T>& out) {
        if (!nodo) return;
        inOrderCollect(nodo->izquierda, out);
        out.push_back(nodo->dato);
        inOrderCollect(nodo->derecha, out);
    }

    // ===============================
    // INSERCIÓN
    // ===============================
    Nodo<T>* insertarRec(Nodo<T>* nodo, const T& valor) {
        if (!nodo) return new Nodo<T>(valor);
        if (valor < nodo->dato)
            nodo->izquierda = insertarRec(nodo->izquierda, valor);
        else
            nodo->derecha = insertarRec(nodo->derecha, valor);
        return nodo;
    }

    // ===============================
    // BÚSQUEDA
    // ===============================
    Nodo<T>* buscarRec(Nodo<T>* nodo, const T& valor) {
        if (!nodo) return nullptr;
        if (valor == nodo->dato) return nodo;
        if (valor < nodo->dato)
            return buscarRec(nodo->izquierda, valor);
        else
            return buscarRec(nodo->derecha, valor);
    }

    // ===============================
    // ========== MERGE SORT ==========
    // ===============================

    void merge(vector<T>& arr, int left, int mid, int right) {

        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<T> L(n1);
        vector<T> R(n2);

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            // usa operator< de T (debe comparar por ID)
            if (L[i] < R[j]) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    void mergeSort(vector<T>& arr, int left, int right) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }


public:

    ABB() : raiz(nullptr) {}

    // ===============================
    // INSERTAR
    // ===============================
    void insertar(const T& valor) {
        raiz = insertarRec(raiz, valor);
    }

    // ===============================
    // BUSCAR
    // ===============================
    bool contiene(const T& valor) {
        return buscarRec(raiz, valor) != nullptr;
    }

    // ===============================
    // MOSTRAR IN-ORDER (debug)
    // ===============================
    void mostrarInOrder() {
        cout << "===== RECORRIDO IN-ORDER =====\n";
        vector<T> items = toListInOrder();
        for (const T& it : items) {
            cout << it << endl;
        }
        cout << "\n";
    }

    // ===============================
    // DEVOLVER LISTA EN ORDEN IN-ORDER
    // ===============================
    vector<T> toListInOrder() {
        vector<T> result;
        inOrderCollect(raiz, result);
        return result;
    }

    // ========================================================
    // DEVOLVER LISTA ORDENADA POR MERGESORT (según ID)
    // ========================================================
    vector<T> toListMergeSort() {
        vector<T> lista = toListInOrder();

        if (!lista.empty())
            mergeSort(lista, 0, lista.size() - 1);

        return lista;
    }
};
