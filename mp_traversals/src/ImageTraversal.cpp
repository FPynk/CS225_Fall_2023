#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
    /**
    * Calculates a metric for the difference between two pixels, used to
    * calculate if a pixel is within a tolerance.
    *
    * @param p1 First pixel
    * @param p2 Second pixel
    * @return the difference between two HSLAPixels
    */
    double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
        double h = fabs(p1.h - p2.h);
        double s = p1.s - p2.s;
        double l = p1.l - p2.l;

        // Handle the case where we found the bigger angle between two hues:
        if (h > 180) { h = 360 - h; }
        h /= 360;

        return sqrt((h*h) + (s*s) + (l*l));
    }
    
    void printSet(std::set<Point> set) {
        std::cout << "Visited_: " << std::endl;
        for (const auto& elem : set) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    /**
    * Adds a Point for the bfs traversal to visit at some point in the future.
    * @param work_list the deque storing a list of points to be processed
    * @param point the point to be added
    */
    void bfs_add(std::deque<Point> & work_list, const Point & point) {
        /** @todo [Part 1] */
        // FIFO, explore oldest seen node
        work_list.push_back(point);
    }

    /**
    * Adds a Point for the dfs traversal to visit at some point in the future.
    * @param work_list the deque storing a list of points to be processed
    * @param point the point to be added
    */
    void dfs_add(std::deque<Point> & work_list, const Point & point) {
        /** @todo [Part 1] */
        // LIFO, explore most recently seen node
        work_list.push_back(point);
    }

    /**
    * Removes the current Point in the bfs traversal
    * @param work_list the deque storing a list of points to be processed
    */
    void bfs_pop(std::deque<Point> & work_list) {
        /** @todo [Part 1] */
        if (!work_list.empty()) {
            work_list.pop_front();
        }
    }

    /**
    * Removes the current Point in the dfs traversal
    * @param work_list the deque storing a list of points to be processed
    */
    void dfs_pop(std::deque<Point> & work_list) {
        /** @todo [Part 1] */
        if (!work_list.empty()) {
            work_list.pop_back();
        }
    }

    /**
    * Returns the current Point in the bfs traversal
    * @param work_list the deque storing a list of points to be processed
    * @return the current Point 
    */
    Point bfs_peek(std::deque<Point> & work_list) {
        /** @todo [Part 1] */
        return work_list.front();
    }

    /**
    * Returns the current Point in the dfs traversal
    * @param work_list the deque storing a list of points to be processed
    * @return the current Point 
    */
    Point dfs_peek(std::deque<Point> & work_list) {
        /** @todo [Part 1] */
        return work_list.back();
    }

    /**
    * Initializes a ImageTraversal on a given `png` image,
    * starting at `start`, and with a given `tolerance`.
    * @param png The image this traversal is going to traverse
    * @param start The start point of this traversal
    * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
    * it will not be included in this traversal
    * @param fns the set of functions describing a traversal's operation
    */
    ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns) 
    : png_(png), start_(start), tolerance(tolerance), fns_(fns) {
        /** @todo [Part 1] */
    }

    /**
    * Returns an iterator for the traversal starting at the first point.
    */
    ImageTraversal::Iterator ImageTraversal::begin() {
        /** @todo [Part 1] */
        return ImageTraversal::Iterator(this, false);
    }

    /**
    * Returns an iterator for the traversal one past the end of the traversal.
    */
    ImageTraversal::Iterator ImageTraversal::end() {
        /** @todo [Part 1] */
        return ImageTraversal::Iterator(this, true);
    }

    /**
    * Default iterator constructor.
    */
    ImageTraversal::Iterator::Iterator()
        : traversal_(nullptr), end_(false) {
    /** @todo [Part 1] */
        std::cout << "Iterator def constructor called " << std::endl;
    }

    // constructor with args, end_ will provide sentinel value for if end
    ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, bool end)
        : traversal_(traversal), end_(end) {
            if (!end_ && traversal_) {
                work_list_.push_back(traversal_->start_);
            }
    }

    bool ImageTraversal::Iterator::isValid(const Point& point) {
        std::cout << "isValid Running for " << point << std::endl;
        // out of bounds
        if (point.x >= traversal_->png_.width() || point.y >= traversal_->png_.height()) {
            std::cout << "isValid: false due to OOB" << std::endl;
            return false;
        }
        // delta checking
        const HSLAPixel & startPix = traversal_->png_.getPixel(traversal_->start_.x, traversal_->start_.y);
        const HSLAPixel & currPix = traversal_->png_.getPixel(point.x, point.y);
        if (calculateDelta(startPix, currPix) > traversal_->tolerance) {
            std::cout << "isValid: false due to tolerance" << std::endl;
            return false;
        }
        // check if point visited
        if (traversal_->visited_.find(point) != traversal_->visited_.end()) {
            std::cout << "isValid: false due to visited" << std::endl;
            return false;
        }
        std::cout << "isValid: true" << std::endl;
        return true;
    }

    /**
    * Iterator increment operator.
    *
    * Advances the traversal of the image.
    */
    ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
        /** @todo [Part 1] */
        // if (work_list_.empty()) {
        //     std::cout << "Work list empty" << std::endl;
        //     traversal_ = nullptr;
        //     end_ = true;
        //     return *this;
        // }

        Point curr = traversal_->fns_.peek(work_list_);
        std::cout << "At: " << curr << std::endl;
        traversal_->fns_.pop(work_list_);
        // Add curr point to visited
        traversal_->visited_.insert(curr);

        // Get info on our neighbours
        std::vector<Point> neighbours = {
            Point(curr.x + 1, curr.y), // right
            Point(curr.x, curr.y + 1), // below
            Point(curr.x - 1, curr.y),  // left
            Point(curr.x, curr.y - 1) // above
        };
        // cycle thru all neighbours, check if in PNG
        for (Point neighbour : neighbours) {
            if (isValid(neighbour)) {
                std::cout << "Added " << neighbour << " to visit list" << std::endl;
                traversal_->visited_.insert(neighbour);
                printSet(traversal_->visited_);
                traversal_->fns_.add(work_list_, neighbour);
            }
        }
        if (work_list_.empty()) {
            std::cout << "Work list empty" << std::endl;
            traversal_ = nullptr;
            end_ = true;
            return *this;
        }
        return *this;
    }

    /**
    * Iterator accessor operator.
    *
    * Accesses the current Point in the ImageTraversal.
    */
    Point ImageTraversal::Iterator::operator*() {
        /** @todo [Part 1] */
        if (traversal_ && !work_list_.empty()) {
            return traversal_->fns_.peek(work_list_);
        }
        std::cout << "Attempted to deref empty iterator" << std::endl;
        return Point(0, 0);
    }

    /**
    * Iterator inequality operator.
    *
    * Determines if two iterators are not equal.
    */
    bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
        /** @todo [Part 1] */
        // checks if they are end iterators
        if (this->end_ || other.end_) {
            return this->end_ != other.end_;
        }
        // conduct check if empty
        if (this->work_list_.empty() || other.work_list_.empty()) {
            return this->work_list_.empty() != other.work_list_.empty();
        }

        // compare front element
        return this->work_list_ != other.work_list_;
    }

    /**
    * Iterator size function.
    *
    * @return size_t the size of the iterator work queue.
    */
    size_t ImageTraversal::Iterator::size() const {
        return work_list_.size();
    }

    /**
    * Iterator empty function.
    *
    * @return bool whether the iterator work queue is empty.
    */
    bool ImageTraversal::Iterator::empty() const {
        return work_list_.empty();
    }

}