/**
This file is part of the CSCI-3081W Project Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/
#include "imagetools/image_editor.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

namespace image_tools {

/** Creates an editor with a NULL pixel buffer.  You will need to set the
 pixel buffer before performing any editing operations. */
ImageEditor::ImageEditor() {
  current_buffer_ = NULL;
}

ImageEditor::ImageEditor(PixelBuffer *buffer) {
  current_buffer_ = buffer;
}

/** Deletes the current pixel buffer if not null. */
ImageEditor::~ImageEditor() {
  delete current_buffer_;
  current_buffer_ = NULL;
}

// FILE SAVING AND LOADING
Tool *ImageEditor::GetToolByName(const std::string &name) {
  if (name == t_blur_.name()) {
    return &t_blur_;
  } else if (name == t_calligraphy_pen_.name()) {
    return &t_calligraphy_pen_;
  } else if (name == t_chalk_.name()) {
    return &t_chalk_;
  } else if (name == t_eraser_.name()) {
    return &t_eraser_;
  } else if (name == t_highlighter_.name()) {
    return &t_highlighter_;
  } else if (name == t_pen_.name()) {
    return &t_pen_;
  } else if (name == t_spray_can_.name()) {
    return &t_spray_can_;
  } else if (name == t_stamp_.name()) {
    return &t_stamp_;
  } else {
    return NULL;
  }
}

void ImageEditor::StartStroke(const std::string &tool_name,
                                const ColorData &color, float radius, int x,
                                int y) {
  current_tool_ = GetToolByName(tool_name);
  tool_color_ = color;
  tool_radius_ = radius;
  if ((current_tool_) && (current_buffer_)) {
    SaveStateForPossibleUndo();
    current_tool_->StartStroke(current_buffer_, x, y, tool_color_,
                               tool_radius_);
  }
}

void ImageEditor::AddToStroke(int x, int y) {
  if ((current_tool_) && (current_buffer_)) {
    current_tool_->AddToStroke(x, y);
  }
}

void ImageEditor::EndStroke(int x, int y) {
  if ((current_tool_) && (current_buffer_)) {
    current_tool_->EndStroke(x, y);
  }
}

void ImageEditor::LoadFromFile(const std::string &filename) {
  if (current_buffer_ != NULL) {
    SaveStateForPossibleUndo();
    current_buffer_->LoadFromFile(filename);
  } else {
    current_buffer_ = new PixelBuffer(filename);
  }
}

void ImageEditor::SaveToFile(const std::string &filename) {
  current_buffer_->SaveToFile(filename);
}

void ImageEditor::ApplyBlurFilter(float radius) {
  SaveStateForPossibleUndo();
  ConvolutionFilterBlur *f1 = new ConvolutionFilterBlur(radius);
  f1 -> ApplyToBuffer(current_buffer_);
  (void)radius;
  delete f1;
}

void ImageEditor::ApplyMotionBlurFilter(float rad,
  ConvolutionFilterMotionBlur::BlurDir dir) {
  SaveStateForPossibleUndo();
  ConvolutionFilterMotionBlur *f1 = new ConvolutionFilterMotionBlur(rad, dir);
  f1 -> ApplyToBuffer(current_buffer_);
  (void)rad;
  (void)dir;
  delete f1;
}

void ImageEditor::ApplySharpenFilter(float rad) {
  SaveStateForPossibleUndo();
  ConvolutionFilterSharpen *f1 = new ConvolutionFilterSharpen(rad);
  f1 -> ApplyToBuffer(current_buffer_);
  (void)rad;
  delete f1;
}

void ImageEditor::ApplyEdgeDetectFilter() {
  SaveStateForPossibleUndo();
    ConvolutionFilterEdge *f1 = new ConvolutionFilterEdge();
    f1 -> ApplyToBuffer(current_buffer_);
    delete f1;
}

void ImageEditor::ApplyThresholdFilter(float value) {
  SaveStateForPossibleUndo();
  FilterThreshold *f1 = new FilterThreshold(value);
  f1 -> ApplyToBuffer(current_buffer_);

  (void)value;
  delete f1;
}

void ImageEditor::ApplySaturateFilter(float scale) {
  SaveStateForPossibleUndo();
  FilterSaturate *f1 = new FilterSaturate(scale);
  f1 -> ApplyToBuffer(current_buffer_);
  (void)scale;
  delete f1;
}

void ImageEditor::ApplyChannelsFilter(float red, float green, float blue) {
  SaveStateForPossibleUndo();
  FilterChannels *f1 = new FilterChannels(red, green, blue);
  f1 -> ApplyToBuffer(current_buffer_);
  (void)red;
  (void)green;
  (void)blue;
  delete f1;
}

void ImageEditor::ApplyQuantizeFilter(int num) {
  SaveStateForPossibleUndo();
  FilterQuantize *f1 = new FilterQuantize(num);
  f1 -> ApplyToBuffer(current_buffer_);
  (void)num;
  delete f1;
}

bool ImageEditor::can_undo() { return saved_states_.size(); }

bool ImageEditor::can_redo() { return undone_states_.size(); }

void ImageEditor::Undo() {
  if (can_undo()) {
    // save state for a possilbe redo
    undone_states_.push_front(current_buffer_);

    // make the top state on the undo stack the current one
    current_buffer_ = saved_states_.front();
    saved_states_.pop_front();
  }
}

void ImageEditor::Redo() {
  if (can_redo()) {
    // save state for a possible undo
    saved_states_.push_front(current_buffer_);

    // make the top state on the redo stack the current one
    current_buffer_ = undone_states_.front();
    undone_states_.pop_front();
  }
}

void ImageEditor::SaveStateForPossibleUndo() {
  PixelBuffer *buffer_copy = new PixelBuffer(*current_buffer_);
  saved_states_.push_front(buffer_copy);

  // remove the oldest undos if we've over our limit
  while (saved_states_.size() > max_undos_) {
    delete saved_states_.back();
    saved_states_.pop_back();
  }

  // committing a new state invalidates the states saved in the redo stack,
  // so, we simply clear out this stack.
  while (!undone_states_.empty()) {
    delete undone_states_.back();
    undone_states_.pop_back();
  }
}

PixelBuffer *ImageEditor::pixel_buffer() { return current_buffer_; }

void ImageEditor::set_pixel_buffer(PixelBuffer *buffer) {
  current_buffer_ = buffer;
  }
}  // namespace image_tools
