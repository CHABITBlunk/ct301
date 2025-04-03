#include "Image.h"

using namespace std;

class PGMImage : public Image {
public:
  using Image::Image;
  int readImageFile() override;
  void normalize();
  int writeToFile(string fname);
};
