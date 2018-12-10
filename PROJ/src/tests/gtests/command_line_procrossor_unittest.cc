/**
This file is part of the Tests Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/

#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <mingfx.h>
#include "gtest/gtest.h"
#include "mia/command_line_processor.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/image_editor.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using image_tools::CommandLineProcessor;
using image_tools::ImageEditor;
using image_tools::PixelBuffer;


// Step1: Construct a test class
class CommandLineProcessorTest : public ::testing::Test {
  void SetUp() override {
    base = "resources/I.png";
    current = "resources/reg/";
    PixelBuffer* pixel = new PixelBuffer(base);
    image = new ImageEditor(pixel);
    process = new CommandLineProcessor();
  }

  void TearDown() override {
    delete image;
    image = NULL;
    delete process;
    process = NULL;
  }

 protected:
  string current;
  string base;
  ImageEditor* image;
  CommandLineProcessor* process;
  // helper variable
  string message =
    string("usage: mia infile.png [image processing commands ...]")
    +("outfile.png\n\n")
    +"infile.png:\t\t" + "input image file in png format\n"
    +"outfile.png:\t\t" + "filename to use for saving the result\n\n"
    +"image processing comamnds:\n"
    +"-blur r:\t\t" + "apply a gaussian blur of radius r\n"
    +"-edgedetect:\t\t" + "apply an edge detection filter\n"
    +"-sharpen r:\t\t" + "apply a sharpening filter of radius r\n"
    +"-red s:\t\t\t" + "scale the red channel by factor s\n"
    +"-green s:\t\t" + "scale the green channel by factor s\n"
    +"-blue s:\t\t" + "scale the blue channel by factor s\n"
    +"-quantize n:\t\t" + "quantize each color channel into n bins\n"
    +"-saturate s:\t\t" + "saturate colors by scale factor s\n"
    +"-threshold c:\t\t" + "threshold using cutoff value c\n"
    +"-motionblur-n-s r:\t"
    +"north-south motion blur with kernel radius r\n"
    +"-motionblur-e-w r:\t"
    +"east-west motion blur with kernel radius r\n"
    +"-motionblur-ne-sw r:\t"
    +"ne-sw motion blur with kernel radius r\n"
    +"-motionblur-nw-se r:\t"
    +"nw-se motion blur with kernel radius r\n";

    // parsing functions
    char ** passing(vector<string> v, int cnt) {
      char** argv = new char* [cnt];
      for (int j = 0; j < cnt; j++) {
        argv[j] = (char*) malloc((v[j].length()+1) * sizeof(char));
        std::strcpy (argv[j], (v.at(j)).c_str());
      }
      return argv;
    }
};

// This is testing valid input 'h'
TEST_F(CommandLineProcessorTest, Input_H_Test) {
  vector<string> v = {"mia", "-h"};
  testing::internal::CaptureStdout();
  process->CommandProcess(2, passing(v, 2));
  string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, message);
}

// This is testing invalid input "m"
TEST_F(CommandLineProcessorTest,Input_2_Test) {
  string valid = message+
    string("Mia: 'm' is not a mia command\n");
  vector<string> v = {"mia", "m"};
  testing::internal::CaptureStdout();
  process->CommandProcess(2, passing(v, 2));
  string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, valid);
}

// This is testing invalid input "missing input file"
TEST_F(CommandLineProcessorTest,InputTest) {
  vector<string> v = {"mia","-edgedetect", "1.png"};
  string valid = message+"Error: The input file should be png or PNG format\n";
  testing::internal::CaptureStdout();
  process->CommandProcess(3, passing(v, 3));
  string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, valid);
}

// This is testing invalid output "missing input file"
TEST_F(CommandLineProcessorTest,OutputTest) {
  vector<string> v = {"mia", "aaa.png", "-edgedetect"};
  string valid = message+
    string("Error: The output file should be png or PNG format\n");
  testing::internal::CaptureStdout();
  process->CommandProcess(3, passing(v, 3));
  string output = testing::internal::GetCapturedStdout();
// This is testing invalid output "missing input file"
  EXPECT_EQ(valid, output);
}

// This is testing bad argument of edgedetect
TEST_F(CommandLineProcessorTest,BadArgument1Test) {
  vector<string> v = {"mia", "aaa.png", "-edgedetect", "p", "AA.png"};
  string valid = string("Invaid command: p\n") +message;
  testing::internal::CaptureStdout();
  process->CommandProcess(5, passing(v, 5));
  string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(valid, output);
}

// This is testing bad argument of blur
TEST_F(CommandLineProcessorTest,BadArgument2Test) {
  vector<string> v = {"mia", "aaa.png", "-blur", "p", "AA.png"};
  string valid =  string("Invaid command: p\n")+message;
  testing::internal::CaptureStdout();
  process->CommandProcess(5, passing(v, 5));
  string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, valid);
}
// This is testing bad argument of blur
TEST_F(CommandLineProcessorTest,BadArgument3Test) {
  vector<string> v = {"mia", "aaa.png", "-blur", "1..1", "AA.png"};
  string valid =  string("Invaid command: 1..1\n")+message;
  testing::internal::CaptureStdout();
  process->CommandProcess(5, passing(v, 5));
  string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, valid);
}

// This is testing bad argument of blur
TEST_F(CommandLineProcessorTest,BadArgument4Test) {
  vector<string> v = {"mia", "aaa.png", "-blur", "1&a1", "AA.png"};
  string valid =  string("Invaid command: 1&a1\n")+message;
  testing::internal::CaptureStdout();
  process->CommandProcess(5, passing(v, 5));
  string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, valid);
}

// This is testing bad argument of blur
TEST_F(CommandLineProcessorTest,BadArgument5Test) {
  vector<string> v = {"mia", "aaa.png", "-blur", "-1", "AA.png"};
  string valid =  string("Invaid command: -1\n")+message;
  testing::internal::CaptureStdout();
  process->CommandProcess(5, passing(v, 5));
  string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, valid);
}

// This is testing command mode of mia
TEST_F(CommandLineProcessorTest,Command1Tests) {
  current = current + "2saturate.png";
  PixelBuffer* old_buf = new PixelBuffer(current);
  vector<string> v =
    {"mia,", "resources/I.png", "-saturate", "2", "/resources/reg/s2.png"};
  process->CommandProcess(5, passing(v, 5));
  image->ApplySaturateFilter(2.0);
  PixelBuffer* new_buf = new PixelBuffer(*(image->pixel_buffer()));
  EXPECT_EQ(*old_buf == *new_buf, true);
  delete old_buf;
  delete new_buf;
  old_buf = NULL;
  new_buf = NULL;
}

// This is testing command mode of mia
TEST_F(CommandLineProcessorTest,Command2Tests) {
  current = current + "2quantize.png";
  PixelBuffer* old_buf = new PixelBuffer(current);
  vector<string> v = {"mia,", "resources/I.png", "-quantize", "2", "q3.png"};
  process->CommandProcess(5, passing(v, 5));
  image->ApplyQuantizeFilter(2.0);
  PixelBuffer* new_buf = new PixelBuffer(*(image->pixel_buffer()));
  EXPECT_EQ(*old_buf == *new_buf, true);
  delete old_buf;
  delete new_buf;
  old_buf = NULL;
  new_buf = NULL;
}
