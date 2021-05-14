//
// Created by hiotareq on 09.04.2021.
//

#include "rectangle.h"

Rectangle::Rectangle(double _width, double _length): width(_width), length(_length) {}

double Rectangle::GetLength() const {
    return length;
}

double Rectangle::GetWidth() const {
    return width;
}

double Rectangle::GetArea() const {
    return length * width;
}

void Rectangle::Rotate() {
    double temp = length;
    length = width;
    width = temp;
}


