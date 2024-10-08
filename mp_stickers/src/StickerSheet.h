/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include <vector>

class StickerSheet {
    public:
        StickerSheet(const Image &picture, unsigned max);
        StickerSheet(const StickerSheet &other);
        const StickerSheet& operator=(const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image& sticker, int x, int y);
        int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
        bool translate(unsigned index, int x, int y);
        void removeSticker (unsigned index);
        Image* getSticker(unsigned index);
        int layers() const;
        Image render() const;
        ~StickerSheet();
    private:
        void _copy(StickerSheet const & other);
        void clear();
        Image* base_;
        std::vector<Image*> stickers_;
        unsigned int max_;
        std::vector<unsigned int> xCords_;
        std::vector<unsigned int> yCords_;
};