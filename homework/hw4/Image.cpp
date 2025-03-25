#include "Image.h"
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <limits.h>

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
  int r = 0, c = 0;
  while (r < height) {
    Pixel nextPixel = file.readPixel();
    if (!isValidEntry(nextPixel.r) || !isValidEntry(nextPixel.g) ||
        !isValidEntry(nextPixel.b)) {
      cerr << "error: entry out of bounds" << endl;
      return -1;
    }
    image[r][c] = nextPixel;
    c++;
    if (c == width) {
      c = 0;
      r++;
    }
  }
  return 0;
}

int min(Pixel p, int l) {
  if (p.r < l) {
    l = p.r;
  }
  if (p.g < l) {
    l = p.g;
  }
  if (p.b < l) {
    l = p.b;
  }
  return l;
}

int max(Pixel p, int h) {
  if (p.r > h) {
    h = p.r;
  }
  if (p.g > h) {
    h = p.g;
  }
  if (p.b > h) {
    h = p.b;
  }
  return h;
}

void Image::normalize() {
  int h = INT_MIN, l = INT_MAX;
  int r, c;
  for (r = 0; r < height; r++) {
    for (c = 0; c < width; c++) {
      h = max(image[r][c], h);
      l = min(image[r][c], l);
    }
  }
  for (r = 0; r < height; r++) {
    for (c = 0; c < width; c++) {
      image[r][c].r = std::round((image[r][c].r - l) * (255 / (h - l)));
      image[r][c].g = std::round((image[r][c].g - l) * (255 / (h - l)));
      image[r][c].b = std::round((image[r][c].b - l) * (255 / (h - l)));
    }
  }
  maxValue = 255;
}

int Image::writeToFile(string fname) {
  ofstream out(fname);
  out << "P3" << endl;
  out << width << " " << height << " " << maxValue << endl;
  int r, c;
  for (r = 0; r < height; r++) {
    for (c = 0; c < width; c++) {
      out << image[r][c].r << " " << image[r][c].g << " " << image[r][c].b
          << endl;
    }
  }
  out.close();
  return 0;
}
