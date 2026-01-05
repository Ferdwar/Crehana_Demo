#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "UtilidadesConsola.h"
#include "ArbolBinarioBusqueda.h"
#include "Cursos.h"

using namespace std;

class Calificaciones {
public:

    // ========================================
    // FUNCION NUEVA: obtener nombre de curso por ID
    // ========================================
    static string obtenerNombreCursoPorID(int idBuscado) {
        ifstream file("Cursos.txt");   // <-- Ajusta el nombre según tu archivo real
        if (!file.is_open()) return "Curso no encontrado";

        string linea;
        while (getline(file, linea)) {
            Curso c = Curso::deserializar(linea);

            if (c.getID() == idBuscado)
                return c.getNombre();
        }

        return "Curso no encontrado";
    }

    // ========================================
    // MOSTRAR LISTA DE ESTUDIANTES
    // ========================================
    static void mostrarEstudiantes() {
        ifstream file("Estudiante.txt");
        if (!file.is_open()) {
            cout << "No se pudo abrir Estudiante.txt\n";
            return;
        }

        cout << "\nLISTA DE ESTUDIANTES :";

        string linea;
        while (getline(file, linea)) {

            int p1 = linea.find('|');
            int p2 = linea.find('|', p1 + 1);
            int p3 = linea.find('|', p2 + 1);
            int p4 = linea.find('|', p3 + 1);
            int p5 = linea.find('|', p4 + 1);

            string email = linea.substr(0, p1);
            string username = linea.substr(p2 + 1, p3 - p2 - 1);
            string rol = linea.substr(p5 + 1);

            cout << email << endl;
            cout << username << endl;
            cout << rol << endl;
            cout << "-----------------------------\n";
        }
        file.close();
    }

    // ========================================
    // OBTENER CURSOS COMPLETADOS POR UN USUARIO
    // ========================================
    static vector<int> obtenerCursosCompletados(string username) {
        ifstream file("CursosCompletados.txt");
        vector<int> cursos;

        if (!file.is_open()) {
            cout << "No se pudo abrir CursosCompletados.txt\n";
            return cursos;
        }

        string linea;
        while (getline(file, linea)) {
            int pos = linea.find('|');
            string user = linea.substr(0, pos);
            int idCurso = stoi(linea.substr(pos + 1));

            if (user == username)
                cursos.push_back(idCurso);
        }

        return cursos;
    }

    // ========================================
    // REGISTRAR CALIFICACION
    // ========================================
    static void registrarCalificacion(string username, int idCurso, int nota) {
        ofstream file("Calificaciones.txt", ios::app);
        int X = 60; // Columna central
        int Y = 5;  // Fila de inicio
        int fila = Y + 10;

        if (!file.is_open()) {
            cout << "Error al abrir Calificaciones.txt\n";
            return;
        }

        file << username << "|" << idCurso << "|" << nota << "\n";
        file.close();

        setColor(10);
        gotoxy(X, fila + 7); cout << ">>> Calificacion registrada correctamente.   ";
    }

    // ========================================
    // FLUJO COMPLETO DE CALIFICAR
    // ========================================
    static void calificarFlujo() {
        int X = 60; // Columna central
        int Y = 5;  // Fila de inicio

        // Título
        gotoxy(X, Y); cout << "========================================";
        gotoxy(X, Y + 1); cout << "           CALIFICAR ESTUDIANTE         ";
        gotoxy(X, Y + 2); cout << "========================================";

        setColor(11);
        mostrarEstudiantes();

        // Ingreso del estudiante
        string username;
        gotoxy(X, Y + 6); setColor(15); cout << "Ingrese el nombre del estudiante: ";
        cin >> username;

        vector<int> cursos = obtenerCursosCompletados(username);

        if (cursos.empty()) {
            setColor(12); // rojo
            gotoxy(X, Y + 8); cout << "El estudiante no tiene cursos completados.";
            return;
        }

        // Mostrar cursos completados
        setColor(14);
        gotoxy(X, Y + 8); cout << "Cursos completados por " << username << ":";
        int fila = Y + 10;
        setColor(11);
        for (int id : cursos) {
            gotoxy(X, fila);
            cout << " - ID: " << id << " | " << obtenerNombreCursoPorID(id);
            fila++;
        }

        // Selección de curso
           // Selección de curso
        int idCurso;
        bool existe = false;
        do {
            // Limpiar línea de entrada y mensaje anterior de error
            gotoxy(X, fila + 1); cout << string(50, ' ');
            gotoxy(X, fila + 2); cout << string(50, ' ');

            gotoxy(X, fila + 1); setColor(15); cout << "Ingrese el ID del curso a calificar: ";
            cin >> idCurso;
            existe = false;
            for (int c : cursos)
                if (c == idCurso) existe = true;
            if (!existe) {
                setColor(12);
                gotoxy(X, fila + 8); cout << "Ese curso no pertenece al estudiante. Intente nuevamente.";
            }
        } while (!existe);

        // Ingreso de nota
        int nota;
        do {
            // Limpiar línea de entrada y mensaje de error previo
            gotoxy(X, fila + 4); cout << string(50, ' ');
            gotoxy(X, fila + 5); cout << string(50, ' ');

            gotoxy(X, fila + 4); setColor(15); cout << "Ingrese la nota (0-20): ";
            cin >> nota;
            if (nota < 0 || nota > 20) {
                setColor(12);
                gotoxy(X, fila + 5); cout << "Nota inválida. Debe ser entre 0 y 20.";
            }
        } while (nota < 0 || nota > 20);

        registrarCalificacion(username, idCurso, nota);

    }

