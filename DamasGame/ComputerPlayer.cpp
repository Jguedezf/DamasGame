#include "ComputerPlayer.h"
#include "CommonTypes.h" 
#include "Board.h"       


#include <vector>
#include <algorithm> 
#include <chrono>    
#include <thread>    

ComputerPlayer::ComputerPlayer(PlayerColor color, const MoveGenerator& moveGenerator, int difficulty)
	: Player(color),
	m_difficulty(difficulty),
	m_moveGeneratorRef(moveGenerator) { // Guardar referencia a MoveGenerator
	// Sembrar el generador de n�meros aleatorios
	unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
	m_rng.seed(seed);
}

// Funci�n de Evaluaci�n Heur�stica
// Devuelve una puntuaci�n para el tablero desde la perspectiva de 'perspectiveColor'.
// Una puntuaci�n m�s alta es mejor para 'perspectiveColor'.
int ComputerPlayer::EvaluateBoardState(const Board& currentBoard, PlayerColor perspectiveColor) const {
	int score = 0;
	PlayerColor opponentColor = (perspectiveColor == PlayerColor::PLAYER_1) ? PlayerColor::PLAYER_2 : PlayerColor::PLAYER_1;

	const int pawnValue = 100; // Valor base de un pe�n
	const int kingValue = 250; // Valor de una Dama (Rey)
	const int advancementBonusBase = 5; // Bonificaci�n por cada fila avanzada
	const int edgePenalty = -10; // Peque�a penalizaci�n por estar en el borde (menos movilidad)

	for (int r = 0; r < currentBoard.GetBoardSize(); ++r) {
		for (int c = 0; c < currentBoard.GetBoardSize(); ++c) {
			PieceType piece = currentBoard.GetPieceAt(r, c);
			if (piece == PieceType::EMPTY) continue;

			// Usar el m_moveGeneratorRef que es miembro de ComputerPlayer
			PlayerColor pieceOwner = m_moveGeneratorRef.GetPlayerFromPiece(piece);
			int pieceBaseValue = 0;
			int positionalBonus = 0;

			if (piece == PieceType::P1_MAN || piece == PieceType::P2_MAN) {
				pieceBaseValue = pawnValue;
				// Bonificaci�n por peones avanzados
				if (pieceOwner == PlayerColor::PLAYER_1) { // Negras, avanzan hacia filas mayores
					positionalBonus += advancementBonusBase * r;
				}
				else { // PlayerColor::PLAYER_2 (Blancas), avanzan hacia filas menores
					positionalBonus += advancementBonusBase * (currentBoard.GetBoardSize() - 1 - r);
				}
			}
			else { // Es Dama (Rey)
				pieceBaseValue = kingValue;
				// Las damas controlan m�s el centro, pero es m�s complejo de evaluar simplemente
			}

			// Penalizaci�n si est� en un borde lateral (columnas 0 o 7)
			if (c == 0 || c == (currentBoard.GetBoardSize() - 1)) {
				positionalBonus += edgePenalty;
			}
			// Podr�amos a�adir m�s bonificaciones/penalizaciones aqu� 

			if (pieceOwner == perspectiveColor) { // Pieza de la IA (o del jugador cuya perspectiva evaluamos)
				score += pieceBaseValue + positionalBonus;
			}
			else if (pieceOwner == opponentColor) { // Pieza del oponente
				score -= (pieceBaseValue + positionalBonus);
			}
		}
	}
	return score;
}


