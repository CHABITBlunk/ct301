#include "Image.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Image::Image(string ppmfname) {
  ppmfilename = ppmfname;
  ppm.open(ppmfilename);
  if (!ppm.is_open()) {
    cerr << "error: unable to open file " << ppmfilename << endl;
  }
}

Image::Image(string ppmfname, string checksumfname) {
  ppmfilename = ppmfname;
  checksumfilename = checksumfname;
  ppm.open(ppmfilename);
  if (!ppm.is_open()) {
    cerr << "error: unable to open file " << ppmfilename << endl;
  }
}

int Image::readSingleValue() {
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

bool Image::hasValidHeader() {
  string firstLine;
  ppm >> firstLine;
  if (ppm.fail()) {
    ppm.clear();
    ppm.ignore();
    return false;
  }
  return firstLine == "P6";
}

bool Image::isValidEntry(int i) { return i <= maxValue && i >= 0; }

int Image::readImageFile() {
  if (!this->hasValidHeader()) {
    cerr << "error: ppm file has incorrect header" << endl;
    return -1;
  }
  height = this->readSingleValue();
  width = this->readSingleValue();
  maxValue = this->readSingleValue();
  this->image = new Pixel *[height];
  this->rowTotals = new int[height];
  this->colTotals = new int[width];
  for (int i = 0; i < height; i++) {
    image[i] = new Pixel[width];
  }
  int nextR, nextG, nextB;
  int r = 0, c = 0;
  while (ppm >> nextR >> nextG >> nextB) {
    if (!this->isValidEntry(nextR) || !this->isValidEntry(nextG) ||
        !this->isValidEntry(nextB)) {
      cerr << "error: entry out of bounds" << endl;
      return -1;
    }
    image[r][c] = Pixel(nextR, nextG, nextB);
    c++;
    if (c == width) {
      c = 0;
      r++;
    }
  }
  if (r != height) {
    cerr << "Error: rows not right size" << endl;
    return -1;
  }
  for (r = 0; r < height; r++) {
    rowTotals[r] = 0;
    for (c = 0; c < width; c++) {
      rowTotals[r] += image[r][c].getSum();
    }
  }
  for (c = 0; c < width; c++) {
    colTotals[c] = 0;
    for (r = 0; r < height; r++) {
      colTotals[c] += image[r][c].getSum();
    }
  }
  return 0;
}

int Image::compareAgainstChecksum() {
  if (readImageFile() != 0) {
    return -1;
  }
  checksum.open(checksumfilename);
  if (!checksum.is_open()) {
    cerr << "Unable to open file " << checksumfilename << endl;
    return -1;
  }
  for (int i = 0; i < height; i++) {
    int rowTotal;
    checksum >> rowTotal;
    if (rowTotals[i] != rowTotal) {
      cerr << "error: checksum in row " << i + 1 << " (" << rowTotal << ") "
           << "does not match calculated total (" << rowTotals[i] << ")"
           << endl;
      return -(i + 2);
    }
  }
  cout << "success" << endl;
  return 0;
}

int Image::writeToChecksumFiles(string rowfname, string colfname) {
  int readImageFileResult = readImageFile();
  if (readImageFileResult != 0) {
    return readImageFileResult;
  }
  int i;
  out.open(rowfname);
  if (!out.is_open()) {
    cerr << "error: unable to open file " << rowfname << endl;
    return -1;
  }
  for (i = 0; i < height; i++) {
    out << rowTotals[i] << std::endl;
  }
  out.close();
  out.open(colfname);
  if (!out.is_open()) {
    cerr << "error: unable to open file " << colfname << endl;
    return -1;
  }
  for (i = 0; i < width; i++) {
    out << colTotals[i] << std::endl;
  }
  out.close();
  return 0;
}

Pixel::Pixel() {
  this->red = -1;
  this->green = -1;
  this->blue = -1;
}

Pixel::Pixel(int r, int g, int b) {
  this->red = r;
  this->green = g;
  this->blue = b;
}

int Pixel::getSum() { return red + green + blue; }
