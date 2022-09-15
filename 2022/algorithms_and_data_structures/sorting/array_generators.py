from math import sin
from statistics import mode

from sorting.utils import random_continious_array


def gen_1(n: int):
    """removes all mode occurances"""
    arr = random_continious_array(n)
    mode_val = mode(arr)
    return list(filter(lambda x: x != mode_val, arr))


def gen_2(n: int):
    """apply sin(x) for every negative value"""
    arr = random_continious_array(n)
    return list(map(lambda x: sin(x) if x < 0 else x, arr))


def gen_3(n: int):
    raise NotImplementedError


def gen_4(n: int):
    raise NotImplementedError


def gen_5(n: int):
    raise NotImplementedError


def gen_6(n: int):
    raise NotImplementedError
