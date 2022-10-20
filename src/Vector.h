#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::random_access_iterator_tag
#include <cstddef> // size_t
#include <stdexcept> // std::range_error
#include <array>
#include <iostream> 
using std::cout, std::endl; 

template <class T>
class Vector {
public:
    class iterator;
private:
    T* array; 
    size_t _capacity, _size;

    // You may want to write a function that grows the vector
    void grow() { 

        if (_capacity == 0) {
            _capacity = 1; 
            array = new T[1];
        }
        else {
            size_t new_capacity = 2*_capacity; // double the size

            T* new_array = new T[new_capacity]; // make bigger array 
            for (size_t i = 0; i < _size; i++) {
                new_array[i] = std::move(this->array[i]);
            }
            // copy contents over 
            //new_array = std::move(this->array);
            _capacity = new_capacity;
            delete[] array; // remove old contents -- prevent memory leaks 

            this->array = new_array;
        }
        
    }  

public:
    Vector() noexcept { 
        this->array = nullptr;
        this->_size = 0; 
        _capacity = 0; 
    }
    Vector(size_t count, const T& value) { 
        this->_capacity = count;
        this->_size = count;
        this->array = new T[_capacity];
        for (size_t i = 0; i < count; i++){
            array[i] = value;
        } 

    }
    explicit Vector(size_t count) { 
        this->_capacity = count;
        this->_size = count;
        this->array = new T[_capacity]{};
    }
    Vector(const Vector& other) { 
        this->array = new T[other.size()];
        this->_size = other.size();
        this->_capacity = other.capacity(); 

        for (size_t i = 0; i < _size; i++) {
            array[i] = other[i]; 
        } 
    }
    Vector(Vector&& other) noexcept { 
        this->array = std::move(other.array);
        this->_capacity = other.capacity();
        this->_size = other.size();
        other.array = nullptr; 
        other._size = 0; 
        other._capacity = 0; 
    }

    ~Vector() {
        delete [] array;
    }


    Vector& operator=(const Vector& other) { 
        if (&other == this)
            return *this; 

        T* temp = new T[other.size()];
        for (size_t i = 0; i < other.size(); i++) {
            temp[i] = other.at(i); 
        }

        delete [] array;
        this->_size = other.size();
        this->_capacity = other.capacity(); 
        array = temp; 

        return *this; 

    }
    Vector& operator=(Vector&& other) noexcept { 
        
        if (&other == this) // seems right? 
            return *this; 

        _size = other.size();
        _capacity = other.capacity(); // check for self assignment!
        delete [] array; 
        array = std::move(other.array);
        
        other.array = nullptr; 
        other._size = 0;
        other._capacity = 0;

        return *this; 
    }

    iterator begin() noexcept { 
        return iterator(array);
    }
    iterator end() noexcept {

        return iterator(array+_size); // bc end of the array 
    }

    [[nodiscard]] bool empty() const noexcept { return _size == 0; }
    size_t size() const noexcept { return _size; }
    size_t capacity() const noexcept { return _capacity; }

    T& at(size_t pos) {

        
        if (_size == 0 || pos < 0 || pos >= _size) {
            throw std::out_of_range("Out of range");
        }   
        else {
            //std::cout << "DEBUG: In at 1 func | pos: " << pos << ", _size: " << _size << ", at pos: " << array[pos] << std::endl;
            return array[pos]; 
        }
            
    }
    const T& at(size_t pos) const {     
        
        if (_size == 0 || pos < 0 || pos >= _size) {
            throw std::out_of_range("Out of range");
        }
        else {
            //std::cout << "DEBUG: In at 2 func | pos: " << pos << ", _size: " << _size << ", at pos: " << array[pos] << " " << std::endl;
            return array[pos]; 
        }
    }

    T& operator[](size_t pos) { return this->at(pos); }
    const T& operator[](size_t pos) const { return this->at(pos); }
    T& front() { return array[0]; }
    const T& front() const { return array[0]; } // std::array::back() use this if no work 

    T& back() { 

        return array[_size-1];

    }
    const T& back() const { 
        return array[_size-1];
    }

    void push_back(const T& value) { 
        if (this->_size == this->_capacity)
            this->grow();
        
        this->array[_size] = value; 
        _size++; 
        
    }
    void push_back(T&& value) { 
        // const T val = static_cast<const T> (value); 
        if (this->_size == this->_capacity)
            this->grow();

        this->array[_size] = std::move(value); 
        _size++;
    }
    void pop_back() { 
        if (_size == 0) return; // throw an error? 
        _size--; 
    }

    iterator insert(iterator pos, const T& value) { 

        
        ptrdiff_t ind = pos - this->begin(); 


        if (_size == _capacity) {
            grow(); 
            pos = iterator(array+ind);  // reset iterator pos after grow 
        }

        iterator next = end(); 
        iterator curr = end()-1; 

        while (next != pos) {// size = 4, cap = 5; pos = 1 ?  
            *next = std::move(*curr); // last element at
            next--;
            curr--; 
        }

        // insert @ pos
        *pos = value; 

        _size++;
        return pos;
    }

    
    iterator insert(iterator pos, T&& value) {  

        ptrdiff_t ind = pos - this->begin(); 


        if (_size == _capacity) {
            grow(); 
            pos = iterator(array+ind);  // to reset after grow since it messes up iterators 
        }

        iterator next = end(); 
        iterator curr = end()-1; 

        while (next != pos) {// size = 4, cap = 5; pos = 1 ?  
            *next = std::move(*curr); // last element at
            next--;
            curr--; 
        }

        // insert @ pos
        *pos = std::move(value); // same as previous insert but the value is moved with the func

        _size++;
        return pos;
    }

