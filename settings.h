#ifndef SETTINGS_H
#define SETTINGS_H

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

typedef std::vector<std::int32_t> Array;
typedef std::vector<Array> Matrix;
typedef std::pair<std::string, std::function<Array(Array)>> FuncPair;
typedef std::vector<FuncPair> FuncVector;

Array sortByBubble(Array array);

Array sortByCounting(Array array);

Array sortByExtraction(Array array);

Array sortByHeap(Array array);

Array sortByInclusion(Array array);

Array sortByMerge(Array array);

Array sortByQuick(Array array);

Array sortByRadixLsd(Array array);

Array sortByTimsort(Array array);

#endif /* SETTINGS_H */
