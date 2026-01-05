#pragma once
#include <iostream>
#include <string>
#include "ArbolBinarioBusqueda.h"
#include "AVLEstudiante.h"
#include "Calificaciones.h"
#include "GeneradorData.h"
#include "UtilidadesConsola.h"
using namespace std;

class Profesor {
private:
    string username;
    int X = 60;
    int Y = 11;

public:
    Profesor(string user = "") {
        username = user;
    }

    // ===========================
    // Calificar estudiante
    // ===========================
    void calificarEstudiante(AVLEstudiantes& avlEst) {
        string user;

        Calificaciones::calificarFlujo();
    }

    // ===========================
    // Comentar estudiante
    // ===========================
    void comentarEstudiante(AVLEstudiantes& avlEst) {
        string user;

        Calificaciones::comentarFlujo();
    }

    // ===========================
    // Eliminar estudiante de un curso
    // ===========================
    void eliminarEstudianteDeCurso() {
        string user;
        int idCurso;
        cout << "\nIngrese username del estudiante a eliminar de curso: ";
        cin >> user;
        cout << "Ingrese ID del curso: ";
        cin >> idCurso;

        ifstream fileIn("CursosCompletados.txt");
        ofstream fileOut("temp.txt");
        string linea;
        bool eliminado = false;

        while (getline(fileIn, linea)) {
            int pos = linea.find('|');
            string u = linea.substr(0, pos);
            int id = stoi(linea.substr(pos + 1));

            if (u == user && id == idCurso) {
                eliminado = true;
            }
            else {
                fileOut << linea << "\n";
            }
        }
        fileIn.close();
        fileOut.close();
        remove("CursosCompletados.txt");
        rename("temp.txt", "CursosCompletados.txt");

        if (eliminado)
            cout << "\nEstudiante eliminado del curso correctamente.\n";
        else
            cout << "\nNo se encontró el estudiante en ese curso.\n";
    }

    // ===========================
    // Mostrar menú
    // ===========================
    void mostrarMenu(AVLEstudiantes& avlEst) {
        int opcion;
        ABB<int> arbolCursos;

        int ids[] = { 40, 4, 30, 57, 20, 21, 45, 60 };
        int n = sizeof(ids) / sizeof(ids[0]);
        for (int i = 0; i < n; i++)
            arbolCursos.insertar(ids[i]);

        do {
            system("pause");
            system("cls");
            setColor(11);

            gotoxy(X, Y);   cout << " ===================================================";
            gotoxy(X, Y + 1); cout << "||                                                 ||";
            gotoxy(X, Y + 2); cout << "||                   MENU PROFESOR                 ||";
            gotoxy(X, Y + 3); cout << "||                                                 ||";
            gotoxy(X, Y + 4); cout << "||=================================================||";
            gotoxy(X, Y + 5); cout << "||                                                 ||";
            gotoxy(X, Y + 6); cout << "||    1. Calificar estudiante                      ||";
            gotoxy(X, Y + 7); cout << "||    2. Comentar a estudiante                     ||";
            gotoxy(X, Y + 8); cout << "||    3. Poner Cursos en ABB (IN ORDEN) por ID     ||";
            gotoxy(X, Y + 9); cout << "||    4. Registro de calificaciones                ||";
            gotoxy(X, Y + 10); cout << "||    5. Generar Data Set (Lista Calificaciones)   ||";
            gotoxy(X, Y + 11); cout << "||    6. Eliminar estudiante de curso              ||";
            gotoxy(X, Y + 12); cout << "||    7. Cerrar sesion                             ||";
            gotoxy(X, Y + 13); cout << "||                                                 ||";
            gotoxy(X, Y + 14); cout << " =================================================== ";
            setColor(14);

            gotoxy(X, Y + 16);
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            system("cls");

            switch (opcion) {
            case 1: calificarEstudiante(avlEst); break;
            case 2: comentarEstudiante(avlEst); break;
            case 3: arbolCursos.mostrarInOrder(); break;
            case 4: GeneradorData<string>::verTodasLasCalificaciones(); break;
            case 5: GeneradorData<string>::generarDataset(); break;
            case 6: eliminarEstudianteDeCurso(); break;
            case 7: cout << "\nCerrando sesion...\n"; break;
            default: cout << "\nOpcion invalida, intente nuevamente.\n"; break;
            }

        } while (opcion != 7);
    }
};
