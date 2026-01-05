#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> 
#include "EstudianteManager.h"
#include "Profesor.h"
#include "Administrador.h"
#include "UtilidadesConsola.h"
#include "ArbolBinarioBusqueda.h"
#include "AVL.h"
#include "AVLEstudiante.h"
#include <windows.h>
using namespace std;

class Login {
private:
    string email;
    string contrasena;

public:
    Login() {}

    // ========================================
    // BUSCAR DATOS EN ARCHIVOS
    // ========================================
    bool buscarEnArchivo(const string& archivo, string& rolEncontrado, string& usernameEncontrado) {
        ifstream file(archivo);
        if (!file.is_open()) return false;

        string linea;
        while (getline(file, linea)) {

            if (linea.find("Email: " + email) != string::npos &&
                linea.find("Contraseña: " + contrasena) != string::npos) {

                // Extraer rol
                size_t posRol = linea.find("Rol: ");
                if (posRol != string::npos)
                    rolEncontrado = linea.substr(posRol + 5);

                // Extraer username
                size_t posUser = linea.find("Usuario: ");
                if (posUser != string::npos) {
                    size_t finUser = linea.find("|", posUser);
                    usernameEncontrado = linea.substr(posUser + 9, finUser - (posUser + 9));
                }

                file.close();
                return true;
            }
        }

        return false;
    }

    string leerContrasenia() {
        string password = "";
        char c;

        while (true) {
            c = _getch();  // Lee una tecla sin mostrarla en pantalla

            if (c == 13) { // ENTER (ASCII 13)
                cout << endl;
                break;
            }
            else if (c == 8) { // BACKSPACE
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b"; // borrar el último '*'
                }
            }
            else {
                password += c;
                cout << "*";
            }
        }
        return password;
    }

    // ========================================
    // INICIAR SESIÓN
    // ========================================
    void iniciarSesion() {
        system("cls");
        setColor(11);

        int anchoConsola = 120;
        int anchoCaja = 60;
        int X = (anchoConsola - anchoCaja);
        int Y = 6;

        gotoxy(X, Y);     cout << " ============================================";
        gotoxy(X, Y + 1); cout << "||              INICIO DE SESION            ||";
        gotoxy(X, Y + 2); cout << "||------------------------------------------||";
        gotoxy(X, Y + 3); cout << "||                                          ||";
        gotoxy(X, Y + 4); cout << "||  Email:                                  ||";
        gotoxy(X, Y + 5); cout << "||                                          ||";
        gotoxy(X, Y + 6); cout << "||  Contrasenia:                            ||";
        gotoxy(X, Y + 7); cout << "||                                          ||";
        gotoxy(X, Y + 8); cout << " ============================================";

        // Input email
        setColor(14);
        gotoxy(X + 11, Y + 4);
        cin.ignore();
        getline(cin, email);

        // Input contraseña
        gotoxy(X + 18, Y + 6);
        contrasena = leerContrasenia();


        setColor(15);
        cout << endl;

        string rolEncontrado;
        string usernameEncontrado;

        // Buscar usuario
        if (buscarEnArchivo("Estudiante.txt", rolEncontrado, usernameEncontrado) ||
            buscarEnArchivo("Profesor.txt", rolEncontrado, usernameEncontrado) ||
            buscarEnArchivo("Administrador.txt", rolEncontrado, usernameEncontrado))
        {
            setColor(10);
            gotoxy(X, Y + 10);
            cout << "Inicio de sesión exitoso";

            gotoxy(X, Y + 11);
            cout << "Rol detectado: " << rolEncontrado;

            gotoxy(X, Y + 12);
            cout << "Bienvenido(a): " << usernameEncontrado;

            setColor(7);
            gotoxy(X, Y + 14);
            Sleep(1500);

            // ========================================
            // SELECCIÓN DE MENÚ SEGÚN ROL
            // ========================================
            if (rolEncontrado == "Estudiante") {

                // Árboles necesarios según la clase EstudiantesManager
                ABB<Curso> abbCursos;
                AVL<Curso> avlCursos;

                EstudiantesManager est(usernameEncontrado);
                est.mostrarMenu(abbCursos, avlCursos);  // ✔ corregido
            }
            else if (rolEncontrado == "Profesor") {

                // Crear AVL de estudiantes para el menú profesor
                AVLEstudiantes avlEst;
                // Aquí puedes cargar estudiantes desde archivo si lo necesitas
                avlEst.cargarDesdeArchivo("Estudiante.txt"); // Carga todos los estudiantes

                Profesor prof(usernameEncontrado);
                prof.mostrarMenu(avlEst);  // ✔ corregido
            }
            else if (rolEncontrado == "Administrador") {
                Administrador admin(usernameEncontrado);
                admin.mostrarMenu();  // ✔ correcto
            }
        }
        else {
            setColor(12);
            gotoxy(X, Y + 10);
            cout << " Email o contraseña incorrectos.";
            Sleep(1500);
        }

        cout << "\n";
    }
};
