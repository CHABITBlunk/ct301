#include "PBMImage.h"

using namespace std;

int PBMImage::readImageFile() {
  if (!file.hasValidHeader()) {
    cerr << "error: file has incorrect header" << endl;
    return -1;
  }
  width = file.readSingleValue();
  height = file.readSingleValue();
  file.readSingleValue();
  maxValue = 1;
  image = new Pixel *[height];
  for (int i = 0; i < height; i++) {
    image[i] = new BinaryPixel[width];
  }
  int r = 0, c = 0;
  while (r < height) {
    Pixel *p = file.readPixel();
    BinaryPixel *nextPixel = dynamic_cast<BinaryPixel *>(p);
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

int PBMImage::writeToFile(string fname) {
  ofstream out(fname);
  out << "P1" << endl;
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
