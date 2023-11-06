#include "maze.h"
#include <ctime>

SquareMaze::SquareMaze() : width_(0), height_(0) {
    // empty constructor
}

void SquareMaze::makeMaze(int width, int height) {
    // initialising
    width_ = width;
    height_ = height;
    int total_cells = width * height;
    maze_ = std::vector<Cell>(total_cells);
    ds_ = DisjointSets();
    ds_.addelements(total_cells);

    // Seed random number gen with current time
    std::srand(std::time(nullptr));
    // Keep track of wall removed
    int removed_walls = 0;

    // removing n-1 walls should connect all cells without cycles
    while (removed_walls < total_cells - 1) {
        // randomly select a cell to remove a random wall
        int cell_idx = rand() % total_cells;
        // right = 1, down = 0
        int wall_idx = rand() % 2;
        // idx to keep track of adjacent cell
        int adj_idx; 

        // Boundary checking for width then height
        if (wall_idx == 1 && (cell_idx % width) < (width - 1)) {
            // right wall can be removed
            adj_idx = cell_idx + 1;
        } else if (wall_idx == 0 && (cell_idx / width) < (height - 1)) {
            // down wall can be removed
            adj_idx = cell_idx + width;
        } else {
            // OOB, skip
            continue;
        }

        // Check if cells are connected, also takes into account if wall is aleady removed
        if (ds_.find(cell_idx) != ds_.find(adj_idx)) {
            // if not, remove and union to keep track of paths
            if (wall_idx == 1) {
                maze_[cell_idx].rightWall = false;
            } else {
                maze_[cell_idx].downWall = false;
            }
            ds_.setunion(cell_idx, adj_idx);
            removed_walls++;
        }

    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    // Calculate index in our 2D maze
    int idx = y * width_ + x;
    // Switch case for dir
    // for all check bounds and check wall
    switch (dir) {
        // right
        case 0:
            return x < width_ - 1 && !maze_[idx].rightWall;
        // down
        case 1:
            return y < height_ - 1 && !maze_[idx].downWall;
        // left
        case 2:
            return x > 0 && !maze_[idx - 1]. rightWall;
        // up
        case 3:
            int above_idx = (y-1) * width_ + x;
            return y > 0 && !maze_[above_idx].downWall;
        default:
            std::cout << "Invalid dir input for canTravel" << std::endl;
            return false;
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    // idx calc
    int idx = y * width_ + x;

    // wall setting
    if (dir == 0) {
        // right wall
        maze_[idx].rightWall = exists;
    } else if (dir == 1) {
        // down wall
        maze_[idx].downWall = exists;
    } else {
        std::cout << "Invalid dir input to setWall" << std::endl;
    }
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