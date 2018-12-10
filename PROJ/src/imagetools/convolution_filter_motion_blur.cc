/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/
#include "imagetools/convolution_filter_motion_blur.h"

#include <assert.h>
#include <algorithm>
#include <cmath>

#include "imagetools/image_tools_math.h"
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
// constructor
ConvolutionFilterMotionBlur::ConvolutionFilterMotionBlur() {
  radius_ = 1;
  direction_ = MBLUR_DIR_N_S;
}
ConvolutionFilterMotionBlur::ConvolutionFilterMotionBlur(BlurDir dir) {
  radius_ = 1;
  direction_ = dir;
/*  kernel_ = new FloatMatrix(radius);
  for (int i = 0; i< kernel_->width(); i++){
    for (int j = 0; j < kernel_->height(); j++){
      kernel_ ->  set_value(i, j, 0.0);
    }
  }
 kernel_ -> set_value(radius, radius, 1.0); */
}
// deconstructor
ConvolutionFilterMotionBlur::~ConvolutionFilterMotionBlur() {}

// constructor
ConvolutionFilterMotionBlur::ConvolutionFilterMotionBlur(float r,
    BlurDir dir) {
  radius_ = static_cast<int>(r);
  direction_ = dir;
}

// Motion blur is achieved by blurring in only 1 direction.
// so first try to identify the direction we want to blur
// then set that specific group of matrixs components to
// that specific value
FloatMatrix* ConvolutionFilterMotionBlur::CreateKernel() {
  FloatMatrix* kernel = new FloatMatrix(radius_);
    for (int i =0 ; i< (kernel->width()); i++) {
      for (int j = 0; j < (kernel->height()); j++) {
        kernel ->  set_value(i, j, 0.0);
      }
    }
  // according to different location and make adjustment
  if (direction_ == MBLUR_DIR_E_W) {
    for (int i = 0; i< (kernel-> width()); i++) {
      kernel -> set_value(i, radius_, 1.0/kernel->width());
    }
  } else if (direction_ == MBLUR_DIR_N_S) {
    for (int i = 0; i< (kernel-> height()); i++) {
  kernel -> set_value(radius_, i, 1.0/kernel->width());
        // kernel -> set_value(i, radius_, 1.0/kernel->width());
      }
  } else if (direction_ == MBLUR_DIR_NE_SW) {
    for (int i = 0; i< (kernel-> height()); i++) {
      kernel -> set_value(kernel->width()-1 -i, i, 1.0/kernel->width());
    }
  } else if (direction_ == MBLUR_DIR_NW_SE) {
    for (int i = 0; i< (kernel-> height()); i++) {
      kernel -> set_value(i, i, 1.0/kernel->width());
    }
  }
  // float product = static_cast<float>(kernel->height() * kernel->width());
  // kernel -> set_value(radius_, radius_, p);
  return kernel;
}





} /* namespace image_tools */
