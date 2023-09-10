#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base_ = new Image(picture);
    max_ = max;
    stickers_.resize(max, nullptr);
    xCords.resize(max, 0);
    yCords.resize(max, 0);
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    StickerSheet::clear();
    StickerSheet::_copy(other);
}
const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {

}
void StickerSheet::changeMaxStickers(unsigned max) {

}
int StickerSheet::addSticker(Image& sticker, int x, int y) {

}
int StickerSheet::setStickerAtLayer(Image &sticker, int x, int y) {

}
bool StickerSheet::translate(unsigned index, int x, int y) {

}
void StickerSheet::removeSticker (unsigned index) {

}
Image* StickerSheet::getSticker(unsigned index) {

}
int StickerSheet::layers() const {

}
Image StickerSheet::render() const {

}

StickerSheet::~StickerSheet() {
    StickerSheet::clear();
}

void StickerSheet::clear() {
    delete base_;
    for (int i = 0; i < max; i++) {
        delete stickers_[i];
    }
    stickers_.clear();
    xCords_.clear();
    yCords_.clear();
}

void StickerSheet::_copy(PNG const & other) {
    base_ = other.base_;
    max_ = other.max_;
    stickers_.resize(max_, nullptr);
    for (int i = 0; i < other.max; i++) {
        stickers_[i] = new Image(&other.stickers_[i]);
    }
    xCords_ = other.xCords_;
    yCords_ = other.yCords_;
}