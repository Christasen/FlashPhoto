/**
This file is part of the CSCI-3081W Project Support Code, which was developed
at the University of Minnesota.

This code is to be used for student coursework.  It is not an open source
project.
Copyright (c) 2015-2018 Daniel Keefe, TAs, & Regents of the University of
Minnesota.

Original Author(s) of this File:
  Seth Johnson, 2/15/15, University of Minnesota

Author(s) of Significant Updates/Modifications to the File:
  Guangyu Yan, 10/11/18, University of Minnesota
*/

#include "imagetools/pixel_buffer.h"
#include <mingfx.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include "imagetools/color_data.h"
#include "imageio/image_manager.h"
#include "imagetools/image_editor.h"
using std::cerr;
using std::endl;
namespace image_tools {

PixelBuffer::PixelBuffer(int w, int h, ColorData background_color)
    : width_(w), height_(h), background_color_(background_color) {
  for (int r = 0; r < h; r++) {
    for (int c = 0; c < w; c++) {
      pixels_.push_back(background_color.red());
      pixels_.push_back(background_color.green());
      pixels_.push_back(background_color.blue());
      pixels_.push_back(background_color.alpha());
    }
  }
}

PixelBuffer::PixelBuffer(const std::string &filename)
  : width_(0), height_(0),
  background_color_(ColorData(1, 1, 1)) {
  LoadFromFile(filename);
}

PixelBuffer::PixelBuffer(const PixelBuffer &rhs)
    : PixelBuffer(rhs.width_, rhs.height_, rhs.background_color_) {
  std::copy(rhs.pixels_.begin(), rhs.pixels_.end(), pixels_.begin());
}

PixelBuffer::~PixelBuffer() {}

ColorData PixelBuffer::pixel(int x, int y) const {
  ColorData pixel_data;

  if ((x < 0) || (x >= width_) || (y < 0) || (y >= height_)) {
    cerr << "pixel(x,y): out of range: " << x << " " << y << endl;
  } else {
    int index = 4 * (x + width_ * y);
    pixel_data = ColorData(pixels_[index + 0], pixels_[index + 1],
                           pixels_[index + 2], pixels_[index + 3]);
  }
  return pixel_data;
}

void PixelBuffer::set_pixel(int x, int y, const ColorData &new_pixel) {
  if ((x < 0) || (x >= width_) || (y < 0) || (y >= height_)) {
    cerr << "setPixel: x,y out of range: " << x << " " << y << endl;
  } else {
    int index = 4 * (x + width_ * y);  // x + width*(height-(y+1));
    pixels_[index + 0] = new_pixel.red();
    pixels_[index + 1] = new_pixel.green();
    pixels_[index + 2] = new_pixel.blue();
    pixels_[index + 3] = new_pixel.alpha();
  }
}

PixelBuffer &PixelBuffer::operator=(const PixelBuffer &rhs) {
  /* Check for self-assignment! */
  if (this == &rhs) {
    return *this;
  }
  this->width_ = rhs.width_;
  this->height_ = rhs.height_;
  this->pixels_ = rhs.pixels_;
  this->background_color_ = rhs.background_color_;

  return *this;
} /* operator=() */

void PixelBuffer::Resize(int new_width, int new_height) {
  PixelBuffer tmp(new_width, new_height, background_color_);
  for (int y = 0; y < new_height; y++) {
    for (int x = 0; x < new_width; x++) {
      if ((x < width_) && (y < height_)) {
        tmp.set_pixel(x, y, pixel(x, y));
      } else {
        tmp.set_pixel(x, y, background_color_);
      }
    }
  }
  *this = tmp;
}

void PixelBuffer::SaveToFile(const std::string &filename) {
  imageio::Image* newphoto = new imageio::Image(width_, height_, 4);
  for (int x = 0; x < height_; x++) {
    for (int y = 0; y < width_; y++) {
      newphoto -> SetFloatValue(y, x, 0, pixel(y, x).red());
      newphoto -> SetFloatValue(y, x, 1, pixel(y, x).green());
      newphoto -> SetFloatValue(y, x, 2, pixel(y, x).blue());
      newphoto -> SetFloatValue(y, x, 3, pixel(y, x).alpha());
    }
  }
  imageio::ImageManager::instance().SaveToFile(filename, *newphoto);
  delete newphoto;
  newphoto = NULL;
}
// loading from file function
void PixelBuffer::LoadFromFile(const std::string &filename) {
  imageio::Image* newphoto =
  imageio::ImageManager::instance().LoadFromFile(filename);
  if (mingfx::Platform::FileExists(filename)) {
    if (newphoto -> Pixels() != NULL) {
      Resize(newphoto -> Width(), newphoto -> Height());
      for (int x = 0; x < newphoto -> Height(); x++) {
        for (int y = 0; y < newphoto -> Width(); y++) {
          int new_idx = 4 *(width_*x + y);
          // std::cout << new_idx;
          pixels_[new_idx + 0] = newphoto -> FloatValue(y, x, 0);
          pixels_[new_idx + 1] = newphoto -> FloatValue(y, x, 1);
          pixels_[new_idx + 2] = newphoto -> FloatValue(y, x, 2);
          pixels_[new_idx + 3] = newphoto -> FloatValue(y, x, 3);
        }
      }} else {
      cerr << "The Pixel Buffer does not exist" << filename << std::endl;
    }} else {
    cerr << "file does not exist" << std::endl;
    }
}
bool operator==(const PixelBuffer &a, const PixelBuffer &b) {
  if ((a.width() != b.width()) || (a.height() != b.height())) {
    return false;
  } else {
    // check the actual pixels
    for (int y = 0; y < a.height(); y++) {
      for (int x = 0; x < a.width(); x++) {
        if (a.pixel(x, y) != b.pixel(x, y)) {
          return false;
        }
      }
    }
    return true;
  }
}

bool operator!=(const PixelBuffer &a, const PixelBuffer &b) {
  return !(a == b);
}

} /* namespace image_tools */
