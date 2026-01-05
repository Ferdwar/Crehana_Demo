#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Estudiante.h"

using namespace std;

// ==================
// NODO DE LA COLA
// ==================
struct NodoCola {
    Estudiante data;
    NodoCola* next;

    NodoCola(const Estudiante& e) {
        data = e;
        next = nullptr;
    }
};

// ====================
// COLA SIMPLE (FIFO)
// ====================
class ColaEstudiantes {
private:
    NodoCola* front; // Primer elemento
    NodoCola* rear;  // Último elemento

public:
    ColaEstudiantes() : front(nullptr), rear(nullptr) {}

    bool vacia() { return front == nullptr; }

    // ==============================
    // ENCOLAR (inserta al final)
    // ==============================
    void encolar(const Estudiante& e) {
        NodoCola* nuevo = new NodoCola(e);
        if (vacia()) front = rear = nuevo;
        else {
            rear->next = nuevo;
            rear = nuevo;
        }
    }

    // ==============================
    // DESENCOLAR (saca del frente)
    // ==============================
    void desencolar() {
        if (vacia()) return;
        NodoCola* temp = front;
        front = front->next;
        delete temp;
        if (front == nullptr) rear = nullptr;
    }

    // ==============================
    // CARGAR DESDE ARCHIVO
    // ==============================
    void cargarDesdeArchivo(const string& archivo = "Estudiante.txt") {
        ifstream file(archivo);
        if (!file.is_open()) {
            cout << "No se pudo abrir " << archivo << "\n";
            return;
        }

        string linea;
        while (getline(file, linea)) {
            Estudiante e = Estudiante::deserializar(linea);
            encolar(e);
        }
        file.close();
    }

    // ==============================
    // GUARDAR EN ARCHIVO
    // ==============================
    void guardarEnArchivo(const string& archivo = "Estudiante.txt") {
        ofstream out(archivo, ios::trunc);
        NodoCola* actual = front;
        while (actual) {
            out << actual->data.serializar() << "\n";
            actual = actual->next;
        }
        out.close();
    }

    // ==============================
    // ELIMINAR ESTUDIANTE POR USERNAME
    // ==============================
    void eliminarEstudiante(const string& username) {
        cargarDesdeArchivo();

        ColaEstudiantes colaTemporal;
        bool eliminado = false;

        while (!vacia()) {
            Estudiante e = front->data;
            if (e.getUsername() == username) {
                eliminado = true; // no se encola, se elimina
            }
            else {
                colaTemporal.encolar(e); // conservar
            }
            desencolar();
        }

        colaTemporal.guardarEnArchivo();

        if (eliminado)
            cout << "\nEstudiante eliminado correctamente.\n";
        else
            cout << "\nNo se encontro un estudiante con ese username.\n";
    }
};
