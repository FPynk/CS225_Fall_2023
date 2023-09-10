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
    // StickerSheet test2 = StickerSheet(alma, 5);
    // test2 = test;

    // Image sticker;
    // sticker.readFromFile("../data/i.png");
    // std::cout << "layers " << test.layers() << std::endl;
    // test.addSticker(sticker, 0, 0);
    // std::cout << "layers " << test.layers() << std::endl;
    // test.addSticker(sticker, 0, 0);
    // std::cout << "layers " << test.layers() << std::endl;
    // test.addSticker(sticker, 0, 0);
    // std::cout << "layers " << test.layers() << std::endl;
    // test.addSticker(sticker, 0, 0);
    // std::cout << "layers " << test.layers() << std::endl;
    // test.addSticker(sticker, 0, 0);
    // std::cout << "layers " << test.layers() << std::endl;
    // test.addSticker(sticker, 0, 0);
    // std::cout << "layers " << test.layers() << std::endl;
    // test.changeMaxStickers(7);
    // std::cout << "layers " << test.layers() << std::endl;
    // test.addSticker(sticker, 0, 0);
    // std::cout << "layers " << test.layers() << std::endl;
    // test.changeMaxStickers(3);
    // test.removeSticker(3);
    // test.removeSticker(2);
    // test.removeSticker(0);
    // test.removeSticker(-1);
    test.render();

  return 0;
}
