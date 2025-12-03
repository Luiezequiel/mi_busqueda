#include "SearchEngine.h"
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <iostream>

SearchEngine::SearchEngine(const std::string& data_dir)
    : fh_(data_dir) { }

void SearchEngine::build_index() {
    index_.clear();
    auto files = fh_.list_filenames();
    std::cout << "Archivos encontrados: " << files.size() << std::endl;
    
    int count = 0;
    // Recorremos archivo por archivo, contamos tokens y añadimos al índice
    for (const auto& fname : files) {
        count++;
        if (count % 5000 == 0) {
            std::cout << "Procesados: " << count << " / " << files.size() << std::endl;
        }
        std::string content = fh_.read_file(fname);
        auto tokens = FileHandler::tokenize(content);
        std::unordered_map<std::string,int> freq;
        for (const auto& t : tokens) ++freq[t];
        for (const auto& kv : freq) index_.add(kv.first, fname, kv.second);
    }
    
    std::cout << "Guardando indice en disco...\n";
    if (index_.save_to_file(fh_.get_dirpath() + "/index.bin")) {
        std::cout << "Indice guardado exitosamente.\n";
    } else {
        std::cout << "Error al guardar el indice.\n";
    }
}

std::vector<std::pair<std::string,int>> SearchEngine::search_one(const std::string& w) const {
    auto postings = index_.get_postings(w);
    std::vector<std::pair<std::string,int>> res(postings.begin(), postings.end());
    std::sort(res.begin(), res.end(), [](const auto& a, const auto& b){
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first; // desempata por nombre
    });
    if (res.size() > 3) res.resize(3);
    return res;
}

std::vector<std::pair<std::string,int>> SearchEngine::search_two(const std::string& w1, const std::string& w2) const {
    auto p1 = index_.get_postings(w1);
    auto p2 = index_.get_postings(w2);
    std::vector<std::pair<std::string,int>> res;
    for (const auto& kv : p1) {
        const auto& fname = kv.first;
        auto it = p2.find(fname);
        if (it != p2.end()) {
            int score = kv.second + it->second;
            res.emplace_back(fname, score);
        }
    }
    std::sort(res.begin(), res.end(), [](const auto& a, const auto& b){
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
    if (res.size() > 3) res.resize(3);
    return res;
}

std::vector<std::pair<std::string,int>> SearchEngine::query(const std::string& raw_query) const {
    auto tokens = FileHandler::tokenize(raw_query);
    if (tokens.empty()) return {};
    if (tokens.size() == 1) return search_one(tokens[0]);
    return search_two(tokens[0], tokens[1]); // usa solo primeras 2
}

std::string SearchEngine::format_results(const std::vector<std::pair<std::string,int>>& res) {
    if (res.empty()) return "No se encontraron archivos relevantes.";
    std::ostringstream oss;
    for (const auto& p : res) {
        oss << p.first << " (puntuacion: " << p.second << ")\n";
    }
    return oss.str();
}
