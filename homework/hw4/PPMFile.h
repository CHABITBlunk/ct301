#include "Pixel.h"
#include <fstream>
#include <iostream>

using namespace std;

class PPMFile {
public:
  inline PPMFile(string fname) { ppm = ifstream(fname); }
  inline bool isOpen() const { return ppm.is_open(); }
  inline bool eof() const { return ppm.eof(); }

  bool hasValidHeader();
  int readSingleValue();
  Pixel readPixel();

private:
  ifstream ppm;
};
