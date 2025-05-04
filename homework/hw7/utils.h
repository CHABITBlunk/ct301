#pragma once
#include "Image.h"
#include <string>

using namespace std;

Image *readImage(string fname);
inline bool sameSize(Image *a, Image *b) {
  return a->width == b->width && a->height == b->height;
}
float correlation(Image *image, Image *jmage);
