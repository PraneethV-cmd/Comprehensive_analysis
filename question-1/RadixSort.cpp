#include <iostream>
#include <sys/resource.h>
#include <list>
#include <unordered_map>
#include <climits>
#include <chrono>

int comparisons = 0;
int swaps = 0;
int basic_operations = 0;

void radixSort(std::list<int>& lst, int place) {
    std::unordered_map<int, std::list<int> > umap;

    // Distribute the elements into buckets based on the current place value
    for (auto i : lst) {
        int x = (i / place) % 10;
        umap[x].push_back(i);
        ++basic_operations; // Basic operation: placing into bucket
    }

    // Clear the original list and collect elements back from the buckets
    lst.clear();
    ++basic_operations; // Basic operation: clearing the list
    for (int i = 0; i < 10; ++i) {
        if (umap.find(i) != umap.end()) {
            for (auto j : umap[i]) {
                lst.push_back(j);
                ++basic_operations; // Basic operation: pushing back into the list
            }
        }
    }
}

void counting_sort(std::list<int>& lst) {
    int max = INT_MIN;

    // Find the maximum value to determine the number of digits
    for (auto i : lst) {
        ++basic_operations; // Basic operation: iterating through the list
        ++comparisons;
        if (i > max) {
            max = i;
            ++basic_operations; // Basic operation: updating max
        }
    }

    // Perform Radix Sort starting from the least significant digit
    for (int place = 1; max / place > 0; place *= 10) {
        radixSort(lst, place);
    }
}

int main() {
    struct rusage usage;

    int size;
    std::cin >> size;
    std::list<int> lst;

    // Input elements into the list
    for (int i = 0; i < size; i++) {
        int x;
        std::cin >> x;
        lst.push_back(x);
        ++basic_operations; // Basic operation: pushing input into the list
    }

    auto start = std::chrono::high_resolution_clock::now();
    // Perform the counting sort (which is implemented using radix sort)
    counting_sort(lst);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Elapsed time: " << elapsed.count()/1000 << " ms" << std::endl;

    getrusage(RUSAGE_SELF, &usage);
    std::cout << "Memory usage: " << usage.ru_maxrss / 1024.0 << " kB" << std::endl;

    // Output the sorted list
    for (auto i : lst) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Output statistics
    std::cout << "Comparisons: " << comparisons << std::endl;
    std::cout << "Swaps: " << swaps << std::endl;
    std::cout << "Basic operations: " << basic_operations << std::endl;

    return 0;
}


