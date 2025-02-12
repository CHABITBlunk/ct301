#include <fstream>
#include <iostream>

using namespace std;

class Image {
public:
  Image(string fname);
  int readSingleValue();
  bool hasValidHeader();
  int createMatrix();

protected:
  string filename;
  ifstream infile;
  unsigned width, height, maxValue;
  int **imageMatrix;
};
