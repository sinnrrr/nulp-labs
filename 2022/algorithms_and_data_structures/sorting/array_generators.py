from math import log, sin
from statistics import mode

from sorting.utils import random_real_array


def gen_1(n: int):
    """removes all mode occurances"""
    arr = random_real_array(n)
    mode_val = mode(arr)
    return list(filter(lambda x: x != mode_val, arr))


def gen_2(n: int):
    """apply sin(x) for every negative value"""
    arr = random_real_array(n)
    return list(map(lambda x: sin(x) if x < 0 else x, arr))


def gen_3(n: int):
    arr_2d = [random_real_array(n) for _ in range(n)]
    arr = list(map(lambda x: log(abs(min(x))), arr_2d))
    return arr


def gen_4(n: int):
    raise NotImplementedError


def gen_5(n: int):
    raise NotImplementedError


def gen_6(n: int):
    raise NotImplementedError
