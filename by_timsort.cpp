#include "settings.h"


struct segment {
    std::int32_t beg; // индекс первого элемента
    std::int32_t len; // длина интервала
    segment() {}

    segment(std::int32_t b, std::int32_t l) : beg(b), len(l) {}
};

typedef std::vector<segment> Segment;


const std::int32_t dx = 1, dy = 2, dz = 3;

inline std::int32_t get_min_size(std::int32_t n);

void selection_sort(Array &mas, std::int32_t beg, std::int32_t last);

void merge(Array &mas, Segment &seg, bool isXY, Array &tmp);

void try_merge(Array &mas, Segment &seg, Array &tmp, bool is_merge = false);


Array sortByTimsort(Array array) {
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

    std::int32_t n = (std::int32_t) array.size();
    Array tmp((unsigned long) n);
    std::int32_t min_size = get_min_size(n);
    std::int32_t size;

    Segment seg;
    seg.reserve((unsigned long) ((n - 1) / min_size + 1));

    for (std::int32_t i = 0; i < n; i += min_size) {
        size = std::min(min_size, n - i);
        selection_sort(array, i, i + size);
        seg.push_back(segment(i, size));
        try_merge(array, seg, tmp);
    }
    while (seg.size() != 1) {
        try_merge(array, seg, tmp, true);
    }

    return array;
}


// ответ должен быть в диапазоне (32,64]
inline std::int32_t get_min_size(std::int32_t n) {
    std::int32_t r = 0;
    while (n >= 64) {
        n >>= 1;
        r |= n & 1;
    }
    return n + r;
}

// Да простит меня Тим Петерсон, но вместо сортировки вставками
// я использую сортировку выбором
void selection_sort(Array &mas, std::int32_t beg, std::int32_t last) {
    for (std::int32_t i = beg; i < last; ++i) {
        std::int32_t min_pos = i;
        for (std::int32_t j = i + 1; j < last; ++j) {
            if (mas[j] < mas[min_pos])
                min_pos = j;
        }
        std::swap(mas[i], mas[min_pos]);
    }
}

void merge(Array &mas, Segment &seg, bool isXY, Array &tmp) {
    segment f = seg[seg.size() - dy];
    segment s = isXY ? seg[seg.size() - dx] : seg[seg.size() - dz];
    if (f.beg > s.beg) std::swap(f, s);
    std::int32_t posF = 0, posS = s.beg, pos = f.beg - 1;
    std::int32_t lstF = f.len, lstS = s.beg + s.len;
    copy(mas.begin() + f.beg + posF, mas.begin() + f.beg + lstF, tmp.begin());
    std::int32_t fAmount = 0, sAmount = 0;
    while (posF < lstF && posS < lstS) {
        if (tmp[posF] < mas[posS]) {
            mas[++pos] = tmp[posF++];
            ++fAmount;
            sAmount = 0;
            if (fAmount == 7) {
                Array::iterator it = upper_bound(tmp.begin() + posF, tmp.begin() + lstF, mas[posS]);
                copy(tmp.begin() + posF, it, mas.begin() + pos + 1);
                pos += it - (tmp.begin() + posF);
                posF += it - (tmp.begin() + posF);
            }
        } else {
            mas[++pos] = mas[posS++];
            fAmount = 0;
            ++sAmount;
            if (sAmount == 7) {
                Array::iterator it = upper_bound(mas.begin() + posS, mas.begin() + lstS, tmp[posF]);
                copy(mas.begin() + posS, it, mas.begin() + pos + 1);
                pos += it - (mas.begin() + posS);
                posS += it - (mas.begin() + posS);
            }
        }
    }
    copy(tmp.begin() + posF, tmp.begin() + lstF, mas.begin() + pos + 1);
}

void try_merge(Array &mas, Segment &seg, Array &tmp, bool is_merge) {
    while (seg.size() > 1) {
        std::int32_t x = seg[seg.size() - dx].len;
        std::int32_t y = seg.size() < 2 ? 0 : seg[seg.size() - dy].len;
        std::int32_t z = seg.size() < 3 ? 0 : seg[seg.size() - dz].len;
        if (seg.size() >= 3 && z <= x + y) {
            if (z < x) {
                merge(mas, seg, false, tmp);
                seg[seg.size() - dz].len += seg[seg.size() - dy].len;
                seg[seg.size() - dy] = seg[seg.size() - dx];

                seg.pop_back();
                break;
            } else {
                merge(mas, seg, true, tmp);
                seg[seg.size() - dy].len += seg[seg.size() - dx].len;

                seg.pop_back();
                break;
            }
        } else if (is_merge || y <= x) {
            merge(mas, seg, true, tmp);
            seg[seg.size() - dy].len += seg[seg.size() - dx].len;
            seg.pop_back();

            break;
        } else
            break;
    }
}
