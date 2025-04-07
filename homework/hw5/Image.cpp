#include "Image.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits.h>

using namespace std;

void PPMImage::normalize() {
  int h = INT_MIN, l = INT_MAX;
  for (int val : data) {
    if (val < l)
      l = val;
    if (val > h)
      h = val;
  }
  for (size_t i = 0; i < data.size(); i++) {
    data[i] = std::round((data[i] - l) * (255 / (h - l)));
  }
  maxValue = 255;
}

void PGMImage::normalize() {
  int max = INT_MIN, min = INT_MAX;
  for (int val : data) {
    if (val < min)
      min = val;
    if (val > max)
      max = val;
  }
  for (size_t i = 0; i < data.size(); i++)
    data[i] = std::round((data[i] - min) * (255 / (max - min)));
  maxValue = 255;
}

void PPMImage::write(string fname) {
  ofstream out(fname);
  out << "P3" << endl;
  out << width << " " << height << " " << maxValue << endl;
  for (size_t i = 0; i < data.size(); i++) {
    out << data[i] << (i % 3 == 2 ? "\n" : " ");
  }
}

void PGMImage::write(string fname) {
  ofstream out(fname);
  out << "P2" << endl;
  out << width << " " << height << " " << maxValue << endl;
  for (size_t i = 0; i < data.size(); i++) {
    out << data[i] << ((i + 1) % width == 0 ? "\n" : " ");
  }
}

void PBMImage::write(string fname) {
  ofstream out(fname);
  out << "P1" << endl;
  out << width << " " << height << " " << 1 << endl;
  for (size_t i = 0; i < data.size(); i++) {
    out << data[i] << ((i + 1) % width == 0 ? "\n" : " ");
  }
}
