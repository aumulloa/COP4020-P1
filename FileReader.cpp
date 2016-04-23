#include "FileReader.h"

FileReader::FileReader(string filePath) {
  this->filePath = filePath;
}

bool FileReader::IsOpen() {
  return (ifs.is_open());
}

void FileReader::OpenFile()  {

    if(ifs.is_open()) {
      return;
    }

    ifs.open(this->filePath.c_str());

    if(ifs.is_open()) {
      return;
    }
    string message = "Error opening file";
    throw logic_error(message);
}
char FileReader::GetNext()  {

  if(!ifs.is_open()) {
    string message = "File is not opened";
    throw logic_error(message);
  }

  char nextChar;
  ifs.get(nextChar);
  return nextChar;
}
void FileReader::PutBack(char c)  {

  ifs.putback(c);
}
