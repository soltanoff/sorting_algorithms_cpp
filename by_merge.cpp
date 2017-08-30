#include "settings.h"


Array sortByMerge(Array array) {
    /*!
     * Сортировка слиянием.
     * Суть: метод сортирует массив последовательным слиянием пар уже отсортированных подмассивов.
     * Сортируемый массив разбивается на две части примерно одинакового размера, затем каждая из получившихся частей
     * сортируется отдельно, например — тем же самым алгоритмом. Два упорядоченных массива половинного размера
     * соединяются в один и тем самым достигается результат.
     *
     * Максимальная временная сложность: О(n*log n)
     * Средняя временная сложность: О(n*log n)
     * Минимальная временная сложность: О(n*log n)
     *
     * Пространственная сложность: О(n)
     *
     * (#) Алгоритм устойчивой сортировки.
     * @param mass: исходный массив
     * @return array: упорядоченный исходный массив
     */
    if (array.size() > 1) {
        std::int32_t mid = (std::int32_t) array.size() / 2;

        Array leftHalf(array.begin(), array.begin() + mid);
        Array rightHalf(array.begin() + mid, array.end());

        leftHalf = sortByMerge(leftHalf);
        rightHalf = sortByMerge(rightHalf);

        std::int32_t i(0), j(0), k(0);

        while (i < leftHalf.size() && j < rightHalf.size()) {
            if (leftHalf[i] < rightHalf[j]) {
                array[k] = leftHalf[i];
                ++i;
            }
            else {
                array[k] = rightHalf[j];
                ++j;
            }
            ++k;
        }
        while (i < leftHalf.size()) {
            array[k] = leftHalf[i];
            ++i;
            ++k;
        }
        while (j < rightHalf.size()) {
            array[k] = rightHalf[j];
            ++j;
            ++k;
        }
    }
    return array;
}
