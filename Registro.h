#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "UtilidadesConsola.h"
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

class Registro {
private:
    string email;
    string contrasena;
    string username;
    string cumpleanios;
    string genero;
    string rol;

    Date fecha;

    int baseX = 60;   // columna donde empiezan los textos
    int baseY = 9;    // fila despues del titulo


public:
    Registro() {}

    void imprimir(const string& texto, int offsetY, int color = 15) {
        setColor(color);
        gotoxy(baseX, baseY + offsetY);
        cout << texto;
        setColor(15);
    }

    void mostrarTitulo(const string& texto) {
        int anchoConsola = 120;
        int X = anchoConsola / 2 ; 
        int Y = 4;

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

    //  Pide la fecha al usuario (funcion recursiva)
    void pedirFecha() {
        system("cls");
        mostrarTitulo("FECHA DE NACIMIENTO");

        imprimir("Dia: ", 0, 14);
        gotoxy(baseX + 10, baseY + 0); cin >> fecha.day;

        imprimir("Mes: ", 1, 14);
        gotoxy(baseX + 10, baseY + 1); cin >> fecha.month;

        imprimir("Anio: ", 2, 14);
        gotoxy(baseX + 10, baseY + 2); cin >> fecha.year;

        if (!fechaValida()) {
            imprimir("Fecha invalida. Intente nuevamente.", 4, 12);
            Sleep(1500);
            pedirFecha();
        }
    }

    // verifica si la fecha ingresada es valida
    bool fechaValida() const {
        if (fecha.year < 1900 || fecha.year > 2012 ||
            fecha.month < 1 || fecha.month > 12 ||
            fecha.day < 1)
            return false;

        int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        bool bisiesto =
            (fecha.year % 4 == 0 && fecha.year % 100 != 0) ||
            (fecha.year % 400 == 0);

        if (bisiesto) daysInMonth[1] = 29;

        return fecha.day <= daysInMonth[fecha.month - 1];
    }

    // pide el genero (funcion recursiva)
    void pedirGenero() {
        int g;
        system("cls");
        mostrarTitulo("SELECCIONE SU GENERO");

        imprimir("1. Masculino", 0);
        imprimir("2. Femenino", 1);
        imprimir("3. Otro", 2);

        imprimir("Opcion: ", 4, 14);
        gotoxy(baseX + 10, baseY + 4);
        cin >> g;

        switch (g) {
        case 1: genero = "Masculino"; break;
        case 2: genero = "Femenino"; break;
        case 3: genero = "Otro"; break;
        default:
            imprimir("Opcion invalida. Intente nuevamente.", 6, 12);
            Sleep(1500);
            pedirGenero();
        }
    }


    // pide el rol (funcion recursiva)
    void pedirRol() {
        int r;
        system("cls");
        mostrarTitulo("SELECCIONE SU ROL");
        imprimir("1. Estudiante", 0);
        imprimir("2. Profesor", 1);
        imprimir("3. Administrador", 2);

        imprimir("Opcion: ", 4, 14);
        gotoxy(baseX + 10, baseY + 4);
        cin >> r;

        switch (r) {
        case 1: rol = "Estudiante"; break;
        case 2: rol = "Profesor"; break;
        case 3: rol = "Administrador"; break;
        default:
            imprimir("Opcion invalida. Intente nuevamente.", 6, 12);
            Sleep(1500);
        }
    }


    // Verificar si el email ya existe en un archivo
    bool emailExisteEnArchivo(const string& archivo, const string& emailBuscado) {
        ifstream file(archivo);
        if (!file.is_open()) return false;

        string linea;
        while (getline(file, linea)) {
            if (linea.find("Email: " + emailBuscado) != string::npos) {
                return true;
            }
        }
        return false;
    }

    // Guardar el registro en el archivo correspondiente
    void guardarEnArchivo() {
        string archivo = rol + ".txt";
        ofstream file(archivo, ios::app);

        if (!file.is_open()) {
            cout << "ERROR: No se pudo abrir " << archivo << endl;
            return;
        }

        file << "Email: " << email << "| ";
        file << "Contraseña: " << contrasena << "| ";
        file << "Usuario: " << username << "|";
        file << "Cumpleaños: "
            << fecha.day << "/" << fecha.month << "/" << fecha.year
            << " | ";
        file << "Genero: " << genero << " | ";
        file << "Rol: " << rol << "\n";

        file.close();
    }

    void mostrarDatos() {
        system("cls");
        mostrarTitulo("DATOS DEL USUARIO");

        int X = 60;   // posición horizontal base
        int Y = 10;   // inicio de los datos

        setColor(11);
        gotoxy(X, Y);
        cout << "Email: ";
        setColor(15);
        cout << email;

        gotoxy(X, Y + 1);
        setColor(11);
        cout << "Contrasena: ";
        setColor(15);
        cout << contrasena;

        gotoxy(X, Y + 2);
        setColor(11);
        cout << "Usuario: ";
        setColor(15);
        cout << username;

        gotoxy(X, Y + 3);
        setColor(11);
        cout << "Cumpleanos: ";
        setColor(15);
        cout << fecha.day << "/" << fecha.month << "/" << fecha.year;

        gotoxy(X, Y + 4);
        setColor(11);
        cout << "Genero: ";
        setColor(15);
        cout << genero;

        gotoxy(X, Y + 5);
        setColor(11);
        cout << "Rol: ";
        setColor(15);
        cout << rol;

        setColor(14);
        gotoxy(X, Y + 7);
        system("pause");

    }


    // Registro de usuario
    void registrarUsuario() {
        mostrarTitulo("REGISTRO DE USUARIO");
        cin.ignore();


        // Email
        imprimir("Ingrese su email: ", 0, 14);
        gotoxy(baseX + 22, baseY + 0);
        getline(cin, email);

        // Validación de email repetido
        if (emailExisteEnArchivo("Estudiante.txt", email) ||
            emailExisteEnArchivo("Profesor.txt", email) ||
            emailExisteEnArchivo("Administrador.txt", email))
        {
            imprimir("El email ya esta registrado. Intente con otro.", 2, 12);
            Sleep(1800);
            return;
        }

        // Contraseña
        imprimir("Ingrese su contrasenia: ", 3, 14);
        gotoxy(baseX + 25, baseY + 3);
        getline(cin, contrasena);

        // Nombre de usuario
        imprimir("Ingrese su nombre de usuario: ", 5, 14);
        gotoxy(baseX + 30, baseY + 5);
        getline(cin, username);


        // Pedir fecha validada
        pedirFecha();

        // Pedir genero validado
        pedirGenero();

        // Pedir rol validado
        pedirRol();

        // Guardar
        guardarEnArchivo();

        system("cls");
        // Mensaje de éxito
        setColor(10);
        gotoxy(baseX, baseY);
        cout << ">>> Registro completado y guardado correctamente.";
        setColor(15);

        // Pregunta
        int ver;
        setColor(14);
        gotoxy(baseX, baseY + 2);
        cout << "Desea ver sus datos? (1 = Si, 2 = No): ";
        setColor(15);

        gotoxy(baseX + 10, baseY + 4); // mover cursor donde escribe el usuario
        cin >> ver;


        if (ver == 1) {
            mostrarDatos();
        }
        system("cls");
        cout << "\n";
    }

};