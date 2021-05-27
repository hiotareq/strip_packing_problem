//
// Created by hiotareq on 09.04.2021.
//

#ifndef STRIP_PACKING_PROBLEM_RECTANGLE_H
#define STRIP_PACKING_PROBLEM_RECTANGLE_H

class Rectangle {
private:
    double length;
    double width;
public:
    Rectangle(double width, double length);
    double GetLength() const;
    double GetWidth() const;
    double GetArea() const;
    void Rotate();
};


#endif //STRIP_PACKING_PROBLEM_RECTANGLE_H
