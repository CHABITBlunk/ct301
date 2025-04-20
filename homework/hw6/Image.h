#pragma once
#include <string>
#include <vector>

using namespace std;

class Image {
public:
  vector<int> data;
  int width, height, maxValue;
  virtual ~Image() = default;

  virtual void normalize() = 0;
  virtual void write(string fname) = 0;
  virtual string getType() = 0;
};

class PPMImage : public Image {
public:
  void normalize() override;
  void write(string fname) override;
  inline string getType() override { return "P3"; }
};

class PGMImage : public Image {
public:
  void normalize() override;
  void write(string fname) override;
  inline string getType() override { return "P2"; }
};

class PBMImage : public Image {
public:
  void normalize() override {}
  void write(string fname) override;
  inline string getType() override { return "P1"; }
};
