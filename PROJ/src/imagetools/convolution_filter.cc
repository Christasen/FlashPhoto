/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/

#include "imagetools/convolution_filter.h"

#include <assert.h>
#include <algorithm>
#include <cmath>

#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/float_matrix.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {

// constructor
// initiallly, set all the values in the kernel to 0
// And set the kernel center's value to 1.0
ConvolutionFilter::ConvolutionFilter() {
  radius_ = 1;
  kernel_ = new FloatMatrix(radius_);
  for (int i = 0; i< kernel_->width(); i++) {
    for (int j = 0; j < kernel_->height(); j++) {
      kernel_ ->  set_value(i, j, 0.0);
    }
  }
  kernel_ -> set_value(radius_, radius_, 1.0);
}

ConvolutionFilter::~ConvolutionFilter() {
  delete kernel_;
  kernel_ = NULL;
}

// Another constructor
// initiallly, set all the values in the kernel to 0 by the user input radius
// And set the kernel center's value to 1.0
// Although the radius is a user input value
// the image will still be the same
ConvolutionFilter::ConvolutionFilter(float r) {
  radius_ = static_cast<int>(r);
  kernel_ = new FloatMatrix(radius_);
  for (int i = 0; i< kernel_->width(); i++) {
    for (int j = 0; j < kernel_->height(); j++) {
      kernel_ ->  set_value(i, j, 0.0);
    }
  }
  kernel_ -> set_value(radius_, radius_, 1.0);
}

// setting up the filter first
void ConvolutionFilter::SetupFilter() {
  kernel_ = CreateKernel();
  radius_ = (kernel_->width()-1)/2;
}


// cleaning up the kernel;
void ConvolutionFilter::CleanupFilter() {
  delete kernel_;
  kernel_ = NULL;
  radius_ = 0;
}

// The calculate funtion here
ColorData ConvolutionFilter::CalculateFilteredPixel(const PixelBuffer& buffer,
  int x, int y) {
//    ColorData d1 = buffer.pixel(x, y);
    double red = 0.0, green = 0.0, blue = 0.0, a = 1.0;
    int buffer_h = buffer.height();
    int buffer_w = buffer.width();
    int matrix_h = kernel_ -> height();
    int matrix_w = kernel_ -> width();
    // multiply every value of the filter with corresponding image pixel
    for (int x1 = 0; x1 < matrix_h; x1++)
    for (int y1 = 0; y1 < matrix_w; y1++) {
      int imageX = (x - matrix_w / 2 + y1 + buffer_w) % buffer_w;
      int imageY = (y - matrix_h / 2 + x1 + buffer_h) % buffer_h;
      red += buffer.pixel(imageX, imageY).red() * kernel_->value(y1, x1);
      green += buffer.pixel(imageX, imageY).green() * kernel_->value(y1, x1);
      blue += buffer.pixel(imageX, imageY).blue() * kernel_->value(y1, x1);
      a += buffer.pixel(imageX, imageY).alpha() * kernel_->value(y1, x1);
    }
    ColorData d2 = ColorData(red, green, blue, a);
    // clamp the color data and set this to [0.0, 1.0]
    d2.Clamp();
    return d2;
    // return ColorData(d1.red()*red_, d1.green()*green_, d1.blue()*blue_, a);
  }

  bool ConvolutionFilter::can_calculate_in_place() {
    return false;
  }

} /* namespace image_tools */
