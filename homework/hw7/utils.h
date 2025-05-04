#pragma once
#include "Image.h"
#include <string>

using namespace std;

Image *readImage(string fname);
inline bool sameSize(const Image *a, const Image *b) {
  return a->width == b->width && a->height == b->height;
}
float correlation(const Image *a, const Image *b);
