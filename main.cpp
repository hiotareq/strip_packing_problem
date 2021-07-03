#include <iostream>
#include "plate.h"
#include "rectangle.h"

int main(){
    std::vector<Rectangle> rectangles = unconstrained_rectangles_generator(50, Rectangle(10,10));

    plate my_plate(10, rectangles.size(), rectangles);

    int Length = my_plate.GetS()/my_plate.GetWidth();

    std::vector<int> before_placed(rectangles.size(),0), current_placed(rectangles.size(), 0);
    while(my_plate.RSegment(Length, my_plate.GetWidth(), 0, 0, before_placed, current_placed, 0) != my_plate.GetS()){
        Length++;
    }

    std::cout << Length << std::endl;

    return 0;
}
