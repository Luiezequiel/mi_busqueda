#include "FileHandler.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>

namespace fs = std::filesystem;

FileHandler::FileHandler(const std::string& directory)
    : dirpath_(directory) { }

std::vector<std::string> FileHandler::list_filenames() const {
    std::vector<std::string> names;
    for (const auto& entry : fs::directory_iterator(dirpath_)) {
        if (!entry.is_regular_file()) continue;
        names.push_back(entry.path().filename().string());
    }
    return names;
}

std::string FileHandler::read_file(const std::string& filename) const {
    std::string full = (fs::path(dirpath_) / filename).string();
    std::ifstream ifs(full, std::ios::in);
    if (!ifs) return "";
    std::ostringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

std::vector<std::string> FileHandler::tokenize(const std::string& text) {
    // Convierte a minúsculas
    std::string lower;
    lower.reserve(text.size());
    for (unsigned char c : text) lower.push_back(std::tolower(c));

    // Regex para palabras: letras y números y apóstrofe
    static const std::regex token_re(R"([a-z0-9']+)");
    std::vector<std::string> tokens;
    auto it = std::sregex_iterator(lower.begin(), lower.end(), token_re);
    auto end = std::sregex_iterator();
    for (; it != end; ++it) tokens.push_back(it->str());
    return tokens;
}

std::string FileHandler::get_dirpath() const {
    return dirpath_;
}
