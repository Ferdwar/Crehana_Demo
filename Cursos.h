#pragma once
#include <iostream>
#include <string>
using namespace std;

class Curso {
private:
    int id;
    string nombre;
    string descripcion;
    string profesor;

public:

    // ===========================
    // Constructores
    // ===========================
    Curso() : id(0), nombre(""), descripcion(""), profesor("") {}

    Curso(int id, const string& nombre,
        const string& descripcion,
        const string& profesor)
        : id(id),
        nombre(nombre),
        descripcion(descripcion),
        profesor(profesor) {
    }

    // ===========================
    // Getters
    // ===========================
    int getID() const { return id; }
    string getNombre() const { return nombre; }
    string getDescripcion() const { return descripcion; }
    string getProfesor() const { return profesor; }

    // ===========================
    // Setters
    // ===========================
    void setID(int nuevoID) { id = nuevoID; }
    void setNombre(const string& n) { nombre = n; }
    void setDescripcion(const string& d) { descripcion = d; }
    void setProfesor(const string& p) { profesor = p; }

    // ===========================
    // Operadores para ABB y AVL
    // ===========================
    bool operator<(const Curso& other) const {
        return id < other.id;
    }

    bool operator>(const Curso& other) const {
        return id > other.id;
    }

    bool operator==(const Curso& other) const {
        return id == other.id;
    }


    // ===========================
    // Mostrar curso (para árboles)
    // ===========================
    friend ostream& operator<<(ostream& os, const Curso& c) {
        os << "[" << c.id << "] "
            << c.nombre
            << " (Prof: " << c.profesor << ")";
        return os;
    }


    // ===========================
    // Serialización a archivo
    // ===========================
    string serializar() const {
        return to_string(id) + "|" + nombre + "|" +
            descripcion + "|" + profesor;
    }

    static Curso deserializar(const string& linea) {
        int p1 = linea.find('|');
        int p2 = linea.find('|', p1 + 1);
        int p3 = linea.find('|', p2 + 1);

        int id = stoi(linea.substr(0, p1));
        string nombre = linea.substr(p1 + 1, p2 - p1 - 1);
        string descripcion = linea.substr(p2 + 1, p3 - p2 - 1);
        string profesor = linea.substr(p3 + 1);

        return Curso(id, nombre, descripcion, profesor);
    }

    // =========================
    // QUICK SORT PARA NOMBRE
    // =========================
    static int partition(vector<pair<string, string>>& arr, int low, int high) {
        string pivot = arr[high].first;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j].first < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    static void quickSort(vector<pair<string, string>>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    // ==========================================================
       // MOSTRAR CURSOS COMPLETADOS ORDENADOS ALFABETICAMENTE
       // ==========================================================
    static void mostrarCursosCompletados(string username) {
        ifstream file("CursosCompletados.txt");
        if (!file.is_open()) {
            cout << "No existe CursosCompletados.txt.\n";
            return;
        }

        string linea;
        vector<pair<string, string>> cursos;

        auto descomponerLinea = [](const string& linea) {
            struct Datos {
                string user;
                int idCurso;
                string nombreCurso;
                string estado;
            };
            int p1 = linea.find('|');
            int p2 = linea.find('|', p1 + 1);
            int p3 = linea.find('|', p2 + 1);

            Datos d;
            d.user = linea.substr(0, p1);
            d.idCurso = stoi(linea.substr(p1 + 1, p2 - p1 - 1));
            d.nombreCurso = linea.substr(p2 + 1, p3 - p2 - 1);
            d.estado = linea.substr(p3 + 1);
            return d;
            };

        while (getline(file, linea)) {
            auto data = descomponerLinea(linea);
            if (data.user == username)
                cursos.push_back({ data.nombreCurso, data.estado });
        }

        file.close();

        if (cursos.empty()) {
            cout << "No has completado ningun curso todavia.\n";
            return;
        }

        quickSort(cursos, 0, cursos.size() - 1);

        cout << "\n====== CURSOS COMPLETADOS POR " << username << " (Orden Alfabetico) ======\n";
        for (auto& c : cursos) {
            cout << "Curso: " << c.first << "\n" << c.second << "\n-----------------------------\n";
        }
    }



    static string buscarNombrePorID(int idBuscado) {
        ifstream file("Cursos.txt");
        if (!file.is_open()) return "";

        string linea;
        while (getline(file, linea)) {
            Curso c = Curso::deserializar(linea);
            if (c.getID() == idBuscado)
                return c.getNombre();
        }

        return "";
    }


};
