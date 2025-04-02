#include "PPMFile.h"
#include <fstream>

using namespace std;

bool PPMFile::hasValidHeader() {
  string firstLine;
  ppm >> firstLine;
  if (ppm.fail() || !isOpen()) {
    ppm.clear();
    ppm.ignore();
    return false;
  }
  return firstLine == "P3";
}

int PPMFile::readSingleValue() {
  int output = -1;
  if (ppm.is_open()) {
    ppm >> output;
    if (ppm.fail()) {
      ppm.clear();
      ppm.ignore();
      output = -1;
    }
  }
  return output;
}

Pixel PPMFile::readPixel() {
  int *pixel = new int[3];
  for (int i = 0; i < 3; i++) {
    pixel[i] = readSingleValue();
  }
  return Pixel(pixel[0], pixel[1], pixel[2]);
}
