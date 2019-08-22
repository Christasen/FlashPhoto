## Project Directory

This is the project directory for flashphoto.

Main page
=============
Welcome to the FlashPhoto & Mia Project main page!

#### Build and Run

```bash
# Build the program with make
make
# Run the program
./build/bin/flashphoto
```

#### Check Style

```bash
# Using cpplint.py
make check-style
# Using cpplint-cse.sh
make check-style-cse
```

#### Run Tests

```bash
./build/test/gtests
```

#### Clean the Project

```bash
# Simply clean the project (for most situations)
make clean
```

----------------

User page
=============
Welcome to the FlashPhoto project developer main page!

This is a software design and development project which has been completed by Guangyu Yan and the CSCI3081 instructors in the University of Minnesota, Twin Cities. We developed software called FlashPhoto which is a digital painting and image-editing tool. It mainly contains eight filters and eight tools to process photos or design and draw new images. With some similar features of Flashphoto, the Medical Images Analysis(Mia) tool aims to support the medical analysis. The mia application is powerful but much smaller than the FlashPhoto since it is a very special-purpose tool. Also, I developed two different modes for Mia to run, the graphics mode and command line mode.

# FlashPhoto Abstract
FlashPhoto is a digital painting and image-editing tool, similar to some you have likely used before (e.g., Adobe Photoshop, Gimp, MS Paint, various smartphone apps). Equipped with the few tools and filters, you can create your own art by using FlashPhoto!

## Tools
Here is introduction of the tools you can use in the FlashPhoto
In the following pictures, different tools examples has been showed
![Flashphoto Interface](pics/pen.png)

### Pen
This tool is designed to look like a pen.  It makes an opaque, circular mark with constant intensity.  This means that when the pen is applied to the canvas the digital ink from the pen completely covers any color that had previously been applied to the canvas at that position.  The color of the pen can be set interactively using the GUI.


### Calligraphy Pen
This tool is designed to look like a calligraphy pen.  It works almost the same way as the Pen tool.  Like the Pen tool, it is completely opaque and it covers up any “paint” that was already applied to the canvas.  However, the difference with the Calligraphy Pen is that the mask is an oval tilted at a 30-degree angle.  The color of the highlighter can be set interactively using the GUI.

### Chalk
This tool is designed to look like a piece of chalk dragged across a bumpy surface.  It has a circular mask, but about 40% of the pixels within the circle are randomly chosen to be completely transparent.  This creates the bumpy effect.  The chalk color can be set interactively using the GUI.

### Highlighter
This tool is designed to look like a highlighter marker.  It uses an oval mask similar to the Calligraphy Pen, but the oval is oriented vertically, and the intensity of the mask is set to make the mark semi-transparent.  The color applied to the canvas is approximately 40% the color of the highlighter and 60% whatever color is already on the canvas; however, a special color blending function is used for the highlighter so that dark colors show through more than light colors.  The color of the highlighter’s ink can be set interactively using the GUI.

### Spray Can
This tool is designed to mimic the look of paint from a spray can.  It uses a special mask that is circular in shape but has a linear falloff to mimic the dispersion of color from the spray.  The intensity is strongest at the center pixel and falls off linearly to zero intensity at the edge of the circle. The specific paint color can be set interactively using the GUI.

### Eraser
This tool erases the digital canvas and returns it to its original background color.  It has a circular mask, and eraser’s color cannot be changed through the GUI because there is currently no user interface for changing the canvas background color.  (Feel free to add one if you wish.)

## Filters
Here is introduction of the filters you can use in the FlashPhoto

For a example, here is an original picture without any modifications
![Original Pic](pics/I.png)


### Threshold Filter
This is the threshold filter.
By using this filter, each of the color channels will be rounded up to the maximum value of 1.0 or down to the minimum value of 0.0 based on whether the pixel’s value is greater or less than the GLUI input value, respectively.

For a example, we applied threshold with 0.7 value here
![Threshold](pics/0.7threshold.png)

### Saturation Filter
This is the Saturation filter. You can use this filter to increase or decrease the colorfulness of the image.

