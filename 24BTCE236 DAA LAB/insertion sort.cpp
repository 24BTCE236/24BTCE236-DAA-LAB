#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        // Store the current element to be inserted
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0...i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // Insert the key element into its correct position
        arr[j + 1] = key;
    }
}

int main() {
    std::vector<int> data = {12, 11, 13, 5, 6};
    std::cout << "Original array: ";
    for (int x : data) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Perform insertion sort
    insertionSort(data);

    std::cout << "Sorted array: ";
    for (int x : data) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}
