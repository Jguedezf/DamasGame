#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>
#include <vector>
#include "CommonTypes.h" // Para PlayerColor y MoveInput

class InputHandler {
public:
    InputHandler();

    MoveInput GetPlayerMoveInput(PlayerColor currentPlayer);

private:
    // Parsea una coordenada estilo "A1", "h8" a �ndices internos (fila, columna)
    // Devuelve true si el parseo es exitoso, false en caso contrario.
    // rowIdx y colIdx son par�metros de salida.
    bool ParseCoordinate(const std::string& coordStr, int& rowIdx, int& colIdx); // <--- Asegurar que esta declaraci�n exista
};

#endif // INPUT_HANDLER_H