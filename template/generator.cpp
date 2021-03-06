#include <fstream> //ifstream, ofstream
#include <string>
#include <sys/types.h> // stat, mkdir
#include <sys/stat.h> // stat, mkdir
#include <cerrno> // errno
#include <iostream>
#include <vector>
#include <cctype> // isupper, toupper

static const std::string defaultClassName = "__CLASS__";

static std::vector<std::string> files = {
    {"Makefile"},
    {"__CLASS__Problem.cpp"},
    {"__CLASS__Problem.hh"},
    {"problem.ini"}
};

static void replace(std::string &file, const std::string &className) {
    size_t start = 0;
    while ((start = file.find(defaultClassName, start)) != std::string::npos) {
        file.replace(start, defaultClassName.length(), className);
        start += className.length();
    }
}

int main(int ac, char **av) {
    if (ac != 2) {
        std::cout << "Usage: generator project_name" << std::endl;
        return -1;
    }
    std::string className(av[1]);
    std::string problemPath = std::string("../problems/") + className;
    if (mkdir(problemPath.c_str(), 0750) == -1) {
        std::cerr << "Could not create directory " << problemPath
                << ". Maybe this problem already exists ?" << std::endl;
        return -1;
    }
    std::cout << "Creation of the directory " << problemPath << std::endl;
    if (isupper(className[0]) == false)
        className[0] = toupper(className[0]); 
    std::ifstream srcFile;
    std::string content, currentFile;
    std::ofstream destFile;
    for (auto file : files) {
        currentFile = "./files/" + file;
        srcFile.open(currentFile, std::ifstream::in);
        if (srcFile.is_open() == false) {
            std::cout << "Error, can't open " << currentFile << std::endl;
            return -1;
        }
        content.assign((std::istreambuf_iterator<char>(srcFile)),
                (std::istreambuf_iterator<char>()));
        srcFile.close();
        replace(content, className);
        replace(file, className);
        currentFile = problemPath + "/" + file;
        std::cout << "Generation of file " << currentFile << std::endl;
        destFile.open(currentFile);
        if (destFile.is_open() == false) {
            std::cout << "Error, can't open " << currentFile << std::endl;
            return -1;
        }
        destFile << content;
        destFile.close();
    }
}
