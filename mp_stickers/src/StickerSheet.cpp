#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base_ = new Image(picture);
    max_ = max;
    stickers_.resize(max, nullptr);
    xCords_.resize(max, 0);
    yCords_.resize(max, 0);
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    StickerSheet::clear();
    StickerSheet::_copy(other);
}
const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    if (this != &other) {
        StickerSheet::clear();
        StickerSheet::_copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
}
int StickerSheet::addSticker(Image& sticker, int x, int y) {
    return 0;
}
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    return 0;
}
bool StickerSheet::translate(unsigned index, int x, int y) {
    return false;
}
void StickerSheet::removeSticker (unsigned index) {

}
Image* StickerSheet::getSticker(unsigned index) {
    return nullptr;
}
int StickerSheet::layers() const {
    return 0;
}
Image StickerSheet::render() const {
    return *base_;
}

StickerSheet::~StickerSheet() {
    StickerSheet::clear();
}

void StickerSheet::clear() {
    delete base_;
    base_ = nullptr;
    for (unsigned int i = 0; i < max_; i++) {
        delete stickers_[i];
        stickers_[i] = nullptr;
    }
    stickers_.clear();
    xCords_.clear();
    yCords_.clear();
}

void StickerSheet::_copy(StickerSheet const & other) {
    base_ = new Image(*other.base_);
    max_ = other.max_;
    stickers_.resize(max_, nullptr);
    for (unsigned int i = 0; i < other.max_; i++) {
        if (other.stickers_[i] != nullptr) {
            stickers_[i] = new Image(*other.stickers_[i]);
        } else {
            stickers_[i] = nullptr;
        } 
    }
    xCords_ = other.xCords_;
    yCords_ = other.yCords_;
}