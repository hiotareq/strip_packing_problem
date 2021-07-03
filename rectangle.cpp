//
// Created by hiotareq on 09.04.2021.
//

#include "rectangle.h"
#include <random>

Rectangle::Rectangle(double _width, double _length): width(_width), length(_length) {}

Rectangle::Rectangle(): Rectangle(0,0) {}

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

std::vector<Rectangle> Rectangle::cut_vertically(double horizontal_position) const{
    std::vector<Rectangle> new_rectangles(2);
    new_rectangles[0] = Rectangle(horizontal_position, GetWidth());
    new_rectangles[1] = Rectangle(GetLength() - horizontal_position, GetWidth());
    return new_rectangles;
}

std::vector<Rectangle> Rectangle::cut_horizontally(double vertical_position) const{
    std::vector<Rectangle> new_rectangles(2);
    new_rectangles[0] = Rectangle(GetLength(), vertical_position);
    new_rectangles[1] = Rectangle(GetLength(), GetWidth() - vertical_position);
    return new_rectangles;
}

std::vector<Rectangle> unconstrained_rectangles_generator(unsigned int n, const Rectangle& given) {
    int counter = 0;
    std::vector<Rectangle> output_rectangles(1);
    output_rectangles[0] = given;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dist(0, counter);
    std::uniform_int_distribution<int> cut(0,1);
    while(counter !=  (n-1)){
        int rectangle_number = dist(gen);
        int cut_way = cut(gen);
        if(cut_way == 1){
            //horizontal cut
            std::uniform_real_distribution<double> cut_pos(0.01, (output_rectangles[rectangle_number].GetWidth() - 0.01));
            std::vector<Rectangle> temp(2);
            temp = output_rectangles[rectangle_number].cut_horizontally(cut_pos(gen));
            output_rectangles[rectangle_number] = temp[0];
            counter++;
            output_rectangles.resize(counter + 1);
            output_rectangles[counter] = temp[1];
        } else{
            //vertical cut
            std::uniform_real_distribution<double> cut_pos(0.01, output_rectangles[rectangle_number].GetLength() - 0.01);
            std::vector<Rectangle> temp(2);
            temp = output_rectangles[rectangle_number].cut_vertically(cut_pos(gen));
            output_rectangles[rectangle_number] = temp[0];
            counter++;
            output_rectangles.resize(counter + 1);
            output_rectangles[counter] = temp[1];
        }
    }
    return output_rectangles;
}
