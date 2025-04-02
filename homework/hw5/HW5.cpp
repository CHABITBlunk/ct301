#include "Image.h"
#include <iostream>
#include <ostream>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "error: should have two arguments (e.g. './HW5 test.ppm output')"
         << endl;
    return -1;
  }
  Image image(argv[1]);
  int readResult = image.readImageFile();
  if (readResult != 0) {
    return readResult;
  }
  image.normalize();
  return image.writeToFile(argv[2]);
}
