#pragma once

#include <string> // Necesario para std::string

// Definimos una estructura simple para contener los datos de una partida
// Esto nos ayudar� a pasar la informaci�n de manera organizada.
struct GameResult {
    std::string date;
    std::string time;
    std::string playerTypes; // e.g., "Humano vs Humano", "Computadora vs Computadora"
    std::string winner;      // e.g., "Negras (b)", "Blancas (w)"
    std::string reason;      // e.g., "se quedo sin piezas", "salio de la partida"
    int totalTurns;
    int winnerCaptures;
    int loserCaptures;
};

class FileHandler {
public:
    // Constructor y Destructor (pueden estar vac�os por ahora si no se necesita inicializaci�n/limpieza compleja)
    FileHandler();
    ~FileHandler();

    // Guarda los datos de una partida al final del archivo de resultados
    // Retorna true si se guard� correctamente, false en caso contrario.
    bool saveGameResult(const GameResult& result);

    // Lee todos los resultados guardados en el archivo y los muestra en la consola
    void displayGameHistory();

private:
    // Nombre del archivo donde se guardar�n los resultados
    const std::string RESULTS_FILENAME = "damas_results.txt";
};