//
// Created by hiotareq on 09.04.2021.
//

#ifndef STRIP_PACKING_PROBLEM_PLATE_H
#define STRIP_PACKING_PROBLEM_PLATE_H

#include "rectangle.h"
#include <map>
#include <vector>

class plate {
private:
    double plate_width;
    int number_of_rectangles;
    std::vector<Rectangle> rectangles;
    double S;
public:
    explicit plate(double, int, std::vector<Rectangle>&);

    //recursive function for filling a segment, returns value of a segment
    double RSegment(double, double, double, double, std::vector<int>&, std::vector<int>&, int);

    //recursive function for filling a block, returns the value of a block
    double RBlock(double, double, double, double, std::vector<int>&, std::vector<int>&, int);

    int GetNumberOfRectangles() const;
};


#endif //STRIP_PACKING_PROBLEM_PLATE_H
