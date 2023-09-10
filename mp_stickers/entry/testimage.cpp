#include "Image.h"

#include <iostream>

int main() {
  Image alma;
  // Image test = Image(100,100);
  std::cout << "Success" << std::endl;

  std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.lighten(0.2);
  alma.writeToFile("lighten.png");

  std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.saturate(0.2);
  alma.writeToFile("saturate.png");

  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.scale(2);
  alma.writeToFile("scale2x.png");

  // alma.scale(100,100);
  // alma.writeToFile("scale100pix.png");
  // alma.scale(1000, 1000);
  // alma.writeToFile("scale1000pix.png");

  std::cout << "Using Image::grayscale to create `grayscale.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.grayscale();
  alma.writeToFile("grayscale.png");

    std::cout << "Using Image::rotateColor to create `rotate.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.rotateColor(100);
  alma.writeToFile("rotateColor.png");

  return 0;
}
