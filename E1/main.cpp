#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Función para leer archivos
string leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string contenido((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    return contenido;
}

// Función para verificar si un código está contenido en una transmisión
bool contieneCodigo(const string& transmision, const string& codigo, size_t& posicion) {
    posicion = transmision.find(codigo);
    return (posicion != string::npos);
}

// Función para verificar si una cadena es un palíndromo
bool esPalindromo(const string& str) {
    return equal(str.begin(), str.begin() + str.size() / 2, str.rbegin());
}

// Función para encontrar el palíndromo más largo
pair<int, string> palindromoMasLargo(const string& transmision) {
    int maxLength = 0;
    pair<int, string> resultado;
    for (int i = 0; i < transmision.size(); ++i) {
        for (int j = i + 1; j <= transmision.size(); ++j) {
            string subcadena = transmision.substr(i, j - i);
            if (esPalindromo(subcadena) && subcadena.length() > maxLength) {
                maxLength = subcadena.length();
                resultado = {i + 1, subcadena}; // posición +1 para índice de inicio en base 1
            }
        }
    }
    return resultado;
}

// Función para encontrar el substring común más largo entre dos transmisiones
tuple<int, int, string> substringComunMasLargo(const string& transmision1, const string& transmision2) {
    int maxLength = 0;
    tuple<int, int, string> resultado;
    for (int i = 0; i < transmision1.size(); ++i) {
        for (int j = 0; j < transmision2.size(); ++j) {
            int k = 0;
            while (i + k < transmision1.size() && j + k < transmision2.size() &&
                   transmision1[i + k] == transmision2[j + k]) {
                ++k;
            }
            if (k > maxLength) {
                maxLength = k;
                resultado = {i + 1, i + k, transmision1.substr(i, k)};
            }
        }
    }
    return resultado;
}

int main() {
    // Leer archivos de transmisión y códigos
    string transmision1 = leerArchivo("transmission1.txt");
    string transmision2 = leerArchivo("transmission2.txt");
    string mcode1 = leerArchivo("mcode1.txt");
    string mcode2 = leerArchivo("mcode2.txt");
    string mcode3 = leerArchivo("mcode3.txt");

    size_t posicion;

    //Parte 1:
    // Llamado a la función para verificar si el código está contenido en la transmisión
    cout << "Parte 1:" << endl;
    cout << (contieneCodigo(transmision1, mcode1, posicion) ? "true " + to_string(posicion + 1) : "false") << endl;
    cout << (contieneCodigo(transmision1, mcode2, posicion) ? "true " + to_string(posicion + 1) : "false") << endl;
    cout << (contieneCodigo(transmision1, mcode3, posicion) ? "true " + to_string(posicion + 1) : "false") << endl;
    cout << (contieneCodigo(transmision2, mcode1, posicion) ? "true " + to_string(posicion + 1) : "false") << endl;
    cout << (contieneCodigo(transmision2, mcode2, posicion) ? "true " + to_string(posicion + 1) : "false") << endl;
    cout << (contieneCodigo(transmision2, mcode3, posicion) ? "true " + to_string(posicion + 1) : "false") << endl;

    //Parte 2:
    // LLamado a la función para encontrar el palíndromo más largo
    cout << "Parte 2:" << endl;
    pair<int, string> palindromo1 = palindromoMasLargo(transmision1);
    pair<int, string> palindromo2 = palindromoMasLargo(transmision2);
    cout << palindromo1.first << " " << (palindromo1.first + palindromo1.second.size() - 1) << " " << palindromo1.second << endl;
    cout << palindromo2.first << " " << (palindromo2.first + palindromo2.second.size() - 1) << " " << palindromo2.second << endl;

    //Parte 3:
    // LLamado a la función para encontrar el substring común más largo entre dos transmisiones
    cout << "Parte 3:" << endl;
    tuple<int, int, string> substringComun = substringComunMasLargo(transmision1, transmision2);
    cout << get<0>(substringComun) << " " << get<1>(substringComun) << " " << get<2>(substringComun) << endl;

    return 0;
}