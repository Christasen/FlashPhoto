/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/

#include "imagetools/filter_saturate.h"

#include <assert.h>
#include <algorithm>
#include <cmath>

#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
// constructor
FilterSaturate::FilterSaturate() {
  grey_value_  = 1.0;
}

// deconstructor
FilterSaturate::~FilterSaturate() {}

// user defined constructor
FilterSaturate::FilterSaturate(float v) {
  grey_value_ = v;
}

// set up the filter
void FilterSaturate::SetupFilter() {}

// clean up the filter
void FilterSaturate::CleanupFilter() {}

// Calculate the luminance theb convert pixel to a grayscale
// Then linearly interpolating between color's grayscale version and
// the color itself.
ColorData FilterSaturate:: CalculateFilteredPixel(const PixelBuffer& buffer,
  int x, int y) {
    ColorData d1 = buffer.pixel(x, y);
    float a = d1.alpha();
    float v = d1.Luminance();
    ColorData d2 = ColorData(v, v, v, a);
    ColorData d3 = ImageToolsMath::Lerp(d2, d1, grey_value_);
    return d3;
  }



} /* namespace image_tools */
