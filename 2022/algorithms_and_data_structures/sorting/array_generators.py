from math import log, sin
from statistics import mode

from sorting.utils import random_real_array


def gen_1(n: int):
    """
    Задано одномірний масив дійсних чисел.
    Виключити з нього моду (елемент, який повторюється найчастіше).
    Отриманий масив посортувати в порядку зростання.
    """
    arr = random_real_array(n)
    mode_val = mode(arr)
    return list(filter(lambda x: x != mode_val, arr))


def gen_2(n: int):
    """
    Задано одномірний масив дійсних чисел.
    До від’ємних елементів масиву застосувати функцію sin(x).
    Отриманий масив посортувати в порядку спадання.
    """
    arr = random_real_array(n)
    return list(map(lambda x: sin(x) if x < 0 else x, arr))


def gen_3(n: int):
    """
    Задано двовимірний масив дійсних чисел.
    Замінити мінімальні елементи кожного рядка на ln(x).
    Впорядкувати (переставити) стовпці масиву в порядку зростання
    їх перших елементів.
    """
    arr_2d = [random_real_array(n) for _ in range(n)]
    arr = list(map(lambda x: log(abs(min(x))), arr_2d))
    return arr


def gen_4(n: int):
    """
    Задано одномірний масив дійсних чисел.
    Впорядкувати елементи, розташовані після максимального елемента
    в порядку спадання.
    """
    arr = random_real_array(n)
    max_el_idx = arr.index(max(arr))

    return arr[max_el_idx:]


def gen_5(n: int):
    """
    Задано одномірний масив дійсних чисел.
    Впорядкувати елементи, розташовані між першим і останнім
    від'ємним елементом по зростанню.
    """
    arr = random_real_array(n)
    return arr[1:-1]


def gen_6(n: int):
    """
    З двох одновимірних масивів цілих чисел сформувати новий,
    який включає всі парні числа з першого і непарні з другого масиву.
    Отриманий масив посортувати в порядку зростання.
    """
    arr = []

    map(lambda x: arr.append(x) if x % 2 == 0 else None, random_real_array(n))
    map(lambda x: arr.append(x) if x % 2 != 0 else None, random_real_array(n))

    return arr
