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
            HSLAPixel pix = PNG::getPixel(row, col);
            pix.l -= 0.1;
        }
    }
}

void Image::lighten(double amount) {
    // Cycle thru each pixel
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            // Increase pixel luminance by 0.1
            HSLAPixel pix = PNG::getPixel(row, col);
            pix.l -= amount;
        }
    }
}
void Image::darker() {
    // Cycle thru each pixel
    // decrease pixel luminance by 0.1
}

void Image::darken(double amount) {

}
void Image::saturate() {

}
void Image::saturate(double amount) {

}
void Image::desaturate() {

}
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