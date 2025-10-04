"""
For testing out code

"""
from math import factorial
from itertools import permutations

def cost_func(x, y, z):
    return (x + y) * z

source = [1, 2, 3]
target = list(permutations(source))
print(target)

print(max(target, key=cost_func))
