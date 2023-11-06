#include "maze.h"

SquareMaze::SquareMaze() : width_(0), height_(0) {
    // empty constructor
}

void SquareMaze::makeMaze(int width, int height) : width_(width), height_(height) {
    
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {

}

std::vector<int> SquareMaze::solveMaze() {
    return std::vector<int>();
}

cs225::PNG* SquareMaze::drawMaze() const {
    return nullptr;
}

cs225::PNG* SquareMaze::drawMazeWithSolution() {
    return nullptr;
}