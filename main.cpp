#include <iostream>
#include "vector.h"

struct ZPoint{
    int x, y;

    ZPoint() {}

    ZPoint(int x_point, int y_point): x(x_point), y(y_point){

    }

    ZPoint(ZPoint& point){
        std::cout << "Copied" << std::endl;
    }

    void Print() const{
        std::cout << "X -> " << x << " y -> " << y << std::endl;
    }

    ZPoint& operator=(const ZPoint& point){
        std::cout << "Copy" << std::endl;
        x = point.x;
        y = point.y;
        return *this;
    }

    ZPoint& operator=(ZPoint&& point){
        std::cout << "Move" << std::endl;
        x = point.x;
        y = point.y;
        return *this;
    }

    ~ZPoint(){
        std::cout << "Destroyed" << std::endl;
    }
};

int main() {
    MyVector<ZPoint> points;
    for(int i = 0; i < 10; i++)
        points.PushBack(ZPoint(i, i + 1));

    for(int i = 0; i < points.Size(); i++)
        points[i].Print();

    return 0;
}
