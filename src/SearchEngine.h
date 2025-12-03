#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include "FileHandler.h"
#include "InvertedIndex.h"
#include <string>
#include <vector>
#include <utility>

// Clase que construye el índice y responde consultas
class SearchEngine {
public:
    SearchEngine(const std::string& data_dir);
    // Construye el índice leyendo archivos (call antes de buscar)
    void build_index();
    // Consulta: raw_query puede ser 1 o 2 palabras; devuelve hasta 3 pares (filename, score)
    std::vector<std::pair<std::string,int>> query(const std::string& raw_query) const;
    // Formatea resultados en string para imprimir
    static std::string format_results(const std::vector<std::pair<std::string,int>>& res);
private:
    FileHandler fh_;
    InvertedIndex index_;
    // búsquedas internas
    std::vector<std::pair<std::string,int>> search_one(const std::string& w) const;
    std::vector<std::pair<std::string,int>> search_two(const std::string& w1, const std::string& w2) const;
};

#endif
