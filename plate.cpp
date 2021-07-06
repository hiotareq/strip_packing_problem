//
// Created by hiotareq on 09.04.2021.
//
#include <iostream>
#include "plate.h"
#include <thread>
#include <algorithm>

#define PLACED 1
#define NOT_PLACED 0

plate::plate(double _width, unsigned long new_number, std::vector<Rectangle> &new_rectangles) : plate_width(_width),
                                                                                      number_of_rectangles(new_number),
                                                                                      rectangles(new_rectangles), S(0) {
    std::sort(rectangles.begin(), rectangles.end(), [](const Rectangle &a, const Rectangle &b) {
        if (a.GetArea() > b.GetArea()) return true;
        return false;
    });
    for (auto &rectangle : rectangles) S += rectangle.GetArea();
}

double plate::GetS() const {
    return S;
}

double plate::GetWidth() const {
    return plate_width;
}

double plate::RSegment(double x_block, double y_block, double value_father, double upper_father,
                       std::vector<int> &before_placed, std::vector<int> &current_placed, int index) {
    //step 1
    y_block = plate_width;
    if (x_block == 0) return 0;

    double v_max = 0, v_best = (S-0.1);
    int i = index;

    int kc = 0;

    //step 2
    while (i < number_of_rectangles) {
        //step 3
        if (before_placed[i] == PLACED) ++i;
        else {
            if (rectangles[i].GetLength() > x_block || rectangles[i].GetWidth() > y_block) {
                //step 5
                //Здесь рассматривается вставка прямоугольника с поворотом
                //step 4
                //step 4.1

                rectangles[i].Rotate();
                if(rectangles[i].GetLength() > x_block || rectangles[i].GetWidth() > y_block){
                    /*
                     *here rotation gave bad result(rectangle do not match the block), so go to the next rectangle
                     *return our rectangle to normal state and go work with next one
                     */
                    rectangles[i].Rotate();
                    ++i;
                    continue;
                }

                if (kc == 0) kc = i;

                //step 4.2
                double x_a = rectangles[i].GetLength();
                double y_a = y_block - rectangles[i].GetWidth();

                double x_b = x_block - rectangles[i].GetLength();
                double y_b = y_block;
                if(x_a < 0 || y_a < 0 || x_b < 0 || y_b < 0) {
                    std::cout << "Rectangle number is " << i << std::endl;
                    exit(-4);
                }

                double u_b = rectangles[i].GetArea() + x_a * y_a + x_b * y_b;//upper bound of the section
                double u_p = value_father + upper_father + u_b;//upper bound of whole pattern

                if (u_b < v_max || u_p < v_best) {
                    //here rotation gave bad result, so go to the next rectangle
                    //return our rectangle to normal state and go work with next one
                    rectangles[i].Rotate();
                    ++i;
                    continue;
                }
                    //step 4.3
                else {
                    before_placed[i] = PLACED;
                    std::vector<int> current_placed_a(number_of_rectangles, NOT_PLACED);
                    double value_a = RBlock(x_a, y_a, value_father + rectangles[i].GetArea(), upper_father + x_b * y_b,
                                            before_placed, current_placed_a, kc);

                    //step 4.4
                    u_b = rectangles[i].GetArea() + value_a + x_b * y_b;
                    u_p = value_father + upper_father + u_b;
                    if (u_b <= v_max || u_p <= v_best) {
                        //STEP 4.9
                        before_placed[i] = NOT_PLACED;
                        if (v_max == x_block * y_block) return v_max;
                    }

                    //STEP 4.5
                    for (auto k=(i+1); k != number_of_rectangles; ++k) {
                        if(current_placed_a[k]) before_placed[k] = PLACED;
                    }
                    std::vector<int> current_placed_b(number_of_rectangles, NOT_PLACED);
                    double value_b = RSegment(x_b, y_b, value_father + rectangles[i].GetArea() + value_a, upper_father,
                                              before_placed, current_placed_b, kc);

                    double value = rectangles[i].GetArea() + value_a + value_b;
                    if (value <= v_max) {
                        //step 4.8
                        for (auto k = (i + 1); k != number_of_rectangles; ++k) {
                            if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                        }
                    } else {//step 4.6
                        if (value <= v_max) {
                            //STEP 4.8
                            for (auto k=(i+1); k != number_of_rectangles; ++k) {
                                if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                            }
                        } else {
                            v_max = value;
                            for (auto k = 0; k != number_of_rectangles; ++k) {
                                if(current_placed_a[k] || current_placed_b[k]) current_placed[k] = PLACED;
                            }
                            current_placed[i] = PLACED;
                            if (value_father + v_max <= v_best) {
                                //STEP 4.8
                                for (auto k=(i+1); k != number_of_rectangles; ++k) {
                                    if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                                }
                            } else {
                                //STEP 4.7
                                v_best = value_father + v_max;
                                if (v_best == S) break;
                            }
                        }
                    }
                }
            } else {//step 4
                //step 4.1
                if (kc == 0) kc = i;

                //step 4.2
                double x_a = rectangles[i].GetLength();
                double y_a = y_block - rectangles[i].GetWidth();

                double x_b = x_block - rectangles[i].GetLength();
                double y_b = y_block;
                if(x_a < 0 || y_a < 0 || x_b < 0 || y_b < 0) {
                    std::cout << "Rectangle number is " << i << std::endl;
                    exit(-3);
                }

                double u_b = rectangles[i].GetArea() + x_a * y_a + x_b * y_b;//upper bound of the section
                double u_p = value_father + upper_father + u_b;//upper bound of whole pattern

                if (u_b < v_max || u_p < v_best) {
                    //step 5
                    //Здесь рассматривается вставка прямоугольника с поворотом
                    //step 4
                    //step 4.1

                    rectangles[i].Rotate();
                    if(rectangles[i].GetLength() > x_block || rectangles[i].GetWidth() > y_block){
                        /*
                         *here rotation gave bad result(rectangle do not match the block), so go to the next rectangle
                         *return our rectangle to normal state and go work with next one
                         */
                        rectangles[i].Rotate();
                        ++i;
                        continue;
                    }

                    if (kc == 0) kc = i;

                    //step 4.2
                    x_a = rectangles[i].GetLength();
                    y_a = y_block - rectangles[i].GetWidth();

                    x_b = x_block - rectangles[i].GetLength();
                    y_b = y_block;

                    u_b = rectangles[i].GetArea() + x_a * y_a + x_b * y_b;//upper bound of the section
                    u_p = value_father + upper_father + u_b;//upper bound of whole pattern

                    if (u_b < v_max || u_p < v_best) {
                        //here rotation gave bad result, so go to the next rectangle
                        //return our rectangle to normal state and go work with next one
                        rectangles[i].Rotate();
                        ++i;
                        continue;
                    }
                        //step 4.3
                    else {
                        before_placed[i] = PLACED;
                        std::vector<int> current_placed_a(number_of_rectangles, NOT_PLACED);
                        double value_a = RBlock(x_a, y_a, value_father + rectangles[i].GetArea(),
                                                upper_father + x_b * y_b,
                                                before_placed, current_placed_a, kc);

                        //step 4.4
                        u_b = rectangles[i].GetArea() + value_a + x_b * y_b;
                        u_p = value_father + upper_father + u_b;
                        if (u_b <= v_max || u_p <= v_best) {
                            //STEP 4.9
                            before_placed[i] = NOT_PLACED;
                            if (v_max == x_block * y_block) return v_max;
                        }

                        //STEP 4.5
                        for (auto k=(i+1); k != number_of_rectangles; ++k) {
                            if(current_placed_a[k]) before_placed[k] = PLACED;
                        }
                        std::vector<int> current_placed_b(number_of_rectangles, NOT_PLACED);
                        double value_b = RSegment(x_b, y_b, value_father + rectangles[i].GetArea() + value_a,
                                                  upper_father,
                                                  before_placed, current_placed_b, kc);

                        double value = rectangles[i].GetArea() + value_a + value_b;
                        if (value <= v_max) {
                            //step 4.8
                            for (auto k=(i+1); k != number_of_rectangles; ++k) {
                                if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                            }
                        } else {//step 4.6
                            if (value <= v_max) {
                                //STEP 4.8
                                for (auto k=(i+1); k != number_of_rectangles; ++k) {
                                    if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                                }
                            } else {
                                v_max = value;
                                for (auto k = 0; k != number_of_rectangles; ++k) {
                                    if(current_placed_a[k] || current_placed_b[k]) current_placed[k] = PLACED;
                                }
                                current_placed[i] = PLACED;
                                if (value_father + v_max <= v_best) {
                                    //STEP 4.8
                                    for (auto k=(i+1); k != number_of_rectangles; ++k) {
                                        if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                                    }
                                } else {
                                    //STEP 4.7
                                    v_best = value_father + v_max;
                                    if (v_best == S) break;
                                }
                            }
                        }
                    }
                }
                    //step 4.3
                else {
                    before_placed[i] = PLACED;
                    std::vector<int> current_placed_a(number_of_rectangles, NOT_PLACED);
                    double value_a = RBlock(x_a, y_a, value_father + rectangles[i].GetArea(), upper_father + x_b * y_b,
                                            before_placed, current_placed_a, kc);

                    //step 4.4
                    u_b = rectangles[i].GetArea() + value_a + x_b * y_b;
                    u_p = value_father + upper_father + u_b;
                    if (u_b <= v_max || u_p <= v_best) {
                        //STEP 4.9
                        before_placed[i] = NOT_PLACED;
                        if (v_max == x_block * y_block) return v_max;
                    }

                    //STEP 4.5
                    for (auto k=(i+1); k < number_of_rectangles; ++k) {
                        if(current_placed_a[k]) before_placed[k] = PLACED;
                    }
                    std::vector<int> current_placed_b(number_of_rectangles, NOT_PLACED);
                    double value_b = RSegment(x_b, y_b, value_father + rectangles[i].GetArea() + value_a, upper_father,
                                              before_placed, current_placed_b, kc);

                    double value = rectangles[i].GetArea() + value_a + value_b;
                    if (value <= v_max) {
                        //step 4.8
                        for (auto k=(i+1); k != number_of_rectangles; ++k) {
                            if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                        }
                    } else {//step 4.6
                        if (value <= v_max) {
                            //STEP 4.8
                            for (auto k=(i+1); k != number_of_rectangles; ++k) {
                                if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                            }
                        } else {
                            v_max = value;
                            for (auto k = 0; k != number_of_rectangles; ++k) {
                                if(current_placed_a[k] || current_placed_b[k]) current_placed[k] = PLACED;
                            }
                            current_placed[i] = PLACED;
                            if (value_father + v_max <= v_best) {
                                //STEP 4.8
                                for (auto k = (i + 1); k != number_of_rectangles; ++k) {
                                    if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                                }
                            } else {
                                //STEP 4.7
                                v_best = value_father + v_max;
                                if (v_best == S) break;
                            }
                        }
                    }
                }
            }
            ++i;
        }

    }
    return v_max;
}

