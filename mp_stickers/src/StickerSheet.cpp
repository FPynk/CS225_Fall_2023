#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base_ = new Image(picture);
    max_ = max;
    stickers_.resize(max, nullptr);
    xCords_.resize(max, 0);
    yCords_.resize(max, 0);
    std::cout << "StickerSheet with max_ = " << max_ << std::endl;
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
    if (max < 0) {
        for (unsigned int i = 0; i < max_; i++) {
            delete stickers_[i];
            stickers_[i] = nullptr;
        }
        stickers_.resize(0);
        xCords_.resize(0);
        yCords_.resize(0);
        max_ = 0;
    } else if (max < max_) {
        // Delete excess stickers
        for (unsigned int i = max; i < max_; i++) {
            delete stickers_[i];
            stickers_[i] = nullptr;
        }
        max_ = max;
        stickers_.resize(max_);
        xCords_.resize(max_);
        yCords_.resize(max_);
    } else {
        std::cout << "Adding " << max - max_ << " layers" << std::endl;
        // resize
        max_ = max;
        stickers_.resize(max_, nullptr);
        xCords_.resize(max_, 0);
        yCords_.resize(max_, 0);
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
            break;
        }
    }
    // if max_ reached, resize
    if (max_reached) {
        std::cout << "Max Stickers reached, resizing" << std::endl;
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
    if (layer >= max_ || layer < 0) { return -1; }
    delete stickers_[layer];
    stickers_[layer] = new Image(sticker);
    xCords_[layer] = x;
    yCords_[layer] = y;
    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (index >= max_ || index < 0 || stickers_[index] == nullptr) { return false; }
    xCords_[index] = x;
    yCords_[index] = y;
    return true;
}

void StickerSheet::removeSticker (unsigned index) {
    if (index >= max_ || index < 0) { 
        std::cout << "invalid index" << std::endl;
        return; 
    }
    delete stickers_[index];
    stickers_[index] = nullptr;
    xCords_[index] = 0;
    yCords_[index] = 0;
}

// Returns a pointer to the sticker at the specified index, not a copy of it.
// That way, the user can modify the Image.
// If the index is invalid, return NULL.
Image* StickerSheet::getSticker(unsigned index) {
    if (index >= max_ || index < 0) { return NULL; }
    return stickers_[index];
}

int StickerSheet::layers() const {
    int count = 0;
    for (unsigned int i = 0; i < max_; i++) {
        if (stickers_[i] == nullptr) {
            count++;
        }
    }
    return count;
}

Image StickerSheet::render() const {
    // Check if sticker is out of bounds of image, resize output accordingly
    // paint sticker onto image
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