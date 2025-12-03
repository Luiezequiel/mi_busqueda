#include "SearchEngine.h"
#include <iostream>
#include <string>

int main() {
    const std::string data_dir = "data/movies";

    std::cout << "Inicializando motor de busqueda...\n";
    SearchEngine engine(data_dir);

    std::cout << "Construyendo indice invertido (esto puede tardar varios minutos con 43k archivos)...\n";
    engine.build_index();
    std::cout << "Indice construido.\n";

    std::cout << "Escribe una consulta (1 o 2 palabras). Escribe 'salir' para terminar.\n";
    while (true) {
        std::cout << "> ";
        std::string line;
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;
        std::string low = line;
        for (auto &c: low) c = (char)std::tolower(c);
        if (low == "salir" || low == "exit" || low == "quit") break;
        auto results = engine.query(line);
        std::cout << SearchEngine::format_results(results) << std::endl;
    }

    std::cout << "Adios.\n";
    return 0;
}
