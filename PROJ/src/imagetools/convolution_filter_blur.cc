/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/
#include "imagetools/convolution_filter_blur.h"

#include <assert.h>
#include <algorithm>
#include <cmath>

#include "imagetools/image_tools_math.h"
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
// constructor
ConvolutionFilterBlur::ConvolutionFilterBlur() {
  radius_ = 1;
/*  kernel_ = new FloatMatrix(radius);
  for (int i = 0; i< kernel_->width(); i++){
    for (int j = 0; j < kernel_->height(); j++){
      kernel_ ->  set_value(i, j, 0.0);
    }
  }
 kernel_ -> set_value(radius, radius, 1.0); */
}

// deconstructor
ConvolutionFilterBlur::~ConvolutionFilterBlur() {}

// constructor
ConvolutionFilterBlur::ConvolutionFilterBlur(float r) {
  radius_ = static_cast<int>(r);
}

// override the create kernel function of the blur filter and implenment
// the functions by usingUse the ImageToolsMath::Gaussian() function
// to compute the value to store in each element of the Blur Kernel.
// this function computes a 2D version of the Gaussian distribution
// plotted above for a given radius.
FloatMatrix* ConvolutionFilterBlur::CreateKernel() {
  FloatMatrix* kernel = new FloatMatrix(radius_);
    for (int i =0 ; i< kernel->width(); i++) {
      for (int j = 0; j < kernel->height(); j++) {
        float xc = pow(i-radius_, 2);
        float yc = pow(j-radius_, 2);
        float value = ImageToolsMath::Gaussian(sqrt(xc+yc), radius_);
        kernel ->  set_value(i, j, value);
      }
    }
  // float product = static_cast<float>(kernel->height() * kernel->width());
  // kernel -> set_value(radius_, radius_, p);
  // It is important to normalize the kernel;
  kernel -> Normalize();
  return kernel;
}


} /* namespace image_tools */
