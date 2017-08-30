#include <ctime>
#include <iomanip>
#include <ratio>
#include <chrono>
#include "settings.h"


FuncVector algorithms{
        sortByBubble,
        sortByCounting,
        sortByExtraction,
        sortByHeap,
        sortByInclusion,
        sortByMerge,
        sortByQuick
};


// TODO: need to test all sorting functions
// TODO: change a timer logic
int main() {
    Array array{1, 2, 6, 8, 99, 1, 4, 6, 7};

    for (auto f: algorithms) {
        // FIXME: wtf?! Change this std::clock
        std::clock_t c_start = std::clock();
        auto t_start = std::chrono::high_resolution_clock::now();

        f(array);

        auto t_end = std::chrono::high_resolution_clock::now();
        std::clock_t c_end = std::clock();

        std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
                  << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
                  << "Wall clock time passed: "
                  << std::chrono::duration<double, std::milli>(t_end - t_start).count()
                  << " ms\n\n";
    }

    return 0;
}