#include "Image.h"

using namespace std;

class PBMImage : public Image {
public:
  using Image::Image;
  int readImageFile() override;
  int writeToFile(string fname);
};
