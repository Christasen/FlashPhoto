/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/

#include "imagetools/filter_threshold.h"

#include <assert.h>
#include <algorithm>
#include <cmath>

#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
// constructor
FilterThreshold::FilterThreshold() {
  average_value_  = 0.5;
}

// deconstructor
FilterThreshold::~FilterThreshold() {}

// user defined constructor
FilterThreshold::FilterThreshold(float v) {
  average_value_ = v;
}

// set up the filter
void FilterThreshold::SetupFilter() {}

// clean up the filter
void FilterThreshold::CleanupFilter() {}

// First, find the average value of the red, green, blue color
// Compare the average we calculated with the value in the class
// then based on the result to change the pixel to black or white
ColorData FilterThreshold:: CalculateFilteredPixel(const PixelBuffer& buffer,
  int x, int y) {
    ColorData d1 = buffer.pixel(x, y);
    float a = d1.alpha();
    float v = (d1.red() + d1.green() + d1.blue()) / 3.0;
    if ( v > average_value_ ) {
      return ColorData(1.0, 1.0, 1.0, a);
    } else {
      return ColorData(0, 0, 0, a);
    }
  }



} /* namespace image_tools */
