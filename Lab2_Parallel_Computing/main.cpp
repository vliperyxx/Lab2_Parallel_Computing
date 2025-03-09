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

    static void findCountAndMaxGreaterThan20(const int arr[], int size, int& count, int& maxValue) {
        count = 0;
        maxValue = INT_MIN;
        for (int i = 0; i < size; i++) {
            if (arr[i] > 20) {
                count++;
                if (arr[i] > maxValue) {
                    maxValue = arr[i];
                }
            }
        }
    }

    static void printArray(const int arr[], int size) {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n\n";
    }
};

int main() {
    int size;
    std::cout << "Enter size of array: ";
    std::cin >> size;

    int* array = new int[size];

    ArrayOperations::fillArray(array, size);

    if (size <= 100) {
        std::cout << "Array: ";
        ArrayOperations::printArray(array, size);
    }

    delete[] array;
    return 0;
}