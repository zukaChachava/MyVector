#include <iostream>

#define INCREMENT 2

template<typename T>
class MyVector{
private:
    T* _data = nullptr;
    std::size_t _size;
    std::size_t _capacity;
public:
    MyVector(){
        _size = 0;
        _capacity = 4;
        _data = new T[_capacity];
    }

    size_t Size() const{
        return _size;
    }

    void PushBack(const T& value){
        if(_size == _capacity)
            Resize();
        _data[_size] = value;
        _size++;
    }

    const T& operator[](size_t index) const{
        std::cout << "Const" << std::endl;
        if(index >= _size)
            throw std::invalid_argument("Out of scope exception");
        return _data[index];
    }

    T& operator[](size_t index){
        if(index >= _size)
            throw std::invalid_argument("Out of scope exception");
        return _data[index];
    }

private:
    void Resize(){
        T* new_data = new T[_capacity * INCREMENT];
        for(int i = 0; i < _size; i++)
            new_data[i] = _data[i];
        delete[] _data;
        _data = new_data;
        _capacity *= 2;
    }

public:
    ~MyVector(){
        delete[] _data;
    }
};
