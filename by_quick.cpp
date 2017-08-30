#include "settings.h"
#include <ctime>


Array sortByQuick(Array array) {
    /*!
     * Быстрая сортировка Хоара.
     * Суть: Разделение массива на две части производится следующим образом. Устанавливаем один курсор на левую границу
     * массива, а второй – на правую границу. Затем осуществляем перемещение курсоров навстречу друг другу до тех пор,
     * пока они не пересекутся. При перемещении курсоров сравниваем значения текущих элементов со «средним». Находим левый
     * текущий элемент, больший «среднего», и правый текущий элемент, меньший «среднего» (т. е. элементы, которые
     * находятся «не на своем месте»). Осуществляем обмен этих элементов.
     *
     * Максимальная временная сложность: О(n^2)
     * Средняя временная сложность: О(n*log n)
     * Минимальная временная сложность: О(n*log n)
     *
     * Пространственная сложность: О(n)
     *
     * (#) Алгоритм НЕ устойчивой сортировки.
     * @param mass: исходный массив
     * @return array: упорядоченный исходный массив
     */
    if (array.size() <= 1) {
        return array;
    }
    else {
        std::srand((unsigned)array.size());
        std::int32_t q = array[rand() % array.size()];

        Array L;
        Array M;
        Array R;

        for (auto elem: array) {
            if (elem < q)
                L.push_back(elem);
            else if (elem > q)
                R.push_back(elem);
            else
                M.push_back(elem);
        }

        Array resultL = sortByQuick(L);
        Array resultR = sortByQuick(R);

        resultL.reserve(M.size() + resultR.size());
        resultL.insert(resultL.end(), M.begin(), M.end());
        resultL.insert(resultL.end(), resultR.begin(), resultR.end());

        return resultL;
    }
}
