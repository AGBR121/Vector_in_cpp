#include<iostream>
#include<cassert>

template<typename T>
class Vector {
    private:
    T* storage_;
    unsigned int size_;
    unsigned int capacity_;
    //Constructors
    public:
    Vector(){
        capacity_ = 5;
        T* storage_ = new T[capacity_];
        size_ = 0;
    }
    Vector(unsigned int c, T element){
        capacity_ = c;
        T* storage_ = new T[capacity_];
        size_ = c;
        for(int i = 0; i < c; i++){
            storage_[i] = element;
        }
    }
    unsigned int size() const{
        return size_;
    }
    T& at(unsigned int pos){
        assert(pos < size_ && pos>=0);
        return storage_[pos];
    }
    const T& at(unsigned int pos) const {
        assert(pos < size_ && pos>=0);
        return storage_[pos];
    }
    const T& operator[](unsigned int pos) const{
        return storage_[pos];
    }
    private:
    void resize(){
        unsigned int capacity2_ = capacity_ * 1.5;
        T* storage2_ = new T[capacity2_];
        for(unsigned int i=0; i<size_; i++){
            storage2_[i] = storage_[i];
        }
        delete[] storage_;
        storage_ = storage2_;
        capacity_ = capacity2_;
    }
    public:
    void push_back(const T& element){
        if (size_ == capacity_) {
            resize();
        }
        storage_[size_] = element;
        size_++;
    }

    void push_front(const T& element){
        if (size_ == capacity_) {
            resize();
        }
        T* storage2_ = new T[capacity_];
        for(unsigned int i=0; i<size_; i++){
            storage2_[i+1] = storage_[i];
        }
        storage2_[0] = element;
        delete[] storage_;
        storage_ = storage2_;
        size_++;
    }

    void pop_back(){
        size_--;
    }
    
    void pop_front(){
        if (size_ == 0) {
            return;
        }
        for (unsigned int i = 0; i < size_ - 1; i++) {
            storage_[i] = storage_[i + 1];
        }
        size_--;
    }

    void print(){
        for(unsinged int i = 0; i<size_ i++){
            cout << " " << storage_[i];
        }
        cout << endl;
    }
};