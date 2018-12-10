/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/
#include "imagetools/convolution_filter_sharpen.h"

#include <assert.h>
#include <algorithm>
#include <cmath>

#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {
// constructor
ConvolutionFilterSharpen::ConvolutionFilterSharpen() {
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
ConvolutionFilterSharpen::~ConvolutionFilterSharpen() {}

// constructor
ConvolutionFilterSharpen::ConvolutionFilterSharpen(float r) {
  radius_ = static_cast<int>(r);
}

// To sharpen the image is very similar to finding edges,add the original image
// and the image after the edge detection to each other
// and the result will be a new image where the edges r enhanced to make it look
// sharper. Adding those two images is done by taking the edge detection filter
// from the previous example, and incrementing the center value of it with 1.
// Now the sum of the filter elements is 1 and the result will be an image with
// the same brightness as the original, but sharper.

FloatMatrix* ConvolutionFilterSharpen::CreateKernel() {
  FloatMatrix* kernel = new FloatMatrix(radius_);
    for (int i =0 ; i< kernel->width(); i++) {
      for (int j = 0; j < kernel->height(); j++) {
        float xc = pow(i-radius_, 2);
        float yc = pow(j-radius_, 2);
        float value = ImageToolsMath::Gaussian(sqrt(xc+yc), radius_);
        kernel ->  set_value(i, j, value);
      }
  }
  kernel -> Normalize();
  kernel -> Scale(-1.0);
  kernel -> set_value(radius_, radius_, (kernel->value(radius_, radius_))+2.0);
  return kernel;
}
} /* namespace image_tools */
