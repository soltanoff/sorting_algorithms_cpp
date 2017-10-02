#include <ctime>
#include <iomanip>
#include <ratio>
#include <chrono>
#include "settings.h"


FuncVector algorithms{
        FuncPair("sortByBubble", sortByBubble),
        FuncPair("sortByCounting", sortByCounting),
        FuncPair("sortByExtraction", sortByExtraction),
        FuncPair("sortByHeap", sortByHeap),
        FuncPair("sortByInclusion", sortByInclusion),
        FuncPair("sortByMerge", sortByMerge),
        FuncPair("sortByQuick", sortByQuick),
        // TODO: need test: FuncPair("sortByRadixLsd", sortByRadixLsd),
        FuncPair("sortByTimsort", sortByTimsort)
};

void start_test(const Array &array, const FuncVector &algs = algorithms);


// TODO: change a timer logic
int main() {
    Array array;

    for (std::uint32_t i = 0; i < ARRAY_SIZE; i++)
        array.push_back(rand() % (2 * ARRAY_SIZE));

    // Array a = sortByRadixLsd(array);
    std::cout << ">>> RANDOM:" << std::endl;
    start_test(array);

    return 0;
}

void start_test(const Array &array, const FuncVector &algs) {
    std::cout << "-= Start the test: array size of " << array.size() << " elements =-";

    for (auto &f: algs) {
        std::clock_t c_start = std::clock();
        auto t_start = std::chrono::high_resolution_clock::now();

        Array a = f.second(array);

        auto t_end = std::chrono::high_resolution_clock::now();
        std::clock_t c_end = std::clock();

        std::cout << std::endl << "Function: " << f.first << std::endl
                  << std::fixed << std::setprecision(4) << "CPU time used: "
                  << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
                  << "Wall clock time passed: "
                  << std::chrono::duration<double, std::milli>(t_end - t_start).count()
                  << " ms\n"
                  << "################################";
    }
}