    // ========================================
    // FLUJO COMPLETO DE COMENTAR
    // ========================================
    static void comentarFlujo() {
        cout << "\n===== COMENTAR A ESTUDIANTE =====\n";

        mostrarEstudiantes();

        string username;
        cout << "\nIngrese el nombre del estudiante: ";
        cin >> username;

        vector<int> cursos = obtenerCursosCompletados(username);

        if (cursos.empty()) {
            cout << "\nEl estudiante no tiene cursos completados.\n";
            return;
        }

        cout << "\nCursos completados por " << username << ":\n";

        for (int id : cursos)
            cout << " - " << obtenerNombreCursoPorID(id)
            << " (ID: " << id << ")\n";

        int idCurso;
        cout << "\nIngrese el ID del curso a comentar: ";
        cin >> idCurso;

        bool existe = false;
        for (int c : cursos)
            if (c == idCurso) existe = true;

        if (!existe) {
            cout << "\nEse curso no pertenece al estudiante.\n";
            return;
        }

        cin.ignore();
        string comentario;
        cout << "Ingrese su comentario: ";
        getline(cin, comentario);

        ofstream file("Comentarios.txt", ios::app);
        if (!file.is_open()) {
            cout << "Error al abrir Comentarios.txt\n";
            return;
        }

        file << username << "|" << idCurso << "|" << comentario << "\n";
        file.close();

        cout << "\n>>> Comentario registrado correctamente.\n";
    }

    // ========================================
    // QUICK SORT PARA CALIFICACIONES
    // ========================================
    static int partition(vector<pair<int, int>>& arr, int low, int high) {
        int pivot = arr[high].second;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j].second > pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    static void quickSort(vector<pair<int, int>>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    // ========================================
    // MOSTRAR CALIFICACIONES DEL ALUMNO
    // ========================================
    static void verCalificaciones(string username) {
        ifstream file("Calificaciones.txt");

        if (!file.is_open()) {
            cout << "\nNo existe Calificaciones.txt\n";
            return;
        }

        cout << "\n====== CALIFICACIONES DE " << username << " ======\n";

        string linea;
        vector<pair<int, int>> calificaciones;

        while (getline(file, linea)) {
            int p1 = linea.find('|');
            int p2 = linea.find('|', p1 + 1);

            string user = linea.substr(0, p1);
            int idCurso = stoi(linea.substr(p1 + 1, p2 - p1 - 1));
            int nota = stoi(linea.substr(p2 + 1));

            if (user == username)
                calificaciones.push_back({ idCurso, nota });
        }

        file.close();

        if (calificaciones.empty()) {
            cout << "No tienes calificaciones aun.\n";
            return;
        }

        quickSort(calificaciones, 0, calificaciones.size() - 1);

        for (auto& c : calificaciones) {
            cout << "ID: " << c.first << "\n";
            cout << "Curso: " << obtenerNombreCursoPorID(c.first) << "\n";
            cout << "Nota: " << c.second << "\n";
            cout << "-----------------------------\n";
        }
    }

    // ========================================
    // MOSTRAR COMENTARIOS
    // ========================================
    static void verComentarios(string username) {
        ifstream file("Comentarios.txt");

        if (!file.is_open()) {
            cout << "\nNo existe Comentarios.txt\n";
            return;
        }

        cout << "\n====== COMENTARIOS PARA " << username << " ======\n";

        string linea;
        bool encontro = false;

        while (getline(file, linea)) {
            int p1 = linea.find('|');
            int p2 = linea.find('|', p1 + 1);

            string user = linea.substr(0, p1);
            int idCurso = stoi(linea.substr(p1 + 1, p2 - p1 - 1));
            string comentario = linea.substr(p2 + 1);

            if (user == username) {
                cout << "Curso ID: " << idCurso << "\n";
                cout << "Curso: " << obtenerNombreCursoPorID(idCurso) << "\n";
                cout << "Comentario: " << comentario << "\n";
                cout << "-----------------------------\n";
                encontro = true;
            }
        }

        if (!encontro)
            cout << "No tienes comentarios aun.\n";

        file.close();
    }
};

