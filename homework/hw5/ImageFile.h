#include "Pixel.h"
#include <fstream>
#include <iostream>

using namespace std;

class ImageFile {
public:
  inline ImageFile(string fname) {
    ppm = ifstream(fname);
    header = getHeader();
  }
  inline bool isOpen() const { return ppm.is_open(); }
  inline bool eof() const { return ppm.eof(); }
  inline bool hasValidHeader() { return header != 0; }

  int readSingleValue();
  Pixel *readPixel();

private:
  ifstream ppm;
  int header = 0;
  int getHeader();
};
