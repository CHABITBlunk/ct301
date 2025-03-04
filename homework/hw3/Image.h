#include "Pixel.h"
#include <fstream>
#include <iostream>

using namespace std;

class Image {
public:
  Image(string ppmfname, string checksumfname);
  int readSingleValue();
  Pixel readPixelValue();
  bool hasValidHeader();
  bool isValidEntry(int i);
  int readImageFile();
  int compareAgainstChecksum();

protected:
  string ppmfilename, checksumfilename;
  ifstream ppm, checksum;
  int width, height, maxValue;
  Pixel **image;
  int *rowTotals;
};
