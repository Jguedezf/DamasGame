#include "FileHandler.h" // Incluimos nuestro archivo de cabecera
#include <fstream>       // Necesario para std::ofstream (output file stream) y std::ifstream (input file stream)
#include <iostream>      // Necesario para std::cout y std::cerr
#include <string>        // Ya incluido en el .h, pero buena pr�ctica si se usa string aqu� directamente
#include <vector>        // Necesario para std::vector si alguna funci�n lo usara (no es el caso actual, pero �til)
#include <chrono>        // Necesario para obtener el tiempo actual (aunque usaremos ctime para formatearlo)
#include <ctime>         // Necesario para time_t, tm, localtime, strftime

// Constructor (puede estar vac�o)
FileHandler::FileHandler() {
    // No se necesita inicializaci�n compleja por ahora
}

// Destructor (puede estar vac�o)
FileHandler::~FileHandler() {
    // No se necesita limpieza compleja por ahora
}

// Implementaci�n para guardar el resultado de la partida
bool FileHandler::saveGameResult(const GameResult& result) {
    // Abrir el archivo en modo ap�ndice (ios::app)
    // Si el archivo no existe, se crear�.
    std::ofstream outputFile(RESULTS_FILENAME, std::ios::app);

    // Verificar si el archivo se abri� correctamente
    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de resultados: " << RESULTS_FILENAME << std::endl;
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
        std::cout << "HISTORIAL DE PARTIDAS GUARDADAS" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "No hay historial de partidas guardado aun." << std::endl;
        return; // Salir de la funci�n si no se puede abrir (o no existe)
    }

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "HISTORIAL DE PARTIDAS GUARDADAS" << std::endl;
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

// Nota: Faltar�a una funci�n para obtener la fecha y hora actual en el formato "YYYY-MM-DD HH:MM:SS"
// Podemos agregarla aqu� o donde se preparen los datos GameResult antes de llamar a saveGameResult.
// Es m�s limpio prepararla antes, en el GameManager.