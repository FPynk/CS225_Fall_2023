/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    if (theTiles.size() == 0) {
        std::cout << "empty theTiles" << std::endl;
    }
    if (theSource.getRows() == 0 || theSource.getColumns() == 0) {
        std::cout << "empty theSource" << std::endl;
    }
    // Output of MosaicCanvas*
    MosaicCanvas* output = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    // Convert vector of tileimages to vector of points
    vector<Point<3>> thePoints;
    for (TileImage TI : theTiles) {
        LUVAPixel colour = TI.getAverageColor();
        Point<3> point =  convertToXYZ(colour);
        thePoints.push_back(point);
    }
    // construct kd tree of points
    KDTree<3> point_tree = KDTree(thePoints);

    // Go through SourceImage and match to closest TileImage
    for (int row = 0; row < theSource.getRows(); row++) {
        for (int col = 0; col < theSource.getColumns(); col++) {
            // convert theSource luva into a point
            LUVAPixel colour = theSource.getRegionColor(row, col);
            Point<3> point =  convertToXYZ(colour);
            
            // Finding closest TileImage using find nearest neighbour
            Point<3> closest_point =  point_tree.findNearestNeighbor(point);
            auto it = find(thePoints.begin(), thePoints.end(), closest_point);
            int pos = distance(thePoints.begin(), it);
            TileImage closest_tile = theTiles[pos];

            // set tile in mosaic
            output->setTile(row, col, &closest_tile);
        }
    }
    return output;
}

