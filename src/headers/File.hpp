#ifndef FILE_H

#define FILE_H

#include <string>

class File {
   public:
    File();
    File(std::string);
    ~File();

   private:
    std::string path;
};

#endif