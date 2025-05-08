// -----------------------------------------------------------------------------
// Board.cpp
// Implementaci�n de la clase Board para el juego de Damas.
// -----------------------------------------------------------------------------

// --- Includes ---
#include "Board.h"       // Incluye la declaraci�n de la clase Board (�Importante!)
#include "ConsoleView.h" // Para usar GoToXY, Set/ResetConsoleTextColor en DisplayBoard TEMPORAL
#include "CommonTypes.h" // Para usar PieceType, PlayerColor

#include <stdexcept>     // Para std::out_of_range (manejo de errores)
#include <vector>        // Para el par�metro opcional de DisplayBoard (si se usa) y std::vector
#include <string>        // Para std::string, std::to_string (si se usa)
#include <iostream>      // Para std::cout, std::endl en DisplayBoard TEMPORAL
#include <iomanip>       // Para std::setw en DisplayBoard TEMPORAL
#include <array>         // Asegurarse que est� incluido si usamos std::array para mGrid


// --- Implementaci�n del Constructor ---
Board::Board() {
    // Estado inicial limpio al crear un tablero.
    ClearBoard();
    ResetPieceCounts();
}

// --- Implementaci�n de M�todos P�blicos ---

void Board::InitializeBoard() {
    ClearBoard();       // Asegura tablero vac�o.
    ResetPieceCounts(); // Contadores a cero.

    // Coloca las piezas iniciales (CORREGIDO: Negras arriba, Blancas abajo).
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (IsPlayableSquare(r, c)) { // Solo en casillas jugables
                if (r < 3) {
                    // Primeras 3 filas jugables (0, 1, 2 internas / 8, 7, 6 visuales) son para Jugador 1 (Negras)
                    SetPieceAt(r, c, PieceType::P1_MAN);
                }
                else if (r >= BOARD_SIZE - 3) { // r >= 5 para 8x8 (5, 6, 7 internas / 3, 2, 1 visuales)
                    // �ltimas 3 filas jugables son para Jugador 2 (Blancas)
                    SetPieceAt(r, c, PieceType::P2_MAN);
                }
            }
        }
    }
}

PieceType Board::GetPieceAt(int row, int col) const {
    if (!IsWithinBounds(row, col)) {
        return PieceType::EMPTY;
    }
    return mGrid[row][col]; // Aseg�rate que 'mGrid' coincida con Board.h
}

void Board::SetPieceAt(int row, int col, PieceType pieceType) {
    if (!IsWithinBounds(row, col)) {
        throw std::out_of_range("Board::SetPieceAt: Coordenadas fuera de rango.");
    }
    PieceType oldPiece = mGrid[row][col]; // Aseg�rate que 'mGrid' coincida con Board.h
    mGrid[row][col] = pieceType;          // Aseg�rate que 'mGrid' coincida con Board.h
    UpdateCountsForSetPiece(row, col, oldPiece, pieceType);
}

bool Board::IsWithinBounds(int row, int col) const {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

bool Board::IsPlayableSquare(int row, int col) const {
    if (!IsWithinBounds(row, col)) {
        return false;
    }
    // Asume (0,0) Blanca -> suma impar (r+c)%2 != 0 es Negra/Jugable
    return (row + col) % 2 != 0;
}

int Board::GetPieceCount(PlayerColor player) const {
    // Aseg�rate que 'mPieceCounts' coincida con Board.h
    int playerIndex = (player == PlayerColor::PLAYER_1) ? 0 : ((player == PlayerColor::PLAYER_2) ? 1 : -1);
    if (playerIndex == -1) return 0;
    return mPieceCounts[playerIndex][0] + mPieceCounts[playerIndex][1]; // MAN + KING
}

int Board::GetKingCount(PlayerColor player) const {
    // Aseg�rate que 'mPieceCounts' coincida con Board.h
    int playerIndex = (player == PlayerColor::PLAYER_1) ? 0 : ((player == PlayerColor::PLAYER_2) ? 1 : -1);
    if (playerIndex == -1) return 0;
    return mPieceCounts[playerIndex][1]; // �ndice [1] es KING
}


// --- Implementaci�n de M�todos Privados ---

void Board::ClearBoard() {
    // Aseg�rate que 'mGrid' coincida con Board.h
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            mGrid[r][c] = PieceType::EMPTY;
        }
    }
}

void Board::ResetPieceCounts() {
    // Aseg�rate que 'mPieceCounts' coincida con Board.h
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            mPieceCounts[i][j] = 0;
        }
    }
}

