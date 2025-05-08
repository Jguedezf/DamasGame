#pragma once
#ifndef COMMON_TYPES_H // Guardia de Inclusi�n (Inclusion Guard) - Inicio
#define COMMON_TYPES_H // Define un s�mbolo para indicar que este archivo ya fue incluido

// --- Includes Est�ndar (Standard Includes) ---
// Incluimos lo b�sico que podr�an necesitar algunas de estas estructuras o enums.
#include <vector>   // Para std::vector (usado en Move)
#include <string>   // Para std::string (usado en funciones auxiliares)
#include <utility>  // Para std::pair (usado en Move y potencialmente mapeos)
#include <map>      // Para std::map (usado potencialmente para mapeos de casillas)

// --- Enumeraciones del Juego (Game Enumerations) ---

// Representa el color del jugador o si una casilla est� vac�a de jugador
// (Represents the player's color or if a square is empty of a player)
enum class PlayerColor {
    PLAYER_1, // Jugador 1 (ej: Negras/Rojas)
    PLAYER_2, // Jugador 2 (ej: Blancas/Azules)
    NONE      // Sin jugador (casilla vac�a o estado neutro)
};

// Representa el tipo de pieza en una casilla
// (Represents the type of piece on a square)
enum class PieceType {
    P1_MAN,   // Pe�n del Jugador 1 (Player 1 Man)
    P1_KING,  // Dama del Jugador 1 (Player 1 King)
    P2_MAN,   // Pe�n del Jugador 2 (Player 2 Man)
    P2_KING,  // Dama del Jugador 2 (Player 2 King)
    EMPTY     // Casilla Vac�a (Empty Square)
};

// Representa la dificultad de la IA (si se implementa)
// (Represents the AI difficulty level, if implemented)
enum class Difficulty {
    EASY,     // F�cil
    MEDIUM,   // Medio
    HARD,     // Dif�cil
    NONE      // No aplica (ej: jugador humano)
};

// Representa el tipo de jugador
// (Represents the type of player)
enum class PlayerType {
    HUMAN,    // Humano
    COMPUTER  // Computadora (IA)
};

// --- Estructuras del Juego (Game Structs) ---

// Estructura para representar un movimiento (se desarrollar� m�s)
// (Structure to represent a move - will be expanded later)
// Esta es la versi�n inicial basada en tu PDF. La refinaremos en la Fase 3.
struct Move {
    int startR_ = -1;             // Fila inicial (Start Row)
    int startC_ = -1;             // Columna inicial (Start Column)
    int endR_ = -1;               // Fila final (End Row)
    int endC_ = -1;               // Columna final (End Column)
    PieceType pieceMoved_ = PieceType::EMPTY; // Tipo de pieza que se movi�
    bool isCapture_ = false;      // �Fue una captura? (Was it a capture?)
    // --- Campos a a�adir despu�s para capturas m�ltiples y promoci�n ---
    // std::vector<std::pair<int, int>> capturedPiecesCoords_; // Coords de piezas capturadas
    // bool causesPromotion_ = false; // �Este movimiento causa promoci�n?

    // Constructor por defecto (�til para movimientos "nulos")
    Move() = default;

    // M�todo para verificar si es un movimiento nulo/placeholder
    // (Method to check if this is a null/placeholder move)
    bool IsNull() const {
        return startR_ == -1; // Si la fila inicial es -1, consideramos que no es un movimiento v�lido.
    }

    // Placeholder para la conversi�n a notaci�n (se implementar� mejor despu�s)
    // (Placeholder for converting to notation - will be implemented better later)
    std::string ToNotation(const std::map<std::pair<int, int>, int>& coordsToNumMap) const {
        if (IsNull()) return "N/A (Mov. Nulo)";

        // L�gica simple S�LO con coordenadas (A1, H8, etc.) por ahora
        // Necesitar�amos las etiquetas de fila/columna o el mapa num�rico para hacerlo bien.
        // Esta es una versi�n muy b�sica.
        std::string startSq = std::string(1, 'A' + startC_) + std::to_string(8 - startR_); // Asume 8..1 para filas
        std::string endSq = std::string(1, 'A' + endC_) + std::to_string(8 - endR_);

        return startSq + (isCapture_ ? "x" : "-") + endSq; // Ej: C3-D4 o C3xD5
    }
};

// Estructura para las estad�sticas del juego (versi�n inicial, se expandir�)
// (Structure for game statistics - initial version, will be expanded)
struct GameStats {
    int player1CapturedCount = 0;  // Piezas capturadas POR el jugador 1
    int player2CapturedCount = 0;  // Piezas capturadas POR el jugador 2
    int currentTurnNumber = 1;     // N�mero de turno actual
    // --- Campos a a�adir despu�s ---
    // std::chrono::duration<double> player1TotalTime;
    // std::chrono::duration<double> player2TotalTime;
};

// Estructura para la informaci�n del resultado final (para guardar en archivo)
// (Structure for final result information - for saving to file)
struct GameResultInfo {
    std::string dateTimeString;         // Fecha y hora
    PlayerType player1Type = PlayerType::HUMAN;
    Difficulty player1Difficulty = Difficulty::NONE;
    PlayerType player2Type = PlayerType::HUMAN;
    Difficulty player2Difficulty = Difficulty::NONE;
    PlayerColor winner = PlayerColor::NONE; // Ganador (NONE puede ser empate)
    bool wasDraw = false;               // Fue empate?
    int numberOfTurns = 0;              // N�mero total de turnos
    int player1FinalPieceCount = 0;     // Piezas totales J1 al final
    int player1FinalKingCount = 0;      // Reyes J1 al final
    int player2FinalPieceCount = 0;     // Piezas totales J2 al final
    int player2FinalKingCount = 0;      // Reyes J2 al final
    std::string player1TotalTimeString; // Tiempo total J1 (formato MM:SS)
    std::string player2TotalTimeString; // Tiempo total J2 (formato MM:SS)
};


// --- Funciones Auxiliares (Potenciales) ---
// Podr�amos poner aqu� funciones peque�as que usen estos tipos,
// como convertir PlayerColor a string, etc., pero las definiremos
// donde se necesiten o en un Utils.h dedicado si crecen mucho.

// Ejemplo:
inline std::string PlayerColorToString(PlayerColor color) {
    switch (color) {
    case PlayerColor::PLAYER_1: return "JUGADOR 1 (NEGRAS)"; // O ROJAS
    case PlayerColor::PLAYER_2: return "JUGADOR 2 (BLANCAS)"; // O AZULES
    case PlayerColor::NONE:     return "NADIE";
    default:                    return "DESCONOCIDO";
    }
}


#endif // COMMON_TYPES_H // Guardia de Inclusi�n - Fin