#pragma once

#include <string>
using namespace std;

const int TAMANO_TABLERO = 8;
const char VACIO = ' ';
const char PEON_NEGRO = 'b';
const char PEON_BLANCO = 'w';
const char REINA_NEGRA = 'B';
const char REINA_BLANCA = 'W';

// Códigos de escape ANSI para colores
const string COLOR_BLANCO_FONDO = "\033[47m";
const string COLOR_GRIS_FONDO = "\033[48;5;240m"; // Gris claro
const string COLOR_NEGRO_TEXTO = "\033[30m";
const string COLOR_BLANCO_TEXTO = "\033[37m";
const string COLOR_RESET = "\033[0m";

void inicializarTablero(char tablero[][TAMANO_TABLERO]);

void dibujarTablero(const char tablero[][TAMANO_TABLERO]);