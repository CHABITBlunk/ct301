#include "PPMImage.h"
#include <cmath>
#include <limits.h>

using namespace std;

int PPMImage::readImageFile() {
  if (!file.hasValidHeader()) {
    cerr << "error: file has incorrect header" << endl;
    return -1;
  }
  width = file.readSingleValue();
  height = file.readSingleValue();
  maxValue = file.readSingleValue();
  image = new Pixel *[height];
  for (int i = 0; i < height; i++) {
    image[i] = new RGBPixel[width];
  }
  int r = 0, c = 0;
  while (r < height) {
    Pixel *p = file.readPixel();
    RGBPixel *nextPixel = dynamic_cast<RGBPixel *>(p);
    if (!isValidEntry(nextPixel->r) || !isValidEntry(nextPixel->g) ||
        !isValidEntry(nextPixel->b)) {
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

int rgbMin(RGBPixel p, int l) {
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

int rgbMax(RGBPixel p, int h) {
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

void PPMImage::normalize() {
  int h = INT_MIN, l = INT_MAX;
  int r, c;
  for (r = 0; r < height; r++) {
    for (c = 0; c < width; c++) {
      RGBPixel *p = dynamic_cast<RGBPixel *>(&image[r][c]);
      if (!p) {
        cerr << "error: found non-RGBPixel" << endl;
        return;
      }
      h = rgbMax(*p, h);
      l = rgbMin(*p, l);
    }
  }
  for (r = 0; r < height; r++) {
    for (c = 0; c < width; c++) {
      RGBPixel *p = dynamic_cast<RGBPixel *>(&image[r][c]);
      if (!p) {
        cerr << "error: found non-RGBPixel" << endl;
        return;
      }
      p->r = std::round((p->r - l) * (255 / (h - l)));
      p->g = std::round((p->g - l) * (255 / (h - l)));
      p->b = std::round((p->b - l) * (255 / (h - l)));
    }
  }
  maxValue = 255;
}

int PPMImage::writeToFile(string fname) {
  ofstream out(fname);
  out << "P3" << endl;
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
