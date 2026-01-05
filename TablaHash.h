#pragma once
#include <iostream>
#include <iomanip> // para setw
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// =========================
// ESTRUCTURA DEL CURSO
// =========================
template <class T>
struct CursoHash {
    int id;
    string nombre;
    string descripcion;
    string profesor;
    T data; 

    CursoHash(int _id = 0, string n = "", string d = "", string p = "", T _data = T()) {
        id = _id;
        nombre = n;
        descripcion = d;
        profesor = p;
        data = _data;
    }
};

// =========================
// CLASE TABLA HASH
// =========================
template <class T>
class HashTable {
private:
    static const int CAPACIDAD = 20;
    static const int MAX_COLISIONES = 4;
    vector<vector<CursoHash<T>>> tabla;

    // =========================
    // FUNCION HASH
    // =========================
    int hashFunction(int id) {
        return id % CAPACIDAD;
    }

public:
    HashTable() {
        tabla.resize(CAPACIDAD);
    }

    // =========================
    // LEER CURSOS DESDE ARCHIVO
    // =========================
    void cargarDesdeArchivo(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error al abrir " << filename << endl;
            return;
        }

        string linea;
        while (getline(file, linea)) {
            stringstream ss(linea);
            string idStr, nombre, descripcion, profesor;

            getline(ss, idStr, '|');
            getline(ss, nombre, '|');
            getline(ss, descripcion, '|');
            getline(ss, profesor, '|');

            int id = stoi(idStr);
            CursoHash<T> curso(id, nombre, descripcion, profesor);

            // ===== insertar respetando max 4 colisiones =====
            int index = hashFunction(id);
            int startIndex = index;
            bool insertado = false;

            do {
                if (tabla[index].size() < MAX_COLISIONES) {
                    tabla[index].push_back(curso);
                    insertado = true;
                    break;
                }
                index = (index + 1) % CAPACIDAD; // siguiente indice circular
            } while (index != startIndex);

            if (!insertado) {
                cout << "No se pudo insertar el curso " << id
                    << " (" << nombre << ") - tabla llena o max 4 colisiones alcanzadas en todos los indices\n";
            }
        }

        file.close();
    }

    // =========================
    // MOSTRAR TABLA HASH
    // =========================
    void mostrar() {
        cout << "\n===== TABLA HASH DE CURSOS =====\n";
        for (int i = 0; i < CAPACIDAD; i++) {
            cout << "Indice " << i << ": ";
            if (tabla[i].empty()) {
                cout << "(vacio)\n";
            }
            else {
                for (auto& c : tabla[i]) {
                    cout
                        << setw(2) << c.id << " "
                        << setw(28) << left << c.nombre
                        << " | ";
                }
                cout << "\n";
            }
        }
    }
};
 