#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// =========================================
//  Estructura para cursos
// =========================================
struct ProgresoCurso {
    int cursoID;
    int nota;        // -1 si no está calificado
    bool completado;
};

// =========================================
//  Clase Estudiante
// =========================================
class Estudiante {
private:
    string username;
    string email;
    string rol;
    vector<ProgresoCurso> cursos;

public:

    // ========= CONSTRUCTORES =========
    Estudiante()
        : username(""), email(""), rol("estudiante") {
    }

    Estudiante(const string& u)
        : username(u), email(""), rol("estudiante") {
    }

    Estudiante(const string& u, const string& e)
        : username(u), email(e), rol("estudiante") {
    }

    Estudiante(const string& u, const string& e, const string& r)
        : username(u), email(e), rol(r) {
    }

    // ========= GETTERS =========
    string getUsername() const { return username; }
    string getEmail() const { return email; }
    string getRol() const { return rol; }
    const vector<ProgresoCurso>& getCursos() const { return cursos; }

    // ========= SETTERS =========
    void setUsername(const string& u) { username = u; }
    void setEmail(const string& e) { email = e; }
    void setRol(const string& r) { rol = r; }

    // ========= PROGRESO =========
    void registrarCurso(int cursoID) {
        cursos.push_back({ cursoID, -1, false });
    }

    void completarCurso(int cursoID) { //int nota
        for (auto& p : cursos)
            if (p.cursoID == cursoID) {
                p.completado = true;
                // p.nota = nota;
            }
    }

    // ========= NECESARIO PARA AVL =========
    bool operator<(const Estudiante& other) const {
        return username < other.username;
    }

    bool operator>(const Estudiante& other) const {
        return username > other.username;
    }

    bool operator==(const Estudiante& other) const {
        return username == other.username;
    }

    // ========= SERIALIZACIÓN =========
    string serializar() const {
        string data = email + "|" + username + "|" + rol + "|";

        for (size_t i = 0; i < cursos.size(); i++) {
            data += to_string(cursos[i].cursoID) + "," +
                to_string(cursos[i].nota) + "," +
                (cursos[i].completado ? "1" : "0");

            if (i + 1 < cursos.size()) data += ";";
        }

        return data;
    }

    // ========= DESERIALIZAR =========
    static Estudiante deserializar(const string& linea) {
        int p1 = linea.find('|');
        int p2 = linea.find('|', p1 + 1);
        int p3 = linea.find('|', p2 + 1);

        string email = linea.substr(0, p1);
        string username = linea.substr(p1 + 1, p2 - p1 - 1);
        string rol = linea.substr(p2 + 1, p3 - p2 - 1);

        // QUITAR ESPACIOS OCULTOS
        auto trim = [](string& s) {
            while (!s.empty() && isspace(s.back())) s.pop_back();
            while (!s.empty() && isspace(s.front())) s.erase(s.begin());
            };
        trim(username);

        Estudiante est(username, email, rol);

        string cursosStr = linea.substr(p3 + 1);

        size_t start = 0;
        while (start < cursosStr.size()) {
            size_t end = cursosStr.find(';', start);
            if (end == string::npos) end = cursosStr.size();

            string c = cursosStr.substr(start, end - start);

            size_t pos1 = c.find(',');
            size_t pos2 = c.find(',', pos1 + 1);

            if (pos1 != string::npos && pos2 != string::npos) {
                int id = stoi(c.substr(0, pos1));
                int nota = stoi(c.substr(pos1 + 1, pos2 - pos1 - 1));
                bool comp = c.substr(pos2 + 1) == "1";

                est.cursos.push_back({ id, nota, comp });
            }

            start = end + 1;
        }

        return est;
    }
};
