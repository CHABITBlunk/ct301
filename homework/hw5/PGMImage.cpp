#include "PGMImage.h"
#include <cmath>
#include <limits.h>

using namespace std;

int PGMImage::readImageFile() {
  if (!file.hasValidHeader()) {
    cerr << "error: file has incorrect header" << endl;
    return -1;
  }
  width = file.readSingleValue();
  height = file.readSingleValue();
  maxValue = file.readSingleValue();
  image = new Pixel *[height];
  for (int i = 0; i < height; i++) {
    image[i] = new GrayscalePixel[width];
  }
  int r = 0, c = 0;
  while (r < height) {
    Pixel *p = file.readPixel();
    GrayscalePixel *nextPixel = dynamic_cast<GrayscalePixel *>(p);
    if (!isValidEntry(nextPixel->value)) {
      cerr << "error: entry out of bounds" << endl;
      return -1;
    }
    image[r][c] = *nextPixel;
    c++;
    if (c == width) {
      c = 0;
      r++;
    }
  }
  return 0;
}

int grayscaleMin(GrayscalePixel p, int l) {
  return (p.value < l) ? p.value : l;
}

int grayscaleMax(GrayscalePixel p, int h) {
  return (p.value > h) ? p.value : h;
}

void PGMImage::normalize() {
  int h = INT_MIN, l = INT_MAX;
  int r, c;
  for (r = 0; r < height; r++) {
    for (c = 0; c < width; c++) {
      GrayscalePixel *p = dynamic_cast<GrayscalePixel *>(&image[r][c]);
      if (!p) {
        cerr << "error: found non-GrayscalePixel" << endl;
        return;
      }
      h = grayscaleMax(*p, h);
      l = grayscaleMin(*p, l);
    }
  }
  for (r = 0; r < height; r++) {
    for (c = 0; c < width; c++) {
      GrayscalePixel *p = dynamic_cast<GrayscalePixel *>(&image[r][c]);
      if (!p) {
        cerr << "error: found non-GrayscalePixel" << endl;
        return;
      }
      p->value = std::round((p->value - l) * (255 / (h - l)));
    }
  }
  maxValue = 255;
}

int PGMImage::writeToFile(string fname) {
  ofstream out(fname);
  out << "P2" << endl;
  out << width << " " << height << " " << maxValue << endl;
  int r, c;
  for (r = 0; r < height; r++) {
    for (c = 0; c < width; c++) {
      out << image[r][c].toString() << endl;
    }
  }
  out.close();
  return 0;
}
