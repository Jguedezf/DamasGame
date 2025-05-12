#include "InputHandler.h" // Incluye la declaraci�n de esta clase
#include "CommonTypes.h"  // Para PlayerColor, PlayerColorToString, y MoveInput

#include <iostream>       // Para std::cout, std::cin, std::getline
#include <string>         // Para std::string
#include <sstream>        // Para std::stringstream
#include <limits>         // Para std::numeric_limits

InputHandler::InputHandler() {
    // Constructor
}

MoveInput InputHandler::GetPlayerMoveInput(PlayerColor currentPlayer) {
    MoveInput inputResult; // MoveInput se define en CommonTypes.h

    // PlayerColorToString se define en CommonTypes.h
    std::string playerStr = PlayerColorToString(currentPlayer);

    std::cout << "Turno de " << playerStr
        << ". Introduce tu movimiento (filaIni colIni filaFin colFin, ej. 2 0 3 1) o 'salir': ";

    std::string lineInput;
    std::getline(std::cin >> std::ws, lineInput); // Lee la l�nea completa, std::ws consume espacios iniciales

    if (lineInput == "salir") {
        inputResult.wantsToExit = true;
        inputResult.isValidFormat = true; // Salir es un formato v�lido de "acci�n"
        return inputResult;
    }

    std::stringstream ss(lineInput);
    // Intenta leer 4 enteros.
    if (ss >> inputResult.startRow >> inputResult.startCol >> inputResult.endRow >> inputResult.endCol) {
        // Verifica si hay m�s datos en la l�nea despu�s de los 4 n�meros
        char remainingCharTest;
        if (ss >> remainingCharTest) { // Si se pudo leer algo m�s...
            inputResult.isValidFormat = false; // ...entonces el formato es incorrecto (demasiados datos)
        }
        else {
            inputResult.isValidFormat = true; // Se leyeron exactamente 4 n�meros
        }
    }
    else {
        // No se pudieron leer 4 n�meros
        inputResult.isValidFormat = false;
    }
    return inputResult;
}