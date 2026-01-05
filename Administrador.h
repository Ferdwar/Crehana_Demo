#pragma once
#include <iostream>
#include <string>
#include "ListaCursos.h"
#include "UtilidadesConsola.h"
#include "TablaHash.h"
#include "AVL.h"
using namespace std;

class Administrador {
private:
    string username;
    int anchoConsola = 120;
    int X = 60;
    int Y = 11;

public:

    Administrador(string user = "") {
        this->username = user;
    }

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

    // ==================================================
    //  AGREGAR – ELIMINAR – LISTAR
    // ==================================================
    void agregarCurso() {
        mostrarTitulo("AGREGAR CURSO");
        ListaCursos lista;
        lista.agregarCurso();
    }

    void eliminarCurso() {
        mostrarTitulo("ELIMINAR CURSO");
        ListaCursos lista;
        lista.eliminarCurso();
    }

    void listarCursos() {
        mostrarTitulo("LISTA DE CURSOS");
        ListaCursos lista;
        lista.listarCursos();
    }

    void listarCursosHash() {
        HashTable <int>hash;
        hash.cargarDesdeArchivo("Cursos.txt");
        hash.mostrar();
    }

    // ==================================================
    //  FUNCIONES AVL PARA BUSQUEDA AVANZADA POR PREFIJO
    // ==================================================
    void buscarCursoPorPrefijo() {
        mostrarTitulo("BUSQUEDA AVANZADA POR PREFIJO");

        // 1. Obtener todos los cursos desde la lista
        ListaCursos lista;
        NodoCurso* p = lista.getHead();

        AVL<Curso> arbol;

        // 2. Insertar cada curso en el AVL
        while (p != nullptr) {
            arbol.insertar(p->data);
            p = p->next;
        }

        cout << "\nIngrese prefijo del nombre del curso: ";
        string prefijo;
        cin >> prefijo;

        // 3. Realizar búsqueda por prefijo en AVL
        arbol.buscarPorPrefijo(prefijo);
    }

    void explorarCursosAVL() {
        mostrarTitulo("EXPLORAR CURSOS (POSTORDER AVL)");

        ListaCursos lista;
        NodoCurso* p = lista.getHead();

        AVL<Curso> arbol;

        while (p != nullptr) {
            arbol.insertar(p->data);
            p = p->next;
        }

        arbol.mostrarPostOrder();
    }

    // ==================================================
    //                    MENU
    // ==================================================
    void mostrarMenu() {
        int opcion;

        do {
            system("cls");
            setColor(11);

            gotoxy(X, Y);     cout << " ===================================================";
            gotoxy(X, Y + 1); cout << "||                                                 ||";
            gotoxy(X, Y + 2); cout << "||               MENU ADMINISTRADOR                ||";
            gotoxy(X, Y + 3); cout << "||                                                 ||";
            gotoxy(X, Y + 4); cout << "||=================================================||";
            gotoxy(X, Y + 5); cout << "||                                                 ||";
            gotoxy(X, Y + 6); cout << "||   1. Agregar curso                              ||";
            gotoxy(X, Y + 7); cout << "||   2. Eliminar curso                             ||";
            gotoxy(X, Y + 8); cout << "||   3. Listar cursos                              ||";
            gotoxy(X, Y + 9); cout << "||   4. Buscar curso por prefijo (AVL)             ||";
            gotoxy(X, Y + 10); cout << "||   5. Explorar cursos (AVL)                      ||";
            gotoxy(X, Y + 11); cout << "||   6. Listar cursos en tabla hash                ||";
            gotoxy(X, Y + 12); cout << "||   7. Cerrar sesión                              ||";
            gotoxy(X, Y + 13); cout << "||                                                 ||";
            gotoxy(X, Y + 14); cout << " ===================================================";

            setColor(14);
            gotoxy(X, Y + 15);
            cout << "  Seleccione una opcion: ";
            cin >> opcion;

            system("cls");

            switch (opcion) {
            case 1: agregarCurso(); break;
            case 2: eliminarCurso(); break;
            case 3: listarCursos(); break;
            case 4: buscarCursoPorPrefijo(); break;
            case 5: explorarCursosAVL(); break;
			case 6: listarCursosHash(); break;
            case 7: cout << "\nCerrando sesion...\n"; break;
            default: cout << "\nOpcion invalida.\n"; break;
            }

            system("pause");

        } while (opcion != 7);
    }
};