For a example, we applied Saturation with 2 value here
![Saturation](pics/2saturate.png)

### Channels Filter
This is the channels filter and you can change the red, blue, green color to change the color settings of you picture!
This filter will independently scale up or down the intensity of each color channel (red, green, and blue).

For a example, we applied channels in red with 1.5 value here
![Channels](pics/1.5red.png)

### Quantize Filter
This is the quantize filter,by using this filter , you can reduce the number of colors in the image by binning.  If using 4 bins, there will only be 4 possible intensity values for each color channel, spaced evenly: 0%, 33%, 66%, and 100%. The filter will adjust each color channel value R, G, and B to put it into the nearest bin.

For a example, we applied quantize with 2 value here
![Quantize](pics/2quantize.png)

### Blur Filter
This is the Blur filter and you can use this filter to blur your pics in a certain degree.
The blur filter use a Gaussian Blur image convolution kernel to blur the image in proportion to the amount specified in the GUI.

For a example, we applied blur with 3 value here
![Blur](pics/3blur.png)

### Motion Blur Filter
This is the motionblur filter. Similar to blur filter, it will blur the pics by a certain degree.
This filter will blur the image by convolving it with an appropriate motion-blurring kernel.  Support four possible blurring directions (North-to-South, East-to-West, Northeast-to-Southwest, and Northwest-to-Southeast) and blur according to the amount specified in the GUI.  

For a example, we applied 7 motion blur in east west direction here
![Motion Blur](pics/7mtblrew.png)

### Sharpen Filter
This is the sharpen filter and you can sharpen the image (accentuate the edges of shapes) in proportion to the amount specified in the GUI by convolving the image with an appropriate sharpening kernel.

For a example, we applied Sharpen with 3 value here
![Sharpen](pics/3sharpen.png)

### Edge Detect Filter
This is the edge detect filter and you can use this filter to make the "edge" pics.
This filter will transform the image into one that only shows the edges of shapes by convolving it with a 3x3 edge detection kernel. Pixels on the border of differently colored regions will be bright, while pixels in areas of low change will be dark.

For a example, we applied edge detection here
![Edge Detect](pics/edge.png)


# MIA Abstract
Medical Image Analysis(Mia) is an application that could be used for interpreting medical images. We offered few tools and filters in the application for you to edit your images. We offered two modes for you to use our app.


## Graphical Mode:
You can simply click on the load file button on the software to load a file. There will be several tool and filter buttons for you to choose to edit your image.

    • A stamp tool that is hardcoded to stamp a bullseye pattern, one circle inside another, that clinicians can use to mark important areas on the image.

    • A pen tool, also useful for annotating images (e.g., circling a break in a bone).

    • A subset of the filters you have implemented previously that would be useful for medical imaging (blur, sharpen, edge detect, threshold, quantize).

    • File Open/Save controls


## Command Line Mode
There's a command mode in this application. You can do the following commands in your terminal to edit your files.

## Commands details:
    • Display a help message for a –h argument or any set of invalid arguments.  You can copy our example (below) or determine your own good format for a useful help message.

        ◦ mia –h

        ◦ mia <any invalid arguments>

    • Load an image specified by the first filename and save it out to the second filename.  With no other arguments specified, this is equivalent to copying the image file.

        ◦ mia in.png out.png

    • Run an image processing command before saving out the new file.  For example, to sharpen an image using a kernel of radius 5 and save the output to a new image:

        ◦ mia in.png –sharpen 5 out.png

    • Run multiple image processing commands in order.  For example, sharpen an image by amount 5, then run an edge detection filter, then save the output to a new image. (This example just shows two filter operations, but you need to support an arbitrary number of filter operations that are specified in order they should be applied.):

        ◦ mia in.png –sharpen 5 –edgedetect out.png

  Here is the complete list of command-line arguments to support as reported by a sample help message, which you are welcome to copy and use as your own:

        • usage: mia infile.png [image processing commands ...] outfile.png

        • infile.png:          input image file in png format

        • outfile.png:         filename to use for saving the result



  image processing comamnds:

        • -blur r:             apply a gaussian blur of radius r

        • -edgedetect:         apply an edge detection filter

        • -sharpen r:          apply a sharpening filter of radius r

        • -red s:              scale the red channel by factor s

        • -green s:            scale the green channel by factor s

        • -blue s:             scale the blue channel by factor s

        • -quantize n:         quantize each color channel into n bins

        • -saturate s:         saturate colors by scale factor s

        • -threshold c:        threshold using cutoff value c

        • -motionblur-n-s r:   north-south motion blur with kernel radius r

        • -motionblur-e-w r:   east-west motion blur with kernel radius r

        • -motionblur-ne-sw r: ne-sw motion blur with kernel radius r

        • -motionblur-nw-se r: nw-se motion blur with kernel radius r




