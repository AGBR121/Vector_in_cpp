#include<iostream>
#include<cassert>
#include <fstream>  
#include <cstdlib> 
#include <ctime>

#include "Vector.h"

using namespace std;

void Data(){
    ofstream archivo("datos.dat", ios::app);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }
    //archivo << "resize*1,5" << endl;
    //archivo << "resize*2,0" << endl;
    //archivo << "resize+1" << endl;
    archivo << "resize+2" << endl;
    archivo << "size capacity" << endl;
    Vector<int> x;
    for(int i = 1; i <= 1000000; i++){
        x.push_back(rand() % 1000);
        if(i % 1000 == 0){
            archivo << x.size() << " " << x.capacity() << endl;
        }
    }

    archivo.close();
}

int main(){
    //Data();
    return 0;

}