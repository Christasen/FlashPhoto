/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/

#ifndef IMAGETOOLS_CONVOLUTION_FILTER_SHARPEN_H_
#define IMAGETOOLS_CONVOLUTION_FILTER_SHARPEN_H_

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

// The Sharpen filter is an Subclasses of the convolution filter
// To sharpen the image is very similar to finding edges,add the original image
// and the image after the edge detection to each other
// and the result will be a new image where the edges r enhanced to make it look
// sharper. Adding those two images is done by taking the edge detection filter
// from the previous example, and incrementing the center value of it with 1.
// Now the sum of the filter elements is 1 and the result will be an image with
// the same brightness as the original, but sharper.
class ConvolutionFilterSharpen : public ConvolutionFilter {
 public:
  ConvolutionFilterSharpen();
  explicit ConvolutionFilterSharpen(float);
  virtual ~ConvolutionFilterSharpen();

  /** Subclasses must fill in this factory method to define the mask for the
   specific tool they implement. */
  // override the CreateKernel functions by following the
  // algorithms of filter motion blur
  FloatMatrix* CreateKernel() override;

  // Specify the name of the filter by calling this function
  static const std::string name() { return "Convolution Sharpen Filter"; }



 private:
  int radius_;


  // Making the copy constructor and assignment operator private makes it
  // impossible to copy, move, or assign Tools.  This is nice because it means
  // we do not need to worry about accidentally having more than one tool
  // point to the same mask or application strategy.  Each tool owns exactly
  // one of each of these and is in charge of deleting them when it gets
  // deleted.
  ConvolutionFilterSharpen(const ConvolutionFilterSharpen &rhs) = delete;
  ConvolutionFilterSharpen &operator=(const ConvolutionFilterSharpen
      &rhs) = delete;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_CONVOLUTION_FILTER_SHARPEN_H_
