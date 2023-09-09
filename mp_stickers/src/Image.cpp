#include "Image.h"
using namespace cs225;

Image::Image() {
    PNG();
}

Image::Image(unsigned int width, unsigned int height) {
    PNG(width, height);
}

void Image::lighten() {
    // Cycle thru each pixel
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            // Increase pixel luminance by 0.1
            if (PNG::getPixel(col, row).l + 0.1 <= 1.0) {
                PNG::getPixel(col, row).l += 0.1;
            } else {
                PNG::getPixel(col, row).l = 1;
            }
        }
    }
}

void Image::lighten(double amount) {
    // Cycle thru each pixel
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    //std::cout << "Width: " << width << " Height: " << height << std::endl;
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            //std::cout << "col " << col << std::endl;
            // Increase pixel luminance by 0.1
            if (PNG::getPixel(col, row).l + amount <= 1.0) {
                PNG::getPixel(col, row).l += amount;
            } else {
                PNG::getPixel(col, row).l = 1;
            }
        }
    }
}

void Image::darken() {
    // Cycle thru each pixel
    // decrease pixel luminance by 0.1
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            if (PNG::getPixel(col, row).l - 0.1 >= 0.0) {
                PNG::getPixel(col, row).l -= 0.1;
            } else {
                PNG::getPixel(col, row).l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    // Cycle thru each pixel
    // decrease pixel luminance by 0.1
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            if (PNG::getPixel(col, row).l - amount >= 0.0) {
                PNG::getPixel(col, row).l -= amount;
            }  else {
                PNG::getPixel(col, row).l = 0;
            }
        }
    }
}



// Saturates an Image by increasing the saturation of every pixel by 0.1.
// This function ensures that the saturation remains in the range [0, 1].

void Image::saturate() {
    // Cycle thru each pixel
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            // Increase pixel saturation by 0.1
            if (PNG::getPixel(col, row).s + 0.1 <= 1.0) {
                PNG::getPixel(col, row).s += 0.1;
            } else {
                PNG::getPixel(col, row).s = 1;
            }
        }
    }
}

// Saturates an Image by increasing the saturation of every pixel by amount
// This function ensures that the saturation remains in the range [0, 1].

void Image::saturate(double amount) {
    // Cycle thru each pixel
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            // Increase pixel saturation by amount
            if (PNG::getPixel(col, row).s + amount <= 1.0) {
                PNG::getPixel(col, row).s += amount;
            } else {
                PNG::getPixel(col, row).s = 1;
            }
        }
    }
}



// Desaturates an Image by decreasing the saturation of every pixel by 0.1.
// This function ensures that the saturation remains in the range [0, 1].

void Image::desaturate() {
    // Cycle thru each pixel
    // decrease pixel saturation by 0.1
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            if (PNG::getPixel(col, row).s - 0.1 >= 0.0) {
                PNG::getPixel(col, row).s -= 0.1;
            } else {
                PNG::getPixel(col, row).s = 0;
            }
        }
    }
}

// Desaturates an Image by decreasing the saturation of every pixel by amount.
// This function ensures that the saturation remains in the range [0, 1].
void Image::desaturate(double amount) {
    // Cycle thru each pixel
    // decrease pixel saturation by 0.1
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            if (PNG::getPixel(col, row).s - amount >= 0.0) {
                PNG::getPixel(col, row).s -= amount;
            } else {
                PNG::getPixel(col, row).s = 0;
            }
        }
    }
}

// Turns the image grayscale. 
void Image::grayscale() {

}

// Rotates the color wheel by degrees.
// Rotating in a positive direction increases the degree of the hue. This function ensures that the hue remains in the range [0, 360].
void Image::rotateColor(double degrees) {

}

// Illinify the image. 
void Image::illinify() {

}

// Scale the Image by a given factor.

// For example:
//     A factor of 1.0 does not change the image.
//     A factor of 0.5 results in an image with half the width and half the height.
//     A factor of 2 results in an image with twice the width and twice the height.
// This function both resizes the Image and scales the contents.

void Image::scale(double factor) {
     
}

// Scales the image to fit within the size (w x h).
// This function preserves the aspect ratio of the image, so the result will always be an image of width w or of height h (not necessarily both).
// For example, if the Image is currently (10, 20) and we want to scale to (100, 100), then this should scale the Image to (50, 100). Note that scaling the image to (100, 200) does not fit within the (100,100) dimensions given and is therefore incorrect.
// This function both resizes the Image and scales the contents.

void Image::scale(unsigned w, unsigned h) {

}