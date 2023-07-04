#include "headers/File.hpp"

#include <iostream>

File::File(std::string path) : path(path) {
}

File::~File() {
}

char* File::getContent() {
    if (this->path.empty()) {
        return nullptr;
    }

    std::ifstream inf(this->path);

    std::string line;
    std::stringstream content;

    while (inf.good()) {
        std::getline(inf, line);
        content << line << '\n';
    }

    std::string fileContent = content.str();
    size_t length = fileContent.length();

    char* stringChar = new char[length + 1];
    fileContent.copy(stringChar, length);

    inf.close();

    return stringChar;
}

void File::setPath(std::string path) {
    this->path = path;
}