#pragma once
#include <iostream>
#include <string>
#include <fstream> // <-- agregar esto si aún no está
#include "Cursos.h"
#include "Calificaciones.h"
#include "UtilidadesConsola.h"
#include "Estudiante.h"
#include "ArbolBinarioBusqueda.h"
#include "AVL.h"
using namespace std;

class EstudiantesManager {
private:
    string username;
    int anchoConsola = 120;
    int X = 60;
    int Y = 3;
    Estudiante estudianteActual; // objeto del estudiante logueado

public:
    EstudiantesManager(string user = "") : username(user), estudianteActual(user) {}

    void mostrarTitulo(const string& texto) {
        setColor(11);
        gotoxy(X, Y);
        cout << "=========================================";

        setColor(14);
        gotoxy(X, Y + 1);
        cout << "        " << texto;

        setColor(11);
        gotoxy(X, Y + 2);
        cout << "=========================================";

        setColor(15);
    }
    void mostrarPerfil() {
        mostrarTitulo("MI PERFIL");
        cout << endl;

        int cx = X;
        int y = Y + 4;

        setColor(14);
        gotoxy(cx, y++); cout << "Username:       "; setColor(15); cout << estudianteActual.getUsername();
       
        setColor(14);
        gotoxy(cx, y++); cout << "Rol:            "; setColor(15); cout << estudianteActual.getRol();

        int totalCursos = estudianteActual.getCursos().size();
        int completados = 0;
        for (auto& c : estudianteActual.getCursos())
            if (c.completado) completados++;

        setColor(14);
        gotoxy(cx, y++); cout << "Cursos registrados: "; setColor(15); cout << totalCursos;
        setColor(14);
        gotoxy(cx, y++); cout << "Cursos completados: "; setColor(15); cout << completados;

        cout << "\n";
    }


    void cargarCursosDesdeTXT(ABB<Curso>& abb, const string& filename) {
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "No existe el archivo " << filename << endl;
            return;
        }

        string linea;
        while (getline(file, linea)) {
            if (linea.empty()) continue;

            int p1 = linea.find('|');
            int p2 = linea.find('|', p1 + 1);
            int p3 = linea.find('|', p2 + 1);

            int id = stoi(linea.substr(0, p1));
            string nombre = linea.substr(p1 + 1, p2 - p1 - 1);
            string descripcion = linea.substr(p2 + 1, p3 - p2 - 1);
            string profesor = linea.substr(p3 + 1);

            Curso c(id, nombre, descripcion, profesor);
            abb.insertar(c);
        }

        file.close();
    }

    void explorarCursos(ABB<Curso>& abbCursos, AVL<Curso>& avlCursos) {
        mostrarTitulo("EXPLORAR CURSOS");
        cout << endl;
        // Cargar datos desde el TXT
        cargarCursosDesdeTXT(abbCursos, "Cursos.txt");
        abbCursos.mostrarInOrder(); // Mostrar cursos disponibles

        int id;
        cout << "\nIngrese el ID del curso que desea registrar (0 para cancelar): ";
        cin >> id;

        if (id != 0) {
            estudianteActual.registrarCurso(id);
            cout << "\n>>> Curso registrado y en proceso.\n";
        }
    }

    void guardarCursoCompletado(const Estudiante& est, int cursoID, const string& nombreCurso) {
        ofstream file("CursosCompletados.txt", ios::app);

        if (!file.is_open()) {
            cout << "No se pudo abrir CursosCompletados.txt\n";
            return;
        }

        file << est.getUsername() << "|"
            << cursoID << "|"
            << nombreCurso << "|Completado: Si\n";

        file.close();
    }

    void verMisCursos() {
        mostrarTitulo("MIS CURSOS");
        cout << endl;

        int cx = X;
        int y = Y + 4;

        const auto& cursos = estudianteActual.getCursos();
        if (cursos.empty()) {
            gotoxy(cx, y);
            cout << "No tiene cursos registrados.\n";
            return;
        }

        for (const auto& c : cursos) {
            gotoxy(cx, y++);
            cout << "ID: " << c.cursoID
                << " | Nota: " << (c.nota == -1 ? 0 : c.nota)
                << " | Estado: " << (c.completado ? "Completado" : "En proceso");
        }

        int id;
        gotoxy(cx, y + 2);
        cout << "Ingrese el ID del curso a completar (0 para cancelar): ";
        cin >> id;

        if (id != 0) {
            string nombreCurso = Curso::buscarNombrePorID(id);
            estudianteActual.completarCurso(id);
            guardarCursoCompletado(estudianteActual, id, nombreCurso);

            gotoxy(cx, y + 4);
            cout << ">>> Curso marcado y guardado como completado.\n";
        }
    }


    void mostrarMenu(ABB<Curso>& abbCursos, AVL<Curso>& avlCursos) {
        int opcion;
        do {
            system("pause");
            system("cls");
            setColor(11);

            gotoxy(X, Y);   cout << " ==================================== ";
            gotoxy(X, Y + 1); cout << "||                                  ||";
            gotoxy(X, Y + 2); cout << "||        MENU ESTUDIANTE           ||";
            gotoxy(X, Y + 3); cout << "||                                  ||";
            gotoxy(X, Y + 4); cout << "||==================================||";
            gotoxy(X, Y + 5); cout << "||   1. Explorar cursos             ||";
            gotoxy(X, Y + 6); cout << "||   2. Mis cursos                  ||";
            gotoxy(X, Y + 7); cout << "||   3. Perfil                      ||";
            gotoxy(X, Y + 8); cout << "||   4. Ver calificaciones          ||";
            gotoxy(X, Y + 9); cout << "||   5. Ver comentarios             ||";
            gotoxy(X, Y + 10); cout << "||   6. Cerrar sesion               ||";
            gotoxy(X, Y + 11); cout << "||                                  ||";
            gotoxy(X, Y + 12); cout << " ==================================== ";
            setColor(14);

            gotoxy(X, Y + 14);
            cout << "  Seleccione una opcion: ";
            cin >> opcion;
            system("cls");

            switch (opcion) {
            case 1:
                explorarCursos(abbCursos, avlCursos);
                break;
            case 2:
                verMisCursos();
                break;
            case 3:
                mostrarPerfil();
                break;

            case 4:
                Calificaciones::verCalificaciones(username);
                break;
            case 5:
                Calificaciones::verComentarios(username);
                break;
            case 6:
                cout << "\n>>> Cerrando sesion...\n";
                break;
            default:
                cout << "\n Opcion invalida, intente nuevamente.\n";
            }

        } while (opcion != 6);
    }
};
