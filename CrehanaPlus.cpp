#include "pch.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include "Estudiante.h"
#include "Profesor.h"
#include "Administrador.h"
#include "Cursos.h"
#include "Nosotros.h"
#include "Registro.h"
#include "Login.h"
#include "UtilidadesConsola.h"
#include "ListaCursos.h"    
#include "ArbolBinarioBusqueda.h"
#include "AVL.h"           

using namespace System;
using namespace std;

// -------------------------------------------------
// Máquina de escribir animada
// -------------------------------------------------
void printWithDelay(string text, int delay = 30) {
    for (char c : text) {
        cout << c;
        Sleep(delay);
    }
}

void intro() {
    system("cls");
    system("chcp 437 > nul");

    const int X = 48, Y = 11;

    vector<string> titulo = {
        "  __________________________________________________________      ",
        " |     _____          _                                     |     ",
        " |    /  ___)_ __ ___| |__   __ _ _ __   __ _               |     ",
        " |    | |   | '__) _ \\ '_  \\/ _` | '_  \\/ _` |   |||  |||   |  ",
        " |    | |___| | |  __/ | | | (_| | | | | (_| |     ||||||   |     ",
        " |    \\_____)_|  \\___)_| |_|\\__,_|_| |_|\\__,_|   |||  |||   | ",
        " |__________________________________________________________|     "
    };

    setColor(9);
    for (int i = 0; i < titulo.size(); ++i) {
        gotoxy(X, Y + i);
        cout << titulo[i];
    }

    setColor(14);
    gotoxy(X + 11, Y + 8);
    printWithDelay("Clon de Crehana - Proyecto UPC 2025", 20);

    setColor(13);
    gotoxy(X + 15, Y + 10);
    cout << "Cargando: ";

    for (int i = 0; i <= 20; i++) {
        cout << (char)219;
        Sleep(50);
    }
}

// --------------------------------------------------------
// FUNCIÓN 3: MOSTRAR CURSOS UTILIZANDO ABB (inOrder)
// --------------------------------------------------------
void mostrarCursosConABB() {
    ListaCursos lista;          // Carga desde archivo automáticamente
    ABB<Curso> arbol;

    // Insertar cada curso del archivo al ABB (y debug print)
    NodoCurso* cur = lista.getHead();
    if (!cur) {
        gotoxy(50, 10);
        cout << "No hay cursos cargados en ListaCursos.\n";
        return;
    }

    cout << " Cursos leidos desde ListaCursos:\n";
    setColor(8);
    while (cur) {
        cout << "  - " << cur->data.getNombre() << "\n";   // Verificar contenido antes de insertar
        arbol.insertar(cur->data);
        cur = cur->next;
    }
    setColor(3);
    cout << "\n===== CURSOS (ORDENADOS ALFABETICAMENTE - ABB) =====\n\n";
    setColor(6);

    // Obtener vector con los cursos en-orden
    vector<Curso> cursosOrdenados = arbol.toListInOrder();

    if (cursosOrdenados.empty()) {
        cout << "No se encontraron cursos en el ABB.\n";
    }
    else {
        for (const Curso& c : cursosOrdenados) {
            // Imprimimos explícitamente el nombre (evitamos operator<<).
            cout << " [" << c.getID() << "] " << c.getNombre()
                << " (Prof: " << c.getProfesor() << ")\n";
        }
    }

    cout << "\n";
}

// --------------------------------------------------------
// FUNCIÓN 4: BUSCAR CURSOS USING AVL (buscarPorPrefijo)
// --------------------------------------------------------
void buscarCursosConAVL() {
    ListaCursos lista;      // Carga desde archivo
    AVL<Curso> avl;

    // Insertamos cursos en el AVL
    NodoCurso* cur = lista.getHead();
    while (cur) {
        avl.insertar(cur->data);
        cur = cur->next;
    }

    cout << "\nIngrese prefijo para buscar cursos: ";
    string prefijo;
    cin.ignore();
    getline(cin, prefijo);

    // Buscar con AVL
    NodoLista<Curso>* resultados = avl.buscarPorPrefijo(prefijo);

    cout << "\n===== RESULTADOS =====\n";

    if (!resultados) {
        cout << "No se encontraron cursos.\n";
        return;
    }

    NodoLista<Curso>* p = resultados;
    while (p) {
        cout << " - " << p->dato.getNombre() << "\n";
        p = p->sig;
    }
}

// --------------------------------------------------------
// MENÚ INVITADO
// --------------------------------------------------------
void mostrarMenuInvitado() {
    system("cls");
    setColor(11);

    int X = 60;
    int Y = 11;

    gotoxy(X, Y);   cout << " ==================================== ";
    gotoxy(X, Y + 1); cout << "||          MENU INVITADO           ||";
    gotoxy(X, Y + 2); cout << "||==================================||";
    gotoxy(X, Y + 3); cout << "|| 1. Registrarse                   ||";
    gotoxy(X, Y + 4); cout << "|| 2. Iniciar sesion                ||";
    gotoxy(X, Y + 5); cout << "|| 3. Explorar cursos (ABB)         ||";
    gotoxy(X, Y + 6); cout << "|| 4. Buscar cursos (AVL)           ||";
    gotoxy(X, Y + 7); cout << "|| 5. Nosotros                      ||";
    gotoxy(X, Y + 8); cout << "|| 6. Salir                         ||";
    gotoxy(X, Y + 9); cout << " ==================================== ";

    setColor(14);
    gotoxy(X, Y + 11);
    cout << "Seleccione una opcion: ";
}

// --------------------------------------------------------
// MAIN
// --------------------------------------------------------
int main() {
    int opcion;
    Registro r;
    Login l;

    intro();

    do {
        mostrarMenuInvitado();
        cin >> opcion;
        system("cls");

        switch (opcion)
        {
        case 1:
            r.registrarUsuario();
            break;

        case 2:
            l.iniciarSesion();
            break;

        case 3:
            mostrarCursosConABB();
            system("pause");
            break;

        case 4:
            buscarCursosConAVL();
            system("pause");
            break;

        case 5:
            Nosotros::mostrarInformacion();
            break;

        case 6:
            cout << "Saliendo del programa...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
            break;
        }

    } while (opcion != 6);

    return 0;
}
