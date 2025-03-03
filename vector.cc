#include<iostream>
#include<cassert>

using namespace std;

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
    
    // Método para obtener el tamaño actual del vector
    unsigned int size() const{
        return size_;
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
        if (size_ > 0) { size_--; return; }
    }
    
    // Elimina el primer elemento del vector y desplaza los demás
    void pop_front(){
        if (size_ > 0) {
        for (unsigned int i = 0; i < size_ - 1; i++) {
            storage_[i] = storage_[i + 1];
        }
            size_--;
        }
    }
    
    // Verifica si el vector está vacío
    bool empty() const { return size_ == 0; }
    
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

// Función principal para probar la clase Vector
int main(){
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
    return 0;
}
