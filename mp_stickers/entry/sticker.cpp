#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
    Image alma;
    alma.readFromFile("../data/alma.png");
    StickerSheet test = StickerSheet(alma, 5);
    StickerSheet test2 = StickerSheet(alma, 5);
    test2 = test;

  return 0;
}
