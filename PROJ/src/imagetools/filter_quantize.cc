/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/


#include "imagetools/filter_quantize.h"

#include <assert.h>
#include <algorithm>
#include <cmath>

#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
// constructor
FilterQuantize::FilterQuantize() {
  num_bins_  = 1.0;
}

// deconstructor
FilterQuantize::~FilterQuantize() {}

// user defined constructor
FilterQuantize::FilterQuantize(float v) {
  num_bins_ = v;
}

// set up the filter
void FilterQuantize::SetupFilter() {}

// clean up the filter
void FilterQuantize::CleanupFilter() {}

// Given a number of bins and when we reduced the number of discrete
// symbols in a given stream, that stream would be compressible.
ColorData FilterQuantize:: CalculateFilteredPixel(const PixelBuffer& buffer,
  int x, int y) {
    ColorData d1 = buffer.pixel(x, y);
    float a = d1.alpha();
    float num_steps = num_bins_ -1;
    float red = round(d1.red() * num_steps) / num_steps;
    float green = round(d1.green() * num_steps) / num_steps;
    float blue = round(d1.blue() * num_steps) / num_steps;
    return ColorData(red, green, blue, a);
  }



} /* namespace image_tools */
