/**
This file is part of the Mia project Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/
#include "mia/command_line_processor.h"

using std::cout;
using std::string;
using std::endl;
namespace image_tools {

CommandLineProcessor::CommandLineProcessor() {
  image_editor_ = new ImageEditor();
}

CommandLineProcessor::CommandLineProcessor(ImageEditor* image) {
  image_editor_ = image;
}

CommandLineProcessor::~CommandLineProcessor() {
  delete image_editor_;
  image_editor_ = NULL;
  (void) command_vec_;
}

bool CommandLineProcessor::CheckPNG(string name) {
  int len = name.length();
  string substr = name.substr(len-4, 4);
  if (substr == ".png" || substr == ".PNG") {
    return true;
  }
  return false;
}

bool CommandLineProcessor::ConvertingToFloat(string name, float &num) {
    int cnt = 0;
    try {
      for (int i = 0; i < static_cast<int>(name.length()); i++) {
        if (cnt > 1) {
          return false;
        }
        if (name[i] == '.') {
          cnt += 1;
        }
        if (name[i] < '0' || name[i] > '9') {
          return false;
        }
      }
      num = std::stof(name);
    }
    catch (...) {
      cout << "Invaid Command: " << name << endl;
      return false;
    }
    return true;
}

void CommandLineProcessor::CommandProcess(int argc, char* argv[]) {
  // the case when you have 2 argc
  if (argc <= 2) {
    string input_cmd = static_cast<string>(argv[1]);

    PrintError(input_cmd);
    return;
  }

  std::vector<ImageEditorCommand*> new_vec;
  string InputFile = static_cast<string>(argv[1]);
  string OutputFile = static_cast<string>(argv[argc-1]);

  // use try catch method to catch commands
  try {
    if (CheckPNG(InputFile) == false) {
      HelperMessage();
      cout << "Error: The input file should be png or PNG format" << endl;
      return;
    }
    if (CheckPNG(OutputFile) == false) {
      HelperMessage();
      cout << "Error: The output file should be png or PNG format" << endl;
      return;
    }
    new_vec.push_back(new LoadCommand(image_editor_, InputFile));
    for (int i = 2; i < argc-1; ++i) {
      string input_cmd = static_cast<string>(argv[i]);
      if (input_cmd == "-blur") {
        if ((i+1) < argc) {
        float checker;
        bool check  = ConvertingToFloat(argv[++i], checker);
        if (checker >= 0 && check == true) {
            new_vec.push_back(
              new BlurFilterCommand(image_editor_, checker));
            command_vec_.push_back(input_cmd);
            command_vec_.push_back(static_cast<string>(argv[i]));
          } else {
            throw static_cast<string>(argv[i]);
          }} else {
        throw static_cast<string>(argv[i]);
      }
    } else if (input_cmd == "-edgedetect") {
          new_vec.push_back(
            new EdgeFilterCommand(image_editor_));
      } else if (input_cmd == "-red") {
        if ((i+1) < argc) {
        float checker;
        bool check  = ConvertingToFloat(argv[++i], checker);
        if (checker >= 0 && check == true) {
            new_vec.push_back(
              new ChannelsFilterCommand(image_editor_, checker, 1.0, 1.0));
            command_vec_.push_back(input_cmd);
            command_vec_.push_back(static_cast<string>(argv[i]));
          } else {
            throw static_cast<string>(argv[i]);
          }
        } else {
        throw static_cast<string>(argv[i]);
      }
    } else if (input_cmd == "-blue") {
        if ((i+1) < argc) {
        float checker;
        bool check  = ConvertingToFloat(argv[++i], checker);
        if (checker >= 0 && check == true) {
            new_vec.push_back(
                new ChannelsFilterCommand(image_editor_, 1.0, 1.0, checker));
            command_vec_.push_back(input_cmd);
            command_vec_.push_back(static_cast<string>(argv[i]));
          } else {
            throw static_cast<string>(argv[i]);
          }
        } else {
        throw static_cast<string>(argv[i]);
      }
    } else if (input_cmd == "-green") {
        if ((i+1) < argc) {
        float checker;
        bool check  = ConvertingToFloat(argv[++i], checker);
        if (checker >= 0 && check == true) {
            new_vec.push_back(
              new ChannelsFilterCommand(image_editor_, 1.0, checker, 1.0));
            command_vec_.push_back(input_cmd);
            command_vec_.push_back(static_cast<string>(argv[i]));
          } else {
            throw static_cast<string>(argv[i]);
          }
        } else {
        throw static_cast<string>(argv[i]);
      }
    } else if (input_cmd == "-quantize") {
        if ((i+1) < argc) {
        float checker;
        bool check  = ConvertingToFloat(argv[++i], checker);
        if (checker >= 0 && check == true) {
            new_vec.push_back(
              new QuantizeFilterCommand(image_editor_, checker));
            command_vec_.push_back(input_cmd);
            command_vec_.push_back(static_cast<string>(argv[i]));
          } else {
            throw static_cast<string>(argv[i]);
          }
        } else {
        throw static_cast<string>(argv[i]);
      }
    } else if (input_cmd == "-saturate") {
        if ((i+1) < argc) {
        float checker;
        bool check  = ConvertingToFloat(argv[++i], checker);
        if (checker >= 0 && check == true) {
            new_vec.push_back(
              new SaturateFilterCommand(image_editor_, checker));
            command_vec_.push_back(input_cmd);
            command_vec_.push_back(static_cast<string>(argv[i]));
          } else {
            throw static_cast<string>(argv[i]);
          }
        } else {
        throw static_cast<string>(argv[i]);
      }
    } else if (input_cmd == "-sharpen") {
      if ((i+1) < argc) {
      float checker;
      bool check  = ConvertingToFloat(argv[++i], checker);
      if (checker >= 0 && check == true) {
          new_vec.push_back(
            new SharpenFilterCommand(image_editor_, checker));
          command_vec_.push_back(input_cmd);
          command_vec_.push_back(static_cast<string>(argv[i]));
        } else {
          throw static_cast<string>(argv[i]);
        }
      } else {
      throw static_cast<string>(argv[i]);
    }
  } else if (input_cmd == "-threshold") {
        if ((i+1) < argc) {
        float checker;
        bool check  = ConvertingToFloat(argv[++i], checker);
        if (checker >= 0 && check == true) {
            new_vec.push_back(
              new ThresholdFilterCommand(image_editor_, checker));
            command_vec_.push_back(input_cmd);
            command_vec_.push_back(static_cast<string>(argv[i]));
          } else {
            throw static_cast<string>(argv[i]);
          }
        } else {
        throw static_cast<string>(argv[i]);
      }
    } else if (input_cmd == "-motionblur-n-s") {
        if ((i+1) < argc) {
        float checker;
        bool check  = ConvertingToFloat(argv[++i], checker);
        if (checker >= 0 && check == true) {
            new_vec.push_back(
              new MotionBlurFilterCommand(image_editor_, checker,
                static_cast<ConvolutionFilterMotionBlur::BlurDir>
                (MBLUR_DIR_N_S)));
            command_vec_.push_back(input_cmd);
            command_vec_.push_back(static_cast<string>(argv[i]));
          } else {
            throw static_cast<string>(argv[i]);
          }
        } else {
        throw static_cast<string>(argv[i]);
      }
    } else if (input_cmd == "-motionblur-e-w") {
        if ((i+1) < argc) {
        float checker;
        bool check  = ConvertingToFloat(argv[++i], checker);
        if (checker >= 0 && check == true) {
            new_vec.push_back(
              new MotionBlurFilterCommand(image_editor_, checker,
                static_cast<ConvolutionFilterMotionBlur::BlurDir>
                (MBLUR_DIR_E_W)));
            command_vec_.push_back(input_cmd);
            command_vec_.push_back(static_cast<string>(argv[i]));
          } else {
            throw static_cast<string>(argv[i]);
          }
        } else {
        throw static_cast<string>(argv[i]);
      }
    } else if (input_cmd == "-motionblur-nw-se") {
        if ((i+1) < argc) {
        float checker;
        bool check  = ConvertingToFloat(argv[++i], checker);
        if (checker >= 0 && check == true) {
            new_vec.push_back(
              new MotionBlurFilterCommand(image_editor_, checker,
                static_cast<ConvolutionFilterMotionBlur::BlurDir>
                (MBLUR_DIR_NW_SE)));
            command_vec_.push_back(input_cmd);
            command_vec_.push_back(static_cast<string>(argv[i]));
          } else {
            throw static_cast<string>(argv[i]);
          }
        } else {
        throw static_cast<string>(argv[i]);
      }
    } else if (input_cmd == "-motionblur-ne-sw") {
        if ((i+1) < argc) {
        float checker;
        bool check  = ConvertingToFloat(argv[++i], checker);
        if (checker >= 0 && check == true) {
            new_vec.push_back(
              new MotionBlurFilterCommand(image_editor_, checker,
                static_cast<ConvolutionFilterMotionBlur::BlurDir>
                (MBLUR_DIR_NE_SW)));
            command_vec_.push_back(input_cmd);
            command_vec_.push_back(static_cast<string>(argv[i]));
          } else {
            throw static_cast<string>(argv[i]);
          }
        } else {
        throw static_cast<string>(argv[i]);
      }
    } else {
        throw input_cmd;
      }  // end of else
  }  // end of for-loop
  }  // end of try statement
  // catch the error
  catch (string name) {
    cout << "Invaid command: " << name << endl;
    HelperMessage();
    return;
  }  // end of catch
  // the vector is empty
  new_vec.push_back(new SaveCommand(image_editor_, OutputFile));
  for (std::vector<int>::size_type i = 0; i < (new_vec.size()); i++) {
    new_vec[i] -> Execute();
    delete new_vec[i];
    new_vec[i] = NULL;
  }
}  // end of the function

void CommandLineProcessor::HelperMessage() {
  cout << "usage: mia infile.png [image processing commands ...]outfile.png";
  cout << endl << endl;
  cout << "infile.png:" << "\t\t" << "input image file in png format\n";
  cout << "outfile.png:\t\t" << "filename to use for saving the result\n\n";
  cout << "image processing comamnds:\n";
  cout << "-blur r:"<< "\t\t" << "apply a gaussian blur of radius r\n";
  cout << "-edgedetect:"<< "\t\t" << "apply an edge detection filter\n";
  cout << "-sharpen r:\t\t" << "apply a sharpening filter of radius r\n";
  cout << "-red s:"<< "\t\t\t" << "scale the red channel by factor s\n";
  cout << "-green s:"<< "\t\t" << "scale the green channel by factor s\n";
  cout << "-blue s:"<< "\t\t" << "scale the blue channel by factor s\n";
  cout << "-quantize n:\t\t" << "quantize each color channel into n bins\n";
  cout << "-saturate s:"<< "\t\t" << "saturate colors by scale factor s\n";
  cout << "-threshold c:"<< "\t\t" << "threshold using cutoff value c\n";
  cout << "-motionblur-n-s r:" << "\t";
  cout << "north-south motion blur with kernel radius r\n";
  cout << "-motionblur-e-w r:" << "\t";
  cout << "east-west motion blur with kernel radius r\n";
  cout << "-motionblur-ne-sw r:" << "\t";
  cout << "ne-sw motion blur with kernel radius r\n";
  cout << "-motionblur-nw-se r:" << "\t"
       << "nw-se motion blur with kernel radius r\n";
}

void CommandLineProcessor::PrintError(std::string tar) {
  if (tar == "-h") {
    HelperMessage();
  } else {
    HelperMessage();
    std::cout << "Mia: '" << tar << "' is not a mia command\n";
  }
}
}  // namespace image_tools
