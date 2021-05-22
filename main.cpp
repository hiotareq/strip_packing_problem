#include <iostream>
#include "plate.h"
#include "rectangle.h"

int main(){
    Rectangle rectangle_1(2,3), rectangle_2(1,1);
    std::vector<Rectangle> rectangles{rectangle_1, rectangle_2};
    plate my_plate(3, rectangles.size(), rectangles);
    std::vector<int> before_placed(rectangles.size(),0), current_placed(rectangles.size(), 0);
    std::cout << my_plate.RSegment(3, 3, 0, 0, before_placed,current_placed, 0);
    return 0;
}