void Board::UpdateCountsForSetPiece(int r, int c, PieceType oldPiece, PieceType newPiece) {
    // Aseg�rate que 'mPieceCounts' coincida con Board.h
    int playerIndexOld = -1, pieceTypeIndexOld = -1;
    if (oldPiece == PieceType::P1_MAN) { playerIndexOld = 0; pieceTypeIndexOld = 0; }
    else if (oldPiece == PieceType::P1_KING) { playerIndexOld = 0; pieceTypeIndexOld = 1; }
    else if (oldPiece == PieceType::P2_MAN) { playerIndexOld = 1; pieceTypeIndexOld = 0; }
    else if (oldPiece == PieceType::P2_KING) { playerIndexOld = 1; pieceTypeIndexOld = 1; }

    if (playerIndexOld != -1) {
        mPieceCounts[playerIndexOld][pieceTypeIndexOld]--;
    }

    int playerIndexNew = -1, pieceTypeIndexNew = -1;
    if (newPiece == PieceType::P1_MAN) { playerIndexNew = 0; pieceTypeIndexNew = 0; }
    else if (newPiece == PieceType::P1_KING) { playerIndexNew = 0; pieceTypeIndexNew = 1; }
    else if (newPiece == PieceType::P2_MAN) { playerIndexNew = 1; pieceTypeIndexNew = 0; }
    else if (newPiece == PieceType::P2_KING) { playerIndexNew = 1; pieceTypeIndexNew = 1; }

    if (playerIndexNew != -1) {
        mPieceCounts[playerIndexNew][pieceTypeIndexNew]++;
    }
}

// --- Implementaci�n de la funci�n DisplayBoard TEMPORAL ---
// Esta funci�n usa GoToXY, SetConsoleTextColor, etc. que DEBEN estar definidas
// en alguno de los archivos incluidos arriba (probablemente ConsoleView.h)
void Board::DisplayBoard() const {
    GoToXY(0, 0); // Mover cursor al inicio

    // --- Imprimir Coordenadas de Columna (A-H) Alineadas (CORREGIDO) ---
    ResetConsoleTextColor();
    std::cout << "   "; // 3 espacios iniciales para la columna de n�meros de fila
    // Imprimimos cada letra centrada en un bloque de 5 espacios
    for (int c = 0; c < BOARD_SIZE; ++c) {
        std::cout << "  " << (char)('A' + c) << "  ";
    }
    std::cout << std::endl; // Nueva l�nea

    // --- Imprimir Filas del Tablero ---
    for (int r = 0; r < BOARD_SIZE; ++r) {
        ResetConsoleTextColor();
        // Imprime n�mero de fila (8 a 1)
        std::cout << std::setw(2) << (BOARD_SIZE - r) << " ";

        for (int c = 0; c < BOARD_SIZE; ++c) {
            // Determina el color de fondo de la casilla
            int squareBgColor = IsPlayableSquare(r, c) ? CONSOLE_COLOR_DARK_GRAY : CONSOLE_COLOR_LIGHT_GRAY;

            // Determina la pieza y su color/s�mbolo
            PieceType piece = GetPieceAt(r, c);
            char symbolToShow = ' ';
            int pieceFgColor = CONSOLE_COLOR_BLACK;

            if (piece == PieceType::P1_MAN) { symbolToShow = 'o'; pieceFgColor = CONSOLE_COLOR_RED; }
            else if (piece == PieceType::P1_KING) { symbolToShow = 'O'; pieceFgColor = CONSOLE_COLOR_LIGHT_RED; }
            else if (piece == PieceType::P2_MAN) { symbolToShow = 'x'; pieceFgColor = CONSOLE_COLOR_BLUE; }
            else if (piece == PieceType::P2_KING) { symbolToShow = 'X'; pieceFgColor = CONSOLE_COLOR_LIGHT_BLUE; }
            else { pieceFgColor = squareBgColor; } // Casilla vac�a

            // Impresi�n de la casilla [ S ]
            ResetConsoleTextColor(); // Color neutro para corchetes
            std::cout << "[";
            SetConsoleTextColor(pieceFgColor, squareBgColor); // Colores de pieza/fondo
            std::cout << " " << symbolToShow << " "; // S�mbolo centrado
            ResetConsoleTextColor(); // Volver a neutro
            std::cout << "]";
        }
        ResetConsoleTextColor(); // Resetear al final de la fila
        std::cout << std::endl;
    }
    ResetConsoleTextColor(); // Asegurar reseteo final
}

// --- Fin de la Implementaci�n de Board ---