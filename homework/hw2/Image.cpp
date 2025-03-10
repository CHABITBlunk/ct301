#include "Image.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
    return output;
  }
  return -1;
}

bool Image::hasValidHeader() {
  string firstLine;
  ppm >> firstLine;
  if (ppm.fail()) {
    ppm.clear();
    ppm.ignore();
    return false;
  }
  string str("P3");
  return firstLine == str;
}

bool Image::isValidEntry(size_t i) { return i <= maxValue; }

int Image::readFile() {
  if (!this->hasValidHeader()) {
    cerr << "error: ppm file has incorrect header" << endl;
    return -1;
  }
  width = this->readSingleValue();
  height = this->readSingleValue();
  maxValue = this->readSingleValue();
  this->image = new int *[height];
  this->rowTotals = new int[height];
  for (size_t i = 0; i < height; i++) {
    image[i] = new int[width];
  }
  int nextR, nextG, nextB;
  size_t r = 0, c = 0;
  while (ppm >> nextR >> nextG >> nextB) {
    if (!this->isValidEntry(nextR) || !this->isValidEntry(nextG) ||
        !this->isValidEntry(nextB)) {
      cerr << "error: entry out of bounds" << endl;
      return -1;
    }
    image[r][c] = nextR + nextG + nextB;
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
      rowTotals[r] += image[r][c];
    }
  }
  return 0;
}

int Image::compareAgainstChecksum() {
  if (readFile() != 0) {
    return -1;
  }
  checksum.open(checksumfilename);
  if (!checksum.is_open()) {
    cerr << "Unable to open file " << checksumfilename << endl;
    return -1;
  }
  vector<int> checksums;
  int rowTotal;
  while (checksum >> rowTotal) {
    if (checksum.fail()) {
      checksum.clear();
      checksum.ignore();
      cerr << "error: checksum file is corrupted" << endl;
      return -1;
    }
    checksums.push_back(rowTotal);
  }
  if (checksums.size() != height) {
    cerr << "error: checksum length " << checksums.size()
         << "does not match expected number of checksums (" << height << ")"
         << endl;
    return -1;
  }
  for (size_t i = 0; i < height; i++) {
    if (rowTotals[i] != checksums[i]) {
      cerr << "error: checksum in row " << i + 1 << " (" << checksums[i] << ") "
           << "does not match calculated total (" << rowTotals[i] << ")"
           << endl;
      return -(i + 2);
    }
  }
  cout << "success" << endl;
  return 0;
}
