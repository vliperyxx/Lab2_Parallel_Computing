#include <iostream>
#include <chrono>
#include <cstdlib>    
#include <thread>   
#include <mutex> 
#include <ctime>     
#include <climits>   

const int threads_num = 8;

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

    static void threadFuncSynchronized(const int arr[], int size, int threadId) {
        for (int i = threadId; i < size; i += threads_num) {
            if (arr[i] > 20) {
                m.lock();
                synchronizedCount++;

                if (arr[i] > synchronizedMaxValue) {
                    synchronizedMaxValue = arr[i];
                }
                m.unlock();
            }
        }
    }

    static void findCountAndMaxSynchronized(const int arr[], int size, int& count, int& maxValue) {
        synchronizedCount = 0;
        synchronizedMaxValue = INT_MIN;
        std::thread threads[threads_num];

        for (int t = 0; t < threads_num; t++) {
            threads[t] = std::thread(threadFuncSynchronized, arr, size, t);
        }

        for (int t = 0; t < threads_num; t++) {
            threads[t].join();
        }

        count = synchronizedCount;
        maxValue = synchronizedMaxValue;
    }

    static void printArray(const int arr[], int size) {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n\n";
    }

private:
    static int synchronizedCount;
    static int synchronizedMaxValue;
    static std::mutex m;
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

    int count, maxValue;

    auto startSingleThread = std::chrono::high_resolution_clock::now();
    ArrayOperations::findCountAndMaxGreaterThan20(array, size, count, maxValue);
    auto endSingleThread = std::chrono::high_resolution_clock::now();

    double durationSingleThread = std::chrono::duration<double, std::milli>(endSingleThread - startSingleThread).count();

    std::cout << "\nSingle-thread execution time: " << durationSingleThread << " ms\n";
    std::cout << "Count of elements > 20: " << count << "\n";
    std::cout << "Maximum element > 20: " << maxValue << "\n";

    delete[] array;
    return 0;
}