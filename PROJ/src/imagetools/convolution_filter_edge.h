/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/

#ifndef IMAGETOOLS_CONVOLUTION_FILTER_EDGE_H_
#define IMAGETOOLS_CONVOLUTION_FILTER_EDGE_H_

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

// EdgeDect is a Subclasses of the convolution filter
// Motion blur is achieved by blurring in only 1 direction.
// so first try to identify the direction we want to blur
// then set that specific group of matrixs components to
// that specific value
class ConvolutionFilterEdge : public ConvolutionFilter {
 public:
  ConvolutionFilterEdge();

  virtual ~ConvolutionFilterEdge();

  /** Subclasses must fill in this factory method to define the mask for the
   specific tool they implement. */
  // override the CreateKernel functions by following the
  // algorithms of filter egde dectect
  FloatMatrix* CreateKernel() override;

  // Specify the name of the filter by calling this function
  static const std::string name() { return "Convolution Edge Dectect Filter"; }



 private:
  int radius_;


  // Making the copy constructor and assignment operator private makes it
  // impossible to copy, move, or assign Tools.  This is nice because it means
  // we do not need to worry about accidentally having more than one tool
  // point to the same mask or application strategy.  Each tool owns exactly
  // one of each of these and is in charge of deleting them when it gets
  // deleted.
  ConvolutionFilterEdge(const ConvolutionFilterEdge &rhs) = delete;
  ConvolutionFilterEdge &operator=(const ConvolutionFilterEdge &rhs) = delete;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_CONVOLUTION_FILTER_EDGE_H_
