#pragma once
#include <string>
#include <vector>

using namespace std;

class Image {
public:
  vector<float> data;
  int width, height;
  float maxValue;
  virtual ~Image() = default;

  float mean();
  void normalize();
};
