#include "Image.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Image::Image(string fname) {
  filename = fname;
  infile.open(filename);
  if (!infile.is_open()) {
    cerr << "Unable to open file " << filename << endl;
  }
}

int Image::readSingleValue() {
  int output = -1;
  if (infile.is_open()) {
    infile >> output;
    if (infile.fail()) {
      infile.clear();
      infile.ignore();
      output = -1;
    }
    return output;
  }
  return -1;
}

bool Image::hasValidHeader() {
  string firstLine;
  infile >> firstLine;
  if (infile.fail()) {
    infile.clear();
    infile.ignore();
    return false;
  }
  string str("P3");
  return firstLine == str;
}

int Image::createMatrix() {
  width = this->readSingleValue();
  height = this->readSingleValue();
  maxValue = this->readSingleValue();
  return 0;
}
