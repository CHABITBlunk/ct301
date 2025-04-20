#include "Image.h"
#include "utils.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "error: should have two arguments (e.g. './HW6 test.ppm output')"
         << endl;
    return -1;
  }

  string input = argv[1];
  string output = argv[2];
  Image *img = readImage(input);
  if (!img) {
    cerr << "failed to read image" << endl;
    return -1;
  }
  if (img->getType() != "P1")
    img->normalize();

  Image *converted = convertImage(img, output);
  if (!converted) {
    cerr << "conversion failed or invalid output filename extension" << endl;
    delete img;
    return -1;
  }
  converted->write(output);
  delete img;
  delete converted;
  return 0;
}
