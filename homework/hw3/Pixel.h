#include <fstream>
#include <iostream>

using namespace std;

class Pixel {
public:
  Pixel(int r, int g, int b);

protected:
  int red, green, blue;
};
