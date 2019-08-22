## Project Directory

This is the project directory for flashphoto.

Main page
=============
Welcome to the CSCI3081W project main page!


For information, select the following sub pages
----------------
1. If you are an user, click
[User information page](src/user.md)
    - [FlashPhoto](src/flash.md)

    - [Medical Image Analysis(mia)](src/mia.md)


2. If you are a developer, click
[Developer information page](src/developer.md)
    - [Programming Reference](src/ref.md)

    - [Highlevel Design](src/uml.md)

    - [Coding Style](src/coding.md)

    - [Common Tasks](src/task.md)

    - [Testing](src/test.md)


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


Coding Style
=============
Welcome to the CSCI3081W project coding style main page!


## Coding style
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


FlashPhoto Information Page
=============
Welcome to the FlashPhoto information page!

# Abstract
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
