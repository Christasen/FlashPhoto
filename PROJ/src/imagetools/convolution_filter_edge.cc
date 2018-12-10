/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/
#include "imagetools/convolution_filter_edge.h"

#include <assert.h>
#include <algorithm>
#include <cmath>

#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
// constructor
ConvolutionFilterEdge::ConvolutionFilterEdge() {
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
ConvolutionFilterEdge::~ConvolutionFilterEdge() {}

// To find the edge, the most easy way to implement the
// CreateKernel function is that first, set the initial float_matrix
// to -1.0 and then change the middle point to 8.0
FloatMatrix* ConvolutionFilterEdge::CreateKernel() {
  FloatMatrix* kernel = new FloatMatrix(radius_);
  // set every pixel to a specific value -1.0
    for (int i = 0; i< kernel->width(); i++) {
      for (int j = 0; j < kernel->height(); j++) {
        kernel -> set_value(i, j, -1.0);
      }
    }
  // int num =  kernel->height() * kernel->width();
  kernel-> set_value(radius_, radius_, 8.0);
  return kernel;
}





} /* namespace image_tools */
