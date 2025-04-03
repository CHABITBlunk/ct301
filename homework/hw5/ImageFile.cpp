#include "ImageFile.h"
#include <fstream>

using namespace std;

int ImageFile::readSingleValue() {
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

Pixel *ImageFile::readPixel() {
  int value;
  switch (header) {
  case 0:
    break;
  case 1:
    value = readSingleValue();
    if (value != 0 || value != 1) {
    }
    return new BinaryPixel(value);
    break;
  case 2:
    value = readSingleValue();
    return new GrayscalePixel(value);
    break;
  case 3:
    int r = readSingleValue(), g = readSingleValue(), b = readSingleValue();
    return new RGBPixel(r, g, b);
    break;
  }
}

int ImageFile::getHeader() {
  string h;
  ppm >> h;
  if (ppm.fail() || !isOpen()) {
    ppm.clear();
    ppm.ignore();
  }
  if (h == "P3") {
    header = 3;
  } else if (h == "P2") {
    header = 2;
  } else if (h == "P1") {
    header = 1;
  }
  return header;
}
