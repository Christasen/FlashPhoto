/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/
#include "imagetools/filter_channels.h"

#include <assert.h>
#include <algorithm>
#include <cmath>

#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
// constructor
FilterChannels::FilterChannels() {
  red_  = 1.0;
  blue_ = 1.0;
  green_ = 1.0;
}

// deconstructor
FilterChannels::~FilterChannels() {}

// user-defined constructor
FilterChannels::FilterChannels(float r, float g, float b) {
  red_  = r;
  blue_ = b;
  green_ = g;
}

// set up the filters
void FilterChannels::SetupFilter() {}

// clean up the filters
void FilterChannels::CleanupFilter() {}

// Given scale factors for colors from the user and  multiply the
// Red, Green, and Blue component for each pixel in
// the image by the scale factor.
ColorData FilterChannels::CalculateFilteredPixel(const PixelBuffer& buffer,
  int x, int y) {
    ColorData d1 = buffer.pixel(x, y);
    float a = d1.alpha();
    float red = d1.red()*red_;
    float green = d1.green()*green_;
    float blue = d1.blue()*blue_;
    ColorData d2 = ColorData(red, green, blue, a);
    return d2;
    // return ColorData(d1.red()*red_, d1.green()*green_, d1.blue()*blue_, a);
  }



} /* namespace image_tools */
