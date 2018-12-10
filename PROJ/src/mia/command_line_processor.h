/**
This file is part of the Mia project Support Code, which was developed
at the University of Minnesota.


Copyright (c) 2018 Guangyu Yan,  University of Minnesota.


*/

#ifndef MIA_COMMAND_LINE_PROCESSOR_H_
#define MIA_COMMAND_LINE_PROCESSOR_H_

#include <mingfx.h>
#include <string>
#include <vector>
#include <fstream>
#include "imagetools/color_data.h"
#include "imagetools/image_editor.h"
#include "imagetools/pixel_buffer.h"
#include "mia/image_editor_commands.h"

namespace image_tools {

class CommandLineProcessor{
 public:
    CommandLineProcessor();
    explicit CommandLineProcessor(ImageEditor* image);
    ~CommandLineProcessor();
    /// Four possible motion blur directions are supported
    enum BlurDir {
      MBLUR_DIR_N_S,
      MBLUR_DIR_E_W,
      MBLUR_DIR_NE_SW,
      MBLUR_DIR_NW_SE
     };
    // the command processing function
    void CommandProcess(int argc, char* argv[]);
    // helper function to process the user I/O command
    // void IOProcess(std::vector<ImageEditorCommand*>comamnds);

    // helper function to print invalid commands
    void PrintError(std::string tar);

    bool ConvertingToFloat(std::string name, float&num);

    bool CheckPNG(std::string name);

    // helper function to print all the helper messages
    void HelperMessage();


 protected:
    ImageEditor* image_editor_;
    std::vector<std::string> command_vec_;
};

}  // namespace image_tools

#endif  // MIA_COMMAND_LINE_PROCESSOR_H_
