# How to check the task

## Insert and Erase methods
In the vector.cc file, you can find the insert and erase methods, exactly on lines 142 and 155. I implemented a function that you can test and see the results of the methods on the vector class on the line 228.

#### Method Insert
```c++
    void insert(unsigned int index, const T& element){
        assert(index <= size_); 

        if(size_ == capacity_){ resize() ; } 

        for(unsigned int i = size_; i > index; i--){
            storage_[i] = storage_[i-1];
        }
        
        storage_[index] = element;
        size_++;
    }
```
#### Method Erase
```c++
void erase (unsigned int index){
        assert(index<size_); 
        if(index == 0){ pop_front(); return; }
        if(index == size_-1){pop_back(); return;}
        for(unsigned int i = index; i<size_-1; i++){
            storage_[i] = storage_[i+1]; 
        }
        size_--; 
    }
```

## Removing duplicates
I write the function so that you can eliminate the elements that are repeated, this function is found in the vector.cc file, the function is found on line 175. I implemented a function that you can test and see the results of the function on the line 260.

#### Function
```c++
template<typename T>
Vector<T> removeDuplicates(const Vector<T>& vector){
    Vector<T> withoutDuplicates;
    for(unsigned int i = 0; i < vector.size(); i++){
        bool duplicate = false;
        for(unsigned int j = 0; j < withoutDuplicates.size(); j++){
            if(withoutDuplicates[j] == vector[i]){
                duplicate = true;
                break;
            }
        }
        if(!duplicate){
            withoutDuplicates.push_back(vector[i]);
        }
    }
    return withoutDuplicates; 
}
```
## Dynamic Array Resizing Analysis
In this exercise, we are asked to write a program that pushes a large amount of random numbers into your vector implementation. Then, using python, we had to plot the increase in capacity versus size according to the 4 resize policies seen in class (capacity+1, capacity+2, capacity*1.5 and capacity*2) and perform the respective analysis in Google Colab, the data is in the file datos.dat. This analysis can be found at the following link https://colab.research.google.com/drive/1aa5RoWi0g139fZ62MF_HoAHp3d_AbqHq?usp=sharing.

#### Function in python to graph
```python
import matplotlib.pyplot as plt

file_path = "/content/datos.dat"

with open(file_path, "r", encoding="utf-8") as file:
    content = file.readlines()

resizes = {}
current_resize = None

for line in content:
    line = line.strip()
    if line.startswith("resize"):  
        current_resize = line
        resizes[current_resize] = {"size": [], "capacity": []}
    elif line and current_resize and not line.startswith("size capacity"):
        size, capacity = map(int, line.split())
        resizes[current_resize]["size"].append(size)
        resizes[current_resize]["capacity"].append(capacity)

fig, axes = plt.subplots(2, 2, figsize=(12, 10))
axes = axes.flatten()

for i, (resize_type, data) in enumerate(resizes.items()):
    axes[i].plot(data["size"], data["capacity"], marker='o', linestyle='-')
    axes[i].set_title(resize_type)
    axes[i].set_xlabel("Size")
    axes[i].set_ylabel("Capacity")

plt.tight_layout()
plt.show()
```


## Implementing a Stack Using a Vector
In this exercise, we are asked to implement the stack structure, this structure that allows storing and retrieving data, being the access mode to its elements of the LIFO type (Last In, First Out) using vectors, this structure is found in the stack.cc file and in the main is the way to test it.
#### Class Stack
```c++
template<typename T>
class Stack{
    private:
    Vector<T> data;

    public:
    Stack() {}

    void push(const T& element) { data.push_back(element); }

    void pop() { assert(!data.empty()); data.pop_back(); }
    //top or peek
    const T& top() const { assert(!data.empty()); return data.at(data.size()-1); }
 
    T& top() { assert(!data.empty()); return data.at(data.size()-1); }
 
    bool empty() const { return data.empty(); }

    unsigned int size() const { return data.size(); }

    void print() { 
        for(unsigned int i = data.size()-1; i>=0; i--){
            cout << data.at(i) << " ";
        }
        cout << endl;
    }
};
```

## Merge sorted vectors
In this exercise, we must create a function that allows merging 2 sorted vectors, this function is located in the vector.cc file and is on line 194. I implemented a function that you can test and see the results of the function on the line 281.

#### Function

```c++
template<typename T>
Vector<T> mergeSortedVectors(Vector<T>& vector1, Vector<T>& vector2){
    if(!vector1.size()){
        return vector2;
    }
    if(!vector2.size()){
        return vector1;
    }
    if(!vector1.size() && !vector2.size()){
        return Vector<T>();
    }
    Vector<T> mergedVector;
    unsigned int i = 0;
    unsigned int j = 0;
    while(i < vector1.size() && j < vector2.size()){
        if(vector1[i] < vector2[j]){
            mergedVector.push_back(vector1[i]);
            i++;
        }else{
            mergedVector.push_back(vector2[j]);
            j++;
        }
    }
    while(i < vector1.size()){
        mergedVector.push_back(vector1[i]);
        i++;
    }
    while(j < vector2.size()){
        mergedVector.push_back(vector2[j]);
        j++;
    }
    return mergedVector;
}
```
