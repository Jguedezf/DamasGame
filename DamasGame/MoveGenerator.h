#pragma once

#include "Board.h"

bool esMovimientoValido(const char tablero[][TAMANO_TABLERO], int filaInicio, int columnaInicio, int filaFin, int columnaFin, char jugador, bool& huboCaptura);

bool realizarMovimiento(char tablero[][TAMANO_TABLERO], int filaInicio, int columnaInicio, int filaFin, int columnaFin, char jugador, bool huboCaptura);

bool hayMovimientosPosibles(const char tablero[][TAMANO_TABLERO], char jugador);

int contarPiezas(const char tablero[][TAMANO_TABLERO], char jugador);