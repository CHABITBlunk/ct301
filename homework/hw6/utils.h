#pragma once
#include "Image.h"
#include <string>

using namespace std;

inline bool hasExtension(string fname, string ext) {
  return fname.size() >= ext.size() &&
         fname.substr(fname.size() - ext.size()) == ext;
}
Image *readImage(string fname);
Image *convertImage(Image *src, string ext);
