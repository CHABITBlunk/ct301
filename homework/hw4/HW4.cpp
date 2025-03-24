#include "Image.cpp"
#include <iostream>
#include <ostream>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 4) {
    cerr << "error: should have three arguments (e.g. './HW2 test.ppm "
            "horiz.checksum vert.checksum')"
         << endl;
    return -1;
  }
  Image image(argv[1]);
  int readResult = image.readImageFile();
  if (readResult != 0) {
    return readResult;
  }
  image.normalize();
  return 0;
}
