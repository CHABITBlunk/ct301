#include <fstream>
#include <iostream>

using namespace std;

class Pixel {
public:
  Pixel();
  Pixel(int r, int g, int b);
  int getSum();

protected:
  int red, green, blue;
};

class Image {
public:
  Image(string ppmfname);
  Image(string ppmfname, string checksumfname);
  int readSingleValue();
  bool hasValidHeader();
  bool isValidEntry(int i);
  int readImageFile();
  int compareAgainstChecksum();
  int writeToChecksumFiles(string rowfname, string colfname);

protected:
  string ppmfilename, checksumfilename;
  ifstream ppm, checksum;
  ofstream out;
  int width, height, maxValue;
  Pixel **image;
  int *rowTotals;
  int *colTotals;
};
