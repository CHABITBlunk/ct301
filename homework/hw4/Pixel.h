class Pixel {
public:
  inline Pixel() { red = 0, green = 0, blue = 0; }
  inline Pixel(int r, int g, int b) { red = r, green = g, blue = b; }
  inline int getR() const { return red; }
  inline int getG() const { return green; }
  inline int getB() const { return blue; }
  inline int sum() const { return red + green + blue; }

private:
  int red, green, blue;
};
