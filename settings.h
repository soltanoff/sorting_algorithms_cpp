#ifndef SETTINGS_H
#define SETTINGS_H

#include <vector>
#include <iostream>
#include <functional>

typedef std::vector<std::int32_t> Array;
typedef std::vector<std::function<Array(Array)>> FuncVector;

Array sortByBubble(Array array);

Array sortByCounting(Array array);

Array sortByExtraction(Array array);

Array sortByHeap(Array array);

Array sortByInclusion(Array array);

Array sortByMerge(Array array);

Array sortByQuick(Array array);


#endif /* SETTINGS_H */
