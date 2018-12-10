/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/
#ifndef IMAGETOOLS_FILTER_H_
#define IMAGETOOLS_FILTER_H_

#include <string>
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

/** The base class for an image editing tool.  Every tool "has a" mask.
 Subclasses must define this mask by filling in the CreateMask factory method.
 This base class will then be able to apply the mask to a pixel buffer as the
 tool is dragged around interactively. */
class Filter {
 public:
  // constructor
  Filter();

  // deconstructor
  virtual ~Filter();

  /** Subclasses must fill in this factory method to define the mask for the
   specific tool they implement. */

  void ApplyToBuffer(PixelBuffer* buffer);

  // set up the filter
  virtual void SetupFilter() = 0;

  // calculate the filter pixel
  // each filter have to implement this function by itself
  virtual ColorData CalculateFilteredPixel(const PixelBuffer& buffer,
    int x, int y) = 0;

  // clean up the filters
  virtual void CleanupFilter() = 0;

  // return true for this
  virtual bool can_calculate_in_place();

 protected:
  PixelBuffer *buffer_;


 private:
  // Making the copy constructor and assignment operator private makes it
  // impossible to copy, move, or assign Tools.  This is nice because it means
  // we do not need to worry about accidentally having more than one tool
  // point to the same mask or application strategy.  Each tool owns exactly
  // one of each of these and is in charge of deleting them when it gets
  // deleted.
  Filter(const Filter &rhs) = delete;
  Filter &operator=(const Filter &rhs) = delete;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_FILTER_H_
