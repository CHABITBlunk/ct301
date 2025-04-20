#include "Image.h"
#include <cfloat>

using namespace std;

float Image::mean() {
  float output = 0.0f;
  size_t i = 0;
  for (; i < this->data.size(); i++) {
    output += this->data[i];
  }
  output /= (i * 1.0);
  return output;
}

void Image::normalize() {
  float max = FLT_MIN, min = FLT_MAX;
  for (float val : data) {
    if (val < min)
      min = val;
    if (val > max)
      max = val;
  }
  for (size_t i = 0; i < data.size(); i++)
    data[i] = (data[i] - min) * (255.0f / (max - min));
  maxValue = 255.0f;
}
