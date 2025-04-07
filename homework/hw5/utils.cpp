#include "utils.h"
#include "Image.h"
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

Image *readImage(string fname) {
  ifstream in(fname);

  if (!in) {
    cerr << "failed to open input file" << endl;
    return nullptr;
  }

  string header;
  in >> header;

  int width, height, maxVal;
  in >> width >> height >> maxVal;

  if (width <= 0 || height <= 0 || maxVal <= 0)
    return nullptr;
  if (header == "P3") {
    auto *img = new PPMImage();
    img->width = width;
    img->height = height;
    img->maxValue = maxVal;
    int size = width * height * 3;
    img->data.resize(size);
    for (int i = 0; i < size; i++) {
      in >> img->data[i];
    }
    return img;
  } else if (header == "P2") {
    auto *img = new PGMImage();
    img->width = width;
    img->height = height;
    img->maxValue = maxVal;
    int size = width * height;
    img->data.resize(size);
    for (int i = 0; i < size; i++)
      in >> img->data[i];
    return img;
  } else if (header == "P1") {
    auto *img = new PBMImage();
    img->width = width;
    img->height = height;
    img->maxValue = maxVal;
    img->data.resize(width * height);
    int size = width * height;
    for (int i = 0; i < size; i++)
      in >> img->data[i];
    for (int val : img->data)
      if (val != 0 && val != 1)
        return nullptr;
    return img;
  } else {
    return nullptr;
  }
}

Image *convertImage(Image *src, string ext) {
  if (hasExtension(ext, ".ppm")) {
    auto *img = new PPMImage();
    img->width = src->width;
    img->height = src->height;
    img->maxValue = 255;
    img->data.resize(img->width * img->height * 3);

    if (src->getType() == "P3") {
      auto *p = static_cast<PPMImage *>(src);
      for (int i = 0; i < img->width * img->height * 3; i++) {
        img->data[i] = p->data[i];
      }
    } else if (src->getType() == "P2") {
      auto *g = static_cast<PGMImage *>(src);
      for (int i = 0; i < g->height * g->width; i++) {
        img->data[i * 3 + 0] = g->data[i];
        img->data[i * 3 + 1] = g->data[i];
        img->data[i * 3 + 2] = g->data[i];
      }
    } else if (src->getType() == "P1") {
      auto *b = static_cast<PBMImage *>(src);
      for (int i = 0; i < b->height * b->width; i++) {
        img->data[i * 3 + 0] = b->data[i] * 255;
        img->data[i * 3 + 1] = b->data[i] * 255;
        img->data[i * 3 + 2] = b->data[i] * 255;
      }
    }
    return img;
  } else if (hasExtension(ext, ".pgm")) {
    auto *img = new PGMImage();
    img->width = src->width;
    img->height = src->height;
    img->maxValue = 255;
    img->data.resize(img->width * img->height);

    if (src->getType() == "P3") {
      auto *p = static_cast<PPMImage *>(src);
      for (int i = 0; i < p->height * p->width; i++) {
        int r = p->data[i * 3 + 0];
        int g = p->data[i * 3 + 1];
        int b = p->data[i * 3 + 2];
        img->data[i] = round((r + g + b) / 3);
      }
    } else if (src->getType() == "P2") {
      auto *g = static_cast<PGMImage *>(src);
      for (int i = 0; i < img->width * img->height; i++) {
        img->data[i] = g->data[i];
      }
    } else if (src->getType() == "P1") {
      auto *b = static_cast<PBMImage *>(src);
      for (int i = 0; i < b->width * b->height; i++) {
        img->data[i] = b->data[i] * 255;
      }
    }
    return img;
  } else if (hasExtension(ext, ".pbm")) {
    auto *img = new PBMImage();
    img->width = src->width;
    img->height = src->height;
    img->maxValue = 1;
    img->data.resize(img->width * img->height);

    if (src->getType() == "P3") {
      auto *p = static_cast<PPMImage *>(src);
      for (int i = 0; i < p->height * p->width; i++) {
        int r = p->data[i * 3 + 0];
        int g = p->data[i * 3 + 1];
        int b = p->data[i * 3 + 2];
        img->data[i] = ((r + g + b) > 382.5) ? 1 : 0;
      }
    } else if (src->getType() == "P2") {
      auto *g = static_cast<PGMImage *>(src);
      for (int i = 0; i < g->height * g->width; i++) {
        img->data[i] = g->data[i] > 127.5 ? 1 : 0;
      }
    } else if (src->getType() == "P1") {

      auto *b = static_cast<PBMImage *>(src);
      for (int i = 0; i < img->width * img->height; i++) {
        img->data[i] = b->data[i];
      }
    }
    return img;
  } else {
    return nullptr;
  }
}
