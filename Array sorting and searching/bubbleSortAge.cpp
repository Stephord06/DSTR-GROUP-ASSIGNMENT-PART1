#include "bubbleSortAge.hpp"
#include "../general-tools/datasets-implementation-array.hpp" 
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std::chrono;
 
arrayDataset bubbleSort(arrayDataset& arr){
    int n = arr.size;
    bool swapped;

    for(int i=0 ; i<n-1; i++){
        swapped=false;
        for(int c = 0; c < n-i-1; c++){
            if(arr.data[c].age > arr.data[c + 1].age) {
                swap(arr.data[c],arr.data[c+1]);
                swapped = true;
            }
        }
        if(swapped == false){
            break;
        }
    }

    return arr;
}