    //  iterator beg(this->begin());
    //     int i = 0; 
    //     while (beg != this->end()) {// size = 4, cap = 5; pos = 1 ?  
    //         cout << i << " " << *beg << ", "; 
    //         beg++; 
    //     }
    

    iterator insert(iterator pos, size_t count, const T& value) {  
        
        //cout << "begin1" << endl; 
        if (count == 0) {
            return pos; 
        }

        //cout << "begin" << endl; 
        ptrdiff_t insert_ind = pos - this->begin(); // index of insertion 

        // get array to right size 
        while((_size + count) > _capacity) { 
           // cout << "before the grow function" << endl; 
            grow(); 
        }
        pos = iterator(array+insert_ind);

        iterator next = this->begin() + _size + count; // move all down a few 
        iterator curr = this->begin() + _size; 

        while (curr != (pos-1)) {
            // cout << "before the move elements over" << endl; 
            *next = *curr; // std move
            next--;
            curr--; 
        }
        
        for(size_t i = 0; i < count; i++) { // insert value count times 
            // cout << "before the insert value part" << endl; 
            *(pos + i) = value; 
        }

        cout << "done" << endl;
        
        _size += count; 
        pos = iterator(this->begin()+insert_ind);
        return (pos); 
    }

    // for(ptrdiff_t i = _size -1; i >= insert_ind; --i) {
        //     array[i+count] = std::move(array[i]); 
        // }

        // for(ptrdiff_t i = count -1; i >= 0; --i) {
        //     array[i+insert_ind] = std::move(value); 
        // }

    
    iterator erase(iterator pos) { 
        
        iterator next(pos+1); 
        iterator curr(pos); 
    
        while (next != this->end()) {// size = 4, cap = 5; pos = 1 ?  
            *curr = *next; // last element at
            next++;
            curr++; 
        }

        _size--;
 
        return pos;
    }
    iterator erase(iterator first, iterator last) { 
        
        // [4,5,6,8,3]
        // [4,*,6,*,3]

        if (first > last) {
            throw std::out_of_range("First is after last");
        }

        size_t num_erase = last - first; 

        // if last = end 
        if (last == this->end())
        {
            _size -= num_erase; 
        }

        // if last != end 
        else {
            iterator curr(first); 
            iterator next(last); 

            while (next != this->end()) {
                *curr = *next; 
                next++;
                curr++; 
            }

            _size -= num_erase;
        }

        

        return first;
    }

    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
    private:
        // Add your own data members here
        pointer ptr;
        // HINT: For random_access_iterator, the data member is a pointer 99.9% of the time
    public:
        iterator() : ptr(nullptr) { }
        iterator(T* x) : ptr(x) { }
        iterator(iterator& iter) {
            this->ptr = iter.ptr; 
        }
        // Add any constructors that you may need

        // This assignment operator is done for you, please do not add more
        iterator& operator=(const iterator&) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept { return *ptr; }
        [[nodiscard]] pointer operator->() const noexcept { return this->ptr; }

        // Prefix Increment: ++a
        iterator& operator++() noexcept { 
            ++ptr; 
            return *this; 
        }
        // Postfix Increment: a++
        iterator operator++(int) noexcept { 
            iterator tmp(*this);  
            ++(*this);
            return tmp; 
        }
        // Prefix Decrement: --a
        iterator& operator--() noexcept { 
            --ptr; 
            return *this; 
        }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept { 
            iterator tmp(*this);  
            --(*this);
            return tmp; 
        }

        iterator& operator+=(difference_type offset) noexcept { 
            this->ptr = this->ptr + offset; 
            return *this; 

        }
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept {  
            return iterator(this->ptr + offset); // saying move the pointer over by this amount 
        }
        
        iterator& operator-=(difference_type offset) noexcept { 
            this->ptr = this->ptr - offset; 
            return *this; 
        }
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept { 
            return iterator(this->ptr - offset); 
        }


        [[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept { return this->ptr - rhs.ptr; }

        [[nodiscard]] reference operator[](difference_type offset) const noexcept { 
            return *(ptr + offset); // dereference and get the value 
        }

        [[nodiscard]] bool operator==(const iterator& rhs) const noexcept { 
            return this->ptr == rhs.ptr; 
        }
        [[nodiscard]] bool operator!=(const iterator& rhs) const noexcept { 
            return this->ptr != rhs.ptr;  
        }
        [[nodiscard]] bool operator<(const iterator& rhs) const noexcept { return this->ptr < rhs.ptr; }
        [[nodiscard]] bool operator>(const iterator& rhs) const noexcept { return this->ptr > rhs.ptr;}
        [[nodiscard]] bool operator<=(const iterator& rhs) const noexcept { return !(this->ptr > rhs.ptr);}
        [[nodiscard]] bool operator>=(const iterator& rhs) const noexcept { return !(this->ptr < rhs.ptr); }
    };


    void clear() noexcept { 
        _size = 0;
    }
};

template <class T>
[[nodiscard]] typename Vector<T>::iterator operator+(typename Vector<T>::iterator::difference_type offset, typename Vector<T>::iterator iterator) noexcept { return iterator+offset; }
#endif

// friend of class = able to access private members 