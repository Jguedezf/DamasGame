#include "GameManager.h"
#include "MoveGenerator.h"

#include "Board.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

int main() {
    char tablero[TAMANO_TABLERO][TAMANO_TABLERO];
    inicializarTablero(tablero);
    char jugadorActual = PEON_NEGRO;
    bool juegoTerminado = false;
    int intentosNegras = 0;
    int intentosBlancas = 0;
    int fichasEliminadasNegras = 0;
    int fichasEliminadasBlancas = 0;

    while (!juegoTerminado) {
        dibujarTablero(tablero);
        cout << "Intentos Negras: " << intentosNegras << " | Fichas Eliminadas: " << fichasEliminadasNegras << endl;
        cout << "Intentos Blancas: " << intentosBlancas << " | Fichas Eliminadas: " << fichasEliminadasBlancas << endl;
        cout << "Turno de " << (jugadorActual == PEON_NEGRO || jugadorActual == REINA_NEGRA ? "Negras" : "Blancas")
            << ". Introduce tu movimiento (filaIni colIni filaFin colFin, ej. 0 2 1 3) o 'salir': ";
        string movimientoStr;
        getline(cin >> ws, movimientoStr);

        if (movimientoStr == "salir") {
            juegoTerminado = true;
            break;
        }

        stringstream ss(movimientoStr);
        int filaInicio, columnaInicio, filaFin, columnaFin;
        if (ss >> filaInicio >> columnaInicio >> filaFin >> columnaFin) {
            if (filaInicio >= 0 && filaInicio < TAMANO_TABLERO && columnaInicio >= 0 && columnaInicio < TAMANO_TABLERO &&
                filaFin >= 0 && filaFin < TAMANO_TABLERO && columnaFin >= 0 && columnaFin < TAMANO_TABLERO) {
                char piezaMover = tablero[filaInicio][columnaInicio];
                char reinaJugador = (jugadorActual == PEON_BLANCO) ? REINA_BLANCA : REINA_NEGRA;
                bool huboCaptura = false;

                if (piezaMover == jugadorActual || piezaMover == reinaJugador) {
                    if (esMovimientoValido(tablero, filaInicio, columnaInicio, filaFin, columnaFin, jugadorActual, huboCaptura)) {
                        realizarMovimiento(tablero, filaInicio, columnaInicio, filaFin, columnaFin, jugadorActual, huboCaptura);
                        if (jugadorActual == PEON_NEGRO || jugadorActual == REINA_NEGRA) {
                            intentosNegras++;
                            if (huboCaptura) {
                                fichasEliminadasNegras++;
                            }
                        }
                        else {
                            intentosBlancas++;
                            if (huboCaptura) {
                                fichasEliminadasBlancas++;
                            }
                        }
                        if (!hayMovimientosPosibles(tablero, (jugadorActual == PEON_NEGRO || jugadorActual == REINA_NEGRA) ? PEON_BLANCO : PEON_NEGRO)) {
                            cout << (jugadorActual == PEON_NEGRO || jugadorActual == REINA_NEGRA ? "¡Blancas ganan!" : "¡Negras ganan!") << endl;
                            juegoTerminado = true;
                        }
                        else {
                            jugadorActual = (jugadorActual == PEON_NEGRO) ? PEON_BLANCO : PEON_NEGRO;
                        }
                    }
                    else {
                        if (jugadorActual == PEON_NEGRO || jugadorActual == REINA_NEGRA) {
                            intentosNegras++;
                        }
                        else {
                            intentosBlancas++;
                        }
                        cout << "Movimiento inválido. Intenta de nuevo." << endl;
                    }
                }
                else {
                    if (jugadorActual == PEON_NEGRO || jugadorActual == REINA_NEGRA) {
                        intentosNegras++;
                    }
                    else {
                        intentosBlancas++;
                    }
                    cout << "¡Esta no es tu pieza! Intenta de nuevo." << endl;
                }
            }
            else {
                if (jugadorActual == PEON_NEGRO || jugadorActual == REINA_NEGRA) {
                    intentosNegras++;
                }
                else {
                    intentosBlancas++;
                }
                cout << "Coordenadas fuera del tablero. Intenta de nuevo." << endl;
            }
        }
        else {
            if (jugadorActual == PEON_NEGRO || jugadorActual == REINA_NEGRA) {
                intentosNegras++;
            }
            else {
                intentosBlancas++;
            }
            cout << "Formato de entrada inválido. Introduce cuatro enteros separados por espacios." << endl;
        }

        if (!hayMovimientosPosibles(tablero, PEON_NEGRO) && !hayMovimientosPosibles(tablero, REINA_NEGRA)) {
            cout << "¡Blancas ganan! Negras no tienen movimientos posibles." << endl;
            juegoTerminado = true;
        }
        else if (!hayMovimientosPosibles(tablero, PEON_BLANCO) && !hayMovimientosPosibles(tablero, REINA_BLANCA)) {
            cout << "¡Negras ganan! Blancas no tienen movimientos posibles." << endl;
            juegoTerminado = true;
        }

        if (contarPiezas(tablero, PEON_NEGRO) == 0 && contarPiezas(tablero, REINA_NEGRA) == 0) {
            cout << "¡Blancas ganan! Todas las piezas negras han sido capturadas." << endl;
            juegoTerminado = true;
        }
        else if (contarPiezas(tablero, PEON_BLANCO) == 0 && contarPiezas(tablero, REINA_BLANCA) == 0) {
            cout << "¡Negras ganan! Todas las piezas blancas han sido capturadas." << endl;
            juegoTerminado = true;
        }
    }

    cout << COLOR_RESET << "¡Gracias por jugar!" << endl;
    return 0;
}