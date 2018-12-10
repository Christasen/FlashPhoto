/**
This file is part of the Flashphoto Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/

#include "imagetools/filter.h"
#include <assert.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
// constructor
Filter::Filter() : buffer_(NULL) {}

Filter::~Filter() {}

// this is how to perform the changes and apply them to buffer
void Filter::ApplyToBuffer(PixelBuffer* buffer) {
  int height = buffer->height();
  int width = buffer->width();
  bool answer = can_calculate_in_place();

  // if we can calculate in space,then we perform the following steps
  if (answer == true) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      ColorData data1 = CalculateFilteredPixel(*buffer, j, i);
      data1.Clamp();
      buffer -> set_pixel(j, i, data1);
      }
    }
  }  else {
    PixelBuffer *buf = new PixelBuffer(*buffer);
    SetupFilter();
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        ColorData data1 = CalculateFilteredPixel(*buf, j, i);
        data1.Clamp();
        buffer -> set_pixel(j, i, data1);
        }
      }
    CleanupFilter();
  }
}

bool Filter::can_calculate_in_place() {
  return true;
}


} /* namespace image_tools */