unsigned long plate::GetNumberOfRectangles() const {
    return number_of_rectangles;
}

double plate::RBlock(double x_block, double y_block, double value_father, double upper_father,
                     std::vector<int> &before_placed, std::vector<int> &current_placed, int index) {
    //step 1
    if (x_block * y_block == 0) return 0;

    double v_max = 0, v_best = (S-0.1);
    int i = index;

    int kc = 0;

    //step 2
    while (i < number_of_rectangles) {
        //step 3
        if (before_placed[i] == PLACED) ++i;
        else {
            if (rectangles[i].GetLength() > x_block || rectangles[i].GetWidth() > y_block) {
                //step 5
                //Здесь рассматривается вставка прямоугольника с поворотом
                //step 4
                //step 4.1

                rectangles[i].Rotate();
                if(rectangles[i].GetLength() > x_block || rectangles[i].GetWidth() > y_block){
                    /*
                     *here rotation gave bad result(rectangle do not match the block), so go to the next rectangle
                     *return our rectangle to normal state and go work with next one
                     */
                    rectangles[i].Rotate();
                    ++i;
                    continue;
                }

                if (kc == 0) kc = i;

                //step 4.2
                double x_a = x_block - rectangles[i].GetLength();
                double y_a = y_block;

                double x_b = x_block;
                double y_b = y_block - rectangles[i].GetWidth();
                if(x_a < 0 || y_a < 0 || x_b < 0 || y_b < 0) {
                    std::cout << "Rectangle number is " << i << std::endl;
                    exit(-1);
                }

                double u_b = rectangles[i].GetArea() + x_a * y_a + x_b * y_b;//upper bound of the section
                double u_p = value_father + upper_father + u_b;//upper bound of whole pattern

                if (u_b < v_max || u_p < v_best) {
                    //here rotation gave bad result, so go to the next rectangle
                    //return our rectangle to normal state and go work with next one
                    rectangles[i].Rotate();
                    ++i;
                    continue;
                }
                    //step 4.3
                else {
                    before_placed[i] = PLACED;
                    std::vector<int> current_placed_a(number_of_rectangles, NOT_PLACED);
                    double value_a = RBlock(x_a, y_a, value_father + rectangles[i].GetArea(), upper_father + x_b * y_b,
                                            before_placed, current_placed_a, kc);

                    //step 4.4
                    u_b = rectangles[i].GetArea() + value_a + x_b * y_b;
                    u_p = value_father + upper_father + u_b;
                    if (u_b <= v_max || u_p <= v_best) {
                        //STEP 4.9
                        before_placed[i] = NOT_PLACED;
                        if (v_max == x_block * y_block) return v_max;
                    }

                    //STEP 4.5
                    for (auto k=(i+1); k != number_of_rectangles; ++k) {
                        if(current_placed_a[k]) before_placed[k] = PLACED;
                    }
                    std::vector<int> current_placed_b(number_of_rectangles, NOT_PLACED);
                    double value_b = RBlock(x_b, y_b, value_father + rectangles[i].GetArea() + value_a, upper_father,
                                            before_placed, current_placed_b, kc);

                    double value = rectangles[i].GetArea() + value_a + value_b;
                    if (value <= v_max) {
                        //step 4.8
                        for (auto k=(i+1); k != number_of_rectangles; ++k) {
                            if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                        }
                    } else {//step 4.6
                        if (value <= v_max) {
                            //STEP 4.8
                            for (auto k=(i+1); k != number_of_rectangles; ++k) {
                                if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                            }
                        } else {
                            v_max = value;
                            for (auto k = 0; k != number_of_rectangles; ++k) {
                                if(current_placed_a[k] || current_placed_b[k]) current_placed[k] = PLACED;
                            }
                            current_placed[i] = PLACED;
                            if (value_father + v_max <= v_best) {
                                //STEP 4.8
                                for (auto k=(i+1); k != number_of_rectangles; ++k) {
                                    if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                                }
                            } else {
                                //STEP 4.7
                                v_best = value_father + v_max;
                                if (v_best == S) break;
                            }
                        }
                    }
                }
            } else {//step 4
                //step 4.1
                if (kc == 0) kc = i;

                //step 4.2
                double x_a = x_block - rectangles[i].GetLength();
                double y_a = y_block;

                double x_b = x_block;
                double y_b = y_block - rectangles[i].GetWidth();
                if(x_a < 0 || y_a < 0 || x_b < 0 || y_b < 0) {
                    std::cout << "Rectangle number is " << i << std::endl;
                    exit(-2);
                }

                double u_b = rectangles[i].GetArea() + x_a * y_a + x_b * y_b;//upper bound of the section
                double u_p = value_father + upper_father + u_b;//upper bound of whole pattern

                if (u_b < v_max || u_p < v_best) {
                    //step 5
                    //Здесь рассматривается вставка прямоугольника с поворотом
                    //step 4
                    //step 4.1

                    rectangles[i].Rotate();
                    if(rectangles[i].GetLength() > x_block || rectangles[i].GetWidth() > y_block){
                        /*
                         *here rotation gave bad result(rectangle do not match the block), so go to the next rectangle
                         *return our rectangle to normal state and go work with next one
                         */
                        rectangles[i].Rotate();
                        ++i;
                        continue;
                    }

                    if (kc == 0) kc = i;

                    //step 4.2
                    x_a = x_block - rectangles[i].GetLength();
                    y_a = y_block;

                    x_b = x_block;
                    y_b = y_block - rectangles[i].GetWidth();

                    u_b = rectangles[i].GetArea() + x_a * y_a + x_b * y_b;//upper bound of the section
                    u_p = value_father + upper_father + u_b;//upper bound of whole pattern

                    if (u_b < v_max || u_p < v_best) {
                        //here rotation gave bad result, so go to the next rectangle
                        //return our rectangle to normal state and go work with next one
                        rectangles[i].Rotate();
                        ++i;
                        continue;
                    }
                        //step 4.3
                    else {
                        before_placed[i] = PLACED;
                        std::vector<int> current_placed_a(number_of_rectangles, NOT_PLACED);
                        double value_a = RBlock(x_a, y_a, value_father + rectangles[i].GetArea(),
                                                upper_father + x_b * y_b,
                                                before_placed, current_placed_a, kc);

                        //step 4.4
                        u_b = rectangles[i].GetArea() + value_a + x_b * y_b;
                        u_p = value_father + upper_father + u_b;
                        if (u_b <= v_max || u_p <= v_best) {
                            //STEP 4.9
                            before_placed[i] = NOT_PLACED;
                            if (v_max == x_block * y_block) return v_max;
                        }

                        //STEP 4.5
                        for (auto k=(i+1); k != number_of_rectangles; ++k) {
                            if(current_placed_a[k]) before_placed[k] = PLACED;
                        }
                        std::vector<int> current_placed_b(number_of_rectangles, NOT_PLACED);
                        double value_b = RBlock(x_b, y_b, value_father + rectangles[i].GetArea() + value_a,
                                                upper_father,
                                                before_placed, current_placed_b, kc);

                        double value = rectangles[i].GetArea() + value_a + value_b;
                        if (value <= v_max) {
                            //step 4.8
                            for (auto k=(i+1); k != number_of_rectangles; ++k) {
                                if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                            }
                        } else {//step 4.6
                            if (value <= v_max) {
                                //STEP 4.8
                                for (auto k=(i+1); k != number_of_rectangles; ++k) {
                                    if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                                }
                            } else {
                                v_max = value;
                                for (auto k = 0; k != number_of_rectangles; ++k) {
                                    if(current_placed_a[k] || current_placed_b[k]) current_placed[k] = PLACED;
                                }
                                current_placed[i] = PLACED;
                                if (value_father + v_max <= v_best) {
                                    //STEP 4.8
                                    for (auto k=(i+1); k != number_of_rectangles; ++k) {
                                        if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                                    }
                                } else {
                                    //STEP 4.7
                                    v_best = value_father + v_max;
                                    if (v_best == S) break;
                                }
                            }
                        }
                    }
                }
                    //step 4.3
                else {
                    before_placed[i] = PLACED;
                    std::vector<int> current_placed_a(number_of_rectangles, NOT_PLACED);
                    double value_a = RBlock(x_a, y_a, value_father + rectangles[i].GetArea(), upper_father + x_b * y_b,
                                            before_placed, current_placed_a, kc);

                    //step 4.4
                    u_b = rectangles[i].GetArea() + value_a + x_b * y_b;
                    u_p = value_father + upper_father + u_b;
                    if (u_b <= v_max || u_p <= v_best) {
                        //STEP 4.9
                        before_placed[i] = NOT_PLACED;
                        if (v_max == x_block * y_block) return v_max;
                    }

                    //STEP 4.5
                    for (auto k=(i+1); k < number_of_rectangles; ++k) {
                        if(current_placed_a[k]) before_placed[k] = PLACED;
                    }
                    std::vector<int> current_placed_b(number_of_rectangles, NOT_PLACED);
                    double value_b = RBlock(x_b, y_b, value_father + rectangles[i].GetArea() + value_a, upper_father,
                                            before_placed, current_placed_b, kc);

                    double value = rectangles[i].GetArea() + value_a + value_b;
                    if (value <= v_max) {
                        //step 4.8
                        for (auto k=(i+1); k != number_of_rectangles; ++k) {
                            if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                        }
                    } else {//step 4.6
                        if (value <= v_max) {
                            //STEP 4.8
                            for (auto k=(i+1); k != number_of_rectangles; ++k) {
                                if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                            }
                        } else {
                            v_max = value;
                            for (auto k = 0; k != number_of_rectangles; ++k) {
                                if(current_placed_a[k] || current_placed_b[k]) current_placed[k] = PLACED;
                            }
                            current_placed[i] = PLACED;
                            if (value_father + v_max <= v_best) {
                                //STEP 4.8
                                for (auto k=(i+1); k != number_of_rectangles; ++k) {
                                    if(current_placed_a[k]) before_placed[k]=NOT_PLACED;
                                }
                            } else {
                                //STEP 4.7
                                v_best = value_father + v_max;
                                if (v_best == S) break;
                            }
                        }
                    }
                }
            }
            ++i;
        }

    }
    return v_max;
}
