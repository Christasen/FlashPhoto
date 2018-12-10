/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/

#ifndef IMAGETOOLS_CONVOLUTION_FILTER_MOTION_BLUR_H_
#define IMAGETOOLS_CONVOLUTION_FILTER_MOTION_BLUR_H_

#include <string>
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/convolution_filter.h"

namespace image_tools {

/** The base class for an image editing tool.  Every tool "has a" mask.
 Subclasses must define this mask by filling in the CreateMask factory method.
 This base class will then be able to apply the mask to a pixel buffer as the
 tool is dragged around interactively. */

// Motion Blur filter is a Subclasses of the convolution filter
// Motion blur is achieved by blurring in only 1 direction.
// so first try to identify the direction we want to blur
// then set that specific group of matrixs components to
// that specific value
class ConvolutionFilterMotionBlur: public ConvolutionFilter {
 public:
  // Four possible motion blur directions are supported
  enum BlurDir {
    MBLUR_DIR_N_S,
    MBLUR_DIR_E_W,
    MBLUR_DIR_NE_SW,
    MBLUR_DIR_NW_SE
  };
  ConvolutionFilterMotionBlur();
  explicit ConvolutionFilterMotionBlur(BlurDir);
  ConvolutionFilterMotionBlur(float, BlurDir);
  virtual ~ConvolutionFilterMotionBlur();

  /** Subclasses must fill in this factory method to define the mask for the
   specific tool they implement. */
  // override the CreateKernel functions by following the
  // algorithms of filter motion blur
  FloatMatrix* CreateKernel() override;

  // Specify the name of the filter by calling this function
  static const std::string name() { return "Convolution Motion Blur Filter"; }



 private:
  int radius_;
  BlurDir direction_;
  // Making the copy constructor and assignment operator private makes it
  // impossible to copy, move, or assign Tools.  This is nice because it means
  // we do not need to worry about accidentally having more than one tool
  // point to the same mask or application strategy.  Each tool owns exactly
  // one of each of these and is in charge of deleting them when it gets
  // deleted.
  ConvolutionFilterMotionBlur(const ConvolutionFilterMotionBlur &rhs) = delete;
  ConvolutionFilterMotionBlur &operator=(const ConvolutionFilterMotionBlur
    &rhs) = delete;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_CONVOLUTION_FILTER_MOTION_BLUR_H_
