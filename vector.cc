#include<iostream>
#include<cassert>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Definimos una plantilla de clase para un vector dinámico
template<typename T>
class Vector {
    private:
    T* storage_; // Puntero a la memoria dinámica donde se almacenan los elementos
    unsigned int size_; // Cantidad de elementos almacenados en el vector
    unsigned int capacity_; // Capacidad máxima antes de necesitar redimensionar

    public:
    // Constructor por defecto: inicializa con una capacidad de 5 y tamaño 0
    Vector(){
        capacity_ = 5;
        storage_ = new T[capacity_];
        size_ = 0;
    }
    
    // Constructor con parámetros: inicializa con capacidad y valores dados
    Vector(unsigned int c, T element){
        capacity_ = c;
        storage_ = new T[capacity_];
        size_ = c;
        for(int i = 0; i < c; i++){
            storage_[i] = element;
        }
    }

    Vector(initializer_list<T> list){
        capacity_ = list.size();  // La capacidad es el número de elementos en la lista
        storage_ = new T[capacity_];
        size_ = list.size();
        unsigned int i = 0;
        for (const T& elem : list) {
            storage_[i++] = elem;  // Copiamos cada elemento al array
        }
    }
    
    // Método para obtener el tamaño actual del vector
    unsigned int size() const{
        return size_;
    }

    //Método para obtener la capacidad atual del vector
    unsigned int capacity() const{
        return capacity_;
    }
    
    // Método para acceder a un elemento con verificación de límites
    T& at(unsigned int pos){
        assert(pos < size_ && pos>=0); // Asegura que la posición sea válida
        return storage_[pos];
    }
    
    // Método `at` para acceder a un elemento en una versión constante del objeto
    const T& at(unsigned int pos) const {
        assert(pos < size_ && pos>=0);
        return storage_[pos];
    }
    
    // Sobrecarga del operador [] para acceso rápido sin verificación
    const T& operator[](unsigned int pos) const{
        return storage_[pos];
    }
    
    private:
    // Método privado para redimensionar el almacenamiento cuando es necesario
    void resize(){
        unsigned int capacity2_ = capacity_ * 3 / 2; // Aumenta la capacidad en 1.5 veces
        T* storage2_ = new T[capacity2_]; // Nuevo arreglo de mayor tamaño
        
        // Copia los elementos al nuevo arreglo
        for(unsigned int i=0; i<size_; i++){
            storage2_[i] = storage_[i];
        }
        
        delete[] storage_; // Libera la memoria del viejo arreglo
        storage_ = storage2_; // Apunta al nuevo arreglo
        capacity_ = capacity2_; // Actualiza la capacidad
    }
    
    public:
    // Agrega un elemento al final del vector
    void push_back(const T& element){
        if (size_ == capacity_) {
            resize();
        }
        storage_[size_] = element;
        size_++;
    }
    
    // Agrega un elemento al inicio del vector
    void push_front(const T& element){
        if (size_ == capacity_) {
            resize();
        }
        
        // Desplaza los elementos hacia la derecha
        for (unsigned int i = size_; i > 0; i--) {
            storage_[i] = storage_[i - 1];
        }
        storage_[0] = element;
        size_++;
    }
    
    // Elimina el último elemento del vector
    void pop_back(){
        assert(size_ > 0);
        size_--; return; 
    }
    
    // Elimina el primer elemento del vector y desplaza los demás
    void pop_front(){
        assert(size_ > 0);
        for (unsigned int i = 0; i < size_ - 1; i++) {
            storage_[i] = storage_[i + 1];
        }
            size_--;
    }
    
    // Verifica si el vector está vacío
    bool empty() const { return size_ == 0; }

    //Devuelve lo que le sobra de espacio de memoria
    unsigned int waste(){ return capacity_ - size_;}

    //Borra la memoria que no utiliza
    void shrink_to_fit(){
        T* storage2_ = new T[size_];
        for(unsigned int i = 0; i < size_; i++){
            storage2_[i] = storage_[i];
        }
        delete[] storage_;
        capacity_ = size_;
        storage_ = storage2_;
    }
    
