#include <iostream>
#include "plate.h"
#include "rectangle.h"

int main(){
    Rectangle rectangle_1(2,3), rectangle_2(1,1);
    std::vector<Rectangle> rectangles{rectangle_1, rectangle_2};

    plate my_plate(3, rectangles.size(), rectangles);

    int Length = my_plate.GetS()/my_plate.GetWidth(), LengthMax = Length * 10;

    std::vector<int> before_placed(rectangles.size(),0), current_placed(rectangles.size(), 0);
    while(my_plate.RSegment(Length, my_plate.GetWidth(), 0, 0, before_placed, current_placed, 0) != my_plate.GetS()){
        Length++;
    }
    std::cout << Length << std::endl;
    return 0;
}
