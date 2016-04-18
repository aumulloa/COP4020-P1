#include <iostream>
#include <fstream>
#include <string>


#ifndef FileReader_H
#define FileReader_H

using namespace std;

class FileReader  {

  private:
    string filePath;

  public:
    FileReader(string filePath);
    ifstream ifs;
    void OpenFile();
    void ReadLine();
    bool IsOpen();
};

#endif
