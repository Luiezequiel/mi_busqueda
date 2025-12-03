#include "InvertedIndex.h"
#include <fstream>
#include <cstring>
#include <cstdint>

void InvertedIndex::add(const std::string& word, const std::string& filename, int count) {
    index_[word][filename] += count;
}

std::unordered_map<std::string,int> InvertedIndex::get_postings(const std::string& word) const {
    auto it = index_.find(word);
    if (it == index_.end()) return {};
    return it->second; // copia
}

void InvertedIndex::clear() {
    index_.clear();
}

bool InvertedIndex::save_to_file(const std::string& filepath) const {
    std::ofstream ofs(filepath, std::ios::binary);
    if (!ofs) return false;

    // Guardar número de palabras
    uint64_t num_words = index_.size();
    ofs.write(reinterpret_cast<const char*>(&num_words), sizeof(num_words));

    for (const auto& word_entry : index_) {
        const auto& word = word_entry.first;
        const auto& postings = word_entry.second;

        // Guardar palabra
        uint64_t word_len = word.length();
        ofs.write(reinterpret_cast<const char*>(&word_len), sizeof(word_len));
        ofs.write(word.c_str(), word_len);

        // Guardar número de postings para esta palabra
        uint64_t num_postings = postings.size();
        ofs.write(reinterpret_cast<const char*>(&num_postings), sizeof(num_postings));

        // Guardar cada posting (filename, frequency)
        for (const auto& posting : postings) {
            const auto& filename = posting.first;
            int freq = posting.second;

            uint64_t fname_len = filename.length();
            ofs.write(reinterpret_cast<const char*>(&fname_len), sizeof(fname_len));
            ofs.write(filename.c_str(), fname_len);
            ofs.write(reinterpret_cast<const char*>(&freq), sizeof(freq));
        }
    }

    return ofs.good();
}

bool InvertedIndex::load_from_file(const std::string& filepath) {
    std::ifstream ifs(filepath, std::ios::binary);
    if (!ifs) return false;

    index_.clear();

    uint64_t num_words;
    ifs.read(reinterpret_cast<char*>(&num_words), sizeof(num_words));
    if (!ifs.good()) return false;

    for (uint64_t i = 0; i < num_words; ++i) {
        uint64_t word_len;
        ifs.read(reinterpret_cast<char*>(&word_len), sizeof(word_len));
        if (!ifs.good()) return false;

        std::string word(word_len, '\0');
        ifs.read(&word[0], word_len);
        if (!ifs.good()) return false;

        uint64_t num_postings;
        ifs.read(reinterpret_cast<char*>(&num_postings), sizeof(num_postings));
        if (!ifs.good()) return false;

        for (uint64_t j = 0; j < num_postings; ++j) {
            uint64_t fname_len;
            ifs.read(reinterpret_cast<char*>(&fname_len), sizeof(fname_len));
            if (!ifs.good()) return false;

            std::string filename(fname_len, '\0');
            ifs.read(&filename[0], fname_len);
            if (!ifs.good()) return false;

            int freq;
            ifs.read(reinterpret_cast<char*>(&freq), sizeof(freq));
            if (!ifs.good()) return false;

            index_[word][filename] = freq;
        }
    }

    return true;
}
