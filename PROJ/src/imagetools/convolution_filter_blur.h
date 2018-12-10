/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/


#ifndef IMAGETOOLS_CONVOLUTION_FILTER_BLUR_H_
#define IMAGETOOLS_CONVOLUTION_FILTER_BLUR_H_

#include <string>
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/filter.h"
#include "imagetools/convolution_filter.h"

namespace image_tools {

/** The base class for an image editing tool.  Every tool "has a" mask.
 Subclasses must define this mask by filling in the CreateMask factory method.
 This base class will then be able to apply the mask to a pixel buffer as the
 tool is dragged around interactively. */

// Blur is a subclasses of convolution filter
// It takes the average of the current pixel and its neighbors.
// Take the sum of the current pixel and its neighbors, and
// divide it through number of neighbors plus one.
class ConvolutionFilterBlur: public ConvolutionFilter {
 public:
  // constructors
  ConvolutionFilterBlur();

  explicit ConvolutionFilterBlur(float);

  virtual ~ConvolutionFilterBlur();

  /** Subclasses must fill in this factory method to define the mask for the
   specific tool they implement. */
  // override the CreateKernel functions by following the
  // algorithms of filter blur
  FloatMatrix* CreateKernel() override;

  // Specify the name of the filter by calling this function
  static const std::string name() { return "Convolution Blur Filter"; }

 private:
  int radius_;

  // Making the copy constructor and assignment operator private makes it
  // impossible to copy, move, or assign Tools.  This is nice because it means
  // we do not need to worry about accidentally having more than one tool
  // point to the same mask or application strategy.  Each tool owns exactly
  // one of each of these and is in charge of deleting them when it gets
  // deleted.
  ConvolutionFilterBlur(const ConvolutionFilterBlur &rhs) = delete;
  ConvolutionFilterBlur &operator=(const ConvolutionFilterBlur &rhs) = delete;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_CONVOLUTION_FILTER_BLUR_H_
