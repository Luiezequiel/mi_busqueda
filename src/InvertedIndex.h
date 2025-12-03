#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <string>
#include <unordered_map>
#include <vector>

// índice invertido: palabra -> mapa archivo -> frecuencia
class InvertedIndex {
public:
    // Añadir conteo de una palabra para un archivo
    void add(const std::string& word, const std::string& filename, int count);
    // Obtener postings para una palabra; devuelve mapa archivo->freq
    std::unordered_map<std::string,int> get_postings(const std::string& word) const;
    // Construir desde pares (se usa en SearchEngine)
    void clear();
    // Guardar índice en archivo binario
    bool save_to_file(const std::string& filepath) const;
    // Cargar índice desde archivo binario
    bool load_from_file(const std::string& filepath);
private:
    std::unordered_map<std::string, std::unordered_map<std::string,int>> index_;
};

#endif
