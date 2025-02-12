#include "Image.cpp"
#include <iostream>
#include <ostream>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Error: should have one argument (e.g. './HW2 test.ppm')" << endl;
    return -1;
  }
  Image image(argv[1]);
  if (!image.hasValidHeader()) {
    cerr << "Error: ppm file not formatted correctly" << endl;
  }
  image.createMatrix();
  return 0;
}
