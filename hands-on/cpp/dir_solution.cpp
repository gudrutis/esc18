#include <algorithm>
#include <dirent.h>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

template<typename T>
std::ostream &operator<<(std::ostream &os, std::vector <T> const &c) {
    os << "{ ";
    std::copy(std::begin(c), std::end(c), std::ostream_iterator < T > {os, " "});
    os << '}';

    return os;
}

std::vector <std::string> entries(DIR &dir) {
    std::vector <std::string> result;

    // relevant function and data structure are:
    //
    // int  readdir_r(DIR* dirp, struct dirent* entry, struct dirent** result);
    //
    // struct dirent {
    //   // ...
    //   char d_name[256];
    // };
    //
    dirent entry; // directory data type
    for (auto *r = &entry; readdir_r(&dir, &entry, &r) == 0 && r;) {
        result.push_back(entry.d_name);
    }
    return result;
}

auto VerboseCloseDir(DIR *dir) -> decltype(closedir(dir)) {  //  auto deduce the return type of a function
    std::cout << "Closing dir... ";
    auto retValue = closedir(dir);
    std::cout << "closed." << std::endl;
    return retValue;
}

using DirPtr = std::unique_ptr<DIR, int (*)(DIR *)>;

DirPtr CreateDirPtr(std::string dirName) {
    return DirPtr{
                opendir(dirName.c_str()),
                VerboseCloseDir};
}

using FilePtr = std::unique_ptr<FILE, int (*)(FILE *)>;

FilePtr CreateFilePtr(std::string fileName) {
    return FilePtr{fopen(fileName.c_str(), "r"), fclose};
}

int main(int argc, char *argv[]) {
    std::string const name = argc > 1 ? argv[1] : ".";

    // create a smart pointer to a DIR here, with a deleter
    // relevant functions and data structures are
    // DIR* opendir(const char* name);
    // int  closedir(DIR* dirp);

    auto dirPtr = CreateDirPtr(name);
    auto files = entries(*dirPtr);
    std::sort(files.begin(), files.end());
    std::cout << files << std::endl;

    std::vector <FilePtr> openedFiles;
    openedFiles.reserve(files.size());
    for (auto &fileName : files) {
        openedFiles.push_back(CreateFilePtr(fileName));
    }
    std::cout << "Now dir should be closed" << std::endl;
}