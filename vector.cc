#include<iostream>
#include<cassert>

using namespace std;

template<typename T>

class Vector {
    //Values
    private:
    T* storage_;
    unsigned int size_;
    unsigned int capacity_;
    //Constructors
    public:
    Vector(){
        capacity_ = 5;
        storage_ = new T[capacity_];
        size_ = 0;
    }
    Vector(unsigned int c, T element){
        capacity_ = c;
        storage_ = new T[capacity_];
        size_ = c;
        for(int i = 0; i < c; i++){
            storage_[i] = element;
        }
    }
    //Methods
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
    //Private resize()
    private:
    void resize(){
        unsigned int capacity2_ = capacity_ * 3 / 2;
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
        for (int i = size_; i > 0; i--) {
            storage_[i] = storage_[i - 1];
        }
        storage_[0] = element;
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

    bool empty() const { return size_ == 0 ; }

    void print(){
        for(unsigned int i = 0; i<size_; i++){
            cout << storage_[i]  << " " ;
        }
        cout << endl;
    }
};

int main(){
    Vector<int> x(10,0);
    cout << "Size of x: " << x.size() << endl;
    cout << "values of x: " ;
    x.print();
    x.at(5) = 100;
    cout << "position using at: " << x.at(5) << endl;
    cout << "position using []: " << x[5] << endl;
    x.print();
    x.push_back(10);
    x.push_front(50);
    cout << "use push_front and push_back" << endl;
    x.print();
    x.pop_front();
    x.pop_back();
    cout << "use pop_front and pop_back" << endl;
    x.print();
    cout << x.empty() << endl;
    return 0;
}