Developer page
=============
Welcome to the CSCI3081W project developer main page!

----------------
### Abstract
Abstract: This is a software design and development project which has been completed by Guangyu Yan and the CSCI3081 instructors in the University of Minnesota, Twin Cities. We developed software called FlashPhoto which is a digital painting and image-editing tool. It mainly contains eight filters and eight tools to process photos or design and draw new images. With some similar features of Flashphoto, the Medical Images Analysis(Mia) tool aims to support the medical analysis. The mia application is powerful but much smaller than the FlashPhoto since it is a very special-purpose tool. Also, I developed two different modes for Mia to run, the graphics mode and command line mode.

For more information about the software, select the following pages
----------------
## [Programming Reference](src/ref.md)
```bash
Programming Reference
=============
Welcome to the CSCI3081W project programming reference page!

### FlashPhoto
The following link is about the main codes we used in the project

[FlashPhoto](file:///home/yanxx630/Desktop/3081/repo-yanxx630/PROJ/web/doxygen-html/flashphoto__app_8h_source.html)

[FlashPhoto Intro](file:///home/yanxx630/Desktop/3081/repo-yanxx630/PROJ/web/doxygen-html/md_src_flash.html)

### Mia
The following link is about the main codes we used in the mia

[Mia](file:///home/yanxx630/Desktop/3081/repo-yanxx630/PROJ/web/doxygen-html/mia__app_8h_source.html)

[Mia Intro](file:///home/yanxx630/Desktop/3081/repo-yanxx630/PROJ/web/doxygen-html/md_src_flash.html)

### Name space
We use the imagetools as the only namespace in our project.
Click the following links to track that out

[Namespace List](file:///home/yanxx630/Desktop/3081/repo-yanxx630/PROJ/web/doxygen-html/namespaceimage__tools.html)

### Class list
The following link is about all the class we used in the projects

[Class List](file:///home/yanxx630/Desktop/3081/repo-yanxx630/PROJ/web/doxygen-html/annotated.html)

### File list
The following link is about all the files we used in the projects

[File List](file:///home/yanxx630/Desktop/3081/repo-yanxx630/PROJ/web/doxygen-html/files.html)
```


## [Highlevel Design](src/uml.md)
```bash
In this project, we used many design patterns to construct the two application.
1. MVC has been used in constructing the overall structure of the two application and the imagetools.
2. Template method, factory method has been used in constructing the imagetools library.
3. Other software design strategy has been used in this project as well.


In order to present our structure clearly, we used the UML diagram here

The Overall Structure
----------------
![](pics/Overall.png)

Image Editor Structure
----------------
![](pics/UML.png)


The Filter Structure
----------------
![](pics/filteruml.png)

The Tool Structure
----------------
![](pics/Tool.png)
```

## [Coding Style](src/coding.md)
We followed the following google style
        ◦ Class interfaces follow McConnell’s guidelines of implementing just a
        single abstract data type within each class and using consistent levels of abstraction.

        ◦ Class and important variable names are informative.

        ◦ Objects that are dynamically allocated using new are later deleted and pointers are set
        to NULL when they do not point to valid memory locations.

        ◦ Comments are included to describe the intent of each public member function in every class.

        ◦ Additional comments are included in areas where the intent of the code is not obvious
        from reading the code itself and where future programmers would encounter a special case or
        unusual aspect of the code that they would find surprising.

        ◦ The tests show evidence of thinking about aspects of the design that are “worth testing”
        (e.g., boundary conditions, areas of change).

