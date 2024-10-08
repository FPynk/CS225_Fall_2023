#include "maze.h"
#include <ctime>
#include <queue>
#include <algorithm>
#include <chrono>

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
    std::srand(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
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
    int above_idx = (y-1) * width_ + x;
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
            return y > 0 && !maze_[above_idx].downWall;
        default:
            std::cout << "Invalid dir input for canTravel" << std::endl;
            return false;
    }
}

int SquareMaze::nextCell(int x, int y, int dir) const {
    // Assume Can travel, will not check
    // Calculate index in our 2D maze
    int idx = y * width_ + x;
    // Switch case for dir
    switch (dir) {
        // right
        case 0:
            return y * width_ + x + 1;
        // down
        case 1:
            return (y + 1) * width_ + x;
        // left
        case 2:
            return y * width_ + x - 1;
        // up
        case 3:
            return (y - 1) * width_ + x;
        default:
            std::cout << "Invalid dir input for canTravel" << std::endl;
            return -1;
    }
}

int SquareMaze::prevCell(int x, int y, int dir) const {
    // Assume Can travel, will not check
    // Calculate index in our 2D maze
    int idx = y * width_ + x;
    // Switch case for dir
    switch (dir) {
        // right
        case 0:
            return y * width_ + x - 1;
        // down
        case 1:
            return (y - 1) * width_ + x;
        // left
        case 2:
            return y * width_ + x + 1;
        // up
        case 3:
            return (y + 1) * width_ + x;
        default:
            std::cout << "Invalid dir input for canTravel" << std::endl;
            return -1;
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
    // vectors to keep track of distances and previous dirs
    // set to invalid value -1
    std::vector<int> dist_vec = std::vector<int>(width_ * height_, -1);
    std::vector<int> prev_dir_vec = std::vector<int>(width_ * height_, -1);
    // queue for bfs taversal, stores our 2D coordinates
    std::queue<int> q;
    // 0: right 1: down 2: left 3: up
    std::vector<int> dirs = {0, 1, 2, 3};
    // Start from 0,0 cell
    q.push(0);
    dist_vec[0] = 0;

    // while q not empty
    while (!q.empty()) {
        int cell = q.front();
        q.pop();
        // Calc current x and y
        int x = cell % width_;
        int y = cell / width_;

        // check all dir if can move
        for (int dir : dirs) {
            // Check backtracking and check canTravel
            if (canTravel(x, y, dir)) {
                int next_cell = nextCell(x, y, dir);
                // check next cell has not been visited
                if (prev_dir_vec[next_cell] == -1) {
                    // push to queue
                    q.push(next_cell);
                    // update prev dir
                    prev_dir_vec[next_cell] = dir;
                    // update dist
                    dist_vec[next_cell] = dist_vec[cell] + 1;
                }
            }
        }
    }

    // find destination cell 
    int dest = width_ * (height_ - 1);
    for (int last_row_cell = width_ * (height_ - 1);
         last_row_cell < width_ * height_;
         ++last_row_cell) {
        // check if last row cell has longer distance
        if (dist_vec[last_row_cell] > dist_vec[dest]) {
            dest = last_row_cell;
        }
    }

    // backtracking to find solution path;
    std::vector<int> path;
    // loop till reach 0,0
    while (dest != 0) {
        path.push_back(prev_dir_vec[dest]);
        int x = dest % width_;
        int y = dest / width_;
        dest = prevCell(x, y, prev_dir_vec[dest]);
    }

    // reverse path
    std::reverse(path.begin(), path.end());

    return path;
}

cs225::PNG* SquareMaze::drawMaze() const {
    cs225::PNG *mazeImage = new cs225::PNG(width_ * 10 + 1, height_ * 10 + 1);

    // blacken border top and left, except entrace to 9,0
    for (unsigned int i = 0; i < mazeImage->width(); ++i) {
        if (i < 1 || i > 9) {
            cs225::HSLAPixel &pix = mazeImage->getPixel(i, 0);
            pix.l = 0;
        }
    }
    for (unsigned int i = 0; i < mazeImage->height(); ++i) {
        cs225::HSLAPixel &pix = mazeImage->getPixel(0, i);
        pix.l = 0;
    }

    // check each cell and blacken correct walls
    for (int x = 0; x < width_; ++x) {
        for (int y = 0; y < height_; ++y) {
            int cell = y * width_ + x;
            // right wall
            if (maze_[cell].rightWall) {
                for (int i = 0; i <= 10; ++i) {
                    cs225::HSLAPixel &pix = mazeImage->getPixel((x + 1) * 10, y * 10 + i);
                    pix.l = 0; 
                }
            }
            // down wall
            if (maze_[cell].downWall) {
                for (int i = 0; i <= 10; ++i) {
                    cs225::HSLAPixel &pix = mazeImage->getPixel(x * 10 + i, (y + 1)* 10);
                    pix.l = 0;
                }
            }
        }
    }

    return mazeImage;
}

cs225::PNG* SquareMaze::drawMazeWithSolution() {
    // draw maze w/o sol
    cs225::PNG* mazeImage = drawMaze();
    //std::cout << "Dimensions: " << mazeImage->width() << "X" << mazeImage->height() << std::endl;

    // get solution
    std::vector<int> sol_vec = solveMaze();
    //std::cout << "Before Path colouring" << std::endl;
    // pix starting pt for sol path
    int x = 5;
    int y = 5;
    // colour for sol path
    cs225::HSLAPixel red = cs225::HSLAPixel(0, 1, 0.5, 1);
    // colour first pix
    cs225::HSLAPixel &pix = mazeImage->getPixel(x, y);
    pix = red;
    //std::cout << " path length: " << sol_vec.size() << std::endl;
    for (unsigned int i = 0; i < sol_vec.size(); ++i) {
        //std::cout << "x: " << x << " y: " << y << " dir: " << sol_vec[i] << " i: " << i <<std::endl;
        // outline path
        for (int j = 0; j < 10; ++j) {
            if (sol_vec[i] == 0) {
                x += 1;
            } else if (sol_vec[i] == 1) {
                y += 1;
            } else if (sol_vec[i] == 2) {
                x -= 1;
            } else if (sol_vec[i] == 3) {
                y -= 1;
            }
            cs225::HSLAPixel &pix = mazeImage->getPixel(x, y);
            pix = red;
        }
    }
    //std::cout << "Before whitening" << std::endl;
    // calc exit position based on the last direction
    int exit_x = x / 10;
    int exit_y = y / 10;

    // Whiten the exit bottom wall
    for (int i = 1; i < 10; i++) {
        cs225::HSLAPixel & pixel = mazeImage->getPixel(exit_x * 10 + i, (exit_y + 1) * 10);
        pixel.l = 1;
    }
    
    return mazeImage;
}

