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

// Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices.
// If the new maximum number of stickers is smaller than the current number number of stickers, the stickers with indices above max - 1 will be lost.
void StickerSheet::changeMaxStickers(unsigned max) {
    if (max < max_) {
        // Delete excess stickers
        for (unsigned int i = max; i < max_; i++) {
            delete stickers_[i];
            stickers_[i] = nullptr;
        }
        stickers_.resize(max_);
        xCords_.resize(max_);
        yCords_.resize(max_);
    } else {
        // resize
        max_ = max;
        stickers_.resize(max_);
        xCords_.resize(max_);
        yCords_.resize(max_);
    }
}

// Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
// The sticker must be added to the lowest possible layer available.
// If all available layers have been filled, a new layer must be added above all existing layers.

int StickerSheet::addSticker(Image& sticker, int x, int y) {
    // Flag
    bool max_reached = true;
    int layer = 0;
    // Cycle through stickers_, add at lowest possible empty spot
    for (unsigned int i = 0; i < max_; i++) {
        if (stickers_[i] == nullptr) {
            stickers_[i] = new Image(sticker);
            xCords_[i] = x;
            yCords_[i] = y;
            max_reached = false;
            layer = i;
        }
    }
    // if max_ reached, resize
    if (max_reached) {
        stickers_.resize(max_ + 1);
        xCords_.resize(max_ + 1);
        yCords_.resize(max_ + 1);
        stickers_[max_] = new Image(sticker);
        xCords_[max_] = x;
        yCords_[max_] = y;
        layer = max_;
        max_ += 1;
    }
    return layer;
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