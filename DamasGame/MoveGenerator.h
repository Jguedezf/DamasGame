#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "CommonTypes.h" // Para PlayerColor, PieceType, Move
#include "Board.h"       // Necesita conocer la estructura de Board
#include <vector>

class MoveGenerator {
public:
    MoveGenerator(); // Constructor

    // Genera todos los movimientos v�lidos (simples y saltos de pe�n por ahora)
    // para una pieza espec�fica en (startRow, startCol).
    // En el futuro, esta funci�n ser� el n�cleo para obtener todos los movimientos legales
    // de un jugador, aplicando todas las reglas (captura obligatoria, prioridad de Dama, etc.).
    std::vector<Move> GenerateMovesForPiece(const Board& gameBoard,
        int startRow, int startCol);

    // Verifica si un movimiento espec�fico es v�lido seg�n las reglas actuales
    // (peones: movimiento simple o captura simple).
    // 'wasCapture' se establece a true si el movimiento fue una captura.
    bool IsValidMove(const Board& gameBoard,
        int startRow, int startCol,
        int endRow, int endCol,
        PlayerColor player, // El jugador que intenta mover
        bool& wasCapture);  // Par�metro de salida para indicar si fue captura

    // Verifica si un jugador tiene alg�n movimiento v�lido posible en el estado actual del tablero.
    bool HasAnyValidMoves(const Board& gameBoard, PlayerColor player);

private:
private:
    // Funciones de ayuda privadas para encontrar tipos espec�ficos de movimientos
    void FindSimplePawnMoves(const Board& gameBoard, int r, int c, PlayerColor player, PieceType piece, std::vector<Move>& moves) const;
    void FindPawnJumps(const Board& gameBoard, int r, int c, PlayerColor player, PieceType piece, std::vector<Move>& moves) const;
};

#endif // MOVE_GENERATOR_H