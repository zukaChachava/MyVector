#include <iostream>

#define INCREMENT 2
#define CAPACITY 4

template<typename T>
class MyVector{
private:
    T* _data = nullptr;
    std::size_t _size;
    std::size_t _capacity;

public:
    MyVector(){
        _size = 0;
        _capacity = CAPACITY;
        _data = new T[CAPACITY];
    }

    size_t Size() const{
        return _size;
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

    void PushBack(const T& value){
        if(_size == _capacity)
            Resize();
        _data[_size++] = value;
    }

    void PushBack(T&& value){
        if(_size == _capacity)
            Resize();
        _data[_size++] = std::move(value);
    }

    template<typename... Args>
    T& EmplaceBack(Args&&... args){
        if(_size == _capacity)
            Resize();

        //_data[_size] = T(std::forward<Args>(args)...); // need move
        new(&_data[_size]) T(std::forward<Args>(args)...); // does not need move
        return _data[_size++];
    }

    void PopBack(){
        if(_size == 0)
            return;
        _size--;
        _data[_size].~T();
    }

    void Clear(){
        delete[] _data;
        _size = 0;
        _data = new T[4];
    }

private:
    void Resize(){
        T* new_data = new T[_capacity * INCREMENT];
        for(int i = 0; i < _size; i++)
            new_data[i] = std::move(_data[i]);
        delete[] _data;
        _data = new_data;
        _capacity *= 2;
    }

public:
    ~MyVector(){
        delete[] _data;
    }
};