    //insert mete un elemento en una posicion index
    void insert(unsigned int index, const T& element){
        assert(index <= size_); //asegurarse que este en el rango

        if(size_ == capacity_){ resize() ; } //ajustar tamano si no alcanza

        for(unsigned int i = size_; i > index; i--){
            storage_[i] = storage_[i-1]; // Mueve los elementos hacia la derecha
        }
        
        storage_[index] = element; //agregar el elemento al vector
        size_++; //aumentar el tamaño
    }
    //erase elimina un elemento del vector
    void erase (unsigned int index){
        assert(index<size_); //asegurarse que este en el rango
        if(index == 0){ pop_front(); return; }
        if(index == size_-1){pop_back(); return;}
        for(unsigned int i = index; i<size_-1; i++){
            storage_[i] = storage_[i+1]; //mover los elementos a 1 posicion a la izquierda
        }
        size_--; //disminuir el tamaño
    }

    // Imprime los elementos del vector
    void print(){
        for(unsigned int i = 0; i<size_; i++){
            cout << storage_[i]  << " " ;
        }
        cout << endl;
    }
};

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

// Función que recibe dos vectores ordenados y los mezcla en un nuevo vector ordenado
template<typename T>
Vector<T> mergeSortedVectors(Vector<T>& vector1, Vector<T>& vector2){
    if(!vector1.size()){ //Si el vector 1 esta vacio, devolvemos el 2
        return vector2;
    }
    if(!vector2.size()){
        return vector1; //Si el vector 2 esta vacío, devolvemos el 1
    }
    if(!vector1.size() && !vector2.size()){
        return Vector<T>(); //Si ambos estan vacios, devolvemos un vector vacío
    }
    Vector<T> mergedVector; //Vector donde se guardaran los elementos ordenados
    unsigned int i = 0; //Indice para recorrer el vector 1
    unsigned int j = 0;//Indice para recorrer el vector 2

    while(i < vector1.size() && j < vector2.size()){ //Insertar los elementos en orden
        if(vector1[i] < vector2[j]){
            mergedVector.push_back(vector1[i]);
            i++;
        }else{
            mergedVector.push_back(vector2[j]);
            j++;
        }
    }
    while(i < vector1.size()){ //Verificar si quedaron elementos en el vector 1
        mergedVector.push_back(vector1[i]);
        i++;
    }
    while(j < vector2.size()){//Verificar si quedaron elementos en el vector 2
        mergedVector.push_back(vector2[j]);
        j++;
    }
    return mergedVector; //Devolver el vector ordenado
}

// Función de prueba para probar la clase Vector y sus metodos
void Prueba(){
    Vector<int> x(10,0); // Crea un vector de 10 elementos inicializados en 0
    cout << "Size of x: " << x.size() << endl;
    cout << "values of x: " ;
    x.print();
    
    x.at(5) = 100; // Modifica el valor en la posición 5
    cout << "position using at: " << x.at(5) << endl;
    cout << "position using []: " << x[5] << endl;
    x.print();
    
    x.push_back(10); // Agrega un 10 al final
    x.push_front(50); // Agrega un 50 al inicio
    cout << "use push_front and push_back" << endl;
    x.print();
    
    x.pop_front(); // Elimina el primer elemento
    x.pop_back(); // Elimina el último elemento
    cout << "use pop_front and pop_back" << endl;
    x.print();
    x.insert(8, 2); //Agrega un 2 en la posicion 8
    cout << "insert(8,2)"<<endl;
    x.print();
    cout << "erase(8)" << endl; //elimina lo que haya en la posicion 8
    x.erase(8);
    x.print();
    cout << x.empty() << endl; // Verifica si el vector está vacío
    return;
}


//Funcion para probar la funcion removeDuplicates
void RemovingDuplicates(){
    Vector<int> numbers = {1, 2, 2, 3, 4, 4, 5};
    Vector<int> uniqueNumbers = removeDuplicates(numbers);

    uniqueNumbers.print(); // Expected: {1, 2, 3, 4, 5}

    Vector<int> numbers2 = {1,1,1,1,1,1};
    Vector<int> uniqueNumbers2 = removeDuplicates(numbers2);
    uniqueNumbers2.print(); // Expected: {1}

    Vector<int> numbers3 = {};
    Vector<int> uniqueNumbers3 = removeDuplicates(numbers3);
    uniqueNumbers3.print(); // Expected: {}

    Vector<int> numbers4 = {1};
    Vector<int> uniqueNumbers4 = removeDuplicates(numbers4);
    uniqueNumbers4.print(); // Expected: {1}
}


