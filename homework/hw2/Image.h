#include <fstream>
#include <iostream>

using namespace std;

class Image {
public:
  Image(string ppmfname, string checksumfname);
  int readSingleValue();
  bool hasValidHeader();
  bool isValidEntry(size_t i);
  int readFile();
  int compareAgainstChecksum();

protected:
  string ppmfilename, checksumfilename;
  ifstream ppm, checksum;
  size_t width, height, maxValue;
  int **image;
  int *rowTotals;
};
