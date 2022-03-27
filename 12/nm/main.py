#!/usr/bin/env python3
from sympy import Pow, lambdify, symbols

x = symbols("x")


def tangentyze(y, a, b, eps):
    y_prime = y.diff(x)
    y_double_prime = y_prime.diff(x)

    f = lambdify(x, y)
    f_prime = lambdify(x, y_prime)
    f_double_prime = lambdify(x, y_double_prime)

    def select_boundpoint(a, b):
        if f(a) * f_double_prime(a) > 0:
            return a

        if f(b) * f_double_prime(b) > 0:
            return b

        print("Provided boundaries are not appliable")
        quit()

    def calculate_next_argument(xi):
        return xi - (f(xi) / f_prime(xi))

    current_argument = select_boundpoint(a, b)

    i = 1
    while True:
        next_argument = calculate_next_argument(current_argument)

        if abs(next_argument - current_argument) < eps:
            break

        current_argument = next_argument
        i += 1

    return (current_argument, i)


# def simply_iterate():
#     def calculate_next_argument(xi):
#         k = 2 - 1

#         return xi - (f(xi) / k)

#     i = 1
#     while True:
#         i += 1


if __name__ == "__main__":
    a = float(input("Please, enter point A value: "))
    b = float(input("Now, enter point B value: "))
    eps = float(input("Its time for EPS value to roll in: "))

    y = Pow(x, 3) - 3 * Pow(x, 2) + 6 * x - 8

    print("\nResults:", tangentyze(y, a, b, eps))
