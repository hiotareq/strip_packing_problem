#include <iostream>
#include "plate.h"
#include <chrono>

int main(){
    std::vector<Rectangle> rectangles = unconstrained_rectangles_generator(8, Rectangle(10,10));

    plate my_plate(10, rectangles.size(), rectangles);

    int Length = my_plate.GetS()/my_plate.GetWidth();

    std::vector<int> before_placed(rectangles.size(),0), current_placed(rectangles.size(), 0);

    auto start = std::chrono::high_resolution_clock::now();
    while(my_plate.RSegment(Length, my_plate.GetWidth(), 0, 0, before_placed, current_placed, 0) != my_plate.GetS()){
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = end - start;
        if(duration > std::chrono::seconds(10)){
            std::cout << "Ran out of time" << std::endl;
            return 0;
        }
        Length++;
    }

    std::cout << Length << std::endl;

    return 0;
}
