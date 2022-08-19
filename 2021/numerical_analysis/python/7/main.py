import math

from common.newton_iteration import NewtonIterationMethod
from common.simple_iteration import SimpleIterationMethod

# cos(x) + y = 1.2
# 2x - sin(y - 0.5) = 2

if __name__ == "__main__":
    eqsys = [
        lambda x: 1.2 - math.cos(x), lambda y: (2 + math.sin(y - 0.5)) / 2
    ]

    for method in [SimpleIterationMethod, NewtonIterationMethod]:
        method(eqsys).compile()
