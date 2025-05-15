#include "HumanPlayer.h"
#include "CommonTypes.h" // Para PlayerColorToString, ToAlgebraic
#include <iostream>      // Para std::cout si se usara (trataremos de usar m_view)

HumanPlayer::HumanPlayer(PlayerColor color, InputHandler& inputHandler, const ConsoleView& view)
    : Player(color), m_inputHandler(inputHandler), m_view(view) {
}

MoveInput HumanPlayer::GetChosenMoveInput(
    const Board& board,
    const MoveGenerator& moveGenerator, // No usado directamente por HumanPlayer b�sico para obtener input
    bool isInCaptureSequence,
    int forcedRow,
    int forcedCol,
    const std::vector<Move>& availableMandatoryJumps // Podr�a usarse para mostrar ayudas
) {
    // GameManager ya habr� mostrado el mensaje de "Turno de..." o "Continuar captura..."
    // Esta funci�n ahora solo llama a InputHandler para obtener el string de entrada.

    // Ejemplo de c�mo se podr�a usar availableMandatoryJumps si quisi�ramos que HumanPlayer
    // diera un feedback m�s directo ANTES de que GameManager valide el movimiento.
    // Por ahora, esta l�gica de feedback detallado est� en GameManager.
    /*
    if (!availableMandatoryJumps.empty() && !isInCaptureSequence) {
        m_view.DisplayMessage("AVISO: Tienes capturas obligatorias disponibles:", true, CONSOLE_COLOR_YELLOW, CONSOLE_COLOR_BLACK);
        for (const auto& jump : availableMandatoryJumps) {
            m_view.DisplayMessage("  -> " + jump.ToNotation(), true, CONSOLE_COLOR_YELLOW, CONSOLE_COLOR_BLACK);
        }
    }
    */

    // InputHandler se encarga del prompt ">" y de leer la l�nea.
    MoveInput userInput = m_inputHandler.GetPlayerMoveInput(m_color);

    // Validaciones superficiales de formato ya las hace InputHandler.
    // Validaciones de reglas del juego (si el movimiento es legal, si es captura obligatoria, etc.)
    // las har� GameManager despu�s de recibir este MoveInput.

    return userInput;
}