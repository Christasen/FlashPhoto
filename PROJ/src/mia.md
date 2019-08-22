Mia Information Page
=============
Welcome to the Mia information page!

# Abstract
Medical Image Analysis(Mia) is an application that could be used for interpreting medical images. We offered few tools and filters in the application for you to edit your images. We offered two modes for you to use our app.

![Mia Interface](pics/mia.png)
## Loading and Editing Images

### Graphical Mode:
You can simply click on the load file button on the software to load a file. There will be several tool and filter buttons for you to choose to edit your image.

    • A stamp tool that is hardcoded to stamp a bullseye pattern, one circle inside another, that clinicians can use to mark important areas on the image.

    • A pen tool, also useful for annotating images (e.g., circling a break in a bone).

    • A subset of the filters you have implemented previously that would be useful for medical imaging (blur, sharpen, edge detect, threshold, quantize).

    • File Open/Save controls.





### Command Line Mode
There's a command mode in this application. You can do the following commands in your terminal to edit your files.

#### Commands details:
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
