#include <iostream>
#include <chrono>
#include <cstdlib>    
#include <thread>   
#include <mutex> 

class ArrayOperations {
public:
    static void fillArray(int arr[], int size) {
        srand(time(nullptr));

        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 1001; 
        }
    }
};
