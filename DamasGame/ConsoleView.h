#ifndef CONSOLE_VIEW_H
#define CONSOLE_VIEW_H

#include <windows.h>
#include <string>
#include <vector>
#include <iostream>

class Board;

// --- CONSTANTES DE COLOR ---
// (Sin cambios, las constantes son las mismas)
const int CONSOLE_COLOR_BLACK = 0;
const int CONSOLE_COLOR_BLUE = 1;
const int CONSOLE_COLOR_GREEN = 2;
const int CONSOLE_COLOR_CYAN = 3;
const int CONSOLE_COLOR_RED = 4;
const int CONSOLE_COLOR_MAGENTA = 5;
const int CONSOLE_COLOR_BROWN = 6;
const int CONSOLE_COLOR_LIGHT_GRAY = 7;
const int CONSOLE_COLOR_DARK_GRAY = 8;
const int CONSOLE_COLOR_LIGHT_BLUE = 9;
const int CONSOLE_COLOR_LIGHT_GREEN = 10;
const int CONSOLE_COLOR_LIGHT_CYAN = 11;
const int CONSOLE_COLOR_LIGHT_RED = 12;
const int CONSOLE_COLOR_LIGHT_MAGENTA = 13;
const int CONSOLE_COLOR_YELLOW = 14;
const int CONSOLE_COLOR_WHITE = 15;

// --- FUNCIONES DE UTILIDAD DE CONSOLA ---
inline void GoToXY(int x, int y) {
    COORD cursorPosition;
    cursorPosition.X = static_cast<SHORT>(x);
    cursorPosition.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

// SetConsoleTextColor ahora siempre toma el color de fondo deseado para el texto.
// Si se quiere el fondo "global" actual, se debe pasar expl�citamente.
inline void SetConsoleTextColor(int foregroundColor, int backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, foregroundColor | (backgroundColor << 4));
}

// Resetear al esquema de juego (negro)
inline void ResetConsoleColorsToGameDefault() {
    SetConsoleTextColor(CONSOLE_COLOR_LIGHT_GRAY, CONSOLE_COLOR_BLACK);
}

// Resetear al esquema de men� (morado)
inline void ResetConsoleColorsToMenuDefault() {
    SetConsoleTextColor(CONSOLE_COLOR_WHITE, CONSOLE_COLOR_MAGENTA);
}


class ConsoleView {
public:
    ConsoleView();

    // Establece colores y limpia para el MEN� (fondo morado)
    void SetMenuColorsAndClear() const;
    // Establece colores y limpia para el JUEGO (fondo negro)
    void SetGameColorsAndClear() const;

    void DisplayMainMenu(int selectedOption) const;
    void DisplayBoard(const Board& gameBoard, int gameBgColor = CONSOLE_COLOR_BLACK) const; // A�adido gameBgColor

    // DisplayMessage ahora requiere el color de fondo expl�cito para el texto.
    void DisplayMessage(const std::string& message, bool newLine = true,
        int fgColor = -1, // -1 para usar el color de texto por defecto del contexto
        int bgColor = -1) const; // -1 para usar el color de fondo por defecto del contexto

    // ClearScreen ahora es m�s gen�rico y solo limpia
    void ClearScreen() const;
    // Limpia una secci�n de la pantalla (�til para mensajes sin borrar todo)
    void ClearLines(int startY, int numLines, int consoleWidth = 80) const;

private:
    // Helper para obtener el color de fondo por defecto actual de la consola
    // (Esto podr�a no ser necesario si siempre seteamos expl�citamente)
    // int GetCurrentConsoleBackgroundColor() const; 
};

#endif // CONSOLE_VIEW_H