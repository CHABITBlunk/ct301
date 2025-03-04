#include <fstream>
#include <iostream>

using namespace std;

class Pixel {
public:
  Pixel();
  Pixel(int r, int g, int b);
  int getSum();

protected:
  int red, green, blue;
};
