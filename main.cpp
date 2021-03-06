#include <iostream>
#include "vector.h"

struct ZPoint{
    int index, x, y;

    ZPoint() {
        std::cout << "Created" << std::endl;
    }

    ZPoint(int index, int x_point, int y_point): index(std::move(index)), x(std::move(x_point)), y(std::move(y_point)){
        std::cout << "Create with parameters index -> " << index << std::endl;
    }

    ZPoint(ZPoint& point){
        std::cout << "Copied" << std::endl;
        x = point.x;
        y = point.y;
        index = point.index;
    }

    void Print() const{
        std::cout << "X -> " << x << " y -> " << y << std::endl;
    }

    ZPoint& operator=(const ZPoint& point){
        std::cout << "Copy" << std::endl;
        x = point.x;
        y = point.y;
        index = point.index;
        return *this;
    }

    ZPoint& operator=(ZPoint&& point) noexcept {
        std::cout << "Move" << std::endl;
        x = point.x;
        y = point.y;
        index = point.index;
        return *this;
    }

    ~ZPoint(){
        std::cout << "Destroyed index "<< index << std::endl;
    }
};

int main() {
    MyVector<ZPoint> points;

    //Move
    for(int i = 1; i < 8; i++){
        points.EmplaceBack(i, i, i + 1);
    }

    // Copy
    std::cout << "------------" << std::endl;
    {
        ZPoint point(100, 5, 5);
        points.PushBack(point);
    }
    std::cout << "------------" << std::endl;

    for(int i = 0; i < points.Size(); i++)
        points[i].Print();

    return 0;
}
