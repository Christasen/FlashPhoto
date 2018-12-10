/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/

#ifndef IMAGETOOLS_FILTER_THRESHOLD_H_
#define IMAGETOOLS_FILTER_THRESHOLD_H_

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

// Threshold filter can change the grayscale image to binary image.
class FilterThreshold: public Filter {
 public:
  // constructor
  FilterThreshold();

  // user defined constructor
  explicit FilterThreshold(float);

  // deconstructor
  virtual ~FilterThreshold();

  /** Subclasses must fill in this factory method to define the mask for the
   specific tool they implement. */
  // set up the filter
  void SetupFilter() override;

  // clean up the filter
  void CleanupFilter() override;

  // calculate the pixel after performing some operations and
  // following a specific algorithm
  ColorData CalculateFilteredPixel(const PixelBuffer& buffer,
                                    int x, int y) override;

 private:
  float average_value_;

  // Making the copy constructor and assignment operator private makes it
  // impossible to copy, move, or assign Tools.  This is nice because it means
  // we do not need to worry about accidentally having more than one tool
  // point to the same mask or application strategy.  Each tool owns exactly
  // one of each of these and is in charge of deleting them when it gets
  // deleted.
  FilterThreshold(const FilterThreshold &rhs) = delete;
  FilterThreshold &operator=(const FilterThreshold &rhs) = delete;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_FILTER_THRESHOLD_H_
