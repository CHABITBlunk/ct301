#include "utils.h"
#include "Image.h"
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

Image *readImage(string fname) {
  ifstream in(fname);

  if (!in) {
    cerr << "failed to open input file" << endl;
    return nullptr;
  }

  string header;
  in >> header;

  int width, height, maxVal;
  in >> width >> height >> maxVal;

  if (width <= 0 || height <= 0 || maxVal <= 0 || header == "P2") {
    auto *img = new Image();
    img->width = width;
    img->height = height;
    img->maxValue = maxVal;
    int size = width * height;
    img->data.resize(size);
    for (int i = 0; i < size; i++)
      in >> img->data[i];
    return img;
  } else {
    return nullptr;
  }
}

float correlation(Image *a, Image *b) {
  float aMean = a->mean();
  float bMean = b->mean();
  float num = 0.0f, denomA = 0.0f, denomB = 0.0f;
  for (int i = 0; i < a->width * a->height; i++) {
    float da = a->data[i] - aMean;
    float db = b->data[i] - bMean;
    num += da * db;
    denomA += da * da;
    denomB += db * db;
  }
  float denom = sqrt(denomA * denomB);
  float output = num / denom;
  return output;
}
