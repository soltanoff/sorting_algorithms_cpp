#include "settings.h"


std::int32_t _getDigit(std::int32_t num, std::int32_t base, std::int32_t digit_num);

Matrix _makeBlanks(std::int32_t size);

Matrix _split(const Array &a_list, std::int32_t base, std::int32_t digit_num);

Array _merge(const Matrix &a_list);

std::int32_t _maxAbs(const Array &a_list);

Matrix _splitBySign(const Array &a_list);


Array sortByRadixLsd(Array array) {  // , std::int32_t base) {
    /*!
     * Поразрядная сортировка least significant digit (LSD).
     * Суть: Числа сортируются по разрядам, сначала сортируются младшие разряды, затем старшие. При LSD сортировке
     * олучается следующий порядок: короткие ключи идут раньше длинных, ключи одного размера сортируются по алфавиту, это
     * совпадает с нормальным представлением чисел: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10.
     *
     * Максимальная временная сложность: О(nk)
     * Средняя временная сложность: О(nk)
     * Минимальная временная сложность: О(nk)
     *
     * Пространственная сложность: О(n)
     *
     * (#) Алгоритм устойчивой сортировки.
     * @param mass: исходный массив
     * @return array: упорядоченный исходный массив
     */

    const std::int32_t base = 10;
    // столько же проходов, сколько цифр в самом длинном числе
    std::int32_t passes = std::int32_t(round(log(_maxAbs(array)) / log(base)) + 1);
    Array newList = array;

    for (auto i = 0; i < passes; i++) {
        newList = _merge(_split(newList, base, i));
    }
    return _merge(_splitBySign(newList));
}

std::int32_t _getDigit(std::int32_t num, std::int32_t base, std::int32_t digit_num) {
    // берем выбранную цифру
    return (std::int32_t) ((unsigned long long int) std::pow((std::uint64_t)(num / base), digit_num) % base);
}


Matrix _makeBlanks(std::int32_t size) {
    // создаем список пустых списков, чтобы провести разделение по цифрам
    return Matrix((unsigned long) size);
}


Matrix _split(const Array &a_list, std::int32_t base, std::int32_t digit_num) {
    Matrix buckets = _makeBlanks(base);

    for (auto &num: a_list) {
        // добавить число в список, выбранный цифрой
        buckets[_getDigit(num, base, digit_num)].push_back(num);
    }
    return buckets;
}


Array _merge(const Matrix &a_list) {
    Array newList;
    for (auto &sublist: a_list) {
        newList.insert(newList.end(), sublist.begin(), sublist.end());
    }
    return newList;
}


std::int32_t _maxAbs(const Array &a_list) {
    return *std::max_element(
            a_list.begin(),
            a_list.end(),
            [](std::int32_t a, std::int32_t b) { return abs(a) <= abs(b); }
    );
}


Matrix _splitBySign(const Array &a_list) {
    Matrix buckets(2);

    for (auto &num: a_list) {
        if (num < 0)
            buckets[0].push_back(num);
        else
            buckets[1].push_back(num);
    }
    return buckets;
}