MoveInput ComputerPlayer::GetChosenMoveInput(
	const Board& board,
	const MoveGenerator& moveGenerator, // Par�metro de la interfaz, aunque ya tenemos m_moveGeneratorRef
	bool isInCaptureSequence,
	int forcedRow,
	int forcedCol,
	const std::vector<Move>& availableMandatoryJumpsFromGameManager // Estos ya est�n priorizados
) {
	MoveInput chosenAiMove;
	chosenAiMove.isValidFormat = false; // Por defecto, si no se encuentra nada
	chosenAiMove.wantsToExit = false;
	chosenAiMove.wantsToShowStats = false;

	std::vector<Move> candidateMoves;

	if (isInCaptureSequence) {
		// los saltos v�lidos para la pieza en (forcedRow, forcedCol).
		candidateMoves = availableMandatoryJumpsFromGameManager;
	}
	else {
		// No est� en secuencia, availableMandatoryJumpsFromGameManager contendr�
		// TODOS los saltos obligatorios (Dama > Pe�n). Si est� vac�a, no hay capturas obligatorias.
		if (!availableMandatoryJumpsFromGameManager.empty()) {
			candidateMoves = availableMandatoryJumpsFromGameManager;
		}
		else {
			// No hay capturas obligatorias, generar todos los movimientos simples posibles.
			for (int r = 0; r < board.GetBoardSize(); ++r) {
				for (int c = 0; c < board.GetBoardSize(); ++c) {
					if (m_moveGeneratorRef.GetPlayerFromPiece(board.GetPieceAt(r, c)) == m_color) {
						// GenerateMovesForPiece para una pieza sin saltos obligatorios globales
						// y sin saltos propios devolver� solo simples.
						std::vector<Move> movesForPiece = m_moveGeneratorRef.GenerateMovesForPiece(board, r, c);
						for (const auto& move : movesForPiece) {
							if (!move.isCapture_) { // Asegurarse de que solo son movimientos simples
								candidateMoves.push_back(move);
							}
						}
					}
				}
			}
		}
	}

	if (candidateMoves.empty()) {
		// No hay movimientos v�lidos (la IA est� bloqueada o es un error si HasAnyValidMoves dijo que s� hab�a)
		return chosenAiMove; // Devuelve isValidFormat = false
	}

	// --- Evaluaci�n de Movimientos y Selecci�n ---
	Move bestMove; // Se inicializar� en el primer bucle o si solo hay un candidato
	int bestScore = std::numeric_limits<int>::min(); // El valor m�s bajo posible para int

	bool firstMoveEvaluated = false;

	for (const Move& currentMove : candidateMoves) {
		Board tempBoard = board;

		PieceType pieceMoved = tempBoard.GetPieceAt(currentMove.startR_, currentMove.startC_);
		tempBoard.SetPieceAt(currentMove.endR_, currentMove.endC_, pieceMoved);
		tempBoard.SetPieceAt(currentMove.startR_, currentMove.startC_, PieceType::EMPTY);
		if (currentMove.isCapture_) {
			int capturedR = currentMove.startR_ + (currentMove.endR_ - currentMove.startR_) / 2;
			int capturedC = currentMove.startC_ + (currentMove.endC_ - currentMove.startC_) / 2;
			tempBoard.SetPieceAt(capturedR, capturedC, PieceType::EMPTY);
		}
		tempBoard.PromotePieceIfNecessary(currentMove.endR_, currentMove.endC_);

		int score = EvaluateBoardState(tempBoard, m_color);

		// Desempate aleatorio simple: si dos movimientos tienen la misma mejor puntuaci�n,
		// hay una probabilidad de elegir el nuevo.
		if (!firstMoveEvaluated || score > bestScore) {
			bestScore = score;
			bestMove = currentMove;
			firstMoveEvaluated = true;
		}
		else if (score == bestScore) {
			// Si las puntuaciones son iguales, elegir al azar (50% de probabilidad de cambiar)
			std::uniform_int_distribution<int> dist(0, 1);
			if (dist(m_rng) == 0) {
				bestMove = currentMove; // Sobrescribir con el nuevo movimiento
			}
		}
	}

	if (!firstMoveEvaluated && !candidateMoves.empty()) {
		// Esto podr�a pasar si todos los movimientos llevan a un estado con puntuaci�n min_int,
		// o si hubo un error. Como fallback, tomar el primer movimiento candidato si existe.
		bestMove = candidateMoves[0];
		firstMoveEvaluated = true; // Para marcar que se ha elegido un bestMove
	}

	if (firstMoveEvaluated) { // Si se encontr� un mejor movimiento
		chosenAiMove.startRow = bestMove.startR_;
		chosenAiMove.startCol = bestMove.startC_;
		chosenAiMove.endRow = bestMove.endR_;
		chosenAiMove.endCol = bestMove.endC_;
		chosenAiMove.isValidFormat = true;
	}
	else {
		// Si despu�s de todo, no se pudo determinar un bestMove 
		chosenAiMove.isValidFormat = false;
	}

	// Simular un peque�o retraso para que la IA no sea instant�nea
	if (chosenAiMove.isValidFormat) { // Solo retrasar si la IA va a hacer un movimiento
		std::uniform_int_distribution<int> delay_dist(200, 800); // Milisegundos
		std::this_thread::sleep_for(std::chrono::milliseconds(delay_dist(m_rng)));
	}

	return chosenAiMove;
}