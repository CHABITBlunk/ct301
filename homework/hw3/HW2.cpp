#include "Image.cpp"
#include <iostream>
#include <ostream>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "error: should have two arguments (e.g. './HW2 test.ppm "
            "test.checksum')"
         << endl;
    return -1;
  }
  Image image(argv[1], argv[2]);
  return image.compareAgainstChecksum();
}
