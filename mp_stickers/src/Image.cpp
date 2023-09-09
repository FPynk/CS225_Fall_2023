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

// Desaturates an Image by decreasing the saturation of every pixel by amount.
// This function ensures that the saturation remains in the range [0, 1].
void Image::desaturate(double amount) {

}

void Image::grayscale() {

}

void Image::rotateColor(double degrees) {

}

void Image::illinify() {

}

void Image::scale(double factor) {
     
}

void Image::scale(unsigned w, unsigned h) {

}