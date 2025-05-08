#pragma once
#ifndef BOARD_H // Guardia de Inclusi�n - Inicio
#define BOARD_H // (Aseg�rate de que estas l�neas est�n o a��delas si no)

// --- Includes Necesarios ---
#include "CommonTypes.h" // MUY IMPORTANTE: Para usar PieceType, PlayerColor, etc.
                         // Asume que CommonTypes.h est� en la misma carpeta Headers.
#include <array>         // Para usar std::array para el tablero (como sugiere el PDF)
#include <vector>        // Podr�a ser necesario para devolver listas de movimientos despu�s
#include <string>        // Para notaciones o mensajes futuros

// --- Declaraci�n de la Clase Board ---
// (Class Board Declaration)
// Representa el tablero de juego de Damas 8x8.
class Board {
public: // Interfaz P�blica (Public Interface)

    // Constante para el tama�o del tablero (Standard checkers board size)
    // Usamos constexpr para constantes conocidas en tiempo de compilaci�n.
    static constexpr int BOARD_SIZE = 8;

    // --- Constructor ---
    // Se llama al crear un objeto Board.
    Board();

    // --- M�todos Principales (Core Methods) ---

    // Inicializa el tablero a la posici�n inicial est�ndar de Damas.
    // (Initializes the board to the standard starting checkers position)
    void InitializeBoard();

    // Obtiene el tipo de pieza en una coordenada espec�fica.
    // (Gets the type of piece at a specific coordinate)
    // Parameters (Par�metros):
    // - row (fila): int, la fila (0-7).
    // - col (columna): int, la columna (0-7).
    // Returns (Devuelve): PieceType, el tipo de pieza (o EMPTY si est� vac�a/fuera de l�mites).
    // 'const' indica que este m�todo no modifica el tablero.
    PieceType GetPieceAt(int row, int col) const;

    // Coloca una pieza de un tipo espec�fico en una coordenada.
    // �IMPORTANTE! Este m�todo tambi�n debe actualizar los contadores de piezas.
    // (Places a piece of a specific type at a coordinate)
    // Parameters (Par�metros):
    // - row (fila): int, la fila (0-7).
    // - col (columna): int, la columna (0-7).
    // - pieceType (tipoDeFicha): PieceType, el tipo de pieza a colocar.
    void SetPieceAt(int row, int col, PieceType pieceType);

    // --- M�todos Auxiliares y de Consulta (Utility and Query Methods) ---

    // Verifica si una coordenada (fila, columna) est� dentro de los l�mites del tablero.
    // (Checks if a coordinate is within the board boundaries)
    // Returns (Devuelve): bool, true si est� dentro, false si est� fuera.
    bool IsWithinBounds(int row, int col) const;

    // Verifica si una casilla es jugable (seg�n las reglas de Damas, usualmente las negras).
    // (Checks if a square is playable - usually the dark squares in Checkers)
    // �IMPORTANTE! Debemos ser consistentes con la convenci�n (ej: �(0,0) es blanca o negra?).
    // Asumiremos (0,0) es BLANCA (NO jugable), por lo tanto, jugables son las de suma impar (r+c)%2 != 0.
    // Si quieres que (0,0) sea NEGRA (jugable), cambia la l�gica a (r+c)%2 == 0.
    bool IsPlayableSquare(int row, int col) const;

    // Obtiene el n�mero total de piezas (Peones + Damas) para un jugador.
    // (Gets the total piece count (Pawns + Kings) for a player)
    // Parameters (Par�metros):
    // - player (jugador): PlayerColor, el jugador (PLAYER_1 o PLAYER_2).
    // Returns (Devuelve): int, el n�mero total de piezas.
    int GetPieceCount(PlayerColor player) const;

    // Obtiene el n�mero de Damas (Reyes) para un jugador.
    // (Gets the King count for a player)
    // Parameters (Par�metros):
    // - player (jugador): PlayerColor, el jugador (PLAYER_1 o PLAYER_2).
    // Returns (Devuelve): int, el n�mero de Damas.
    int GetKingCount(PlayerColor player) const;

    // Obtiene el tama�o del tablero (siempre 8 en este caso).
    // (Gets the size of the board - always 8 here)
    int GetBoardSize() const { return BOARD_SIZE; }

    void DisplayBoard() const;

private: // Miembros Privados (Private Members)

    // --- Datos Miembro (Member Data) ---

    // La cuadr�cula del tablero. Usamos std::array porque el tama�o es fijo (8x8).
    // Es m�s eficiente que std::vector para tama�os fijos conocidos en compilaci�n.
    // grid_[fila][columna]
    std::array<std::array<PieceType, BOARD_SIZE>, BOARD_SIZE> mGrid; // (cuadriculaMiembro)

    // Contadores de piezas. Mantenemos un registro separado para cada jugador y tipo.
    // pieceCounts_[�ndiceJugador][�ndiceTipo]
    // �ndiceJugador: 0 para PLAYER_1, 1 para PLAYER_2
    // �ndiceTipo: 0 para MAN (Pe�n), 1 para KING (Dama)
    // Acceder�amos p.ej. como pieceCounts_[0][0] para P1_MAN.
    int mPieceCounts[2][2]; // (contadoresPiezasMiembro)

    // --- M�todos Auxiliares Privados (Private Helper Methods) ---

    // Reinicia todos los contadores de piezas a cero.
    // (Resets all piece counters to zero)
    void ResetPieceCounts();

    // Actualiza los contadores cuando una pieza cambia en SetPieceAt.
    // (Updates the counters when a piece changes in SetPieceAt)
    // Parameters (Par�metros):
    // - row, col: coordenadas donde ocurri� el cambio.
    // - oldPiece (piezaAntigua): El tipo de pieza que HAB�A ANTES.
    // - newPiece (piezaNueva): El tipo de pieza que HAY AHORA.
    void UpdateCountsForSetPiece(int r, int c, PieceType oldPiece, PieceType newPiece);

    // Limpia el tablero (pone todas las casillas a EMPTY). �til antes de InitializeBoard.
    // (Clears the board, setting all squares to EMPTY)
    void ClearBoard();
};

#endif // BOARD_H // Guardia de Inclusi�n - Fin
