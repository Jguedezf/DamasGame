#include "Board.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>


using namespace std;

void inicializarTablero(char tablero[][TAMANO_TABLERO]) {
    for (int fila = 0; fila < TAMANO_TABLERO; ++fila) {
        for (int columna = 0; columna < TAMANO_TABLERO; ++columna) {
            tablero[fila][columna] = VACIO;
        }
    }
    for (int fila = 0; fila < 3; ++fila) {
        for (int columna = (fila % 2 == 0); columna < TAMANO_TABLERO; columna += 2) {
            tablero[fila][columna] = PEON_NEGRO;
        }
    }
    for (int fila = TAMANO_TABLERO - 3; fila < TAMANO_TABLERO; ++fila) {
        for (int columna = (fila % 2 == 0); columna < TAMANO_TABLERO; columna += 2) {
            tablero[fila][columna] = PEON_BLANCO;
        }
    }
} 

void dibujarTablero(const char tablero[][TAMANO_TABLERO]) {
    cout << "    ";
    for (int i = 0; i < TAMANO_TABLERO; ++i) {
        cout << i << "   ";
    }
    cout << COLOR_RESET << endl;

    for (int fila = 0; fila < TAMANO_TABLERO; ++fila) {
        cout << setw(2) << setfill('0') << fila << "|";
        for (int columna = 0; columna < TAMANO_TABLERO; ++columna) {
            if ((fila + columna) % 2 != 0) {
                cout << COLOR_GRIS_FONDO << "   " << COLOR_RESET << "|";
            }
            else {
                cout << COLOR_BLANCO_FONDO << "   " << COLOR_RESET << "|";
            }
        }
        cout << endl;

        cout << "  |";
        for (int columna = 0; columna < TAMANO_TABLERO; ++columna) {
            if ((fila + columna) % 2 != 0) {
                cout << COLOR_GRIS_FONDO << " ";
                if (tablero[fila][columna] == PEON_NEGRO || tablero[fila][columna] == REINA_NEGRA) {
                    cout << COLOR_NEGRO_TEXTO << tablero[fila][columna] << COLOR_RESET << COLOR_GRIS_FONDO;
                }
                else if (tablero[fila][columna] == PEON_BLANCO || tablero[fila][columna] == REINA_BLANCA) {
                    cout << COLOR_BLANCO_TEXTO << tablero[fila][columna] << COLOR_RESET << COLOR_GRIS_FONDO;
                }
                else {
                    cout << " ";
                }
                cout << " " << COLOR_RESET << "|";
            }
            else {
                cout << COLOR_BLANCO_FONDO << "   " << COLOR_RESET << "|";
            }
        }
        cout << endl;
    }
    cout << COLOR_RESET;
}