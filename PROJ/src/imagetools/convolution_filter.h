/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/

#ifndef IMAGETOOLS_CONVOLUTION_FILTER_H_
#define IMAGETOOLS_CONVOLUTION_FILTER_H_

#include <string>
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/filter.h"

namespace image_tools {

/** The base class for an image editing tool.  Every tool "has a" mask.
 Subclasses must define this mask by filling in the CreateMask factory method.
 This base class will then be able to apply the mask to a pixel buffer as the
 tool is dragged around interactively. */
class ConvolutionFilter : public Filter {
 public:
  // constructor
  ConvolutionFilter();

  // user defined constructor
  explicit ConvolutionFilter(float);

  // deconstructor
  virtual ~ConvolutionFilter();

  /** Subclasses must fill in this factory method to define the mask for the
   specific tool they implement. */
  // set up the filter for convolution filters
  void SetupFilter() override;

  // Clean up the filter for convolution filters
  void CleanupFilter() override;

  // A boolean value would be determined by calling this function
  // If it is false, then it'll be convolution filters
  // If it is true, then it'll be the normal filters
  bool can_calculate_in_place() override;

  // A general method to create the specific kernel for each
  // specific convolution filter
  virtual FloatMatrix* CreateKernel() = 0;

  // Calculate the new pixel by giving a different kernel
  ColorData CalculateFilteredPixel(const PixelBuffer& buffer, int x,
     int y) override;

 private:
  int radius_;
  FloatMatrix* kernel_;

  // Making the copy constructor and assignment operator private makes it
  // impossible to copy, move, or assign Tools.  This is nice because it means
  // we do not need to worry about accidentally having more than one tool
  // point to the same mask or application strategy.  Each tool owns exactly
  // one of each of these and is in charge of deleting them when it gets
  // deleted.
  ConvolutionFilter(const ConvolutionFilter &rhs) = delete;
  ConvolutionFilter &operator=(const ConvolutionFilter &rhs) = delete;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_CONVOLUTION_FILTER_H_
