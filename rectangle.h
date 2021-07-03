//
// Created by hiotareq on 09.04.2021.
//

#ifndef STRIP_PACKING_PROBLEM_RECTANGLE_H
#define STRIP_PACKING_PROBLEM_RECTANGLE_H

#include <vector>

class Rectangle {
private:
    double length{};
    double width{};
public:
    Rectangle(double width, double length);

    Rectangle();

    double GetLength() const;

    double GetWidth() const;

    double GetArea() const;

    void Rotate();

    /*cut-functions take one rectangle and return two rectangles to replace first
     * positions' bounds are from 0 to old_rectangle's max length/width
     */
    std::vector<Rectangle> cut_vertically(double horizontal_position) const;

    std::vector<Rectangle> cut_horizontally(double vertical_position) const;


};
    /*
     * function-generator for unconstrained rectangles
     * with this generator we know minimal length of set of rectangles
     */
std::vector<Rectangle> unconstrained_rectangles_generator(unsigned int n, const Rectangle& given);


#endif //STRIP_PACKING_PROBLEM_RECTANGLE_H
