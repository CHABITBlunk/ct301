#include <cstdio>
#include <string>
using namespace std;

class Pixel {
public:
  virtual ~Pixel() {}
  virtual string toString() const = 0;
};

class RGBPixel : public Pixel {
public:
  inline RGBPixel() : r(0), g(0), b(0) {}
  inline RGBPixel(int red, int green, int blue) : r(red), g(green), b(blue) {}
  inline string toString() const override {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%d %d %d", r, g, b);
    return buffer;
  }
  int r, g, b;
  inline int sum() const { return r + g + b; }
};

class GrayscalePixel : public Pixel {
public:
  inline GrayscalePixel() : value(0) {}
  inline GrayscalePixel(int v) : value(v) {}
  inline string toString() const override {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%d", value);
    return buffer;
  }
  int value;
};

class BinaryPixel : public Pixel {
public:
  inline BinaryPixel() { value = 0; }
  inline BinaryPixel(int v) { value = v; }
  inline string toString() const override {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%d", value);
    return buffer;
  }
  int value;
};
