#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
class GeneradorData {

public:

    // ===============================================
    // GENERAR DATASET DE PRUEBA Calificaciones.txt
    // ===============================================
    static void generarDataset() {
        ofstream file("Calificaciones.txt");

        if (!file.is_open()) {
            cout << "Error creando Calificaciones.txt\n";
            return;
        }

        // username | idCurso | nota
        vector<string> dataset = {
            "juan|1|15",
            "juan|2|11",
            "maria|1|18",
            "maria|3|14",
            "pedro|2|10",
            "pedro|3|19",
            "ana|1|17",
            "ana|2|16"
        };

        for (auto& linea : dataset)
            file << linea << "\n";

        file.close();

        cout << "\nDataset generado correctamente en Calificaciones.txt\n";
    }

    // ===============================
    // VER TODAS LAS CALIFICACIONES
    // ===============================
    static void verTodasLasCalificaciones() {
        ifstream file("Calificaciones.txt");

        if (!file.is_open()) {
            cout << "\nNo existe Calificaciones.txt\n";
            return;
        }

        cout << "\n====== TODAS LAS CALIFICACIONES (PROFESOR) ======\n";

        string linea;
        bool hayDatos = false;

        while (getline(file, linea)) {

            if (linea.size() == 0)
                continue;

            if (linea.find('|') == string::npos)
                continue;

            hayDatos = true;

            int p1 = linea.find('|');
            int p2 = linea.find('|', p1 + 1);

            string user = linea.substr(0, p1);
            T idCurso;

            string idStr = linea.substr(p1 + 1, p2 - p1 - 1);
            if constexpr (is_same<T, int>::value) {
                idCurso = stoi(idStr);
            }
            else if constexpr (is_same<T, string>::value) {
                idCurso = idStr;
            }
            else {
                idCurso = static_cast<T>(stoi(idStr));
            }

            string nota = linea.substr(p2 + 1);

            cout << "Alumno: " << user << "\n";
            cout << "ID Curso: " << idCurso << "\n";
            cout << "Nota: " << nota << "\n";
            cout << "-------------------------------------\n";
        }

        if (!hayDatos)
            cout << "No existen calificaciones para mostrar.\n";

        file.close();
    }

};