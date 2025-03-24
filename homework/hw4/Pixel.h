class Pixel {

public:
  inline Pixel() { r = 0, g = 0, b = 0; }
  inline Pixel(int red, int green, int blue) { r = red, g = green, b = blue; }
  int r, g, b;
  inline int sum() const { return r + g + b; }
};
