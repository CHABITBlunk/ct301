#include "Image.h"
#include <cstdio>
#include <iostream>

using namespace std;

int Image::readImageFile() {
  if (!file.hasValidHeader()) {
    cerr << "error: ppm file has incorrect header" << endl;
    return -1;
  }
  width = file.readSingleValue();
  height = file.readSingleValue();
  maxValue = file.readSingleValue();
  image = new Pixel *[height];
  for (int i = 0; i < height; i++) {
    image[i] = new Pixel[width];
  }
  Pixel nextPixel;
  int r = 0, c = 0;
  while (!file.eof()) {
    (nextPixel = file.readPixel());
    for (int i = 0; i < 3; i++) {
      if (!isValidEntry(nextPixel.getR()) || !isValidEntry(nextPixel.getG()) ||
          !isValidEntry(nextPixel.getB())) {
        cerr << "error: entry out of bounds" << endl;
        return -1;
      }
    }
    image[r][c] = nextPixel;
    c++;
    if (c == width) {
      c = 0;
      r++;
    }
  }
  if (r != height) {
    cerr << "error: rows not right size" << endl;
    return -1;
  }
  if (c != width) {
    cerr << "error: columns not right size" << endl;
    return -1;
  }
  return 0;
}

void Image::normalize() {
  cout << "image before normalization" << endl;
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      cout << "(" << image[i][j].getR() << "," << image[i][j].getG() << ","
           << image[i][j].getB() << ") ";
    }
    cout << endl;
  }
}
