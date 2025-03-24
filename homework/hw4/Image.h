#include "PPMFile.h"
#include <fstream>
#include <iostream>

using namespace std;

class Image {
public:
  inline Image(string fname) : file(fname) {}
  inline bool isValidEntry(int i) const { return i <= maxValue && i >= 0; };
  inline int size() const { return width * height; }

  int readImageFile();
  void normalize();

protected:
  PPMFile file;
  int width, height, maxValue;
  Pixel **image;
};
