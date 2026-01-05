#pragma once
#include <iostream>
#include <string>
#include "UtilidadesConsola.h"
using namespace std;

class Nosotros {
public:

    // ============================
    // Muestra informacion del equipo
    // ============================
    static void mostrarInformacion() {
        int X = 60;
        int Y = 10;

        setColor(14);
        gotoxy(X, Y); cout << "====================================\n";
        gotoxy(X, Y + 1); cout << "         SOBRE EL PROGRAMA           \n";
        gotoxy(X, Y + 2); cout << "====================================\n";
        setColor(3);
        gotoxy(X, Y + 3); cout << "Nombre del sistema: CrehanaPlus\n";
        gotoxy(X, Y + 4); cout << "Version: 2.0\n";
        gotoxy(X, Y + 5); cout << "Descripcion: Este sistema permite a estudiantes\n";
        gotoxy(X, Y + 6); cout << "visualizar cursos, completarlos, recibir calificaciones\n";
        gotoxy(X, Y + 7); cout << "y comentarios de profesores.\n";

        setColor(14);
        gotoxy(X, Y + 9); cout << "====================================\n";
        gotoxy(X, Y + 10); cout << "       EQUIPO DE DESARROLLO          \n";
        gotoxy(X, Y + 11); cout << "====================================\n";
        setColor(3);
        gotoxy(X, Y + 12); cout << "- Felipe Marcelo Huamanchumo Chicchon - U20241B932\n";
        gotoxy(X, Y + 13); cout << "- Cristina Marcela Yarleque Ruiz - U20241F859\n";
        gotoxy(X, Y + 14); cout << "- Diego Alexis Osorio Acevedo - U202321908\n";

        setColor(7);
        gotoxy(X, Y + 16); system("pause");
        system("cls");
    }
};