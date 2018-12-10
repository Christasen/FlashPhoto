/**
This file is part of the Tests Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/

#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include "imagetools/image_editor.h"
#include "imagetools/convolution_filter_motion_blur.h"
#include "mia/command_line_processor.h"
#include "mia/image_editor_commands.h"
#include "gtest/gtest.h"

using std::string;
using std::cout;
using std::endl;
using mingfx::Platform;
using image_tools::ConvolutionFilterMotionBlur;
using image_tools::ColorData;
using image_tools::ImageEditor;
using image_tools::Tool;
using image_tools::PixelBuffer;
using image_tools::ToolBlur;
using image_tools::ToolCalligraphyPen;
using image_tools::ToolChalk;
using image_tools::ToolPen;
using image_tools::ToolSprayCan;
using image_tools::ToolEraser;
using image_tools::ToolHighlighter;
using image_tools::ToolStamp;

class RegressionTest : public ::testing::Test {
public:
  void SetUp() override {
    current = "resources/reg/";
    base = "resources/I.png";
    PixelBuffer* pixel = new PixelBuffer(base);
    image = new ImageEditor(pixel);
  }

  void TearDown () override {
    delete image;
    image = NULL;
  }

  enum BlurDir {
  MBLUR_DIR_N_S,
  MBLUR_DIR_E_W,
  MBLUR_DIR_NE_SW,
  MBLUR_DIR_NW_SE
 };

protected:
  ImageEditor *image;
  string current;
  string base;
  // TOOLS that I can use
};
// Threshold TEST

TEST_F(RegressionTest,ThresholdTest) {
  PixelBuffer initial = PixelBuffer(*image->pixel_buffer());
  image -> ApplyThresholdFilter(0.7);
  PixelBuffer later = PixelBuffer(*(image->pixel_buffer()));
  current = current + "0.7threshold.png";
  if(!Platform::Platform::FileExists(current)) {
    image->SaveToFile(current);
    initial = PixelBuffer(current);
    cout << "New file here applying Threshold" << endl;
  } else {
    initial = PixelBuffer(current);
  }
  EXPECT_TRUE(initial == later);
}
// Red TEST

TEST_F(RegressionTest,RedTest) {
  PixelBuffer initial = PixelBuffer(*image->pixel_buffer());
  image -> ApplyChannelsFilter(1.5, 1.0, 1.0);
  PixelBuffer later = PixelBuffer(*(image->pixel_buffer()));
  current = current + "1.5red.png";
  if(!Platform::Platform::FileExists(current)) {
    image->SaveToFile(current);
    initial = PixelBuffer(current);
    cout << "New file here applying channels red" << endl;
  } else {
    initial = PixelBuffer(current);
  }
  EXPECT_TRUE(initial== later);
}

// Blue TEST
TEST_F(RegressionTest,BlueTest) {
  PixelBuffer initial = PixelBuffer(*image->pixel_buffer());
  image -> ApplyChannelsFilter(1.0, 1.0, 1.5);
  PixelBuffer later = PixelBuffer(*(image->pixel_buffer()));
  current = current + "1.5blue.png";
  if(!Platform::Platform::FileExists(current)) {
    image->SaveToFile(current);
    initial = PixelBuffer(current);
    cout << "New file here applying channels blue" << endl;
  } else {
    initial = PixelBuffer(current);
  }
  EXPECT_TRUE(initial== later);
}

// GreenTest
TEST_F(RegressionTest,GreenTest) {
  PixelBuffer initial = PixelBuffer(*image->pixel_buffer());
  image -> ApplyChannelsFilter(1.0, 1.5, 1.0);
  PixelBuffer later = PixelBuffer(*(image->pixel_buffer()));
  current = current + "1.5green.png";
  if(!Platform::Platform::FileExists(current)) {
    image->SaveToFile(current);
    initial = PixelBuffer(current);
    cout << "New file here applying channels green" << endl;
  } else {
    initial = PixelBuffer(current);
  }
  EXPECT_TRUE(initial== later);
}

// EdgeDetectTest
TEST_F(RegressionTest,EdgeDetectTest) {
  PixelBuffer initial = PixelBuffer(*image->pixel_buffer());
  image -> ApplyEdgeDetectFilter();
  PixelBuffer later = PixelBuffer(*(image->pixel_buffer()));
  current = current + "edge.png";
  if(!Platform::Platform::FileExists(current)) {
    image->SaveToFile(current);
    initial = PixelBuffer(current);
    cout << "New file here applying EdgeDetect" << endl;
  } else {
    initial = PixelBuffer(current);
  }
  EXPECT_TRUE(initial== later);
}
// sharpen
TEST_F(RegressionTest,SharpenTest) {
  PixelBuffer initial = PixelBuffer(*image->pixel_buffer());
  image -> ApplySharpenFilter(3.0);
  PixelBuffer later = PixelBuffer(*(image->pixel_buffer()));
  current = current + "3sharpen.png";
  if(!Platform::Platform::FileExists(current)) {
    image->SaveToFile(current);
    initial = PixelBuffer(current);
    cout << "New file here applying SharpenTest" << endl;
  } else {
    initial = PixelBuffer(current);
  }
  EXPECT_TRUE(initial== later);
}
// saturateMBLUR_DIR_E_W
TEST_F(RegressionTest,SaturateTest) {
  PixelBuffer initial = PixelBuffer(*image->pixel_buffer());
  image -> ApplySaturateFilter(2.0);
  PixelBuffer later = PixelBuffer(*(image->pixel_buffer()));
  current = current + "2saturate.png";
  if(!Platform::Platform::FileExists(current)) {
    image->SaveToFile(current);
    initial = PixelBuffer(current);
    cout << "New file here applying SaturateTest" << endl;
  } else {
    initial = PixelBuffer(current);
  }
  EXPECT_TRUE(initial== later);
}
// blur
TEST_F(RegressionTest,BlurTest) {
  PixelBuffer initial = PixelBuffer(*image->pixel_buffer());
  image -> ApplyBlurFilter(3.0);
  PixelBuffer later = PixelBuffer(*(image->pixel_buffer()));
  current = current + "3blur.png";
  if(!Platform::Platform::FileExists(current)) {
    image->SaveToFile(current);
    initial = PixelBuffer(current);
    cout << "New file here applying BlurTest" << endl;
  } else {
    initial = PixelBuffer(current);
  }
  EXPECT_TRUE(initial== later);
}
// quantize
TEST_F(RegressionTest,QuantizeTest) {
  PixelBuffer initial = PixelBuffer(*image->pixel_buffer());
  image -> ApplyQuantizeFilter(2.0);
  PixelBuffer later = PixelBuffer(*(image->pixel_buffer()));
  current = current + "2quantize.png";
  if(!Platform::Platform::FileExists(current)) {
    image->SaveToFile(current);
    initial = PixelBuffer(current);
    cout << "New file here applying QuantizeTest" << endl;
  } else {
    initial = PixelBuffer(current);
  }
  EXPECT_TRUE(initial== later);
}
// motionblur EW
TEST_F(RegressionTest,MotionBlurEWTest) {
  PixelBuffer initial = PixelBuffer(*image->pixel_buffer());
  image -> ApplyMotionBlurFilter(7.0,
    static_cast<ConvolutionFilterMotionBlur::BlurDir>
    (MBLUR_DIR_E_W));
  PixelBuffer later = PixelBuffer(*(image->pixel_buffer()));
  current = current + "7mtblrew.png";
  if(!Platform::Platform::FileExists(current)) {
    image->SaveToFile(current);
    initial = PixelBuffer(current);
    cout << "New file here applying MotionBlurEWTest" << endl;
  } else {
    initial = PixelBuffer(current);
  }
  EXPECT_TRUE(initial== later);
}

// motionblur NS
TEST_F(RegressionTest,MotionBlurNSTest) {
  PixelBuffer initial = PixelBuffer(*image->pixel_buffer());
  image -> ApplyMotionBlurFilter(7.0,
    static_cast<ConvolutionFilterMotionBlur::BlurDir>
    (MBLUR_DIR_N_S));
  PixelBuffer later = PixelBuffer(*(image->pixel_buffer()));
  current = current + "7mtblrns.png";
  if(!Platform::Platform::FileExists(current)) {
    image->SaveToFile(current);
    initial = PixelBuffer(current);
    cout << "New file here applying MotionBlurNSTest" << endl;
  } else {
    initial = PixelBuffer(current);
  }
  EXPECT_TRUE(initial== later);
}
// motionblur NWSE
TEST_F(RegressionTest,MotionBlurNWSETest) {
  PixelBuffer initial = PixelBuffer(*image->pixel_buffer());
  image -> ApplyMotionBlurFilter(7.0,
    static_cast<ConvolutionFilterMotionBlur::BlurDir>
    (MBLUR_DIR_NW_SE));
  PixelBuffer later = PixelBuffer(*(image->pixel_buffer()));
  current = current + "7mtblrnwse.png";
  if(!Platform::Platform::FileExists(current)) {
    image->SaveToFile(current);
    initial = PixelBuffer(current);
    cout << "New file here applying MotionBlurNWSETest" << endl;
  } else {
    initial = PixelBuffer(current);
  }
  EXPECT_TRUE(initial== later);
}
// motionblur NESW
TEST_F(RegressionTest,MotionBlurNESWTest) {
  PixelBuffer initial = PixelBuffer(*image->pixel_buffer());
  image->ApplyMotionBlurFilter(7.0,
    static_cast<ConvolutionFilterMotionBlur::BlurDir>
    (MBLUR_DIR_NE_SW));
  PixelBuffer later = PixelBuffer(*(image->pixel_buffer()));
  current = current + "7mtblrnesw.png";
  if(!Platform::Platform::FileExists(current)) {
    image->SaveToFile(current);
    initial = PixelBuffer(current);
    cout << "New file here applying MotionBlurNESWTest" << endl;
  } else {
    initial = PixelBuffer(current);
  }
  EXPECT_TRUE(initial== later);
}


// tool_blur

TEST_F(RegressionTest, BlurToolTest) {
  // Save a file
  float radius = 5.0;
  int x = 25;
  int y = 75;
  // ImageEditor* image1 = new ImageEditor(new PixelBuffer(base));
  // image1 -> StartStroke("Blur",
  //                   ColorData(0.5, 0.5, 0.5), radius, x, y);
  // image1 -> AddToStroke(x, y);
  // image1 -> EndStroke(x, y);
  // image1->SaveToFile ("resources/reg/toolBlur.png");
  //ImageEditor* ground = new ImageEditor(new PixelBuffer(ground_true));
  ImageEditor* initial = new ImageEditor(new PixelBuffer(base));
  initial -> StartStroke("Blur",
                    ColorData(0.5, 0.5, 0.5), radius, x, y);
  initial -> AddToStroke(x, y);
  initial -> EndStroke(x, y);
  PixelBuffer* limit = new PixelBuffer("resources/reg/toolBlur.png");
  PixelBuffer buf = PixelBuffer(*(initial->pixel_buffer()));
  EXPECT_TRUE(*limit == buf);
  delete initial;
  delete limit;
  initial = NULL;
  limit = NULL;
}


// t_calligraphy_pen_
TEST_F(RegressionTest,CaligraphyToolTest) {
  float radius = 5.0;
  int x = 55;
  int y = 75;
  // ImageEditor* image1 = new ImageEditor(new PixelBuffer(base));
  // image1 -> StartStroke("Calligraphy Pen",
  //                   ColorData(0.5, 0.5, 0.5), radius, x, y);
  // image1 -> AddToStroke(x, y);
  // image1 -> EndStroke(x, y);
  // image1->SaveToFile ("resources/reg/toolCaliPen.png");
  // ImageEditor *image2 = new ImageEditor(
  ImageEditor* initial = new ImageEditor(new PixelBuffer(base));
  initial -> StartStroke("Calligraphy Pen",
                    ColorData(0.5, 0.5, 0.5), radius, x, y);
  initial -> AddToStroke(x, y);
  initial -> EndStroke(x, y);
  PixelBuffer* limit = new PixelBuffer("resources/reg/toolCaliPen.png");
  PixelBuffer buf = PixelBuffer(*(initial->pixel_buffer()));
  EXPECT_TRUE(*limit == buf);
  delete initial;
  delete limit;
  initial = NULL;
  limit = NULL;
}

// ToolChalk t_chalk_;

TEST_F(RegressionTest,ChalkToolTest) {
  float radius = 5.0;
  int x = 55;
  int y = 75;
  // ImageEditor* image1 = new ImageEditor(new PixelBuffer(base));
  // image1 -> StartStroke("Chalk",
  //                   ColorData(0.5, 0.5, 0.5), radius, x, y);
  // image1 -> AddToStroke(x, y);
  // image1 -> EndStroke(x, y);
  // image1->SaveToFile ("resources/reg/toolChalk.png");
  // EXPECT_TRUE(true);

  ImageEditor* initial = new ImageEditor(new PixelBuffer(base));
  initial -> StartStroke("Chalk",
                    ColorData(0.5, 0.5, 0.5), radius, x, y);
  initial -> AddToStroke(x, y);
  initial -> EndStroke(x, y);
  PixelBuffer* limit = new PixelBuffer("resources/reg/toolChalk.png");
  PixelBuffer buf = PixelBuffer(*(initial->pixel_buffer()));
  EXPECT_TRUE(*limit == buf);
  delete initial;
  delete limit;
  initial = NULL;
  limit = NULL;
}


// ToolEraser t_eraser_;
TEST_F(RegressionTest,EraserToolTest) {
  float radius = 5.0;
  int x = 55;
  int y = 75;
  // ImageEditor* image1 = new ImageEditor(new PixelBuffer(base));
  // image1 -> StartStroke("Eraser",
  //                   ColorData(0.5, 0.5, 0.5), radius, x, y);
  // image1 -> AddToStroke(x, y);
  // image1 -> EndStroke(x, y);
  // image1->SaveToFile ("resources/reg/ToolEraser.png");
  ImageEditor* initial = new ImageEditor(new PixelBuffer(base));
  initial -> StartStroke("Eraser",
                    ColorData(0.5, 0.5, 0.5), radius, x, y);
  initial -> AddToStroke(x, y);
  initial -> EndStroke(x, y);
  PixelBuffer* limit = new PixelBuffer("resources/reg/ToolEraser.png");
  PixelBuffer buf = PixelBuffer(*(initial->pixel_buffer()));
  EXPECT_TRUE(*limit == buf);
  delete initial;
  delete limit;
  initial = NULL;
  limit = NULL;
}

// ToolHighlighter t_highlighter_;
TEST_F(RegressionTest,HighlighterToolTest) {
  float radius = 5.0;
  int x = 55;
  int y = 75;
  // ImageEditor* image1 = new ImageEditor(new PixelBuffer(base));
  // image1 -> StartStroke("Hilighter",
  //                   ColorData(0.5, 0.5, 0.5), radius, x, y);
  // image1 -> AddToStroke(x, y);
  // image1 -> EndStroke(x, y);
  // image1->SaveToFile ("resources/reg/ToolHighlighter.png");
  // EXPECT_TRUE(true);
  ImageEditor* initial = new ImageEditor(new PixelBuffer(base));
  initial -> StartStroke("Hilighter",
                    ColorData(0.5, 0.5, 0.5), radius, x, y);
  initial -> AddToStroke(x, y);
  initial -> EndStroke(x, y);
  PixelBuffer* limit = new PixelBuffer("resources/reg/ToolHighlighter.png");
  PixelBuffer buf = PixelBuffer(*(initial->pixel_buffer()));
  EXPECT_TRUE(*limit == buf);
  delete initial;
  delete limit;
  initial = NULL;
  limit = NULL;
}

// ToolPen t_pen_;
TEST_F(RegressionTest,PenToolTest) {
  float radius = 5.0;
  int x = 55;
  int y = 75;
  // ImageEditor* image1 = new ImageEditor(new PixelBuffer(base));
  // image1 -> StartStroke("Pen",
  //                   ColorData(0.5, 0.5, 0.5), radius, x, y);
  // image1 -> AddToStroke(x, y);
  // image1 -> EndStroke(x, y);
  // image1->SaveToFile ("resources/reg/ToolPen.png");
  // EXPECT_TRUE(true);
  ImageEditor* initial = new ImageEditor(new PixelBuffer(base));
  initial -> StartStroke("Pen",
                    ColorData(0.5, 0.5, 0.5), radius, x, y);
  initial -> AddToStroke(x, y);
  initial -> EndStroke(x, y);
  PixelBuffer* limit = new PixelBuffer("resources/reg/ToolPen.png");
  PixelBuffer buf = PixelBuffer(*(initial->pixel_buffer()));
  EXPECT_TRUE(*limit == buf);
  delete initial;
  delete limit;
  initial = NULL;
  limit = NULL;
}
// ToolSprayCan t_spray_can_;

TEST_F(RegressionTest,SprayCanToolTest) {
  float radius = 5.0;
  int x = 55;
  int y = 75;
  // ImageEditor* image1 = new ImageEditor(new PixelBuffer(base));
  // image1 -> StartStroke("Spray Can",
  //                   ColorData(0.5, 0.5, 0.5), radius, x, y);
  // image1 -> AddToStroke(x, y);
  // image1 -> EndStroke(x, y);
  // image1->SaveToFile ("resources/reg/ToolSprayCan.png");
  // EXPECT_TRUE(true);
  ImageEditor* initial = new ImageEditor(new PixelBuffer(base));
  initial -> StartStroke("Spray Can",
                    ColorData(0.5, 0.5, 0.5), radius, x, y);
  initial -> AddToStroke(x, y);
  initial -> EndStroke(x, y);
  PixelBuffer* limit = new PixelBuffer("resources/reg/ToolSprayCan.png");
  PixelBuffer buf = PixelBuffer(*(initial->pixel_buffer()));
  EXPECT_TRUE(*limit == buf);
  delete initial;
  delete limit;
  initial = NULL;
  limit = NULL;
}

// ToolStamp t_stamp_;
TEST_F(RegressionTest,StampToolTest) {
  float radius = 5.0;
  int x = 55;
  int y = 75;
  // ImageEditor* image1 = new ImageEditor(new PixelBuffer(base));
  // image1 -> StartStroke("Stamp",
  //                   ColorData(0.5, 0.5, 0.5), radius, x, y);
  // image1 -> AddToStroke(x, y);
  // image1 -> EndStroke(x, y);
  // image1->SaveToFile ("resources/reg/ToolStamp.png");
  // EXPECT_TRUE(true);
  ImageEditor* initial = new ImageEditor(new PixelBuffer(base));
  initial -> StartStroke("Stamp",
                    ColorData(0.5, 0.5, 0.5), radius, x, y);
  initial -> AddToStroke(x, y);
  initial -> EndStroke(x, y);
  PixelBuffer* limit = new PixelBuffer("resources/reg/ToolStamp.png");
  PixelBuffer buf = PixelBuffer(*(initial->pixel_buffer()));
  EXPECT_TRUE(*limit == buf);
  delete initial;
  delete limit;
  initial = NULL;
  limit = NULL;
}
