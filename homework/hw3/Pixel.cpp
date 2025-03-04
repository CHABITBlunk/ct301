#include "Pixel.h"

using namespace std;

Pixel::Pixel() {
  this->red = -1;
  this->green = -1;
  this->blue = -1;
}

Pixel::Pixel(int r, int g, int b) {
  this->red = r;
  this->green = g;
  this->blue = b;
}

int Pixel::getSum() { return red + green + blue; }
