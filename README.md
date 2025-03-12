# How to check the task code

## The task
The task was requested on Google Collab, which can be found at this link: https://colab.research.google.com/drive/1aa5RoWi0g139fZ62MF_HoAHp3d_AbqHq?usp=sharing

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
### Complexity Analysis

The operations `insert` and `erase` require shifting elements within the dynamic array, impacting their efficiency.

#### **1. `insert(index, element)`**
- In the worst case (when inserting at the beginning), all elements must be shifted one position to the right.
- On average, about `n/2` elements need to be moved.
- If resizing is required, copying elements takes \(O(n)\), but this does not happen on every insertion.
- **Time Complexity: \(O(n)\) in the worst case.**

#### **2. `erase(index)`**
- In the worst case (when deleting the first element), all elements must be shifted one position to the left.
- On average, about `n/2` elements need to be moved.
- **Time Complexity: \(O(n)\) in the worst case.**

Both operations have linear worst-case efficiency due to element shifting, but they remain practical for most use cases.


## Removing duplicates
I write the function so that you can eliminate the elements that are repeated, this function is found in the vector.cc file, the function is found on line 175. I implemented a function that you can test and see the results of the function on the line 260.

#### Function
```c++
Vector<int> removeDuplicates(const Vector<int>& vector){
    Vector<int> withoutDuplicates;
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

### **Complexity Analysis**

1. **Outer Loop:**  
   - Iterates through all elements of the input vector.  
   - Runs **\(O(n)\)** times.

2. **Inner Loop:**  
   - Iterates through the `withoutDuplicates` vector to check for duplicates.  
   - In the worst case (when all elements are unique), `withoutDuplicates` contains up to **\(n\)** elements.
   - Runs **\(O(m)\)** times, where \( m \) is the number of unique elements.
   - Since \( m ≤ n \), the worst-case complexity is **\(O(n)\)**.

#### **Overall Complexity**
- The worst-case scenario occurs when all elements are unique.
- The function results in a **nested loop** structure:  
\[ O(n) \times O(n) = O(n^2) \]
- **Final Worst-Case Complexity: \(O(n^2)\)**.


## Dynamic Array Resizing Analysis
In this exercise, we are asked to write a program that pushes a large amount of random numbers into your vector implementation. Then, using python, we had to plot the increase in capacity versus size according to the 4 resize policies seen in class (capacity+1, capacity+2, capacity*1.5 and capacity*2) and perform the respective analysis in Google Colab, the data is in the file datos.dat.

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
        assert(!data.empty());
        for(int i = data.size()-1; i>=0; i--){
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
