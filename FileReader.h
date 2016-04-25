#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstring>

#ifndef FileReader_H
#define FileReader_H

using namespace std;

class FileReader  {

  private:
    //string filePath;

  public:
    //FileReader(string filePath);
    FileReader(char* filePath);
    ifstream ifs;    char* filePath;

    void OpenFile();
    void ReadLine();
    bool IsOpen();
    char GetNext();
    void PutBack(char c);
};

#endif