//Funcion para probar la funcion mergeSortedVectors
void MergeSortVectorsPrueba(){
    Vector<int> vector1 = {1, 3, 5};
    Vector<int> vector2 = {2, 4, 6};
    Vector<int> mergedVector = mergeSortedVectors(vector1, vector2);

    mergedVector.print(); // Expected: {1, 2, 3, 4, 5, 6}

    Vector<int> vector3 = {1, 2, 3};
    Vector<int> vector4 = {};
    Vector<int> mergedVector2 = mergeSortedVectors(vector3, vector4);
    mergedVector2.print(); // Expected: {1, 2, 3}

    Vector<int> vector5 = {};
    Vector<int> vector6 = {4,5,6};
    Vector<int> mergedVector3 = mergeSortedVectors(vector5, vector6);
    mergedVector3.print(); // Expected: {4, 5, 6}

    Vector<int> vector7 = {1,1,1,1};
    Vector<int> vector8 = {1,1,1,1};
    Vector<int> mergedVector4 = mergeSortedVectors(vector7, vector8);
    mergedVector4.print(); // Expected: {1,1,1,1,1,1,1,1}
}

void AnalizeTimeInsertAndErase(){
    for( int k = 0; k<3; k++){
        switch (k)
        {
        case 0:
            cout << "Insert and erase 100000 elements in the middle three times" << endl ;
            break;
        case 1:
            cout << "Insert and erase 100000 elements at the beginning  three times" << endl ;
            break;
        case 2:
            cout << "Insert and erase 100000 elements at the end  three times" << endl ;
            break;
        default:
            break;
        }
            
        for(unsigned int j = 1; j<= 3; j++){

            Vector<int> numbers = {1, 2, 3, 4, 5};
            unsigned int place = 0 ;
            if(k==0){
                unsigned int place = numbers.size() /2 ;
            }else if(k==2){
                unsigned int place = numbers.size() -1 ;
            }

            auto inicio = high_resolution_clock::now();
            for(unsigned int i=0; i<100000;i++){
                
                numbers.insert(place, i);
            }
            auto fin = high_resolution_clock::now();
            auto duracion = duration_cast<milliseconds>(fin - inicio);
            cout << "Time on " << j << " insertion: " << duracion.count() << " ms" << endl;

            auto inicio2 = high_resolution_clock::now();

            for (unsigned int i = 0; i < 100000; i++) {
                if (numbers.empty()) break;

                unsigned int place = 0;
                if (k == 0) {
                    place = numbers.size() / 2;
                } else if (k == 2) {
                    place = numbers.size() - 1;
                }

                numbers.erase(place);
            }

            auto fin2 = high_resolution_clock::now();
            auto duracion2 = duration_cast<milliseconds>(fin2 - inicio2);
            cout << "Time on " << j << " erase: " << duracion2.count() << " ms" << endl;
        }
        cout << endl;
    }
}

void AnalizeTimeRemoveDuplicates() {
    for (unsigned int i = 1; i <= 3; i++) {
        Vector<int> numbers;
        
        switch (i) {
            case 1: 
                cout << "Case 1: No duplicates" << endl;
                for (unsigned int j = 0; j < 100000; j++) {
                    numbers.push_back(j);
                }
                break;
                
            case 2: 
                cout << "Case 2: Some duplicates" << endl;
                for (unsigned int j = 0; j < 50000; j++) {
                    numbers.push_back(j);
                    numbers.push_back(j);
                }
                break;

            case 3: 
                cout << "Case 3: All elements are the same" << endl;
                for (unsigned int j = 0; j < 100000; j++) {
                    numbers.push_back(1);
                }
                break;
        }

        auto inicio = high_resolution_clock::now();
        Vector<int> newNumbers = removeDuplicates(numbers);
        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<milliseconds>(fin - inicio);

        cout << "Time for case " << i << ": " << duracion.count() << " ms" << endl;
    }
}


int main(){
    //Prueba();
    //RemovingDuplicates();
    //MergeSortVectorsPrueba();
    //AnalizeTimeInsertAndErase();
    //AnalizeTimeRemoveDuplicates();
    return 0;
}
