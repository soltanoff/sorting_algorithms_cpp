#include "settings.h"


void _heapify(Array &array, std::int32_t end, std::int32_t i) {
    std::int32_t l = 2 * i + 1;
    std::int32_t r = 2 * (i + 1);
    std::int32_t max = i;

    if (l < end && array[i] < array[l])
        max = l;
    if (r < end && array[max] < array[r])
        max = r;
    if (max != i) {
        std::swap(array[i], array[max]);
        _heapify(array, end, max);
    }
}


Array sortByHeap(Array array) {
    /*!
     * Пирамидальная сортировка.
     * Суть: Сортировка пирамидой использует бинарное сортирующее дерево. Выстраиваем элементы массива в виде сортирующего
     * дерева, затем будем удалять элементы из корня по одному за раз и перестраивать дерево. То есть на первом шаге
     * обмениваем Array[1] и Array[n], преобразовываем Array[1], Array[2], … , Array[n-1] в сортирующее дерево.
     * После чего переставляем Array[1] и Array[n-1], преобразовываем Array[1], Array[2], … , Array[n-2] в сортирующее
     * дерево. Процесс продолжается до тех пор, пока в сортирующем дереве не останется один элемент. Тогда Array[1],
     * Array[2], … , Array[n] — упорядоченная последовательность.
     *
     * Максимальная временная сложность: О(n*log n)
     * Средняя временная сложность: О(n*log n)
     * Минимальная временная сложность: О(n*log n)
     *
     * Пространственная сложность: О(1)
     *
     * (#) Алгоритм НЕ устойчивой сортировки.
     * @param mass: исходный массив
     * @return array: упорядоченный исходный массив
     */
    std::int32_t end = (std::int32_t) array.size();
    std::int32_t start = end / 2 - 1;

    for (auto i = start; i >= 0; --i) {
        _heapify(array, end, i);
    }

    for (auto i = end - 1; i > 0; --i) {
        std::swap(array[i], array[0]);
        _heapify(array, i, 0);
    }
    return array;
}
