#include "Image.h"

using namespace std;

class PPMImage : public Image {
public:
  using Image::Image;
  int readImageFile() override;
  void normalize();
  int writeToFile(string fname);
};
