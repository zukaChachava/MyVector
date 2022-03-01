#include <iostream>

template<typename T>
class MyVector{
private:
    T* _data = nullptr;
    std::size_t _size;
    std::size_t _capacity;
public:
    MyVector()
    {
        _size = 0;
        _capacity = 4;
        _data = new T[_capacity];
    }

private:
    void resize(){
        T* new_data = new T[_capacity * 2];
        for(int i = 0; i < _size; i++)
            new_data[i] = _data[i];
        delete[] _data;
        _data = new_data;
    }
};
