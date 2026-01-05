#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Cursos.h"
using namespace std;

// Nodo para la lista enlazada de cursos
struct NodoCurso {
    Curso data;
    NodoCurso* next;
    NodoCurso(const Curso& c) : data(c), next(nullptr) {}
};

// Lista enlazada simple para cursos
class ListaCursos {
private:
    NodoCurso* head;

public:
    ListaCursos() : head(nullptr) {
        cargarDesdeArchivo();
    }

    ~ListaCursos() {
        NodoCurso* cur = head;
        while (cur) {
            NodoCurso* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }

    // ========================================
    // GETTERS PARA ADMINISTRADOR
    // ========================================
    NodoCurso* getHead() {      
        return head;
    }

    Curso* buscarPorID(int id) { 
        NodoCurso* cur = head;
        while (cur) {
            if (cur->data.getID() == id)
                return &(cur->data);
            cur = cur->next;
        }
        return nullptr;
    }

    Curso* buscarPorNombre(const string& nombre) {  
        NodoCurso* cur = head;
        while (cur) {
            if (cur->data.getNombre() == nombre)
                return &(cur->data);
            cur = cur->next;
        }
        return nullptr;
    }

    bool insertarCurso(const Curso& c) { 
        if (existeID(c.getID())) return false;

        NodoCurso* nuevo = new NodoCurso(c);

        if (!head) head = nuevo;
        else {
            NodoCurso* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = nuevo;
        }

        guardarEnArchivo();
        return true;
    }

    bool eliminarPorID(int id) {  
        NodoCurso* cur = head;
        NodoCurso* prev = nullptr;

        while (cur) {
            if (cur->data.getID() == id) {
                if (prev) prev->next = cur->next;
                else head = cur->next;
                delete cur;
                guardarEnArchivo();
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    // ========================================
    // CARGAR DESDE ARCHIVO
    // ========================================
    void cargarDesdeArchivo(const string& filename = "Cursos.txt") {
        NodoCurso* cur = head;
        while (cur) {
            NodoCurso* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
        head = nullptr;

        ifstream file(filename);
        if (!file.is_open()) return;

        string linea;
        NodoCurso* tail = nullptr;

        while (getline(file, linea)) {
            if (linea.empty()) continue;

            Curso c = Curso::deserializar(linea);
            NodoCurso* nuevo = new NodoCurso(c);

            if (!head) {
                head = nuevo;
                tail = nuevo;
            }
            else {
                tail->next = nuevo;
                tail = nuevo;
            }
        }
        file.close();
    }

    // ========================================
    // GUARDAR EN ARCHIVO
    // ========================================
    void guardarEnArchivo(const string& filename = "Cursos.txt") {
        ofstream out(filename, ios::trunc);
        if (!out.is_open()) {
            cout << "Error al abrir " << filename << " para guardar.\n";
            return;
        }

        NodoCurso* cur = head;
        while (cur) {
            out << cur->data.serializar() << "\n";
            cur = cur->next;
        }

        out.close();
    }

    // ========================================
    // AGREGAR CURSO (interactivo)
    // ========================================
    void agregarCurso() {
        cout << "\n===== AGREGAR NUEVO CURSO =====\n";

        int id;
        string nombre, descripcion, profesor;

        cout << "ID del curso: ";
        cin >> id;
        cin.ignore();

        if (existeID(id)) {
            cout << "Ya existe un curso con ese ID.\n";
            return;
        }

        cout << "Nombre: ";
        getline(cin, nombre);

        cout << "Descripción: ";
        getline(cin, descripcion);

        cout << "Profesor: ";
        getline(cin, profesor);

        insertarCurso(Curso(id, nombre, descripcion, profesor));
        cout << ">>> Curso agregado correctamente.\n";
    }

    // ========================================
    // ELIMINAR CURSO (interactivo)
    // ========================================
    void eliminarCurso() {
        cout << "\n===== ELIMINAR CURSO =====\n";
        cout << "1. Por ID\n2. Por Nombre\nOpcion: ";

        int opcion;
        cin >> opcion;
        cin.ignore();

        if (!head) {
            cout << "No hay cursos registrados.\n";
            return;
        }

        bool eliminado = false;

        if (opcion == 1) {
            int idEliminar;
            cout << "Ingrese ID: ";
            cin >> idEliminar;
            cin.ignore();

            eliminado = eliminarPorID(idEliminar);
        }

        else if (opcion == 2) {
            string nombre;
            cout << "Ingrese nombre: ";
            getline(cin, nombre);

            Curso* c = buscarPorNombre(nombre);
            if (c) eliminado = eliminarPorID(c->getID());
        }

        else {
            cout << "Opción inválida.\n";
            return;
        }

        if (eliminado)
            cout << ">>> Curso eliminado correctamente.\n";
        else
            cout << "No se encontró el curso especificado.\n";
    }

    // ========================================
    // LISTAR CURSOS
    // ========================================
    void listarCursos() {
        if (!head) {
            cout << "No hay cursos registrados.\n";
            return;
        }

        cout << "\n===== LISTA DE CURSOS =====\n";

        NodoCurso* cur = head;
        while (cur) {
            cout << "ID: " << cur->data.getID()
                << "\nNombre: " << cur->data.getNombre()
                << "\nDescripción: " << cur->data.getDescripcion()
                << "\nProfesor: " << cur->data.getProfesor()
                << "\n-----------------------------\n";
            cur = cur->next;
        }
    }

    bool existeID(int idBuscado) {
        NodoCurso* cur = head;
        while (cur) {
            if (cur->data.getID() == idBuscado)
                return true;
            cur = cur->next;
        }
        return false;
    }

    void recargar() {
        cargarDesdeArchivo();
    }
};
