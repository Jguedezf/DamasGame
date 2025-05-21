#include "FileHandler.h" 
#include <fstream>       
#include <iostream>      
#include <string>        
#include <vector>        
#include <chrono>        
#include <ctime>         


FileHandler::FileHandler(const LocalizationManager& i18n) :
    m_i18n(i18n)
{
}


FileHandler::~FileHandler() {
   
}

// Implementaci�n para guardar el resultado de la partida
bool FileHandler::saveGameResult(const GameResult& result) {
    // Abrir el archivo en modo ap�ndice (ios::app)
    // Si el archivo no existe, se crear�.
    std::ofstream outputFile(RESULTS_FILENAME, std::ios::app);

    // Verificar si el archivo se abri� correctamente
    if (!outputFile.is_open()) {
        std::cerr << m_i18n.GetString("error_opening_results_file") << RESULTS_FILENAME << std::endl;
        return false; // Indicar que fall� el guardado
    }

    // Formatear la l�nea de texto seg�n la estructura de la imagen:
    // Fecha Hora;TipoJugador1 vs TipoJugador2;Ganador;RazonGanador;Turnos;CapturasGanador;CapturasPerdedor
    outputFile << result.date << " " << result.time << ";"
        << result.playerTypes << ";"
        << result.winner << ";"
        << result.reason << ";"
        << result.totalTurns << ";"
        << result.winnerCaptures << ";"
        << result.loserCaptures << std::endl; // std::endl a�ade un salto de l�nea y vac�a el buffer

    // Cerrar el archivo
    outputFile.close();

    // Indicar que se guard� correctamente
    return true;
}

// Implementaci�n para leer y mostrar el historial de partidas
void FileHandler::displayGameHistory() {
    // Abrir el archivo en modo lectura (ios::in es por defecto para ifstream)
    std::ifstream inputFile(RESULTS_FILENAME);

    // Verificar si el archivo se abri� correctamente
    // Esto tambi�n verifica si el archivo existe.
    if (!inputFile.is_open()) {
        std::cout << "-----------------------------------" << std::endl;
        std::cout << m_i18n.GetString("stats_history_title") << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        std::cout << m_i18n.GetString("stats_no_history") << std::endl;
        return; // Salir de la funci�n si no se puede abrir (o no existe)
    }

    std::cout << "-----------------------------------" << std::endl;
    std::cout << m_i18n.GetString("stats_history_title") << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    std::string line;
    // Leer el archivo l�nea por l�nea
    while (std::getline(inputFile, line)) {
        // Imprimir cada l�nea le�da (que ya est� formateada)
        std::cout << line << std::endl;
    }

    // Cerrar el archivo
    inputFile.close();

    std::cout << "-----------------------------------" << std::endl; // L�nea de cierre para la visualizaci�n
}

