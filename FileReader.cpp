#include "FileReader.h"

FileReader::FileReader(string filePath) {
  this->filePath = filePath;
}

bool FileReader::IsOpen() {
  return (ifs.is_open());
}

void FileReader::OpenFile()  {

    if(ifs.is_open()) {
      cout << "File already open" << endl;
      return;
    }

    ifs.open(this->filePath.c_str());

    if(ifs.is_open()) {
      cout << "File open, ready to start reading!" << endl;
      return;
    }
      cout << "Failed opening file" << endl;
}
