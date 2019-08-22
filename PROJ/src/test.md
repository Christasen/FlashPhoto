Testing
=============
Welcome to the CSCI3081W project testing information page!


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