For more information about google style, visit [Google Style Guide](https://google.github.io/styleguide/cppguide.html)



## [Common Tasks](src/task.md)
This page is aimed to give you some ideas of adding a new tool or a new filters to the application.

#### Tools&Filters Design and Development
1. Go to the PROJ/src/imagetools, adding the filter or tools with both .h and .cc files
2. Your filter or tools should inherit the parent filter or tool class
3. Follow the same structure of develop existing filters and tools, design your own tools
4. Add your new tools to the imagetools and also in your FlashPhoto.
5. Follow the same structure of existing apply functions, write the new apply functions to your own filters or tools.
6. If you want your Mia application have the your new stuff, add new commands processing functions to the Mia Command Line class and Command Processor class.
7. Debug and writing unit tests and integration tests for your own filter or tools.More information about testing, [click here](src/test.md)


Finally, you will see them work on your applications :)


#### [Testing](src/test.md)
```bash
## Testing
For testing, first, we used the CSE-check-style tests which have developed by the Computer Science Department, University of Minnesota, Twin Cities. So, our codes satisfied the google coding style after doing the first tests.
Then, to test all the filters and the tools we implemented, I wrote few integration tests
 to ensure the correctness of all those features. Apart from the integration test,
 I wrote a few unit tests for Mia’s command line mode.

### Overall structure:
    • Implement your tests using Google Test and by adding files to the tests directory, as we have been practicing so far.

    • Running “make all” inside the tests directory should run all the tests.


### Unit tests:
    • Write a series of unit tests to thoroughly test your command line parsing.

    • Test to make sure that you command line parsing routines generate the expected command list for valid command lines.

    • Test to make sure you catch errors in the command line so that you can respond by printing out a help message.

    • The other tests cover:

        ◦ Testing to make sure you detect an invalid command line for common errors or typos that users
        might make, such as forgetting to include the input or output file or leaving off an argument
        for commands that require arguments.


        ◦ Testing to make sure you calculate the correct set of image processing commands to run for
        valid command lines that list 0, 1, or multiple image processing commands.


### Regression tests:

• For regression tests, the goal is to verify that features that worked once stay working, even as you continue to add to the code.

• For a library that involves manipulating images, this means that once we have the blur filter working, we should expect
 that if we run blur with radius=5.0 on Monday on an image, test-input.png, and save the result to blur-5.0-monday.png and then on Wednesday we run blur with radius=5.0 on the same test-input.png and save the result to blur-5.0-wednesday.png, we should
 see that the two resulting images are exactly the same (i.e., each pixel in blur-5.0-monday.png is exactly the same color as the corresponding pixel in blur-5.0-wednesday.png).

• To use this testing strategy with Google Test, you should add a PROJ/resources directory to your repo where you can
store images.  Then add some PROJ/resources/test-input.png that you can use as a consistent test input image.  Then,
for each feature you wish to test, you need to create and save an expected output image to treat as the “ground truth”.  
You can come up with your own naming scheme for these, for example, you might store the ground truth for a blur filter
with radius=5 as: PROJ/resources/blur-5-expected.png or blur-5-output.png or blur-5-truth.png.  
Finally, after this initialization, you can go ahead and write your tests.  Each test should load
 PROJ/resources/test-input.png into a pixel buffer, apply the feature you want to test, then load the
 corresponding expected output (e.g., PROJ/resources/blur-5-expected.png) into a second pixel buffer and
 compare the two pixel buffers (note that PixelBuffer has an overloaded == operator) to see if they are equal.

• You should test all of your filters and all of your tools using this strategy.  For the tools, note that you can “fake” user input from the mouse by calling StartStroke(), AddToStroke(), and EndStroke() directly from your testing code.
```
