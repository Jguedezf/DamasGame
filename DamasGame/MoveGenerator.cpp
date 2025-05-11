#include "Board.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;


bool esMovimientoValido(const char tablero[][TAMANO_TABLERO], int filaInicio, int columnaInicio, int filaFin, int columnaFin, char jugador, bool& huboCaptura) {
    huboCaptura = false;
    char peonEnemigo = (jugador == PEON_BLANCO || jugador == REINA_BLANCA) ? PEON_NEGRO : PEON_BLANCO;
    char reinaEnemiga = (jugador == PEON_BLANCO || jugador == REINA_BLANCA) ? REINA_NEGRA : REINA_BLANCA;

    if (filaFin < 0 || filaFin >= TAMANO_TABLERO || columnaFin < 0 || columnaFin >= TAMANO_TABLERO || tablero[filaFin][columnaFin] != VACIO) {
        return false;
    }

    int deltaFila = filaFin - filaInicio;
    int deltaColumna = abs(columnaFin - columnaInicio);

    // Movimiento simple de peón
    if (abs(deltaFila) == 1 && deltaColumna == 1) {
        if ((jugador == PEON_BLANCO && deltaFila == -1) || (jugador == PEON_NEGRO && deltaFila == 1) || (jugador == REINA_BLANCA || jugador == REINA_NEGRA)) {
            return true;
        }
    }

    // Captura simple
    if (abs(deltaFila) == 2 && deltaColumna == 2) {
        int filaCaptura = filaInicio + deltaFila / 2;
        int columnaCaptura = columnaInicio + (columnaFin - columnaInicio) / 2;
        char piezaCapturada = tablero[filaCaptura][columnaCaptura];
        if (filaCaptura >= 0 && filaCaptura < TAMANO_TABLERO && columnaCaptura >= 0 && columnaCaptura < TAMANO_TABLERO &&
            (piezaCapturada == peonEnemigo || piezaCapturada == reinaEnemiga)) {
            huboCaptura = true;
            return true;
        }
    }

    return false;
}

bool realizarMovimiento(char tablero[][TAMANO_TABLERO], int filaInicio, int columnaInicio, int filaFin, int columnaFin, char jugador, bool huboCaptura) {
    if (!esMovimientoValido(tablero, filaInicio, columnaInicio, filaFin, columnaFin, jugador, huboCaptura)) {
        return false;
    }

    tablero[filaFin][columnaFin] = tablero[filaInicio][columnaInicio];
    tablero[filaInicio][columnaInicio] = VACIO;

    // Si hubo captura, eliminar la pieza capturada
    if (huboCaptura) {
        int deltaFila = filaFin - filaInicio;
        int columnaCaptura = columnaInicio + (columnaFin - columnaInicio) / 2;
        int filaCaptura = filaInicio + deltaFila / 2;
        tablero[filaCaptura][columnaCaptura] = VACIO;
    }

    // Coronación
    if ((jugador == PEON_BLANCO && filaFin == 0) || (jugador == PEON_NEGRO && filaFin == TAMANO_TABLERO - 1)) {
        tablero[filaFin][columnaFin] = (jugador == PEON_BLANCO) ? REINA_BLANCA : REINA_NEGRA;
    }

    return true;
}

bool hayMovimientosPosibles(const char tablero[][TAMANO_TABLERO], char jugador) {
    char peonEnemigo = (jugador == PEON_BLANCO || jugador == REINA_BLANCA) ? PEON_NEGRO : PEON_BLANCO;
    char reinaEnemiga = (jugador == PEON_BLANCO || jugador == REINA_BLANCA) ? REINA_NEGRA : REINA_BLANCA;
    char reinaJugador = (jugador == PEON_BLANCO) ? REINA_BLANCA : REINA_NEGRA;

    for (int fila = 0; fila < TAMANO_TABLERO; ++fila) {
        for (int columna = 0; columna < TAMANO_TABLERO; ++columna) {
            char pieza = tablero[fila][columna];
            if (pieza == jugador || pieza == reinaJugador) {
                int cambiosFila[] = { -1, -1, 1, 1 };
                int cambiosColumna[] = { -1, 1, -1, 1 };

                for (int k = 0; k < 4; ++k) {
                    int nuevaFila = fila + cambiosFila[k];
                    int nuevaColumna = columna + cambiosColumna[k];
                    if (nuevaFila >= 0 && nuevaFila < TAMANO_TABLERO && nuevaColumna >= 0 && nuevaColumna < TAMANO_TABLERO && tablero[nuevaFila][nuevaColumna] == VACIO) {
                        return true; // Movimiento simple
                    }
                    nuevaFila = fila + 2 * cambiosFila[k];
                    nuevaColumna = columna + 2 * cambiosColumna[k];
                    int filaCaptura = fila + cambiosFila[k];
                    int columnaCaptura = columna + cambiosColumna[k];
                    if (nuevaFila >= 0 && nuevaFila < TAMANO_TABLERO && nuevaColumna >= 0 && nuevaColumna < TAMANO_TABLERO && tablero[nuevaFila][nuevaColumna] == VACIO &&
                        filaCaptura >= 0 && filaCaptura < TAMANO_TABLERO && columnaCaptura >= 0 && columnaCaptura < TAMANO_TABLERO &&
                        (tablero[filaCaptura][columnaCaptura] == peonEnemigo || tablero[filaCaptura][columnaCaptura] == reinaEnemiga)) {
                        return true; // Captura
                    }
                }
            }
        }
    }
    return false;
}


int contarPiezas(const char tablero[][TAMANO_TABLERO], char jugador) {
    int contador = 0;
    for (int fila = 0; fila < TAMANO_TABLERO; ++fila) {
        for (int columna = 0; columna < TAMANO_TABLERO; ++columna) {
            char pieza = tablero[fila][columna];
            if (pieza == jugador || pieza == ((jugador == PEON_BLANCO) ? REINA_BLANCA : REINA_NEGRA)) {
                contador++;
            }
        }
    }
    return contador;
}