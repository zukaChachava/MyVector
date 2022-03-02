#include <iostream>

#define INCREMENT 2
#define CAPACITY 4

template<typename MyVector, typename ValueType>
class MyVectorIterator{
private:
    ValueType* _pointer;

public:
    MyVectorIterator(ValueType* pointer): _pointer(std::move(pointer)){}

    MyVectorIterator& operator++(){
        _pointer++;
        return *this;
    }

    MyVectorIterator<MyVector, ValueType> operator++(int){
        MyVectorIterator<MyVector, ValueType> myVectorIterator = *this;
        ++(*_pointer);
        return myVectorIterator;
    }

    MyVectorIterator<MyVector, ValueType>& operator--(){
        _pointer--;
        return *this;
    }

    MyVectorIterator<MyVector, ValueType> operator--(int){
        MyVectorIterator<MyVector, ValueType> myVectorIterator = *this;
        --(*_pointer);
        return myVectorIterator;
    }

    ValueType& operator[](int index){
        return *(_pointer + index);
    }

    ValueType* operator->(){
        return _pointer;
    }

    ValueType& operator*(){
        return &_pointer;
    }

    bool operator==(const MyVectorIterator<MyVector, ValueType>& other) const{
        return _pointer == other._pointer;
    }

    bool operator!=(const MyVectorIterator<MyVector, ValueType>& other) const{
        return !(*this == other);
    }
};


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
        _data = (T*)::operator new(CAPACITY * sizeof(T)); // creates space without calling constructor -> malloc
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
        InnerClear();
        _size = 0;
    }

    MyVectorIterator<MyVector, T> begin(){
        return MyVectorIterator<MyVector, T>(&_data[0]);
    }

    MyVectorIterator<MyVector, T> end(){
        return MyVectorIterator<MyVector, T>(_data + _size);
    }

private:
    void InnerClear(){
        for(int i = 0; i < _size; i++)
            _data[i].~T();
    }

    void Resize(){
        T* new_data = (T*)::operator new(_capacity * INCREMENT * sizeof(T));

        for(int i = 0; i < _size; i++)
            new_data[i] = std::move(_data[i]);

        InnerClear();

        ::operator delete(_data, _capacity * sizeof(T));
        _data = new_data;
        _capacity *= 2;
    }

public:
    ~MyVector(){
        InnerClear();
        ::operator delete(_data, _capacity * sizeof(T)); // deletes space without calling destructor
    }
};

