#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <unordered_map>

// Lee archivos de un directorio y tokeniza (normaliza) el texto.
class FileHandler {
public:
    explicit FileHandler(const std::string& directory);
    // Devuelve lista de nombres de archivo dentro del directorio
    std::vector<std::string> list_filenames() const;
    // Devuelve el contenido completo de un archivo por nombre
    std::string read_file(const std::string& filename) const;
    // Normaliza y tokeniza un texto: devuelve tokens en minúsculas
    static std::vector<std::string> tokenize(const std::string& text);
    // Devuelve la ruta del directorio
    std::string get_dirpath() const;
private:
    std::string dirpath_;
};

#endif
