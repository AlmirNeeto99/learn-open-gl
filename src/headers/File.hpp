#ifndef FILE_H

#define FILE_H

#include <string>
#include <fstream>
#include <sstream>

class File {
   public:
    File();
    File(std::string);
    ~File();
    void setPath(std::string path);
    char* getContent();

   private:
    std::string path;
};

#endif