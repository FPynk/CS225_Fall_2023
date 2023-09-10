#include "StickerSheet.h"

StickerSheet(const Image &picture, unsigned max) {
    base_ = new Image(picture);
    max_ = max;
    stickers_.resize(max, nullptr);
    xCords.resize(max, 0);
    yCords.resize(max, 0);
}

StickerSheet(const StickerSheet &other) {

}
const StickerSheet& operator=(const StickerSheet &other) {

}
void changeMaxStickers(unsigned max) {

}
int addSticker(Image& sticker, int x, int y) {

}
int setStickerAtLayer(Image &sticker, int x, int y) {

}
bool translate(unsigned index, int x, int y) {

}
void 	removeSticker (unsigned index) {

}
Image* getSticker(unsigned index) {

}
int layers() const {

}
Image render() const {

}