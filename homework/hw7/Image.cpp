#include "Image.h"

using namespace std;

float Image::mean() {
  float output = 0.0f;
  int i = 0;
  int n = width * height;
  for (; i < n; i++) {
    output += this->data[i];
  }
  output /= static_cast<float>(i);
  return output;
}

void Image::normalize() {
  float max = data[0], min = data[0];
  for (float val : data) {
    if (val < min)
      min = val;
    if (val > max)
      max = val;
  }
  float range = max - min;
  if (range == 0.0f)
    return;
  for (float &val : data)
    val = (val - min) * (255.0f / range);
  maxValue = 255.0f;
}
