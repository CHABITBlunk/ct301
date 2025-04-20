#include "Image.h"
#include "utils.h"
#include <cstdio>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "error: should have two arguments (e.g. './HW6 a.pgm b.pgm')"
         << endl;
    return -1;
  }
  string aPGM = argv[1];
  string bPGM = argv[2];
  Image *a = readImage(aPGM);
  Image *b = readImage(bPGM);
  if (!a || !b) {
    cerr << "failed to read an image" << endl;
    return -1;
  }
  a->normalize();
  b->normalize();
  if (!sameSize(a, b)) {
    delete a;
    delete b;
    cerr << "pgm files not same size" << endl;
    return -1;
  }
  printf("%f\n", correlation(a, b));
  delete a;
  delete b;
  return 0;
}
